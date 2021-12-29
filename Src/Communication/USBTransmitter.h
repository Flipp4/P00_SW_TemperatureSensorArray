/*
 * USBTransmitter.h
 *
 *  Created on: 15 gru 2021
 *      Author: Filip
 */

#ifndef COMMUNICATION_USBTRANSMITTER_H_
#define COMMUNICATION_USBTRANSMITTER_H_

#include "stm32f4xx_hal.h"
#include "../Inc/usbd_cdc_if.h"
#include "../Application/Application.h"
#include <stdbool.h>
#include <stdint.h>

void USB_InitalizeTransmitterLogic();
bool USB_TransmitData(uint8_t *Dataset, uint8_t u8Length);
void USB_CheckForUSBConnection();

void USB_SignalizeVBUSMeasurementReady(uint32_t u32Result);

#endif /* COMMUNICATION_USBTRANSMITTER_H_ */
