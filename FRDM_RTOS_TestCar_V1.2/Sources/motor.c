/*
 * motor.c
 *
 *  Created on: Dec 7, 2016
 *      Author: pirzi
 */
#include "motor.h"
#include <stdlib.h>
#include "FRTOS1.h"


#define MOTOR_OFFSET	0
#define MODULO          (0xFFFF-1)


static int16_t pwmLeft;
static int16_t pwmRight;

/**
 * returns the pwm value of the left motor
 * 
 * @returns
 *    the value 0..+/-127
 */
int8_t motorGetPWMLeft(void)
{
  return pwmLeft;
}

/**
 * returns the pwm value of the right motor
 * 
 * @returns
 *    the value 0..+/-127
 */
int8_t motorGetPWMRight(void)
{
  return pwmRight;
}

/**
 * increments the speed of the left motor
 * 
 * @param [in] value
 *    the desired offset
 */
void motorIncrementPWMLeft(int8_t value)
{
  int8_t v = pwmLeft + value;
  if (v > 127) v = 127;
  if (v < -127) v = -127;
  motorSetPWMLeft((int8_t)v);
}


/**
 * increments the speed of the right motor
 * 
 * @param [in] value
 *    the desired offset
 */
void motorIncrementPWMRight(int8_t value)
{
  int8_t v = pwmRight + value;
  if (v > 127) v = 127;
  if (v < -127) v = -127;
  motorSetPWMRight((int8_t)v);
}


/**
 * sets the speed of the left motor
 * 
 * @param [in] value
 *  +1..+127 => speed in forward direction
 *  -1..-127 => speed in backward direction
 *  0 => stop
 */
void motorSetPWMLeft(int8_t value)
{
  if (value < 0)              // backward
  {
	  if (value < -127) value = -127;
    DIR_LEFT_PutVal(DIR_LEFT_DeviceData,1);
    PWM_LEFT_SetRatio16(MODULO/127*(-value));
  }
  else if (value > 0)         // forward
  {
	  if (value > 127) value = 127;
	DIR_LEFT_PutVal(DIR_LEFT_DeviceData,0);
	PWM_LEFT_SetRatio16(MODULO/127*value);
  } 
  else                        // stop
  {
	  PWM_LEFT_SetRatio16(0);
	  }
  pwmLeft = value;
}

/**
 * sets the speed of the right motor
 * 
 * @param [in] value
 *  +1..+127 => speed in forward direction
 *  -1..-127 => speed in backward direction
 *  0 => stop
 */
void motorSetPWMRight(int8_t value)
{
	  if (value < 0)              // backward
	  {
		  if (value < -127) value = -127;
	    DIR_RIGHT_PutVal(DIR_RIGHT_DeviceData,0);
	    PWM_RIGHT_SetRatio16(MODULO/127*(-value));
	  }
	  else if (value > 0)         // forward
	  {
		  if (value > 127) value = 127;
		DIR_RIGHT_PutVal(DIR_RIGHT_DeviceData,1);
		PWM_RIGHT_SetRatio16(MODULO/127*value);
	  } 
	  else                        // stop
	  {
		  PWM_RIGHT_SetRatio16(0);
	  }  
	  pwmRight = value;
}

/**
 * Increment or decrement the speed of the motor in a specified time
 * 
 * @param [in] value
 *  +1..+127 => speed in forward direction
 *  -1..-127 => speed in backward direction
 *  0 => stop
 *  @param [in] time
 *  time in witch the motor has to reach the speed of value (in ms)
 */
void motorStartupRight(int8_t value, uint8_t time){
	int8_t dif = value - pwmRight; 
	uint8_t i;
	int8_t increment = dif/abs(dif);
	for(i = 0; i <= abs(dif); i++){
		motorIncrementPWMRight(increment);
		FRTOS1_vTaskDelay(pdMS_TO_TICKS(abs(dif)/time));
	}
}

/**
 * Increment or decrement the speed of the motor in a specified time
 * 
 * @param [in] value
 *  +1..+127 => speed in forward direction
 *  -1..-127 => speed in backward direction
 *  0 => stop
 *  @param [in] time
 *  time in witch the motor has to reach the speed of value (in ms)
 */
void motorStartupLeft(int8_t value, uint8_t time){
	int8_t dif = value - pwmLeft; 
	uint8_t i;
	int8_t increment = dif/abs(dif);
	for(i = 0; i <= abs(dif); i++){
		motorIncrementPWMLeft(increment);
		vTaskDelay(pdMS_TO_TICKS(abs(dif)/time));
	}
}

/**
 * Increment or decrement the speed of the motors in a specified time
 * 
 * @param [in] valueLeft
 *  +1..+127 => speed in forward direction
 *  -1..-127 => speed in backward direction
 *  0 => stop
 *  @param [in] valueRight
 *  +1..+127 => speed in forward direction
 *  -1..-127 => speed in backward direction
 *  0 => stop
 *  @param [in] time
 *  time in witch the motor has to reach the speed of value (in ms)
 */
void motorsStartup(int16_t valueLeft, int16_t valueRight, uint16_t time){
	if(valueLeft>127){
		valueLeft = 127;
	}else if(valueLeft<-127){
		valueLeft = -127;
	}
	if(valueRight>127){
		valueRight = 127;
	}else if(valueRight<-127){
		valueRight = -127;
	}
	
	
	if(time > 0){
	int8_t incrementLeft = (valueLeft - pwmLeft)/time;
	int8_t incrementRight = (valueRight - pwmRight)/time;
	uint8_t i;
		for(i = 1; i <= time; i++){
			//motorSetPWMRight(pwmRight+incrementRight*i);
			//motorSetPWMLeft(pwmLeft+incrementLeft*i);
			motorIncrementPWMLeft(incrementLeft);	
			motorIncrementPWMRight(incrementRight);
			vTaskDelay(pdMS_TO_TICKS(1));
		}
	}

	motorSetPWMRight(valueRight);
	motorSetPWMLeft(valueLeft);
}
