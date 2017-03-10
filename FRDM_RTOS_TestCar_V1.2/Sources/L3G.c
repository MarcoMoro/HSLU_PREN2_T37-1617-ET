/*
 * L3G.c
 *
 *  Created on: Jan 13, 2017
 *      Author: pirzi
 */

#include "L3G.h"
#include "GI2C1.h"
#include "WAIT1.h"
#include <stdlib.h>

// Defines ////////////////////////////////////////////////////////////////

// IIC two-wire interface uses a 7-bit number for the address,
// and sets the last bit correctly based on reads and writes
#define D20_SA0_HIGH_ADDRESS      0b1101011 // also applies to D20H
#define D20_SA0_LOW_ADDRESS       0b1101010 // also applies to D20H
#define L3G4200D_SA0_HIGH_ADDRESS 0b1101001
#define L3G4200D_SA0_LOW_ADDRESS  0b1101000

#define TEST_REG_ERROR -1

#define D20H_WHO_ID     0xD7
#define D20_WHO_ID      0xD4
#define L3G4200D_WHO_ID 0xD3

#define MAXOFFSET 20

#define FULLSCALE 500		// 250, 500, 2000 �/s

#define NBROFFSET 200

#if(FULLSCALE == 250)
#define SENSITIVITY (20000/875)		// Sensitivity is 8.75mdps/digit [millidegreePerS/digit] at 250dps		875/100		(200: abtastrate * 100/875)
#endif
#if(FULLSCALE == 500)
#define SENSITIVITY (2000/175)		// Sensitivity is 17.5mdps/digit -> frequency 200Hz -> 1/Sensitivity = 200/17.5 = 2000/175
#endif
#if(FULLSCALE == 2000)
#define SENSITIVITY (20/7)			// Sensitivity is 70mdps/digit -> frequency 200Hz -> 1/Sensitivity = 200/70 = 10/7
#endif
deviceType_t device;
uint8_t address;
sa0State_t sa0;
gyro_t gyro;
int16_t vX[NBROFFSET],vY[NBROFFSET],vZ[NBROFFSET];
int16_t writingPos;
int8_t OffsetX;
int8_t OffsetY;
int8_t OffsetZ;

// Public Methods //////////////////////////////////////////////////////////////

void L3Ginit(void){
	device = device_D20;
	address = D20_SA0_HIGH_ADDRESS;
	sa0 = sa0_high;
	L3GenableDefault();
	gyro.offsetX = OffsetX;
	gyro.offsetY = OffsetY;
	gyro.offsetZ = OffsetZ;
	gyro.vX = 0;
	gyro.vY = 0;
	gyro.vZ = 0;
	gyro.x = 0;
	gyro.y = 0;
	gyro.z = 0;
}


/*
Enables the L3G's gyro. Also:
- Sets gyro full scale (gain) to default power-on value of +/- 250 dps
  (specified as +/- 245 dps for L3GD20H).
- Selects 200 Hz ODR (output data rate). (Exact rate is specified as 189.4 Hz
  for L3GD20H and 190 Hz for L3GD20.)
Note that this function will also reset other settings controlled by
the registers it writes to.
*/
void L3GenableDefault(void)
{
  if (device == device_D20H)
  {
    // 0x00 = 0b00000000
    // Low_ODR = 0 (low speed ODR disabled)
    L3GwriteReg(LOW_ODR, 0x00);
  }
  

#if(FULLSCALE == 250)
  // 0x00 = 0b00000000
  // FS = 00 (+/- 250 dps full scale)
  L3GwriteReg(CTRL_REG4, 0x00);
#endif
#if(FULLSCALE == 500)
  // 0x10 = 0b00010000
  // FS = 00 (+/- 250 dps full scale)
  L3GwriteReg(CTRL_REG4, 0x10);
#endif
#if(FULLSCALE == 2000)
  // 0x20 = 0b00100000
  // FS = 00 (+/- 250 dps full scale)
  L3GwriteReg(CTRL_REG4, 0x20);
#endif
  // 0x6F = 0b01101111
  // DR = 01 (200 Hz ODR); BW = 10 (50 Hz bandwidth); PD = 1 (normal mode); Zen = Yen = Xen = 1 (all axes enabled)
  L3GwriteReg(CTRL_REG1, 0x6F);
  
  // 0b0000 0010 = 0x02
  // I2C_FIFO overrun interrupt on DRDY/INT2 enable
  L3GwriteReg(CTRL_REG3, 0x02);
  
  //0x40 = 0b01000000
  // FIFO enable
  L3GwriteReg(CTRL_REG5, 0x40);
  
  //0xE0 = 0b11100000
  // FIFO Stream mode
  L3GwriteReg(FIFO_CTRL_REG, 0xE0);
  
  // 0x24 = 0b0010 0100	-> cut off 0.9Hz
  // 0x21 = 0b0010 0001 -> cut off 7.2Hz
  // 0x20 = 0b0010 0000	-> cut off 13.5Hz
  // 0x07 = 0b0000 0111 -> cut off 0.09Hz
  // 0x10 =	0b0001 0000
  //High pass filter: Normal Mode/  cut off 0.9Hz
  L3GwriteReg(CTRL_REG2, 0x10);
}


// Writes a gyro register
uint8_t L3GwriteReg(uint8_t reg, uint8_t value)
{
	uint8_t tmp[2];
	tmp[0] = reg;
	tmp[1] = reg&0xff;
	return GI2C1_WriteAddress(address, &tmp[0], sizeof(tmp), (uint8_t*)(&value), sizeof(value));
}

// Reads a gyro register
uint8_t L3GreadReg(uint8_t reg, uint8_t nbrOfBytes, uint8_t* value)
{
	uint8_t tmp[2];
	tmp[0] = reg;
	tmp[1] = reg&0xff;
	return GI2C1_ReadAddress(address, &tmp[0], sizeof(tmp), (uint8_t*)value, nbrOfBytes);
}

void L3Greadxyz(void)
{
 uint8_t value[6];
 uint8_t i;
 for(i=0; i<6; i++){
	 L3GreadReg((OUT_X_L+i), 1, &value[i]);
 }
  // combine high and low bytes
  gyro.vX = (int16_t)(value[1] << 8 | value[0])/SENSITIVITY-gyro.offsetX;
  gyro.vY = (int16_t)(value[3] << 8 | value[2])/SENSITIVITY-gyro.offsetY;
  gyro.vZ = (int16_t)(value[5] << 8 | value[4])/SENSITIVITY-gyro.offsetZ;
  
  gyro.x += gyro.vX;
  gyro.y += gyro.vY;
  gyro.z += gyro.vZ;
}

void L3Gread(char dim){
	uint8_t value[2];
	uint8_t i;
	uint8_t reg;
	switch(dim){
	case 'x':;
	case 'X': reg = OUT_X_L;
	break;
	case 'y':;
	case 'Y': reg = OUT_Y_L;
	break;
	case 'z':;
	case 'Z': reg = OUT_Z_L;
	break;
	default:; // error
	break;
	}
	for(i=0; i<2; i++){
		L3GreadReg((reg+i), 1, &value[i]);
	}
	// combine high and low bytes
	switch(dim){
	case 'x':;
	case 'X': 	gyro.vX = (int16_t)(value[1] << 8 | value[0])/SENSITIVITY-gyro.offsetX;
				gyro.x += gyro.vX;
	break;
	case 'y':;
	case 'Y': 	gyro.vY = (int16_t)(value[1] << 8 | value[0])/SENSITIVITY-gyro.offsetY;
				gyro.y += gyro.vY;
	break;
	case 'z':;
	case 'Z': 	gyro.vZ = (int16_t)(value[1] << 8 | value[0])/SENSITIVITY-gyro.offsetZ;
				gyro.z += gyro.vZ;
	break;
	default:; // error
	break;
	}

}


void L3GgetDegree(char dim, int16_t* value){
	switch(dim){
	case 'x':;
	case 'X':*value = gyro.x/1000;
	break;
	case 'y':;
	case 'Y':*value = gyro.y/1000;
	break;
	case 'z':;
	case 'Z': *value = gyro.z/1000;
	break;
	default: ; // error
	break;
	}
	if(*value>180){
		*value-=360;
	}else if(*value<-180){
		*value+=360;
	}
}
/*
 * Read temperature from the sensor
 * 
 */
void L3GreadTemp(void){
	L3GreadReg(OUT_TEMP, 1, &(gyro.temp));
}

// Calculate the offset of the 3 axis. Don't move the device while calculating!
// this has to be done just 1 time, as the value is almost not depending on time or temperature!
// the offset is +/- 10% max of +/-250dps fullscale -> Sensitivity = 8.75mdps/digit
//offsetMAX = 2^16*8.75*0.1/2 = +/- 28'672
void calculateOffset(void){
	
	for(writingPos=0;writingPos<NBROFFSET;writingPos++){
		L3Greadxyz();
		vX[writingPos]=(int16_t)gyro.vX;
		vY[writingPos]=(int16_t)gyro.vY;
		vZ[writingPos]=(int16_t)gyro.vZ;
		WAIT1_Waitms(4);
	}
	qsort(&vX[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
	qsort(&vY[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
	qsort(&vZ[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
	gyro.offsetX += vX[NBROFFSET/2];
	gyro.offsetY += vY[NBROFFSET/2];
	gyro.offsetZ += vZ[NBROFFSET/2];
	gyro.x = 0;
	gyro.y = 0;
	gyro.z = 0;
	
	OffsetX = gyro.offsetX;
	OffsetY = gyro.offsetY;
	OffsetZ = gyro.offsetZ;
	
	writingPos = 0;

}


int16_t cmpfunc (const void * a, const void * b)
{
   return ( *(int16_t*)a - *(int16_t*)b );
}


gyro_t* getG(void){
	return &gyro;
}

void refreshMovingOffset(void){
	vX[writingPos] = gyro.vX;
	vY[writingPos] = gyro.vY;
	vZ[writingPos] = gyro.vZ;
	if(++writingPos  >= NBROFFSET){
		writingPos = 0;
		qsort(&vX[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
		qsort(&vY[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
		qsort(&vZ[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
		if((gyro.offsetX+vX[NBROFFSET/2])<(OffsetX+MAXOFFSET) && (gyro.offsetX+vX[NBROFFSET/2])>(OffsetX-MAXOFFSET)){
			gyro.offsetX += vX[NBROFFSET/2];
		}
		if((gyro.offsetY+vY[NBROFFSET/2])<(OffsetY+MAXOFFSET) && (gyro.offsetY+vY[NBROFFSET/2])>(OffsetY-MAXOFFSET)){
			gyro.offsetY += vY[NBROFFSET/2];
		}
		if((gyro.offsetZ+vZ[NBROFFSET/2])<(OffsetZ+MAXOFFSET) && (gyro.offsetZ+vZ[NBROFFSET/2])>(OffsetZ-MAXOFFSET)){
			gyro.offsetZ += vZ[NBROFFSET/2];
		}
	}
	
}

void L3GSetAngel(char dimension, int16_t value){
	switch(dimension){
	case 'X': ;
	case 'x': gyro.x = (int32_t)value;
	break;
	case 'Y': ;
	case 'y': gyro.y = (int32_t)value;
	break;
	case 'Z': ;
	case 'z': gyro.z = (int32_t)value;
	break;
	default: ; //error;
	break;
	}
}

