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

bool leftParcour;
uint8_t kpToF, kiToF, kdToF;
uint8_t kpGyro, kiGyro, kdGyro;
uint8_t factor;

//Task2
void driveToStair(int8_t speed, uint8_t optRange, uint8_t startupTime, uint16_t frontdistance){
	uint8_t err;
	uint8_t done = 0;
	int16_t range = 0;
	int16_t corrGyro = 0;
	int16_t corrToF = 0;
	uint8_t device;
	if(leftParcour){
		device = TOFLEFT;
	}
	else{
		device = TOFRIGHT;
	}
	RED_Put(0);
	LED_GREEN_Put(1);
	motorsStartup(speed, speed, startupTime);
	while(!done){
		// Motor-Regulation
		 err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, 0, &corrGyro);
		 if(err == ERR_OK){
			 err = calcPID(device,kpToF, kiToF, kdToF, optRange, &corrToF);
			 	 if(err != ERR_OK){
			 		 corrToF = 0;
			 	 }
			 motorsStartup(speed-corrGyro+factor*corrToF, speed+corrGyro-factor*corrToF, 2);
		 }
		 else{
			 // error
		 }
		 
		 // check if stair is detected
		 VL_GetDistance(TOFFRONT, &range);
		 if(range <= frontdistance && range > 0){
			 LED_GREEN_Put(0);
			 RED_Put(1);
			 done = 1;
		 }
		 
		 refreshMovingOffset();
		 vTaskDelay(pdMS_TO_TICKS(12));
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
	uint8_t device;
	uint8_t stairState = 0;
	int16_t angel;
	uint8_t done = 0;
	L3GSetAngel('z', 0);
	if(leftParcour){
		device = TOFLEFT;
	}
	else{
		device = TOFRIGHT;
	}
	motorsStartup(speed,speed,0);
	do{
		// Regulate Motors
		err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, 0, &corrGyro);
		if(err == ERR_OK){
			err = calcPID(device, kpToF, kiToF, kdToF, optRange, &corrToF);
		}
		
		if(err == ERR_OK){
			motorsStartup(speed-corrGyro+factor*corrToF, speed+corrGyro-factor*corrToF, 2);
		}
		else{
			motorsStartup(0, 0, 0);		// error
		}
		
		//
		
		L3GgetDegree('Z', &angel);
		if(stairState == 0 && angel <= -25){
			stairState = 1;	// stair upwards
			LED_GREEN_Put(1);
		}
		else if(stairState == 1 && angel < 5 && angel > -5){
			stairState = 2;	// on top of the stair
			RED_Put(1);
		}
		else if(stairState == 2 && angel >= 25){
			stairState = 3; // stair downwards
			LED_GREEN_Put(0);
		}
		else if(stairState == 3 && angel < 5 && angel > -5){
			stairState = 4; // stair done
			RED_Put(0);
			vTaskDelay(pdMS_TO_TICKS(20));
			done = 1;
		}
		vTaskDelay(pdMS_TO_TICKS(12));
	}
	while(!done);
	/* \todo stop doesnt work with 10ms*/
	motorsStartup(0, 0, 0);
	
	taskDone(3);
}

//Task4
void driveToTurningPlace(int8_t speed, uint8_t optRange){
	uint8_t err = ERR_OK;
	int16_t corrToF = 0;
	int16_t corrGyro = 0;
	uint8_t device;
	uint8_t done = 0;
	int16_t ToFLeft;
	int16_t ToFRight;
	if(leftParcour){
		device = TOFLEFT;
	}
	else{
		device = TOFRIGHT;
	}
	motorsStartup(speed,speed,0);
	do{
		// Regulate Motors
		err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, 0, &corrGyro);
		if(err == ERR_OK){
			err = calcPID(device, kpToF, kiToF, kdToF, optRange, &corrToF);
		}
		
		if(err == ERR_OK){
			motorsStartup(speed-corrGyro+factor*corrToF, speed+corrGyro-factor*corrToF, 2);
		}
		else{
			motorsStartup(0, 0, 0);		// error
		}
		
		// stop condition
		VL_GetDistance(TOFRIGHT, &ToFRight);
		VL_GetDistance(TOFLEFT, &ToFLeft);
		if((ToFLeft == 255 || ToFLeft == 0) && (ToFRight == 255 || ToFRight == 0)){
			done = 1;
		}
		
		vTaskDelay(pdMS_TO_TICKS(12));
	}
	while(!done);
	
	motorsStartup(0, 0, 0);
	
	taskDone(4);
}

//Task5
void driveThroughtTurningPlace(uint8_t speed, uint8_t frontdistance){
	int16_t range = 0;
	uint8_t err;
	uint8_t done = 0;
	int16_t corrGyro = 0;
	int16_t optAngel = 0;
	int8_t actualSpeed = speed;
	uint8_t partState = 0;
	RED_Put(0);
	LED_GREEN_Put(1);
	motorsStartup(speed, speed, 2);
	while(partState == 0){
		// Motor-Regulation
		 err = calcPID(GYRO, kpGyro, kiGyro, kdGyro, optAngel, &corrGyro);
		 if(err == ERR_OK){
			 motorsStartup(actualSpeed-corrGyro, actualSpeed+corrGyro, 2);
		 }
		 else{
			 // error
		 }
		 
		 // check if stair is detected
		 VL_GetDistance(TOFFRONT, &range);
		 if(range <= frontdistance && range > 0){
			 LED_GREEN_Put(0);
			 RED_Put(1);
			 done = 1;
		 }
		 
		 vTaskDelay(pdMS_TO_TICKS(12));
	}
	motorsStartup(0, 0, 0);
	RED_Put(0);
	taskDone(2);
}

void initDriving(uint8_t kpT, uint8_t kiT, uint8_t kdT, uint8_t kpG, uint8_t kiG, uint8_t kdG, bool isLeftParcour){
	leftParcour = isLeftParcour;
	if(leftParcour){
		factor = 1;
	}
	else{
		factor = -1;
	}
	kpToF = kpT;
	kiToF = kiT;
	kdToF = kdT;
	kpGyro = kpG;
	kiGyro = kiG;
	kdGyro = kdG;
	
}

