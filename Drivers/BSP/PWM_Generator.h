/*
 * PWM_Generator.h
 *
 *  Created on: Jan 4, 2022
 *      Author: Filip
 */

#ifndef BSP_PWM_GENERATOR_H_
#define BSP_PWM_GENERATOR_H_

#define dPulseCounter					( 50 )
#define dSignalFrequencymHz 			( 200 )
#define dPulseUpdate 					( 200 )

#define dStepPerUpdatePerHalfPeriod		( dPulseCounter / ( dPulseUpdate * ( 500.0 / dSignalFrequencymHz  ) ) )
#define dUpdatesPerHalfPeriod			( dPulseUpdate * ( 500.0 / dSignalFrequencymHz ) )


void PWMGenerator_Initialize();
void PWMGenerator_RecalculatePWM();
void PWMGenerator_TurnPWMTimerOn();

void PWMGenerator_ApplyNewWidth();


#endif /* BSP_PWM_GENERATOR_H_ */
