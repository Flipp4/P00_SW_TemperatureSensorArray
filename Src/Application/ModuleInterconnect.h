/*
 * ModuleInterconnect.h
 *
 *  Created on: Dec 18, 2021
 *      Author: Filip
 */

#ifndef APPLICATION_MODULEINTERCONNECT_H_
#define APPLICATION_MODULEINTERCONNECT_H_

void CallForTransmissionEvent();
void CallForUSBConnection();
void CallForUSBDisonnection();
void CallForAverageAddition();
void CallForSensorReset();
void CallForErrorSignalize_Supervisor();
void CallForErrorSignalize_Sensor();

#endif /* APPLICATION_MODULEINTERCONNECT_H_ */
