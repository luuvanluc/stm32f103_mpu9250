/*
 * SpiStm32f103.h
 *
 *  Created on: Nov 8, 2020
 *      Author: luclv
 */

#ifndef _SPISTM32F103_H_
#define _SPISTM32F103_H_

class SpiStm32f103 : public SpiBase{
public:
	static SpiStm32f103* getInstance()
	{
		if(!instance)
		{
			instance = new SpiStm32f103();
		}

		return instance;
	}

	// Open port
	virtual bool openPort(const char* name, SPI_SPEED speed);

	// Write data
	virtual bool writeData(const uint8_t* ptr, unsigned len);

	// Read data
	virtual bool readData(uint8_t* ptr, unsigned len);

private:
	static SpiStm32f103* instance;

	SPI_HandleTypeDef* mFd;
	SpiStm32f103();
	virtual ~SpiStm32f103() {};
};

#endif /* LAYERPLATFORM_PLATFORMDRIVER_SPI_SPISTM32F103_H_ */
