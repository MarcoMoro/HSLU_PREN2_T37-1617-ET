/*
 * L3G.c
 *
 *  Created on: Jan 13, 2017
 *      Author: pirzi
 */

#include "L3G.h"
#include "GI2C1.h"
#include <stdlib.h>
#include <math.h>


// Defines ////////////////////////////////////////////////////////////////
#define PI 3.14159265
#define MMA1 1

#if MMA1
	#include "MMA1.h"
#endif

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

#define FULLSCALE 250		// 250, 500, 2000 �/s

#define NBROFFSET 200

#if(FULLSCALE == 250)
#define SENSITIVITY (20000/875)		//default (20000/875) Sensitivity is 8.75mdps/digit [millidegreePerS/digit] at 250dps		875/100		(200: abtastrate * 100/875)
#endif
#if(FULLSCALE == 500)
#define SENSITIVITY (2000/175)		//default (2000/175) Sensitivity is 17.5mdps/digit -> frequency 200Hz -> 1/Sensitivity = 200/17.5 = 2000/175
#endif
#if(FULLSCALE == 2000)
#define SENSITIVITY (20/7)			// Sensitivity is 70mdps/digit -> frequency 200Hz -> 1/Sensitivity = 200/70 = 10/7
#endif

static deviceType_t device;
static gyro_t gyro;
static int16_t vX[NBROFFSET],vY[NBROFFSET],vZ[NBROFFSET];
static int8_t Offset[3];
static uint8_t res;

// Public Methods //////////////////////////////////////////////////////////////

void L3Ginit(void){
	device = device_D20;
	gyro.address = D20_SA0_HIGH_ADDRESS;
	while(L3GenableDefault()!= ERR_OK){
		L3GenableDefault();
	}
	gyro.vX = 0;
	gyro.vY = 0;
	gyro.vZ = 0;
	gyro.x = 0;
	gyro.y = 0;
	gyro.z = 0;
}


/*
Enables the L3G's gyro. Also:
- Sets gyro full scale (gain) to default power-on value of defined for FULLSCALE
- Selects 200 Hz ODR (output data rate). (Exact rate is specified as 189.4 Hz
  for L3GD20H and 190 Hz for L3GD20.)
Note that this function will also reset other settings controlled by
the registers it writes to.
*/
uint8_t L3GenableDefault(void)
{
  if (device == device_D20H)
  {
    // 0x00 = 0b00000000
    // Low_ODR = 0 (low speed ODR disabled)
    res = L3GwriteReg(LOW_ODR, 0x00);
    if(res != ERR_OK){
    	return res;
    }
  }
  

#if(FULLSCALE == 250)
  // 0x00 = 0b00000000
  // FS = 00 (+/- 250 dps full scale)
  res = L3GwriteReg(CTRL_REG4, 0x00);
  if(res != ERR_OK){
  	return res;
  }
#endif
#if(FULLSCALE == 500)
  // 0x10 = 0b00010000
  // FS = 00 (+/- 250 dps full scale)
  res = L3GwriteReg(CTRL_REG4, 0x10);
  if(res != ERR_OK){
  	return res;
  }
#endif
#if(FULLSCALE == 2000)
  // 0x20 = 0b00100000
  // FS = 00 (+/- 250 dps full scale)
  res = L3GwriteReg(CTRL_REG4, 0x20);
  if(res != ERR_OK){
  	return res;
  }
#endif
  // 0x6F = 0b01101111
  // DR = 01 (190 Hz ODR); BW = 10 (50 Hz bandwidth); PD = 1 (normal mode); Zen = Yen = Xen = 1 (all axes enabled)
  res = L3GwriteReg(CTRL_REG1, 0x6F);
  if(res != ERR_OK){
  	return res;
  }
  
  // 0b0000 0010 = 0x02
  // I2C_FIFO overrun interrupt on DRDY/INT2 enable
  res = L3GwriteReg(CTRL_REG3, 0x02);
  if(res != ERR_OK){
  	return res;
  }
  
  //0x40 = 0b01000000
  // FIFO enable
  res = L3GwriteReg(CTRL_REG5, 0x40);
  if(res != ERR_OK){
  	return res;
  }
  
  //0xE0 = 0b11100000
  // FIFO Stream mode
  res = L3GwriteReg(FIFO_CTRL_REG, 0xE0);
  if(res != ERR_OK){
  	return res;
  }
  
  // 0x24 = 0b0010 0100	-> cut off 0.9Hz
  // 0x21 = 0b0010 0001 -> cut off 7.2Hz
  // 0x20 = 0b0010 0000	-> cut off 13.5Hz
  // 0x07 = 0b0000 0111 -> cut off 0.09Hz
  // 0x10 =	0b0001 0000
  //High pass filter: Normal Mode/  cut off 0.9Hz
  res = L3GwriteReg(CTRL_REG2, 0x10);
  if(res != ERR_OK){
  	return res;
  }
  return ERR_OK;
}


// Writes a gyro register
uint8_t L3GwriteReg(uint8_t reg, uint8_t value)
{
	uint8_t tmp[2];
	tmp[0] = reg;
	tmp[1] = reg&0xff;
	return GI2C1_WriteAddress(gyro.address, &tmp[0], sizeof(tmp), (uint8_t*)(&value), sizeof(value));
}

// Reads a gyro register
uint8_t L3GreadReg(uint8_t reg, uint8_t nbrOfBytes, uint8_t* value)
{
	uint8_t tmp[2];
	tmp[0] = reg;
	tmp[1] = reg&0xff;
	return GI2C1_ReadAddress(gyro.address, &tmp[0], sizeof(tmp), (uint8_t*)value, nbrOfBytes);
}

/*
 * Read all three axes of the gyro and write it in the gyro struct
 * returns ERR_OK if all went good, else error
 */
uint8_t L3Greadxyz(void)
{
 uint8_t value[6];
 uint8_t i;
 for(i=0; i<6; i++){
	 res = L3GreadReg((OUT_X_L+i), 1, &value[i]);
	 WAIT1_WaitOSms(10);
	 if(res!=ERR_OK){
		 return res;
	 }
	 
 }
  // combine high and low bytes
  gyro.vX = (int16_t)(value[1] << 8 | value[0])/SENSITIVITY-gyro.offsetX;
  gyro.vY = (int16_t)(value[3] << 8 | value[2])/SENSITIVITY-gyro.offsetY;
  gyro.vZ = (int16_t)(value[5] << 8 | value[4])/SENSITIVITY-gyro.offsetZ;
  
  gyro.x += gyro.vX;
  gyro.y += gyro.vY;
  gyro.z += gyro.vZ;
  
#if MMA1
  combineAccel();
#endif  
  return ERR_OK;
}

/*
 * Read one axis of the gyro and write it in the gyro struct
 * returns ERR_OK if all went good, else error
 */
uint8_t L3Gread(char dim){
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
		res = L3GreadReg((reg+i), 1, &value[i]);
		WAIT1_WaitOSms(10);
		 if(res!=ERR_OK){
			 return res;
		 }
		 
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
				
				#if MMA1
					combineAccel();
				#endif
				 
	break;
	default:; // error
	break;
	}
	return ERR_OK;
}


int8_t L3GgetDegree(char dim, int16_t* value){
	int8_t err = ERR_OK;
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
		err = ERR_OVERFLOW; 
	}else if(*value<=-180){
		*value+=360;
		err = ERR_OVERFLOW;
	}
	return err;
}
/*
 * Read temperature from the sensor
 * 
 */
void L3GreadTemp(void){
	L3GreadReg(OUT_TEMP, 1, &(gyro.temp));
}

/*
 * Calculate the offset of the 3 axis. Don't move the device while calculating!
 * this has to be done just 1 time, as the value is almost not depending on time or temperature!
 * the offset is +/- 10% max of +/-250dps fullscale -> Sensitivity = 8.75mdps/digit
 * offsetMAX = 2^16*8.75*0.1/2 = +/- 28'672
 */
uint8_t calculateOffset(void){
	uint16_t i;
	uint8_t errCount = 0;
	uint8_t err;
	res = ERR_OK;
	for(i=0;i<NBROFFSET;i++){
		res = L3Greadxyz();
		if (res != ERR_OK) {
			vX[i]=0;
			vY[i]=0;
			vZ[i]=0;
			errCount++;
			err = res;
		}else{
		vX[i]=gyro.vX;
		vY[i]=gyro.vY;
		vZ[i]=gyro.vZ;
		}
		//vTaskDelay(pdMS_TO_TICKS(6));

	}
	if(errCount>=(NBROFFSET/10)){
		return err;
	}
	qsort(&vX[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
	qsort(&vY[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
	qsort(&vZ[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
	gyro.offsetX += (int8_t)vX[NBROFFSET/2];
	gyro.offsetY += (int8_t)vY[NBROFFSET/2];
	gyro.offsetZ += (int8_t)vZ[NBROFFSET/2];
	gyro.noiseX = (int8_t)(vX[NBROFFSET/3*2]-vY[NBROFFSET/3]);
	gyro.noiseY = (int8_t)(vY[NBROFFSET/3*2]-vY[NBROFFSET/3]);
	gyro.noiseZ = (int8_t)(vZ[NBROFFSET/3*2]-vZ[NBROFFSET/3]);
	gyro.x = 0;
	gyro.y = 0;
	gyro.z = 0;
	
	Offset[0] = gyro.offsetX;
	Offset[1] = gyro.offsetY;
	Offset[2] = gyro.offsetZ;
	return ERR_OK;
}


int16_t cmpfunc (const void * a, const void * b)
{
   return ( *(int16_t*)a - *(int16_t*)b );
}

void refreshMovingOffset(char dim){
	static uint16 iX;
	static uint16 iY;
	static uint16 iZ;
	int8_t noise;
	
	switch(dim){
	case 'x':;
	case 'X':	vX[iX] = gyro.vX;
				if(++iX  >= NBROFFSET){
					iX = 0;
					qsort(&vX[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
					noise = (int8_t)(vX[NBROFFSET/3*2]-vY[NBROFFSET/3]);
					if(noise <= gyro.noiseX){
						gyro.offsetX = (int8_t)vX[NBROFFSET/2];
					}
					/*
					if((gyro.offsetX+vX[NBROFFSET/2])<(Offset[0]+MAXOFFSET) && (gyro.offsetX+vX[NBROFFSET/2])>(Offset[0]-MAXOFFSET)){
						gyro.offsetX += vX[NBROFFSET/2];
					}
					*/
				}
	break;
	case 'y':;
	case 'Y':	vY[iY] = gyro.vY;
				if(++iY  >= NBROFFSET){
					iY = 0;
					qsort(&vY[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
					noise = (int8_t)(vY[NBROFFSET/3*2]-vY[NBROFFSET/3]);
					if(noise <= gyro.noiseY){
						gyro.offsetY = (int8_t)vY[NBROFFSET/2];
					}
					/*
					if((gyro.offsetY+vY[NBROFFSET/2])<(Offset[1]+MAXOFFSET) && (gyro.offsetY+vY[NBROFFSET/2])>(Offset[1]-MAXOFFSET)){
						gyro.offsetY += vY[NBROFFSET/2];
					}
					*/
				}
	break;
	case 'z':;
	case 'Z': 	vZ[iZ] = gyro.vZ;
				if(++iZ  >= NBROFFSET){
					iZ = 0;
					qsort(&vZ[0], NBROFFSET, sizeof(int16_t), (_compare_function) cmpfunc);
					noise = (int8_t)(vZ[NBROFFSET/3*2]-vZ[NBROFFSET/3]);
					if(noise <= gyro.noiseZ){
						gyro.offsetZ = (int8_t)vZ[NBROFFSET/2];
					}
					/*
					if((gyro.offsetZ+vZ[NBROFFSET/2])<(Offset[2]+MAXOFFSET) && (gyro.offsetZ+vZ[NBROFFSET/2])>(Offset[2]-MAXOFFSET)){
						gyro.offsetZ += vZ[NBROFFSET/2];
					}
					*/
				}
	break;
	default: ; // error
	}	
}

void L3GSetAngel(char dim, int16_t value){
	switch(dim){
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

#if MMA1
void combineAccel(void){
	   float xyzAccel[3];
	   float pitch;
	   static uint8_t accelCounter;
	  
	  if(accelCounter >=32){
		  xyzAccel[1] = (float)MMA1_GetXmg()*PI/1000;
		  xyzAccel[2] = (float)MMA1_GetYmg()*PI/1000;
		  xyzAccel[3] = (float)MMA1_GetZmg()*PI/1000;
		  
		  //calc pitch in degree
		  pitch = atan(xyzAccel[1]/sqrt(xyzAccel[2]*xyzAccel[2]+xyzAccel[3]*xyzAccel[3]))*180/PI; 
		  
		  // set new pitch to register
		  gyro.z = gyro.z*0.95 + (int32_t)(pitch*50); 		// pitch*50 => pitch*1000*0.05;
		  accelCounter = 0;
	  }
	  accelCounter++;
}
#endif

