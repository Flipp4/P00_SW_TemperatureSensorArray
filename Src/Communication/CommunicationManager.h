/*
 * CommunicationManager.h
 *
 *  Created on: Dec 16, 2021
 *      Author: Filip
 */

#ifndef COMMUNICATION_COMMUNICATIONMANAGER_H_
#define COMMUNICATION_COMMUNICATIONMANAGER_H_

typedef enum USBState_t
{
	USB_Disconnected = 0,
	USB_Connected = 1
};

void CommManager_Initialize();
void CommManager_Operate();

void CommManager_SetUSBConnectionState( USBState_t eState );

#endif /* COMMUNICATION_COMMUNICATIONMANAGER_H_ */
