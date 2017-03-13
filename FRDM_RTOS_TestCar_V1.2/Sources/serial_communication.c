/*
 * serial_communication.c
 *
 *  Created on: Feb 23, 2017
 *      Author: pirzi
 */

#include "serial_communication.h"
#include "frtos_tasks.h"
#include "L3G.h"
#include "RED.h"
#include "LED_GREEN.h"
#include "VL6180X.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "driving.h"
#include "MMA1.h"
#include <math.h>


#define PI 3.14159265
#define RXBUFSIZE 48

uint8_t state;
bool leftParcour;
static int app_value = 0;
static int app_start = 0;

static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t tmp;
  const uint8_t *p;
  uint8_t buf[16];

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "app help")==0) {
    CLS1_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of app commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  val <number>", (const unsigned char*)"Set value\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  start <number>", (const unsigned char*)"Set 1 to start char\r\n", io->stdOut);
    *handled = TRUE;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "app status")==0)) {
    CLS1_SendStatusStr((unsigned char*)"app", (const unsigned char*)"\r\n", io->stdOut);
    UTIL1_Num32sToStr(buf, sizeof(buf), app_value);
    UTIL1_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
    CLS1_SendStatusStr((const uint8_t*)"  val", buf, io->stdOut);
    UTIL1_Num32sToStr(buf, sizeof(buf), app_start);						// app_start
    UTIL1_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
    CLS1_SendStatusStr((const uint8_t*)"  start", buf, io->stdOut);
    
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "app val", sizeof("app val")-1)==0) {
    p = cmd+sizeof("app val")-1;
    res = UTIL1_xatoi(&p, &tmp);
    if (res==ERR_OK) {
      app_value = tmp;
      *handled = TRUE;
    }
    return res;
  } else if (UTIL1_strncmp((char*)cmd, "app start", sizeof("app start")-1)==0){
	  p = cmd+sizeof("app start")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  app_start = tmp;
		  *handled = TRUE;
	  }
  }
  return res;
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand, /* default shell parser */
  ParseCommand, /* my own shell parser */
  NULL /* Sentinel, must be last */
};



void startCommunication(void){
	int16_t angelX = 0;
	int16_t angelZ = 0;
	int8_t err = ERR_OK;
	unsigned char RXbuffer[RXBUFSIZE];
	
	vTaskDelay(pdMS_TO_TICKS(1000));
	
	app_value = 0;
	RXbuffer[0] = '\0';
	(void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable); /* write help */
	while(!app_start){
		LED_GREEN_Put(1);
		(void)CLS1_ReadAndParseWithCommandTable(RXbuffer, sizeof(RXbuffer), CLS1_GetStdio(), CmdParserTable);
	}
	LED_GREEN_Put(0);
	
	RED_Put(1);
	//ToF Init
	while(VL_Init()!=ERR_OK){
		VL_Init();
	}
	
	// Gyro Init
	L3Ginit();
	calculateOffset();
	
	// Start GyroTask
	CreateGyroTask();
	
	
	//Accel init
	while(MMA1_Enable() != ERR_OK){
		MMA1_Enable();
	}
	while(MMA1_Init() != ERR_OK){
		MMA1_Init();
	}
	MMA1_CalibrateX1g();
	MMA1_CalibrateY1g();
	MMA1_CalibrateZ1g();
	
	RED_Put(0);
	
	
	leftParcour = 1;		// temporär
	state = 1;				// temporär
	
	//Main part
	for(;;){
		
		(void)CLS1_ReadAndParseWithCommandTable(RXbuffer, sizeof(RXbuffer), CLS1_GetStdio(), CmdParserTable);
		
		L3GgetDegree('x', &angelX);
		if(state == 2){
			L3GgetDegree('z', &angelZ);
		}
		
		
		FRTOS1_taskENTER_CRITICAL();
		CLS1_SendNum16s(angelX, CLS1_GetStdio()->stdOut);
		CLS1_SendStr((uint8_t*)", ", CLS1_GetStdio()->stdOut);
		CLS1_SendNum16s(angelZ, CLS1_GetStdio()->stdOut);
		//CLS1_SendStr((uint8_t*)", ", CLS1_GetStdio()->stdOut);
		//CLS1_SendNum16s(newPitch, CLS1_GetStdio()->stdOut);
		CLS1_SendStr((uint8_t*)"\n\r", CLS1_GetStdio()->stdOut);
		FRTOS1_taskEXIT_CRITICAL();
		
		refreshTasks();
		
		vTaskDelay(pdMS_TO_TICKS(300));
	}
}

void taskDone(uint8_t taskNbr){
	state = taskNbr;
}

void readGyro(void){
	uint8_t i;
	//read the gyro
	for(i=0; i<32; i++){
		L3Gread('x');
		if(state == 2){
			L3Gread('z');
		}
	}
	vTaskDelay(pdMS_TO_TICKS(100));
}

void refreshTasks(void){
	  switch(state){
	  case 1: initDriving(11, 0, 3, 30, 0, 40, leftParcour);	//11 0 3 30 0 40
		  	  CreateTask2();	// drive to stair
	  break;
	  case 2: CreateTask3();	// drive over stair to entanglement (verschränkung)
	  break;
	  case 3: CreateTask4();	// drive over gully to seesaw 
	  break;
	  case 4: CreateTask5();	// drive throught turningpoint to gully 
	  break;
	  case 5: CreateTask6();	// drive to end zone
	  break;
	  case 6: CreateTask7();	// push the button
	  break;
	  
	  	  	  	  	  	  	  	  //push the right button
	  default: ; //error
	  }
}

