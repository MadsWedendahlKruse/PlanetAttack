


#ifndef _TIMER_H_
#define _TIMER_H_

// includes
#include <stdint.h>
#include <stdio.h>
#include "stm32f30x_conf.h"

// timer counts number of interrupts since timer start. (by default its 128 pr. second)
volatile uint32_t time_15;

// start timer 15
void timer_start15(uint16_t reloadVal, uint32_t psc);

// handle the interrupt and increment time_15
void TIM1_BRK_TIM15_IRQHandler();

#endif /* _TIMER_H_ */
