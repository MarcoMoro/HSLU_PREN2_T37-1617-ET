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
#include "FRTOS1.h"
#include "driving.h"
#include "MMA1.h"
#include <math.h>
#include "motor.h"


#define PI 3.14159265
#define RXBUFSIZE 48

uint8_t res;

// Comunication values reads
static bool hello = TRUE;
static bool start = FALSE;		// startbefehl
static bool course = NULL;		// fahrbanwahl	links->true rechts->false
static int16_t tof_l_s = 0;	// tof_links_sollwert
static int16_t tof_r_s = 0;	// tof_rechts_sollwert
static int16_t tof_f_s = 0;	// tof_front_sollwert
static int8_t 	raupe_i_l = 0;	// raupe ist links
static int8_t	raupe_i_r = 0;	// raupe ist rechts
static uint8_t	gyroskop_s = 0; // gyroskop soll
static uint8_t	servo_s = 0;	// servo soll
static uint8_t	letter = 0;		// buchstabe

// Comunication values writes
static int16_t tof_l_i = 0;
static int16_t tof_r_i = 0;
static int16_t tof_f_i = 0;
static int8_t	raupe_l_i = 0;
static int8_t	raupe_r_i = 0;
static int16_t gyro_n = 0;
static int16_t gyro_g = 0;
static uint8_t 	gyroskop_i = 0;
static uint8_t 	servo_i = 0;
static uint8_t 	state = 1;
static uint8_t 	errState = ERR_OK;


static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand, /* default shell parser */
  ParseCommand, /* my own shell parser */
  NULL /* Sentinel, must be last */
};




void startCommunication(void){
	unsigned char RXbuffer[RXBUFSIZE];
	RXbuffer[0] = '\0';
	
	//Say hello to Raspberry Pi
	while(hello){
		(void)CLS1_ReadAndParseWithCommandTable(RXbuffer, sizeof(RXbuffer), CLS1_GetStdio(), CmdParserTable);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
	// confirm hello
	  CLS1_SendStr((uint8_t*)"hello,", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum8u(1, CLS1_GetStdio()->stdOut);
	  CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	
	  // Init devices
	errState = initAllDevices();
	
	// Wait until start
	while(!start){
		LED_GREEN_Put(1);
		(void)CLS1_ReadAndParseWithCommandTable(RXbuffer, sizeof(RXbuffer), CLS1_GetStdio(), CmdParserTable);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
	// confirm start
	  CLS1_SendStr((uint8_t*)"start,", CLS1_GetStdio()->stdOut);
	  CLS1_SendNum8u(start, CLS1_GetStdio()->stdOut);
	  CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	  
	LED_GREEN_Put(0);

	//Loop
	for(;;){
		
		(void)CLS1_ReadAndParseWithCommandTable(RXbuffer, sizeof(RXbuffer), CLS1_GetStdio(), CmdParserTable);
		readValues();
		//sendStatus();
		sendStatusBT();
		refreshTasks();
		
		vTaskDelay(pdMS_TO_TICKS(300));
	}
}

void taskDone(uint8_t taskNbr){
	state = taskNbr;
}

uint8_t comGetState(){
	return state;
}

void refreshTasks(void){
	  switch(state){
	  case 1: initDriving(11, 0, 3, 30, 0, 40, course);	//11 0 3 30 0 40
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

/* Comunication values
static bool start = FALSE;		// startbefehl
static bool course = NULL;		// fahrbanwahl
static uint16_t tof_l_s = 0;	// tof_links_sollwert
static uint16_t tof_r_s = 0;	// tof_rechts_sollwert
static uint16_t tof_f_s = 0;	// tof_front_sollwert
static int8_t 	raupe_i_l = 0;	// raupe ist links
static int8_t	raupe_i_r = 0;	// raupe ist rechts
static uint8_t	gyroskop_s = 0; // gyroskop soll
static uint8_t	servo_s = 0;	// servo soll
static uint8_t	letter = 0;		// buchstabe
*/
static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t tmp;
  const uint8_t *p;
  uint8_t buf[16];

  
  //Help
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "help")==0) {
	//FRTOS1_taskENTER_CRITICAL(); ////////CRITICAL///////////
		CLS1_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of app commands\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  hello,<bool>", (const unsigned char*)"True->FRDM, False->RBI\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  start,<bool>", (const unsigned char*)"Set 1 to start\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  course,<bool>", (const unsigned char*)"true->links, false->rechts\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  tof_l_s,<uint16>", (const unsigned char*)"tof_links_sollwert\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  tof_r_s,<uint16>", (const unsigned char*)"tof_rechts_sollwert\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  tof_f_s,<uint16>", (const unsigned char*)"tof_front_sollwert\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  raupe_i_l,<int8>", (const unsigned char*)"raupe_links_ist\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  raupe_i_r,<int8>", (const unsigned char*)"raupe_rechts_ist\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  gyroskop_s,<uint8_t>", (const unsigned char*)"gyroskop_soll\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  servo_s,<uint8_t>", (const unsigned char*)"servo_soll\n", io->stdOut);
		CLS1_SendHelpStr((unsigned char*)"  letter,<uint8_t>", (const unsigned char*)"letter_to_push\n", io->stdOut);
   // FRTOS1_taskEXIT_CRITICAL();	///////////Critical End//////////////
    *handled = TRUE;
    //Status
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "status")==0)) {
	CLS1_SendStatusStr((unsigned char*)"app", (const unsigned char*)"\n", io->stdOut);
	// start
	UTIL1_Num32sToStr(buf, sizeof(buf), start);						
	UTIL1_strcat(buf, sizeof(buf), (const unsigned char*)"\n");
	CLS1_SendStatusStr((const uint8_t*)"  start,", buf, io->stdOut);
    *handled = TRUE;
    // command handling
  } else if (UTIL1_strncmp((char*)cmd, "hello,", sizeof("hello,")-1)==0){		//Start
	  p = cmd+sizeof("hello,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  hello = tmp;
		  *handled = TRUE;
	  }
  }else if (UTIL1_strncmp((char*)cmd, "start,", sizeof("start,")-1)==0){		//Start
	  p = cmd+sizeof("start,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  start = tmp;
		  *handled = TRUE;
	  }
  }else if (UTIL1_strncmp((char*)cmd, "course,", sizeof("course,")-1)==0){		// Course
	  p = cmd+sizeof("course,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  course = tmp;
		  //bestätigen
		  CLS1_SendStr((uint8_t*)"course,", CLS1_GetStdio()->stdOut);
		  CLS1_SendNum8u(course, CLS1_GetStdio()->stdOut);
		  CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
		  *handled = TRUE;
	  }
}else if (UTIL1_strncmp((char*)cmd, "tof_l_s,", sizeof("tof_l_s,")-1)==0){		// tof_l_s
	  p = cmd+sizeof("tof_l_s,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  tof_l_s = tmp;
		  *handled = TRUE;
	  }
}else if (UTIL1_strncmp((char*)cmd, "tof_r_s,", sizeof("tof_r_s,")-1)==0){		// tof_r_s
	  p = cmd+sizeof("tof_r_s,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  tof_r_s = tmp;
		  *handled = TRUE;
	  }
}else if (UTIL1_strncmp((char*)cmd, "tof_f_s,", sizeof("tof_f_s,")-1)==0){		// tof_f_s
	  p = cmd+sizeof("tof_f_s,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  tof_f_s = tmp;
		  *handled = TRUE;
	  }
}else if (UTIL1_strncmp((char*)cmd, "raupe_i_l,", sizeof("raupe_i_l,")-1)==0){		// raupe_i_l
	  p = cmd+sizeof("raupe_i_l,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  raupe_i_l = tmp;
		  *handled = TRUE;
	  }
}else if (UTIL1_strncmp((char*)cmd, "raupe_i_r,", sizeof("raupe_i_r,")-1)==0){		// raupe_i_r
	  p = cmd+sizeof("raupe_i_r,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  raupe_i_r = tmp;
		  *handled = TRUE;
	  }
}else if (UTIL1_strncmp((char*)cmd, "gyroskop_s,", sizeof("gyroskop_s,")-1)==0){		// gyroskop_s
	  p = cmd+sizeof("gyroskop_s,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  gyroskop_s = tmp;
		  *handled = TRUE;
	  }
}else if (UTIL1_strncmp((char*)cmd, "servo_s,", sizeof("servo_s,")-1)==0){		// servo_s
	  p = cmd+sizeof("servo_s,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  servo_s = tmp;
		  *handled = TRUE;
	  }
}else if (UTIL1_strncmp((char*)cmd, "letter,", sizeof("letter,")-1)==0){		// letter
	  p = cmd+sizeof("letter,")-1;
	  res = UTIL1_xatoi(&p, &tmp);
	  if(res==ERR_OK){
		  letter = tmp;
		  *handled = TRUE;
	  }
	  // bestätigen
		  CLS1_SendStr((uint8_t*)"letter,", CLS1_GetStdio()->stdOut);
		  CLS1_SendNum8u(letter, CLS1_GetStdio()->stdOut);
		  CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
}
  return res;
}

uint8_t initAllDevices(void){
	uint8_t err = ERR_OK;
	RED_Put(1);
		//ToF Init
		while(VL_Init()!=ERR_OK){
			VL_Init();
		}
		
		/*
		// Set scaling of ToF Frong to 2
		  res = VL6180XsetScaling(1, TOFFRONT);
		  if(res != ERR_OK){
		      CLS1_SendStr("ERROR: Failed scaling of TOF device: ", CLS1_GetStdio()->stdErr);
		      CLS1_SendNum8u(TOFFRONT, CLS1_GetStdio()->stdErr);
		      CLS1_SendStr("\r\n", CLS1_GetStdio()->stdErr);
		  }
		  int16_t range;
		  for(;;){
			  VL_GetDistance(TOFFRONT, &range);
				FRTOS1_taskENTER_CRITICAL();
				CLS1_SendNum16s(range, CLS1_GetStdio()->stdOut);
				CLS1_SendStr((uint8_t*)"\n\r", CLS1_GetStdio()->stdOut);
				FRTOS1_taskEXIT_CRITICAL();
				vTaskDelay(pdMS_TO_TICKS(300));
		  }
		  */
		
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
		
		return err;
}

/*
 * // Comunication values writes
static int16_t tof_l_i = 0;
static int16_t tof_r_i = 0;
static int16_t tof_f_i = 0;
static int8_t	raupe_l_i = 0;
static int8_t	raupe_r_i = 0;
static int16_t gyro_n = 0;
static int16_t gyro_g = 0;
static uint8_t 	gyroskop_i = 0;
static uint8_t 	servo_i = 0;
static uint8_t 	state = 0;
static uint8_t 	errState = ERR_OK;
 */
void sendStatus(void){
	CLS1_SendStr((uint8_t*)"tof_l_i,", CLS1_GetStdio()->stdOut);		// tof_l_i
	CLS1_SendNum16s(tof_l_i, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"tof_r_i,", CLS1_GetStdio()->stdOut);		// tof_r_i
	CLS1_SendNum16s(tof_r_i, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"tof_f_i,", CLS1_GetStdio()->stdOut);		// tof_f_i
	CLS1_SendNum16s(tof_f_i, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"raupe_l_i,", CLS1_GetStdio()->stdOut);		// raupe_l_i
	CLS1_SendNum8s(raupe_l_i, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"raupe_r_i,", CLS1_GetStdio()->stdOut);		// raupe_r_i
	CLS1_SendNum8s(raupe_r_i, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"gyro_n,", CLS1_GetStdio()->stdOut);			// gyro_n
	CLS1_SendNum16s(gyro_n, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"gyro_g,", CLS1_GetStdio()->stdOut);			// gyro_g
	CLS1_SendNum16s(gyro_g, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"gyroskop_i,", CLS1_GetStdio()->stdOut);		// gyroskop_i
	CLS1_SendNum16u(gyroskop_i, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"servo_i,", CLS1_GetStdio()->stdOut);		// servo_i
	CLS1_SendNum16u(servo_i, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"state,", CLS1_GetStdio()->stdOut);			// state
	CLS1_SendNum16u(state, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"errState,", CLS1_GetStdio()->stdOut);		// errState
	CLS1_SendNum16u(errState, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
}

void readValues(void){
	tof_l_i = VL_GetLastDistance(TOFLEFT);
	tof_r_i = VL_GetLastDistance(TOFRIGHT);
	tof_f_i = VL_GetLastDistance(TOFFRONT);
	raupe_l_i = (int8_t)motorGetPWMLeft();
	raupe_r_i = (int8_t)motorGetPWMRight();
	L3GgetDegree('x', &gyro_g);
	L3GgetDegree('z', &gyro_n);
	// \todo gyroskop_i =....
	// \todo servo_i = ...
	
}

void sendStatusBT(void){
	// gyro_g
	CLS1_SendNum16s(gyro_g, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)",", CLS1_GetStdio()->stdOut);
	// gyro_n
	CLS1_SendNum16s(gyro_n, CLS1_GetStdio()->stdOut);
	CLS1_SendStr((uint8_t*)"\n", CLS1_GetStdio()->stdOut);
}
