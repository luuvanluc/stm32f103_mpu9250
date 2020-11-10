/*
 * SpiStm32f103.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: luclv
 */

#include "../PlatformInclude.h"

extern SPI_HandleTypeDef hspi2;

SpiStm32f103* SpiStm32f103::instance = NULL;

SpiStm32f103::SpiStm32f103()
{
	mFd = NULL;
}



bool SpiStm32f103::openPort(const char* name, SPI_SPEED speed)
{
	if(strcmp(name, "dev/spi2") == 0)
	{
		mFd = &hspi2;
		mFd->Instance = SPI2;
		mFd->Init.Mode = SPI_MODE_MASTER;
		mFd->Init.Direction = SPI_DIRECTION_2LINES;
		mFd->Init.DataSize = SPI_DATASIZE_8BIT;
		mFd->Init.CLKPolarity = SPI_POLARITY_LOW;
		mFd->Init.CLKPhase = SPI_PHASE_1EDGE;
		mFd->Init.NSS = SPI_NSS_SOFT;
		mFd->Init.FirstBit = SPI_FIRSTBIT_MSB;
		mFd->Init.TIMode = SPI_TIMODE_DISABLE;
		mFd->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		mFd->Init.CRCPolynomial = 10;
	}
	else if(strcmp(name, "dev/spi1") == 0)
	{
		// Reserve
	}
	else
		return false;

	switch(speed)
	{
	case SPI_SPEED_LOWEST:
		mFd->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
		break;

	case SPI_SPEED_LOW:
		mFd->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
		break;

	case SPI_SPEED_MEDIUM:
		mFd->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
		break;

	case SPI_SPEED_HIGH:
		mFd->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
		break;

	case SPI_SPEED_HIGHEST:
		mFd->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
		break;

	default:
		return false;
	}

	if(mFd != NULL)
	{
		if (HAL_SPI_Init(mFd) != HAL_OK)
		{
			Error_Handler();
		}
	}
	return true;
}


bool SpiStm32f103::writeData(const uint8_t* ptr, unsigned len)
{
	uint8_t RxBuf[20];
	uint8_t* pRx = RxBuf;
	uint8_t* pTx = (uint8_t*)ptr;
	if(HAL_SPI_TransmitReceive(mFd, pTx, pRx, len, len*100) != HAL_OK)
	{
		return false;
	}
	return true;
}


bool SpiStm32f103::readData(uint8_t* ptr, unsigned len)
{
	uint8_t TxBuf[20];
	uint8_t* pTx = TxBuf;
	uint8_t* pRx = ptr;
	if(HAL_SPI_TransmitReceive(mFd, pTx, pRx, len, len*100) != HAL_OK)
	{
		return false;
	}
	return true;
}
