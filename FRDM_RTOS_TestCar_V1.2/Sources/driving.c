/*
 * driving.c
 *
 *  Created on: Feb 23, 2017
 *      Author: pirzi
 */

#include "serial_communication.h"
#include "motor.h"
#include "FRTOS1.h"
#include "VL6180X.h"
#include "LED_GREEN.h"
#include "RED.h"
#include "L3G.h"
#include <math.h>
#include <stdlib.h>
#include "CLS1.h"
#include "pid.h"

#define TOFFRONT 0
#define TOFLEFT 1
#define TOFRIGHT 2
#define GYRO 3
#define PI 3.14159265
#define DELAY 15	// in ms

uint8_t kpToF, kiToF, kdToF;
uint8_t kpGyro, kiGyro, kdGyro;
int8_t factor;
uint8_t device;

//Task2
void driveToStair(int8_t speed, uint8_t optRange, uint16_t frontdistance){
	uint8_t err;
	uint8_t done = 0;
	int16_t range = 0;
	int16_t corrGyro = 0;
	int16_t corrToF = 0;
	
	LED_GREEN_Put(1);
	while(!done){
		// Motor-Regulation
		 err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, 0, &corrGyro);
		 if(err != ERR_OK){
			 corrGyro = 0;
			// error 
		 }
		 err = calcPID(device,kpToF, kiToF, kdToF, optRange, &corrToF);
		 if(err != ERR_OK){
			 corrToF = 0;
			 // error
		 }
		 motorsStartup(speed-corrGyro+factor*corrToF, speed+corrGyro-factor*corrToF, 0);

			 
		 refreshMovingOffset('x');
		 
		 // check if stair is detected
		 VL_GetDistance(TOFFRONT, &range);
		 if(range <= frontdistance && range > 0){
			 LED_GREEN_Put(0);
			 RED_Put(1);
			 done = 1;
		 }
		 
		 vTaskDelay(pdMS_TO_TICKS(DELAY));
	}
	motorsStartup(0, 0, 0);
	RED_Put(0);
	taskDone(2);
}

//Task3
void driveOverStair(int8_t speed, uint8_t optRange){
	uint8_t err = ERR_OK;
	int16_t corrToF = 0;
	int16_t corrGyro = 0;
	uint8_t stairState = 0;
	int16_t angel = 0;
	uint8_t done = 0;

	while(!done){
		// Regulate Motors
		err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, 0, &corrGyro);
		if(err != ERR_OK){
			corrGyro = 0;
			//error
		}
		err = calcPID(device, kpToF, kiToF, kdToF, optRange, &corrToF);
		if(err != ERR_OK){
			corrToF = 0;
			// error
		}
		motorsStartup(speed-corrGyro+factor*corrToF, speed+corrGyro-factor*corrToF, 0);
		
		/* \todo test if it helps to avoid drift */
		refreshMovingOffset('x'); // Test if good or not
		
		L3GgetDegree('Z', &angel);
		// stair upwards
		if(stairState == 0 && angel <= -25){
			stairState = 1;	
			LED_GREEN_Put(1);
		}
		// on top of the stair
		else if(stairState == 1 && angel < 5 && angel > -5){
			stairState = 2;	
			L3GSetAngel('z', 0);
			RED_Put(1);
			speed -= 20;
		}
		// stair downwards
		else if(stairState == 2 && angel >= 25){
			stairState = 3; 
			LED_GREEN_Put(0);
		}
		// stair done
		else if(stairState == 3 && angel < 10 && angel > -10){ 
			RED_Put(0);
			vTaskDelay(pdMS_TO_TICKS(20));
			done = 1;
		}
		vTaskDelay(pdMS_TO_TICKS(DELAY));
	}
	
	motorsStartup(0, 0, 0);
	taskDone(3);
}

//Task4
void driveToTurningPlace(int8_t speed, uint8_t optRange){
	uint8_t err = ERR_OK;
	int16_t corrToF = 0;
	int16_t corrGyro = 0;
	uint8_t done = 0;
	int16_t ToFLeft;
	int16_t ToFRight;
	motorsStartup(speed,speed,0);
	while(!done){
		// Regulate Motors
		err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, 0, &corrGyro);
		if(err != ERR_OK){
			corrGyro = 0;
			//error
		}
		err = calcPID(device, kpToF, kiToF, kdToF, optRange, &corrToF);
		if(err != ERR_OK){
			corrToF = 0;
			// error
		}
		motorsStartup(speed-corrGyro+factor*corrToF, speed+corrGyro-factor*corrToF, 0);
		
		/* \todo test if it helps to avoid drift */
		refreshMovingOffset('x'); // Test if good or not
		
		// stop condition
		VL_GetDistance(TOFRIGHT, &ToFRight);
		VL_GetDistance(TOFLEFT, &ToFLeft);
		if((ToFLeft == 255 || ToFLeft == 0) && (ToFRight == 255 || ToFRight == 0)){
			done = 1;
		}
		
		vTaskDelay(pdMS_TO_TICKS(DELAY));
	}
	
	motorsStartup(0, 0, 0);
	taskDone(4);
}

//Task5
void driveThroughtTurningPlace(uint8_t speed, uint8_t optRange, uint8_t frontdistance){
	int16_t range = 0, rangeOld = 0;
	uint8_t err = ERR_OK;
	int16_t corrGyro = 0;
	int16_t optAngel = 0;
	uint8_t partState = 0;
	int16_t corrToF = 0;
	uint16_t count = 0;
	uint16_t time = 1000; // drive for 1 seconds over the end

	
	// drive straight for defined time
	while(partState == 0){
		LED_GREEN_Put(1);
		// Motor-Regulation
		 err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, optAngel, &corrGyro);
		 if(err != ERR_OK){
			 corrGyro = 0;
			 // error
		 }
		 motorsStartup(speed-corrGyro, speed+corrGyro, 0);
		 
		 // check end condition
		 count++;
		 if(count >= (time/DELAY)){
			 LED_GREEN_Put(0);
			 partState = 1;
			 motorsStartup(0, 0, 0);
			 count = 0;
		 }
		 
		 vTaskDelay(pdMS_TO_TICKS(DELAY));
	}
	
	// turn 90 degree
	optAngel = -90*factor;
	while(partState == 1){
		// Motor-Regulation
		RED_Put(1);
		 err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, optAngel, &corrGyro);
		 if(err != ERR_OK){
			 corrGyro = 0;
			 count--;
			 // error
		 }
		 motorsStartup(speed-corrGyro/4, speed+corrGyro/4, 10);
		 
		 // check end condition
		 if(corrGyro <= 5 && corrGyro >= -5){
			 count++;
		 }
		 if(count >= 10){
			 RED_Put(0);
			 count = 0;
			 motorsStartup(0, 0, 0);
			 partState = 2;
		 }
		 
		 vTaskDelay(pdMS_TO_TICKS(DELAY));
	}
	
	// drive to the wall
	while(partState == 2){
		LED_GREEN_Put(1);
		 err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, optAngel, &corrGyro);
		 if(err == ERR_OK){
			 corrGyro = 0;
			 // error
		 }
		 motorsStartup(speed-corrGyro, speed+corrGyro, 0);

		
		// check end condition
		VL_GetDistance(TOFFRONT, &range);
		if(range <= frontdistance && range > 0){
			LED_GREEN_Put(0);
			motorsStartup(0, 0, 0);
			partState = 3;
		}
	}
	
	// turn 90 degree
	optAngel = -180*factor;
	while(partState == 3){
		RED_Put(1);
		// Motor-Regulation
			 err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, optAngel, &corrGyro);
			 if(err != ERR_OK){
				 corrGyro = 0;
				 count--;
				 // error
			 }
			 motorsStartup(speed-corrGyro/4, speed+corrGyro/4, 10);
			 
			 // check end condition
			 if(corrGyro <= 5 && corrGyro >= -5){
				 count++;
			 }
			 if(count >= 10){
				 RED_Put(0);
				 motorsStartup(0, 0, 0);
				 partState = 4;
			 }
			 
			 vTaskDelay(pdMS_TO_TICKS(DELAY));
	}
	
	//drive to the door
	range = 0;
	while(partState == 4){
		LED_GREEN_Put(1);
		// Regulate Motors
		err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, optAngel, &corrGyro);
		if(err != ERR_OK){
			corrGyro = 0;
			// error
		}
		err = calcPID(device, kpToF, kiToF, kdToF, optRange, &corrToF);	
		if(err != ERR_OK){
			corrToF = 0;
			// error
		}
		motorsStartup(speed-corrGyro+factor*corrToF, speed+corrGyro-factor*corrToF, 0);
		
		//end condition
		rangeOld = range;
		VL_GetDistance(device, &range);
		if((rangeOld-range) >= 45 && (rangeOld-range)<=55){
			partState = 5;
		}		
	}
	// drive throught the door
	rangeOld = 0;
	while(partState == 5){
		RED_Put(1);
		// Regulate Motors
		err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, optAngel, &corrGyro);
		if(err != ERR_OK){
			corrGyro = 0;
			// error
		}
		err = calcPID(device, kpToF, kiToF, kdToF, optRange-50, &corrToF);	
		if(err != ERR_OK){
			corrToF = 0;
			// error
		}
		motorsStartup(speed-corrGyro+factor*corrToF, speed+corrGyro-factor*corrToF, 0);
		
		rangeOld = range;
		VL_GetDistance(device, &range);
		if((range-rangeOld) >= 45 && (rangeOld-range)<=55){
			RED_Put(0);
			LED_GREEN_Put(0);
			partState = 6;
		}
		
	}
	
		motorsStartup(0, 0, 0);
		taskDone(5);
}

//Task6
void driveToEndZone(int8_t speed, uint8_t optRange, uint8_t frontdistance){
	uint8_t err = ERR_OK;
	int16_t corrToF = 0;
	int16_t corrGyro = 0;
	uint8_t done = 0;
	int16_t range;
	while(!done){
		// Regulate Motors
		err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, -180*factor, &corrGyro);
		if(err != ERR_OK){
			corrGyro = 0;
			//error
		}
		err = calcPID(device, kpToF, kiToF, kdToF, optRange, &corrToF);
		if(err != ERR_OK){
			corrToF = 0;
			// error
		}
		motorsStartup(speed-corrGyro+factor*corrToF, speed+corrGyro-factor*corrToF, 0);
		
		/* \todo test if it helps to avoid drift */
		refreshMovingOffset('x'); // Test if good or not
		
		 // stop condition
		 VL_GetDistance(TOFFRONT, &range);
		 if(range <= frontdistance && range > 0){
			 done = 1;
		 }
		
		vTaskDelay(pdMS_TO_TICKS(DELAY));
	}
	
	motorsStartup(0, 0, 0);
	taskDone(6);
}

void pushTheButton(uint8_t number, uint8_t fronddistance){
	
}

void initDriving(uint8_t kpT, uint8_t kiT, uint8_t kdT, uint8_t kpG, uint8_t kiG, uint8_t kdG, bool leftParcour){
	if(leftParcour){
		factor = -1;
		device = TOFRIGHT;
	}
	else{
		factor = 1;
		device = TOFLEFT;
	}
	kpToF = kpT;
	kiToF = kiT;
	kdToF = kdT;
	kpGyro = kpG;
	kiGyro = kiG;
	kdGyro = kdG;
	
}

