/*
 * SpiBase.h
 *
 *  Created on: 8 thg 11, 2020
 *      Author: luclv
 */

#ifndef _SPIBASE_H_
#define _SPIBASE_H_

enum SPI_SPEED
{
	SPI_SPEED_LOWEST,
	SPI_SPEED_LOW,
	SPI_SPEED_MEDIUM,
	SPI_SPEED_HIGH,
	SPI_SPEED_HIGHEST
};

class SpiBase {
public:
	~SpiBase(){};
	// Open port
	virtual bool openPort(const char* name, SPI_SPEED speed) = 0;

	// Write data
	virtual bool writeData(const uint8_t* ptr, unsigned len) = 0;

	// Read data
	virtual bool readData(uint8_t* ptr, unsigned len) = 0;

};


#endif /* _SPIBASE_H_ */
