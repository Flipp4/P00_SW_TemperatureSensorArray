/*
 * CommunicationManager.h
 *
 *  Created on: Dec 16, 2021
 *      Author: Filip
 */

#ifndef COMMUNICATION_COMMUNICATIONMANAGER_H_
#define COMMUNICATION_COMMUNICATIONMANAGER_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum USBState_t
{
	USB_Disconnected = 0,
	USB_Connected = 1
}USBState_t;

void CommManager_Initialize();
void CommManager_Operate();

void CommManager_SetUSBConnectionState( USBState_t eState );

void ComManager_ArmTransmission();

#endif /* COMMUNICATION_COMMUNICATIONMANAGER_H_ */
