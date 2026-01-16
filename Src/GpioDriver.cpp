#include "GpioDriver.h"

// Constructor
GpioDriver(GPIO_RegDef_t *port, GPIO_PinConfig_t config) : _pGPIOx(port), _pinConfig(config);


	// Methods
void enablePeripheralClock()
{
	if(port == GPIOA)
	{
		GPIOA_PCLK_EN();
	}else if (port == GPIOB)
	{
		GPIOB_PCLK_EN();
	}else if (port == GPIOC)
	{
		GPIOC_PCLK_EN();
	}else if (port == GPIOD)
	{
		GPIOD_PCLK_EN();
	}else if (port == GPIOE)
	{
		GPIOE_PCLK_EN();
	}else if (port == GPIOF)
	{
		GPIOF_PCLK_EN();
	}else if (port == GPIOG)
	{
		GPIOG_PCLK_EN();
	}else if (port == GPIOH)
	{
		GPIOH_PCLK_EN();
	}else if (port == GPIOI)
	{
		GPIOI_PCLK_EN();
	}
}

void disenablePeripheralClock()
{
	if(port == GPIOA)
	{
		GPIOA_PCLK_DI();
	}else if (port == GPIOB)
	{
		GPIOB_PCLK_DI();
	}else if (port == GPIOC)
	{
		GPIOC_PCLK_DI();
	}else if (port == GPIOD)
	{
		GPIOD_PCLK_DI();
	}else if (port == GPIOE)
	{
		GPIOE_PCLK_DI();
	}else if (port == GPIOF)
	{
		GPIOF_PCLK_DI();
	}else if (port == GPIOG)
	{
		GPIOG_PCLK_DI();
	}else if (port == GPIOH)
	{
		GPIOH_PCLK_DI();
	}else if (port == GPIOI)
	{
		GPIOI_PCLK_DI();
	}
}



void init()
{
	    uint32_t temp = 0;
	    uint32_t pin = pinConfig.GPIO_PinNumber; // Short helper variable

	    // 1. Enable Peripheral Clock
	    // It is mandatory to enable the clock BEFORE writing to any GPIO register.
	    enablePeripheralClock();

	    // 2. Configure GPIO Mode (Input, Output, Alt Function, Analog)
	    // MODER register uses 2 bits per pin.
	    temp = (pinConfig.GPIO_PinMode << (2 * pin));
	    pGPIOx->MODER &= ~(0x3 << (2 * pin)); // Clear the 2 bits (Reset state)
	    pGPIOx->MODER |= temp;                // Set the new mode

	    // 3. Configure GPIO Speed (Low, Medium, Fast, High)
	    // OSPEEDR register uses 2 bits per pin.
	    temp = (pinConfig.GPIO_PinSpeed << (2 * pin));
	    pGPIOx->OSPEEDR &= ~(0x3 << (2 * pin)); // Clear previous setting
	    pGPIOx->OSPEEDR |= temp;                // Set new speed

	    // 4. Configure Pull-Up / Pull-Down settings
	    // PUPDR register uses 2 bits per pin.
	    temp = (pinConfig.GPIO_PinPuPdControl << (2 * pin));
	    pGPIOx->PUPDR &= ~(0x3 << (2 * pin)); // Clear previous setting
	    pGPIOx->PUPDR |= temp;                // Set new resistor config

	    // 5. Configure Output Type (Push-Pull or Open-Drain)
	    // OTYPER register uses 1 bit per pin.
	    temp = (pinConfig.GPIO_PinOPType << pin);
	    pGPIOx->OTYPER &= ~(0x1 << pin); // Clear bit
	    pGPIOx->OTYPER |= temp;          // Set output type

	    // 6. Configure Alternate Function (Only if Mode is set to Alt Function)
	    if (pinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {
	        // AFR registers use 4 bits per pin.
	        // AFR[0] (Low) is for pins 0-7, AFR[1] (High) is for pins 8-15.

	        uint8_t temp1 = pin / 8; // Index: 0 for AFRL, 1 for AFRH
	        uint8_t temp2 = pin % 8; // Position within the register (0 to 7)

	        pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)); // Clear 4 bits (0xF = 1111)
	        pGPIOx->AFR[temp1] |= (pinConfig.GPIO_PinAltFunMode << (4 * temp2)); // Set AF mode
	    }
	}
}

void DeInit()
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}else if (pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}else if (pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}else if (pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}else if (pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}

}
void write(bool state) {
        if (state) {
            pGPIOx->ODR |= (1 << pinConfig.GPIO_PinNumber);
        } else {
            pGPIOx->ODR &= ~(1 << pinConfig.GPIO_PinNumber);
        }
    }

    bool read() {
        uint8_t val = (uint8_t)((pGPIOx->IDR >> pinConfig.GPIO_PinNumber) & 0x1);
        return (val == 1);
    }

    void toggle() {
        pGPIOx->ODR ^= (1 << pinConfig.GPIO_PinNumber);
    }




