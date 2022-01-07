/*
 * Supervisor.h
 *
 *  Created on: 7 sty 2022
 *      Author: Filip
 */

#ifndef ERROR_SUPERVISOR_H_
#define ERROR_SUPERVISOR_H_

#include <stdint.h>

void Supervisor_Initialize();
void Supervisor_TickA();
void Supervisor_TickB();
void Supervisor_Verify();

#endif /* ERROR_SUPERVISOR_H_ */
