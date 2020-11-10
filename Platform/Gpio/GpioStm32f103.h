/*
 * GpioStm32f103.h
 *
 *  Created on: Oct 12, 2020
 *      Author: luclv
 */

#ifndef _GPIOSTM32F103_H_
#define _GPIOSTM32F103_H_

typedef struct Gpio_t
{
	GPIO_TypeDef* 	mGpioBase;
	uint16_t 		mPin;
} Gpio_t;


class GpioStm32f103 : public GpioBase {
public:
	static GpioStm32f103* getInstance()
	{
		if(!instance)
		{
			instance = new GpioStm32f103();
		}

		return instance;
	};

	bool configPin(int pin, GPIO_MODE mode = GPIO_INPUT, GPIO_PULL pull = GPIO_NO_PULL);
	void turnOnPin(int pin);
	void turnOffPin(int pin);
	void togglePin(int pin);
	bool isPinInputOn(int pin);
	bool isPinOutputOn(int pin);


private:
	const static int GPIO_NUM = 3;
	static GpioStm32f103* instance;
	GpioStm32f103();
	virtual ~GpioStm32f103(){};

	Gpio_t mGpio[GPIO_NUM];
};

#endif /* _GPIOSTM32F103_H_ */
