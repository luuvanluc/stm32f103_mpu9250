/*
 * GpioStm32f103.cpp
 *
 *  Created on: Oct 12, 2020
 *      Author: luclv
 */

#include "../PlatformInclude.h"

GpioStm32f103* GpioStm32f103::instance = NULL;

GpioStm32f103::GpioStm32f103()
{
	mGpio[0] = {GPIOB, GPIO_PIN_10};
	mGpio[1] = {GPIOB, GPIO_PIN_11};
	mGpio[2] = {GPIOB, GPIO_PIN_12};
}

bool GpioStm32f103::configPin(int pin, GPIO_MODE mode /*= GPIO_INPUT*/, GPIO_PULL pull /*= GPIO_NO_PULL*/)
{
	if((pin < 0) && (pin > GPIO_NUM - 1))
		return false;
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	switch(mode)
	{
	case GPIO_INPUT:
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		break;
	case GPIO_OUPUT:
		HAL_GPIO_WritePin(mGpio[pin].mGpioBase, mGpio[pin].mPin, GPIO_PIN_RESET);
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		break;
	default:
		return false;
	}

	switch(pull)
	{
	case GPIO_NO_PULL:
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		break;
	case GPIO_PULL_UP:
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		break;
	case GPIO_PULL_DOWN:
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		break;
	default:
		return false;
	}

	GPIO_InitStruct.Pin = mGpio[pin].mPin;
	HAL_GPIO_Init(mGpio[pin].mGpioBase, &GPIO_InitStruct);

	return true;
}


void GpioStm32f103::turnOnPin(int pin)
{
	HAL_GPIO_WritePin(mGpio[pin].mGpioBase, mGpio[pin].mPin, GPIO_PIN_SET);
}

void GpioStm32f103::turnOffPin(int pin)
{
	HAL_GPIO_WritePin(mGpio[pin].mGpioBase, mGpio[pin].mPin, GPIO_PIN_RESET);
}

void GpioStm32f103::togglePin(int pin)
{
	HAL_GPIO_TogglePin(mGpio[pin].mGpioBase, mGpio[pin].mPin);
}

bool GpioStm32f103::isPinInputOn(int pin)
{
	return (HAL_GPIO_ReadPin(mGpio[pin].mGpioBase, mGpio[pin].mPin) == GPIO_PIN_SET);
}

bool GpioStm32f103::isPinOutputOn(int pin)
{
	return (HAL_GPIO_ReadPin(mGpio[pin].mGpioBase, mGpio[pin].mPin) == GPIO_PIN_SET);
}

