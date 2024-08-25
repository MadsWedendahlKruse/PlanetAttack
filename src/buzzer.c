

#include "buzzer.h"


// the note, time and pointer to the melody thats currently playing.
uint16_t _buzzer_noteIdx = 0; // the note we are one
uint8_t  _buzzer_time = 0; // the time before next note
uint8_t* _buzzer_currentSong = NULL;

void buzzer_init(){

    /* Set timer 2 */

    RCC->APB1ENR |= 0x00000001; // Enable clock line to timer 2
    TIM2->CR1 = 0x0000; //Disable Timer
    TIM2->ARR = 1000; //Set auto reload value
    TIM2->PSC = PRESCALE_PWM; //Set pre-scaler value
    TIM2->CR1 |= 0x0001; //Enable Timer

    // Counter Compare Registers of the Timer Configuration

    TIM2->CCER &= ~TIM_CCER_CC3P; //Clear CCER Register
    TIM2->CCER |= 0x00000001 << 8; //Enable OC3 output
    TIM2->CCMR2 &= ~TIM_CCMR2_OC3M; //Clear CCMR2 Register
    TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
    TIM2->CCMR2 |= TIM_OCMode_PWM1; //Set output mode to PWM1

    TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
    TIM2->CCMR2 |= TIM_OCPreload_Enable;

    TIM2->CCR3 = 500; // Set duty cycle to 50%

    //Pin Connect to Timer

    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable clock line for GPIO bank B
    GPIOB->MODER &= ~(0x00000003 << (10 * 2));  // Clear Mode register
    GPIOB->MODER |= (0x00000002 << (10 * 2)); //Set mode register

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_1);

    buzzer_setFreq(0);
}

void buzzer_setFreq(uint16_t freq) {
    uint32_t reload = 64e6 / freq / (PRESCALE_PWM + 1) - 1;

    TIM2->ARR = reload; //Set Auto Reload Value
    TIM2->CCR3  = reload/2; //Set compare register

    TIM2->EGR |= 0x01;
}

void buzzer_update() {
    // are we playing a song
    if(_buzzer_currentSong != NULL) {

        // change node
        if (_buzzer_time == 0) {


            // reached end of song
            if (_buzzer_currentSong[_buzzer_noteIdx * SIZE + NOTE] == UINT8_MAX){

                 _buzzer_currentSong = NULL;
                 _buzzer_noteIdx = 0;
                 _buzzer_time = 0;
                 buzzer_setFreq(0);

            } else {

                // change node and take note of how long to hold it
                _buzzer_time = _buzzer_currentSong[_buzzer_noteIdx * SIZE + TIME];
                buzzer_setFreq(NOTES[_buzzer_currentSong[_buzzer_noteIdx * SIZE + NOTE]]);
                _buzzer_noteIdx++;
            }

        // decrease time and wait for node to end
        } else {

            _buzzer_time--;
        }
    }
}



void buzzer_play(const uint8_t* melody) {

    // reset song position
    _buzzer_noteIdx = 0;
    _buzzer_time = 0;

    // point to the song we want to play
    _buzzer_currentSong = melody;
}
