
#include "timer.h"

volatile uint32_t time_15 = 0;


// start timer 15
void timer_start15(uint16_t reloadVal, uint32_t psc) {

    /* Set timer15*/

    RCC->APB2ENR |= RCC_APB2Periph_TIM15; //Enable clock line to timer 15
    TIM15->CR1 = 0x0000;
    TIM15->ARR = reloadVal; //Set auto reload value
    TIM15->PSC = psc; //
    TIM15->DIER |= 0x0001; //Enable Timer Interrupt

    NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0);
    NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);

    TIM15->CR1 |= 0x0001; // Enable Timer
}

// handle the interrupt for the song time keeping
void TIM1_BRK_TIM15_IRQHandler () {

    time_15++;
    TIM15->SR &= ~0x0001;
}
