/*
 * TemperatureCollector.c
 *
 *  Created on: 2 gru 2021
 *      Author: Filip
 */

#include "TemperatureCollector.h"

#include "../../Drivers/Sensors/TemperatureSensor_MCP9808.h"
#include "../../Drivers/Sensors/TemperatureSensor_MCP9803.h"
#include "Application.h"
#include "DataHandler.h"
#include "HandlesAssigner.h"
#include "ModuleInterconnect.h"
#include "../Drivers/BSP/BSP.h"
#include "../Communication/DataFormat.h"

#define dTimeoutMaxWait		(10)
#define dSensorResetTime	(80)

typedef enum TemperatureCollectorState_t
{
	TempCollect_EntryState,
	TempCollect_Initialized,
	TempCollect_TemperatureReadRequest,
	TempCollect_ProcessData,
	TempCollect_ArmNewReading,
	TempCollect_Waiting,
	TempCollect_Error
}TemperatureCollectorState_t;

typedef struct kTempCollect_Data_t
{
	uint8_t u8DeviceCount;
	bool bEnabledFlag;
	bool bScheduleMeasurement;
	TemperatureCollectorState_t eState;
	bool bReadFinished[2];
	bool bStateReady[2];
	float fConvertedTemperature[2];
	uint16_t u16ArrayASensorIndex;
	uint16_t u16ArrayBSensorIndex;
	uint32_t u32MeasurementCounter;
	uint8_t u8TimeoutCounter;
	bool bErrorOnArray[2];
	uint16_t u16ErrorWaitingCounter;
	bool bResetRequest;
	I2C_HandleTypeDef *hTranscieverA;
	I2C_HandleTypeDef *hTranscieverB;

}kTempCollect_Data_t;

static void TempCollect_FillRemainingReadingsWithError();

kTempCollect_Data_t kTemperatureData =
{
	.bEnabledFlag = false,
	.eState = TempCollect_EntryState,
};

void TempCollect_Operate()
{
	switch(kTemperatureData.eState)
	{
	case(TempCollect_EntryState):
		AssertError(eAppError_TempCollectUninitialized); // Incorrect entry - before initialization
		break;
	case(TempCollect_Initialized):
		if(kTemperatureData.bScheduleMeasurement)
		{
			kTemperatureData.eState = TempCollect_TemperatureReadRequest;
			kTemperatureData.u16ArrayASensorIndex = 0;
			kTemperatureData.u16ArrayBSensorIndex = 0;
			kTemperatureData.bReadFinished[0] = false;
			kTemperatureData.bReadFinished[1] = false;
			kTemperatureData.u8TimeoutCounter = 0;
		}
		break;
	case(TempCollect_TemperatureReadRequest):
		kTemperatureData.bScheduleMeasurement = false;
		if(kTemperatureData.u16ArrayASensorIndex < Sensor_I2CA_DeviceCount)
		{
			/*
			 * By placing "ready" flag clearing here this app will not get stuck
			 * if the sensor number on each array branch would be not equal
			 */
			kTemperatureData.bStateReady[0] = false;
			kaSensorArrayDataA[kTemperatureData.u16ArrayASensorIndex].fcnReadTemperature(&kaSensorArrayDataA[kTemperatureData.u16ArrayASensorIndex]);
		}
		if(kTemperatureData.u16ArrayBSensorIndex < Sensor_I2CB_DeviceCount)
		{
			kTemperatureData.bStateReady[1] = false;
			kaSensorArrayDataB[kTemperatureData.u16ArrayBSensorIndex].fcnReadTemperature(&kaSensorArrayDataB[kTemperatureData.u16ArrayBSensorIndex]);
		}
		kTemperatureData.eState = TempCollect_Waiting;
		break;
	case(TempCollect_Waiting):
		if(kTemperatureData.bStateReady[0] && kTemperatureData.bStateReady[1])
		{
			kTemperatureData.eState = TempCollect_ProcessData;
			kTemperatureData.u8TimeoutCounter = 0;
		}
		else
		{
			//todo: add handling of the acknowledge failed/other error in the I2C interrupt
			kTemperatureData.u8TimeoutCounter++;

			/* Additional check are made to handle also the faults that were signalized by I2C event interrupt */
			if( (kTemperatureData.u8TimeoutCounter > dTimeoutMaxWait) || kTemperatureData.bErrorOnArray[0] || kTemperatureData.bErrorOnArray[1] )
			{
				kTemperatureData.u8TimeoutCounter = 0;
				if(!kTemperatureData.bStateReady[0] || kTemperatureData.bErrorOnArray[0])
				{
					kTemperatureData.bErrorOnArray[0] = true;
					AssertError(eAppError_ArrayAError);
				}
				if(!kTemperatureData.bStateReady[1] || kTemperatureData.bErrorOnArray[1])
				{
					kTemperatureData.bErrorOnArray[1] = true;
					AssertError(eAppError_ArrayBError);
				}
				CallForErrorSignalize_Sensor();
				kTemperatureData.eState = TempCollect_ProcessData;
			}
		}
		break;
	case(TempCollect_ProcessData):
		if( !kTemperatureData.bReadFinished[0] )
		{
			if(kTemperatureData.bErrorOnArray[0])
			{
				kTemperatureData.fConvertedTemperature[0] = dErrorIndication;
				kTemperatureData.bErrorOnArray[0] = false;
			}
			else
			{
				kTemperatureData.fConvertedTemperature[0] = kaSensorArrayDataA[kTemperatureData.u16ArrayASensorIndex].fcnDecodeTemperature(&kaSensorArrayDataA[kTemperatureData.u16ArrayASensorIndex]);
			}
		DataHandler_StoreMeasurement(kTemperatureData.fConvertedTemperature[0]);
		}
		if( !kTemperatureData.bReadFinished[1] )
		{
			if(kTemperatureData.bErrorOnArray[1])
			{
				kTemperatureData.fConvertedTemperature[1] = dErrorIndication;
				kTemperatureData.bErrorOnArray[1] = false;
			}
			else
			{
				kTemperatureData.fConvertedTemperature[1] = kaSensorArrayDataB[kTemperatureData.u16ArrayBSensorIndex].fcnDecodeTemperature(&kaSensorArrayDataB[kTemperatureData.u16ArrayBSensorIndex]);
			}
			DataHandler_StoreMeasurement(kTemperatureData.fConvertedTemperature[1]);
		}

		kTemperatureData.eState = TempCollect_ArmNewReading;
		break;

	case(TempCollect_ArmNewReading):
		kTemperatureData.u16ArrayASensorIndex++;

		if( kTemperatureData.u16ArrayASensorIndex >= Sensor_I2CA_DeviceCount)
		{
			kTemperatureData.bReadFinished[0] = true;
		}

		kTemperatureData.u16ArrayBSensorIndex++;

		if( kTemperatureData.u16ArrayBSensorIndex >= Sensor_I2CB_DeviceCount)
		{
			kTemperatureData.bReadFinished[1] = true;
		}

		if ( kTemperatureData.bReadFinished[0] && kTemperatureData.bReadFinished[1] )
		{
			kTemperatureData.eState = TempCollect_Initialized;

			/*
			 * Open new measurement at the end of current session
			 */
			DataHandler_OpenNewMeasurement(kTemperatureData.u32MeasurementCounter++);
		}
		else
		{
			if( kTemperatureData.bResetRequest)
			{
				kTemperatureData.eState = TempCollect_Error;
			}
			else
			{
				kTemperatureData.eState = TempCollect_TemperatureReadRequest;
			}
		}
		break;
	case TempCollect_Error:
		kTemperatureData.u16ErrorWaitingCounter++;
		if( kTemperatureData.u16ErrorWaitingCounter == 1 )
		{
			TurnAllSensorOff();
		}
		else if( kTemperatureData.u16ErrorWaitingCounter == ( dSensorResetTime - 25 ) )
		{

			HAL_I2C_ER_IRQHandler(kTemperatureData.hTranscieverA);
			HAL_I2C_ER_IRQHandler(kTemperatureData.hTranscieverB);

			HAL_I2C_DeInit(kTemperatureData.hTranscieverA);
			HAL_I2C_DeInit(kTemperatureData.hTranscieverB);

			HAL_I2C_Init(kTemperatureData.hTranscieverA);
			HAL_I2C_Init(kTemperatureData.hTranscieverB);
		}
		else if( kTemperatureData.u16ErrorWaitingCounter == ( dSensorResetTime - 35 ) )
		{
			TurnAllSensorOn();
			TempCollect_FillRemainingReadingsWithError();
		}
		else if( kTemperatureData.u16ErrorWaitingCounter >= dSensorResetTime)
		{
			kTemperatureData.bScheduleMeasurement = false;
			kTemperatureData.eState = TempCollect_Initialized;
			kTemperatureData.u16ErrorWaitingCounter = 0;
		}

		kTemperatureData.bResetRequest = false;
		break;

	default:
		AssertError(eAppError_TempCollectDefaultState); // Incorrect entry
	break;
	}
}

void TempCollect_Initialize()
{
	TurnAllSensorOn();

	kTemperatureData.eState = TempCollect_Initialized;
	kTemperatureData.bEnabledFlag = true;
	kTemperatureData.u16ErrorWaitingCounter = 0;

	if(Sensor_I2CA_DeviceCount == 0)
	{
		kTemperatureData.bStateReady[0] = true;
	}
	if(Sensor_I2CB_DeviceCount == 0)
	{
		kTemperatureData.bStateReady[1] = true;
	}
	/* Sensor configuration in blocking mode: once during startup */
	//todo: Reconsider the implementation
	for(uint8_t u8Idx = 0; u8Idx < Sensor_I2CA_DeviceCount; u8Idx++ )
	{
		if (kaSensorArrayDataA[u8Idx].eSensorType == eSensor_MCP9803)
		{
			kaSensorArrayDataA[u8Idx].fcnSendConfig(&kaSensorArrayDataA[u8Idx], eMCP9803_Resolution_12bit);
		}
	}
	for(uint8_t u8Idx = 0; u8Idx < Sensor_I2CB_DeviceCount; u8Idx++ )
	{
		if (kaSensorArrayDataB[u8Idx].eSensorType == eSensor_MCP9803)
		{
			kaSensorArrayDataB[u8Idx].fcnSendConfig(&kaSensorArrayDataB[u8Idx], eMCP9803_Resolution_12bit);
		}
	}

	kTemperatureData.hTranscieverA = HandlesAssigner_GetHandle(eHandle_I2C1);
	kTemperatureData.hTranscieverB = HandlesAssigner_GetHandle(eHandle_I2C2);
}

/* Interrupt callback functions */

void TempCollect_ScheduleMeasurement()
{
	ToggleLED_A();
	if(kTemperatureData.bScheduleMeasurement)
	{
		AssertError(eAppError_TempCollectRequestOverlap); // Overlap of requests;
	}
	else
	{
		kTemperatureData.bScheduleMeasurement = true;
	}
}

void TempCollect_I2CA_Done()
{
	kTemperatureData.bStateReady[0] = true;
}
void TempCollect_I2CB_Done()
{
	kTemperatureData.bStateReady[1] = true;
}

void TempCollect_CommFaultOccured(CommunicationModule_t eModule)
{
	if( eModule == eModule_I2CA)
	{
		kTemperatureData.bErrorOnArray[0] = true;
	}
	if( eModule == eModule_I2CB)
	{
		kTemperatureData.bErrorOnArray[1] = true;
	}
}

void TempCollect_ResetSensors()
{
	kTemperatureData.bResetRequest = true;
}

static void TempCollect_FillRemainingReadingsWithError()
{
	for( ; ; )
	{
		if( !kTemperatureData.bReadFinished[0] )
		{
			kTemperatureData.fConvertedTemperature[0] = dErrorIndication;
			kTemperatureData.bErrorOnArray[0] = false;
			DataHandler_StoreMeasurement(kTemperatureData.fConvertedTemperature[0]);
		}
		if( !kTemperatureData.bReadFinished[1] )
		{
			kTemperatureData.fConvertedTemperature[1] = dErrorIndication;
			kTemperatureData.bErrorOnArray[1] = false;
			DataHandler_StoreMeasurement(kTemperatureData.fConvertedTemperature[1]);
		}
		kTemperatureData.u16ArrayASensorIndex++;

		if( kTemperatureData.u16ArrayASensorIndex >= Sensor_I2CA_DeviceCount)
		{
			kTemperatureData.bReadFinished[0] = true;
		}

		kTemperatureData.u16ArrayBSensorIndex++;

		if( kTemperatureData.u16ArrayBSensorIndex >= Sensor_I2CB_DeviceCount)
		{
			kTemperatureData.bReadFinished[1] = true;
		}
		if ( kTemperatureData.bReadFinished[0] && kTemperatureData.bReadFinished[1] )
		{
			break;
		}
	}
	DataHandler_OpenNewMeasurement(kTemperatureData.u32MeasurementCounter++);
	kTemperatureData.bErrorOnArray[0] = false;
	kTemperatureData.bErrorOnArray[1] = false;
}
