#include "GPIOsetup.h"

// initializes the GPIO module and should be called before calling any other GPIO function
void GPIO_init() {

    // Enable clock for GPIO Port A, B and C. Since we are using all 3 sets
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC;

}

// changes pin state to output mode
void GPIO_setPinToOut(GPIO_TypeDef* registerSet, uint16_t pin) {

    registerSet->OSPEEDR &= ~(0x00000003 << (pin * 2)); // Clear speed register
    registerSet->OSPEEDR |= (0x00000002 << (pin * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    registerSet->OTYPER &= ~(0x0001 << (pin)); // Clear output type register
    registerSet->OTYPER |= (0x0000 << (pin)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    registerSet->MODER &= ~(0x00000003 << (pin * 2)); // Clear mode register
    registerSet->MODER |= (0x00000001 << (pin * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
}

// changes the logic state of an output-mode pin
void GPIO_setPinOutVal(GPIO_TypeDef* registerSet, uint16_t pin, uint8_t val) {

    if (val == 1) {

        registerSet->ODR |= (0x0001 << pin);

    } else {

        registerSet->ODR &= ~(0x0001 << pin);
    }
}

// initializes the LED, should be called before changing LED color
void GPIO_initLed() {

    GPIO_setPinToOut(GPIOB, 4); // initialize red LED
    GPIO_setPinToOut(GPIOC, 7); // initialize green LED
    GPIO_setPinToOut(GPIOA, 9); // initialize blue LED
}

// changes the color of the LED
void GPIO_setLed(uint8_t color) {

    int r, g, b;
    switch (color) {

        case WHITE:
            r = 0;
            g = 0;
            b = 0;
        break;

        case RED:
            r = 0;
            g = 1;
            b = 1;
        break;

        case GREEN:
            r = 1;
            g = 0;
            b = 1;
        break;

        case BLUE:
            r = 1;
            g = 1;
            b = 0;
        break;

        case YELLOW:
            r = 0;
            g = 0;
            b = 1;
        break;

        case CYAN:
            r = 1;
            g = 0;
            b = 0;
        break;

        case MAGENTA:
            r = 0;
            g = 1;
            b = 0;
        break;

        case OFF:
            r = 1;
            g = 1;
            b = 1;
        break;
    }

    GPIO_setPinOutVal(GPIOB, 4, r); //Set pin PA9 to 'r'
    GPIO_setPinOutVal(GPIOC, 7, g); //Set pin PC7 to 'g'
    GPIO_setPinOutVal(GPIOA, 9, b); //Set pin PB4 to 'b'

}

// initializes the joystick, should be called before reading joystick inputs
void GPIO_initJoystick() {

    /*
        Joystick is connected to
        Right  -> PC0
        UP     -> PA4
        Center -> PB5
        Left   -> PC1
        Down   -> PB0
    */

    GPIO_setPinToRead(GPIOC, 0);
    GPIO_setPinToRead(GPIOA, 4);
    GPIO_setPinToRead(GPIOB, 5);
    GPIO_setPinToRead(GPIOC, 1);
    GPIO_setPinToRead(GPIOB, 0);
}

// returns the current state of the joystick
uint8_t GPIO_readJoystick() {

    uint8_t read = 0;
    read += GPIO_readPinVal(GPIOA, 4) << 0; // up
    read += GPIO_readPinVal(GPIOB, 0) << 1; // down
    read += GPIO_readPinVal(GPIOC, 1) << 2; // left
    read += GPIO_readPinVal(GPIOC, 0) << 3; // right
    read += GPIO_readPinVal(GPIOB, 5) << 4; // center

    return read;
}

// changes pin state to input mode
void GPIO_setPinToRead(GPIO_TypeDef* registerSet, uint16_t pin) {

    registerSet->MODER &= ~(0x00000003 << (pin * 2)); // Clear mode register
    registerSet->MODER |= (0x00000000 << (pin * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    registerSet->PUPDR &= ~(0x00000003 << (pin * 2)); // Clear push/pull register
    registerSet->PUPDR |= (0x00000002 << (pin * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)
}

// reads the logic state of an input-mode pin
uint8_t GPIO_readPinVal(GPIO_TypeDef* registerSet, int16_t pin) {

    return ((registerSet->IDR & (0x0001 << pin)) >> pin);
}
