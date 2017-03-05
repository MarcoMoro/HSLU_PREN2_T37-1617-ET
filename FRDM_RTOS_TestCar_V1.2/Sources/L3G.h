/*
 * L3G.h
 *
 *  Created on: Jan 13, 2017
 *      Author: pirzi
 */

#ifndef L3G_H_
#define L3G_H_

#include "PE_Types.h"

typedef enum deviceType { device_4200D, device_D20, device_D20H, device_auto }deviceType_t;
typedef enum sa0State { sa0_low, sa0_high, sa0_auto }sa0State_t;

// register addresses
   enum L3GregAddr
   {
      WHO_AM_I       = 0x0F,

      CTRL1          = 0x20, // D20H
      CTRL_REG1      = 0x20, // D20, 4200D
      CTRL2          = 0x21, // D20H
      CTRL_REG2      = 0x21, // D20, 4200D
      CTRL3          = 0x22, // D20H
      CTRL_REG3      = 0x22, // D20, 4200D
      CTRL4          = 0x23, // D20H
      CTRL_REG4      = 0x23, // D20, 4200D
      CTRL5          = 0x24, // D20H
      CTRL_REG5      = 0x24, // D20, 4200D
      REFERENCE      = 0x25,
      OUT_TEMP       = 0x26,
      STATUS         = 0x27, // D20H
      STATUS_REG     = 0x27, // D20, 4200D

      OUT_X_L        = 0x28,
      OUT_X_H        = 0x29,
      OUT_Y_L        = 0x2A,
      OUT_Y_H        = 0x2B,
      OUT_Z_L        = 0x2C,
      OUT_Z_H        = 0x2D,

      FIFO_CTRL      = 0x2E, // D20H
      FIFO_CTRL_REG  = 0x2E, // D20, 4200D
      FIFO_SRC       = 0x2F, // D20H
      FIFO_SRC_REG   = 0x2F, // D20, 4200D

      IG_CFG         = 0x30, // D20H
      INT1_CFG       = 0x30, // D20, 4200D
      IG_SRC         = 0x31, // D20H
      INT1_SRC       = 0x31, // D20, 4200D
      IG_THS_XH      = 0x32, // D20H
      INT1_THS_XH    = 0x32, // D20, 4200D
      IG_THS_XL      = 0x33, // D20H
      INT1_THS_XL    = 0x33, // D20, 4200D
      IG_THS_YH      = 0x34, // D20H
      INT1_THS_YH    = 0x34, // D20, 4200D
      IG_THS_YL      = 0x35, // D20H
      INT1_THS_YL    = 0x35, // D20, 4200D
      IG_THS_ZH      = 0x36, // D20H
      INT1_THS_ZH    = 0x36, // D20, 4200D
      IG_THS_ZL      = 0x37, // D20H
      INT1_THS_ZL    = 0x37, // D20, 4200D
      IG_DURATION    = 0x38, // D20H
      INT1_DURATION  = 0x38, // D20, 4200D

      LOW_ODR        = 0x39  // D20H
   };

   typedef struct gyro{
	   int32_t vX;
	   int32_t vY;
	   int32_t vZ;
	   int32_t x;
	   int32_t y;
	   int32_t z;
	   int16_t offsetX;
	   int16_t offsetY;
	   int16_t offsetZ;
	   uint8_t temp;
   }gyro_t;
   
   void L3Ginit(void);
   void L3GenableDefault(void);
   uint8_t L3GwriteReg(uint8_t reg, uint8_t value);
   uint8_t L3GreadReg(uint8_t reg, uint8_t nbrOfBytes, uint8_t* value);
   void L3Greadxyz(void);
   gyro_t* getG(void);
   void calculateOffset(void);
   int16_t cmpfunc (const void * a, const void * b);
   void refreshMovingOffset(void);
   void L3GreadTemp(void);
   void L3GgetDegree(char dim, int16_t* value);
   void L3Gread(char dim);


#endif /* L3G_H_ */