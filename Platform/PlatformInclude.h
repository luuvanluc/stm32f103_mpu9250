/*
 * PlatformInclude.h
 *
 *  Created on: Nov 10, 2020
 *      Author: luclv
 */

#ifndef PLATFORMINCLUDE_H_
#define PLATFORMINCLUDE_H_

// C++ compiler Standard Library for C/C++ source code.
#include "cstdio"
#include "cstdlib"
#include "cstring"
#include "cstdarg"
#include "cctype"
#include "cmath"
#include "cfloat"
#include "climits"
#include "stdint.h"
#include "queue"

using namespace std;


// declare type of library build
#include "main.h"
#include "string.h"
#include "stddef.h"
#include "stm32f1xx_it.h"

// Platform
#include "Gpio/GpioBase.h"
#include "Gpio/GpioStm32f103.h"
#include "Spi/SpiBase.h"
#include "Spi/SpiStm32f103.h"
#include "Imu/Mpu9250.h"



#endif /* PLATFORMINCLUDE_H_ */
