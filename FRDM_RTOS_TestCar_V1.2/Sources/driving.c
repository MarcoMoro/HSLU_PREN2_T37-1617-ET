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
#define PI 3.14159265


void driveToStair(int8_t speed, uint8_t startupTime, uint16_t frontdistance){
	uint8_t err;
	uint8_t done = 0;
	int16_t range = 0;
	int16_t corr;
	RED_Put(0);
	LED_GREEN_Put(1);
	motorsStartup(speed, speed, startupTime);
	while(!done){
		 VL_GetDistance(TOFFRONT, &range);
		 err = calcPID(3, 40, 0, 10, 0, &corr);
		 if(err == ERR_OK){
			 motorsStartup(speed-corr, speed+corr, 2);
		 }
		 else{
			 // error
		 }
		 if(range <= frontdistance && range > 0){
			 LED_GREEN_Put(0);
			 RED_Put(1);
			 motorsStartup(0, 0, startupTime);
			 done = 1;
		 }
		 refreshMovingOffset();
		 vTaskDelay(pdMS_TO_TICKS(12));
	}
	RED_Put(0);
	taskDone(2);
}

void driveOverStair(uint8_t device, int8_t speed, uint8_t optRange, uint8_t kp, uint8_t ki, uint8_t kd){
	uint8_t err = ERR_OK;
	int16_t corrToF = 0;
	int16_t corrGyro = 0;
	motorsStartup(speed,speed,0);
	do{
		err = calcPID(3, 40, 0, 10, 0, &corrGyro);
		if(err == ERR_OK){
			err = calcPID(device, 4, 0, 1, optRange, &corrToF);
		}
		
		if(err == ERR_OK){
			motorsStartup(speed-corrGyro+corrToF, speed+corrGyro-corrToF, 0);
		}
		else{
			motorsStartup(0, 0, 10);		// error
		}
		vTaskDelay(pdMS_TO_TICKS(12));
	}
	while(1);
}
