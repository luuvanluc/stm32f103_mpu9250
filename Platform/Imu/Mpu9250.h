/*
 * Mpu9250.h
 *
 *  Created on: Nov 8, 2020
 *      Author: luclv
 */

#ifndef _MPU9250_H_
#define _MPU9250_H_

#define READWRITE_CMD 				0x80
#define MULTIPLEBYTE_CMD 			0x40

// MPU9250 registers
#define ACCEL_OUT 					0x3B
#define TEMP_OUT 					0x41
#define GYRO_OUT 					0x43
#define EXT_SENS_DATA_00 			0x49
#define ACCEL_CONFIG 				0x1C
#define ACCEL_FS_SEL_2G				0x00
#define ACCEL_FS_SEL_4G 			0x08
#define ACCEL_FS_SEL_8G 			0x10
#define ACCEL_FS_SEL_16G 			0x18
#define GYRO_CONFIG 				0x1B
#define GYRO_FS_SEL_250DPS 			0x00
#define GYRO_FS_SEL_500DPS 			0x08
#define GYRO_FS_SEL_1000DPS 		0x10
#define GYRO_FS_SEL_2000DPS 		0x18
#define ACCEL_CONFIG2 				0x1D
#define DLPF_184 					0x01
#define DLPF_92 					0x02
#define DLPF_41 					0x03
#define DLPF_20 					0x04
#define DLPF_10 					0x05
#define DLPF_5 						0x06
#define CONFIG 						0x1A
#define SMPDIV 						0x19
#define INT_PIN_CFG 				0x37
#define INT_ENABLE 					0x38
#define INT_DISABLE 				0x00
#define INT_PULSE_50US 				0x00
#define INT_WOM_EN 					0x40
#define INT_RAW_RDY_EN 				0x01
#define PWR_MGMNT_1 				0x6B
#define PWR_CYCLE 					0x20
#define PWR_RESET 					0x80
#define CLOCK_SEL_PLL 				0x01
#define PWR_MGMNT_2 				0x6C
#define SEN_ENABLE 					0x00
#define DIS_GYRO 					0x07
#define USER_CTRL 					0x6A
#define I2C_MST_EN 					0x20
#define I2C_MST_CLK 				0x0D
#define I2C_MST_CTRL 				0x24
#define I2C_SLV0_ADDR 				0x25
#define I2C_SLV0_REG 				0x26
#define I2C_SLV0_DO 				0x63
#define I2C_SLV0_CTRL 				0x27
#define I2C_SLV0_EN 				0x80
#define I2C_READ_FLAG 				0x80
#define MOT_DETECT_CTRL 			0x69
#define ACCEL_INTEL_EN 				0x80
#define ACCEL_INTEL_MODE 			0x40
#define LP_ACCEL_ODR 				0x1E
#define WOM_THR 					0x1F
#define WHO_AM_I 					0x75
#define FIFO_EN 					0x23
#define FIFO_TEMP 					0x80
#define FIFO_GYRO 					0x70
#define FIFO_ACCEL 					0x08
#define FIFO_MAG 					0x01
#define FIFO_COUNT 					0x72
#define FIFO_READ 					0x74

#define ACC_LSB_0					0.0610360876f;
#define GYR_LSB_0					0.00762951095f;

struct ImuData
{
	int16_t gyroRaw[3];
	int16_t acclRaw[3];
	float gyro[3];
	float accl[3];
};

enum MPU_SCALE_ACCL
{
	MPU_SCALE_2G,
	MPU_SCALE_4G,
	MPU_SCALE_8G,
	MPU_SCALE_16G
};

enum MPU_SCALE_GYRO
{
	MPU_SCALE_250DPS,
	MPU_SCALE_500DPS,
	MPU_SCALE_1000DPS,
	MPU_SCALE_2000DPS
};

class Mpu9250 {
public:
	static Mpu9250* getInstance()
	{
		if(!instance)
		{
			instance = new Mpu9250();
		}

		return instance;
	}

	bool configImu(MPU_SCALE_ACCL acc_max, MPU_SCALE_GYRO gyr_max);
	void getData(ImuData& data);

private:
	static Mpu9250* instance;
	const static int mCS = 2;
	GpioBase* mPio;
	SpiBase* mSpi;
	uint8_t mBuffer[14];
	float mLsbAcc;
	float mLsbGyr;

	uint8_t readRegister(uint8_t address);
	bool writeRegister(uint8_t address, uint8_t data);
	void writeDataFromAddress(uint8_t *pBuffer, uint8_t addressWrite, int16_t numByteToWrite);
	void readDataFromAddress(uint8_t *pBuffer, uint8_t addressRead, int16_t numByteToRead);

	Mpu9250();
	virtual ~Mpu9250(){};
};

#endif /* _MPU9250_H_ */
