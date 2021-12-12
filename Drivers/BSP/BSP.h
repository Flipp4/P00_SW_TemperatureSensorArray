/*
 * BSP.h
 *
 *  Created on: 29 lis 2021
 *      Author: Filip
 */

#ifndef BSP_BSP_H_
#define BSP_BSP_H_

typedef enum LEDState_t
{
	eLED_On,
	eLED_Off,
	eLED_StateCount
}LEDState_t;

typedef enum SensorState_t
{
	eSensor_On,
	eSensor_Off,
	eSensor_StateCount
}SensorState_t;

void OperateLED_A (LEDState_t eState);
void OperateLED_B (LEDState_t eState);
void OperateLED_C (LEDState_t eState);
void OperateLED_D (LEDState_t eState);

void ToggleLED_B();
void ToggleLED_D();

void OperateSensorPower_A (SensorState_t eState);
void OperateSensorPower_B (SensorState_t eState);

void TurnAllSensorOn();


#endif /* BSP_BSP_H_ */
