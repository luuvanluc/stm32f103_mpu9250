/*
 * GpioBase.h
 *
 *  Created on: Oct 12, 2020
 *      Author: luclv
 */

#ifndef _GPIO_GPIOBASE_H_
#define _GPIO_GPIOBASE_H_

enum GPIO_MODE {
	GPIO_INPUT,
	GPIO_OUPUT,
	GPIO_NONE
};

enum GPIO_PULL {
	GPIO_PULL_UP,
	GPIO_PULL_DOWN,
	GPIO_NO_PULL
};

enum GPIO_INT_MODE {
	GPIO_INT_RISING_EDGE,
	GPIO_INT_FALLING_EDGE,
	GPIO_INT_RISING_FALLING_EDGE
};

class GpioBase
{
public:
	virtual bool configPin(int pin, GPIO_MODE mode = GPIO_INPUT, GPIO_PULL pull = GPIO_NO_PULL) = 0;
	virtual void turnOnPin(int pin) = 0;
	virtual void turnOffPin(int pin) = 0;
	virtual void togglePin(int pin) = 0;
	virtual bool isPinInputOn(int pin) = 0;
	virtual bool isPinOutputOn(int pin) = 0;
};



#endif /* _GPIO_GPIOBASE_H_ */
