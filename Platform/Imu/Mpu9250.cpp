/*
 * Mpu9250.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: luclv
 */

#include "../PlatformInclude.h"

Mpu9250* Mpu9250::instance = NULL;

Mpu9250::Mpu9250()
{
	mPio = GpioStm32f103::getInstance();
	mPio->configPin(mCS, GPIO_OUPUT, GPIO_PULL_UP);
	mPio->turnOnPin(mCS);
	mSpi = SpiStm32f103::getInstance();
	mSpi->openPort("dev/spi2", SPI_SPEED_LOWEST);

	memset(mBuffer, 0, 14*sizeof(uint8_t));
	mLsbAcc = ACC_LSB_0;
	mLsbGyr = GYR_LSB_0;
}

bool Mpu9250::configImu(MPU_SCALE_ACCL acc_max, MPU_SCALE_GYRO gyr_max)
{
	mSpi->openPort("dev/spi2", SPI_SPEED_LOWEST);
	uint8_t byte = this->readRegister(ACCEL_CONFIG);
	byte &= 0xE7;
	switch(acc_max)
	{
	case MPU_SCALE_2G:
		byte |= ACCEL_FS_SEL_2G;
		mLsbAcc = ACC_LSB_0;
		break;
	case MPU_SCALE_4G:
		byte |= ACCEL_FS_SEL_4G;
		mLsbAcc = 2.0f * ACC_LSB_0;
		break;
	case MPU_SCALE_8G:
		byte |= ACCEL_FS_SEL_8G;
		mLsbAcc = 4.0f * ACC_LSB_0;
		break;
	case MPU_SCALE_16G:
		byte |= ACCEL_FS_SEL_16G;
		mLsbAcc = 8.0f * ACC_LSB_0;
		break;
	default:
		return false;
	}

	if(!this->writeRegister(ACCEL_CONFIG, byte))
		return false;
	byte = this->readRegister(GYRO_CONFIG);
	byte &= 0xE7;
	switch(gyr_max)
	{
	case MPU_SCALE_250DPS:
		byte |= GYRO_FS_SEL_250DPS;
		mLsbGyr = GYR_LSB_0;
		break;
	case MPU_SCALE_500DPS:
		byte |= GYRO_FS_SEL_500DPS;
		mLsbGyr = 2.0f * GYR_LSB_0;
		break;
	case MPU_SCALE_1000DPS:
		byte |= GYRO_FS_SEL_1000DPS;
		mLsbGyr = 4.0f * GYR_LSB_0;
		break;
	case MPU_SCALE_2000DPS:
		byte |= GYRO_FS_SEL_2000DPS;
		mLsbGyr = 8.0f * GYR_LSB_0;
		break;
	default:
		return false;
	}
	if(!this->writeRegister(GYRO_CONFIG, byte))
		return false;

	mSpi->openPort("dev/spi2", SPI_SPEED_HIGHEST);

	return true;
}

void Mpu9250::getData(ImuData& data)
{
	this->readDataFromAddress(mBuffer, ACCEL_OUT, 14);
	data.acclRaw[0] = (((int16_t)mBuffer[0]) << 8) | mBuffer[1];
	data.acclRaw[1] = (((int16_t)mBuffer[2]) << 8) | mBuffer[3];
	data.acclRaw[2] = (((int16_t)mBuffer[4]) << 8) | mBuffer[5];
	data.gyroRaw[0] = (((int16_t)mBuffer[8]) << 8) | mBuffer[9];
	data.gyroRaw[1] = (((int16_t)mBuffer[10]) << 8) | mBuffer[11];
	data.gyroRaw[2] = (((int16_t)mBuffer[12]) << 8) | mBuffer[13];

	data.accl[0] = data.acclRaw[0] * mLsbAcc * 0.001f;
	data.accl[1] = data.acclRaw[1] * mLsbAcc * 0.001f;
	data.accl[2] = data.acclRaw[2] * mLsbAcc * 0.001f;
	data.gyro[0] = data.gyroRaw[0] * mLsbGyr;
	data.gyro[1] = data.gyroRaw[1] * mLsbGyr;
	data.gyro[2] = data.gyroRaw[2] * mLsbGyr;
}

void Mpu9250::writeDataFromAddress(uint8_t *pBuffer, uint8_t addressWrite, int16_t numByteToWrite)
{
	mPio->turnOffPin(mCS);
	mSpi->writeData(&addressWrite, 1);
	mSpi->writeData(pBuffer,numByteToWrite);
	mPio->turnOnPin(mCS);
}
void Mpu9250::readDataFromAddress(uint8_t *pBuffer, uint8_t addressRead, int16_t numByteToRead)
{
	mPio->turnOffPin(mCS);
	addressRead |= (uint8_t)READWRITE_CMD;
	mSpi->writeData(&addressRead, 1);
	mSpi->readData(pBuffer,numByteToRead);
	mPio->turnOnPin(mCS);
}

uint8_t Mpu9250::readRegister(uint8_t address)
{
	uint8_t readByte;
	readDataFromAddress(&readByte, address, 1);
	return readByte;
}
bool Mpu9250::writeRegister(uint8_t address, uint8_t data)
{
	uint8_t readData;
	writeDataFromAddress(&data, address, 1);
	HAL_Delay(10);									//FIXME: must be abstract
	readData = readRegister(address);
	if(readData == data)
		return true;
	else
		return false;
}

