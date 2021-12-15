/*
 * USBTransmitter.h
 *
 *  Created on: 15 gru 2021
 *      Author: Filip
 */

#ifndef COMMUNICATION_USBTRANSMITTER_H_
#define COMMUNICATION_USBTRANSMITTER_H_


#include "../Inc/usbd_cdc_if.h"
#include "../Application/Application.h"
#include <stdbool.h>
#include <stdint.h>

#if dStoreReultsAsFloat
bool USB_TransmitData(float *Dataset);
#else
bool USB_TransmitData(int16_t *Dataset);
#endif



#endif /* COMMUNICATION_USBTRANSMITTER_H_ */
