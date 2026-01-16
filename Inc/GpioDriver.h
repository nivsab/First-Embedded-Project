

#ifndef GPIODRIVER_H_
#define GPIODRIVER_H_

#include "stm32f405_device.h"

class GpioDriver {
private:
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t pinConfig;

public:
	// Constructor
	GpioDriver(GPIO_RegDef_t *port, GPIO_PinConfig_t config);

	// Methods
	void init();
	void write(bool state);
	void toggle();
	bool read();
};



#endif /* GPIODRIVER_H_ */
