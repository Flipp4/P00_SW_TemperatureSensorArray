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

bool USB_TransmitData(float *Dataset);

#endif /* COMMUNICATION_USBTRANSMITTER_H_ */
