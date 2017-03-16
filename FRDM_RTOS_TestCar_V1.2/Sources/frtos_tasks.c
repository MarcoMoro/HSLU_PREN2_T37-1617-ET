
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include "TSK1.h"
#include "FRTOS1.h"
#include "frtos_tasks.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

#include "RED.h"
#include "LED_GREEN.h"
#include <stdlib.h>
#include "serial_communication.h"
#include "driving.h"
#include "serial_communication.h"

uint8_t Task2Started;
uint8_t Task3Started;
uint8_t Task4Started;
uint8_t	Task5Started;
uint8_t Task6Started;
uint8_t Task7Started;
uint8_t GyroTaskStarted;

static portTASK_FUNCTION(Task1Task, pvParameters) {

  /* Write your task initialization code here ... */
(void) pvParameters;

  for(;;) {
    /* Write your task code here ... */
	  startCommunication();
    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  }
  /* Destroy the task */
  vTaskDelete(Task1Task);
}

static portTASK_FUNCTION(Task2Task, pvParameters) {

  /* Write your task initialization code here ... */
(void) pvParameters;
  //for(;;) {
    /* Write your task code here ... */

	  driveToStair(50, 150, 200);
	  vTaskDelay(pdMS_TO_TICKS(1));
	  FRTOS1_vTaskSuspend(NULL);

    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  //}
  /* Destroy the task */
  FRTOS1_vTaskDelete(Task2Task);
}

static portTASK_FUNCTION(Task3Task, pvParameters) {

  /* Write your task initialization code here ... */
	(void)pvParameters;
  //for(;;) {
    /* Write your task code here ... */
	  
		
		driveOverStair(50, 150);
		vTaskDelay(pdMS_TO_TICKS(1));
		FRTOS1_vTaskSuspend(NULL);

    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  //}
  /* Destroy the task */
  vTaskDelete(Task3Task);
}

static portTASK_FUNCTION(Task4Task, pvParameters) {

  /* Write your task initialization code here ... */
(void) pvParameters;
  //for(;;) {
    /* Write your task code here ... */
	  driveToTurningPlace(50, 150);
	  vTaskDelay(pdMS_TO_TICKS(1));
	  FRTOS1_vTaskSuspend(NULL);
    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  //}
  /* Destroy the task */
  vTaskDelete(Task4Task);
}

static portTASK_FUNCTION(Task5Task, pvParameters) {

  /* Write your task initialization code here ... */
(void) pvParameters;
  //for(;;) {
    /* Write your task code here ... */

	driveThroughtTurningPlace(50, 190, 200);
	vTaskDelay(pdMS_TO_TICKS(1));
	FRTOS1_vTaskSuspend(NULL);
    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  //}
  /* Destroy the task */
  vTaskDelete(Task5Task);
}

static portTASK_FUNCTION(Task6Task, pvParameters) {

  /* Write your task initialization code here ... */
(void) pvParameters;
  //for(;;) {
    /* Write your task code here ... */
	driveToEndZone(50, 150);
	vTaskDelay(pdMS_TO_TICKS(1));
	FRTOS1_vTaskSuspend(NULL);
    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  //}
  /* Destroy the task */
  vTaskDelete(Task6Task);
}

static portTASK_FUNCTION(Task7Task, pvParameters) {

  /* Write your task initialization code here ... */
(void) pvParameters;
  //for(;;) {
    /* Write your task code here ... */
	pushTheButton(3, 190);
	vTaskDelay(pdMS_TO_TICKS(1));
	vTaskSuspend(NULL);

    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  //}
  /* Destroy the task */
  vTaskDelete(Task7Task);
}


static portTASK_FUNCTION(GyroTask, pvParameters) {

  /* Write your task initialization code here ... */
(void) pvParameters;
  	for(;;) {
    /* Write your task code here ... */
	
  		uint8_t i;
  		//read the gyro
  		for(i=0; i<32; i++){
  			L3Gread('x');
  			if(comGetState() == 2){
  				L3Gread('z');
  			}
  		}
  		vTaskDelay(pdMS_TO_TICKS(100));

    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  }
  /* Destroy the task */
  vTaskDelete(Task7Task);
}

void CreateTasks(void) {
  if (FRTOS1_xTaskCreate(
	 Task1Task,  /* pointer to the task */
	  "Task1", /* task name for kernel awareness debugging */
	  configMINIMAL_STACK_SIZE + 0, /* task stack size */
	  (void*)NULL, /* optional task startup argument */
	  tskIDLE_PRIORITY + 3,  /* initial priority */
	  (xTaskHandle*)NULL /* optional task handle to create */
	) != pdPASS) {
	  /*lint -e527 */
	  for(;;){}; /* error! probably out of memory */
	  /*lint +e527 */
  }
}

void CreateTask2(void){
	if(!Task2Started){
	  if (FRTOS1_xTaskCreate(
		 Task2Task,  /* pointer to the task */
		  "Task2", /* task name for kernel awareness debugging */
		  configMINIMAL_STACK_SIZE + 0, /* task stack size */
		  (void*)NULL, /* optional task startup argument */
		  tskIDLE_PRIORITY + 4,  /* initial priority */
		  (xTaskHandle*)NULL /* optional task handle to create */
		) != pdPASS) {
		  /*lint -e527 */
		  for(;;){}; /* error! probably out of memory */
		  /*lint +e527 */
	  }
	}
	Task2Started = 1;
}

void CreateTask3(void){
	if(!Task3Started){
	  if (FRTOS1_xTaskCreate(
		 Task3Task,  /* pointer to the task */
		  "Task3", /* task name for kernel awareness debugging */
		  configMINIMAL_STACK_SIZE + 0, /* task stack size */
		  (void*)NULL, /* optional task startup argument */
		  tskIDLE_PRIORITY + 4,  /* initial priority */
		  (xTaskHandle*)NULL /* optional task handle to create */
		) != pdPASS) {
		  /*lint -e527 */
		  for(;;){}; /* error! probably out of memory */
		  /*lint +e527 */
	  }
	}
	Task3Started = 1;
}

void CreateTask4(void){
	if(!Task4Started){
	  if (FRTOS1_xTaskCreate(
		 Task4Task,  /* pointer to the task */
		  "Task4", /* task name for kernel awareness debugging */
		  configMINIMAL_STACK_SIZE + 0, /* task stack size */
		  (void*)NULL, /* optional task startup argument */
		  tskIDLE_PRIORITY + 4,  /* initial priority */
		  (xTaskHandle*)NULL /* optional task handle to create */
		) != pdPASS) {
		  /*lint -e527 */
		  for(;;){}; /* error! probably out of memory */
		  /*lint +e527 */
	  }
	}
	Task4Started = 1;
}

void CreateTask5(void){
	if(!Task5Started){
	  if (FRTOS1_xTaskCreate(
		 Task5Task,  /* pointer to the task */
		  "Task5", /* task name for kernel awareness debugging */
		  configMINIMAL_STACK_SIZE + 0, /* task stack size */
		  (void*)NULL, /* optional task startup argument */
		  tskIDLE_PRIORITY + 4,  /* initial priority */
		  (xTaskHandle*)NULL /* optional task handle to create */
		) != pdPASS) {
		  /*lint -e527 */
		  for(;;){}; /* error! probably out of memory */
		  /*lint +e527 */
	  }
	}
	Task5Started = 1;
}

void CreateTask6(void){
	if(!Task6Started){
		if (FRTOS1_xTaskCreate(
		 Task6Task,  /* pointer to the task */
		  "Task6", /* task name for kernel awareness debugging */
		  configMINIMAL_STACK_SIZE + 0, /* task stack size */
		  (void*)NULL, /* optional task startup argument */
		  tskIDLE_PRIORITY + 4,  /* initial priority */
		  (xTaskHandle*)NULL /* optional task handle to create */
		) != pdPASS) {
		  /*lint -e527 */
		  for(;;){}; /* error! probably out of memory */
		  /*lint +e527 */
	  }
	}
	Task6Started = 1;
}

void CreateTask7(void){
	if(!Task7Started){
	  if (FRTOS1_xTaskCreate(
		 Task7Task,  /* pointer to the task */
		  "Task7", /* task name for kernel awareness debugging */
		  configMINIMAL_STACK_SIZE + 0, /* task stack size */
		  (void*)NULL, /* optional task startup argument */
		  tskIDLE_PRIORITY + 4,  /* initial priority */
		  (xTaskHandle*)NULL /* optional task handle to create */
		) != pdPASS) {
		  /*lint -e527 */
		  for(;;){}; /* error! probably out of memory */
		  /*lint +e527 */
	  }
	}
	Task7Started = 1;
}

void CreateGyroTask(void){
	if(!GyroTaskStarted){
	  if (FRTOS1_xTaskCreate(
		 GyroTask,  /* pointer to the task */
		  "Gyro", /* task name for kernel awareness debugging */
		  configMINIMAL_STACK_SIZE + 0, /* task stack size */
		  (void*)NULL, /* optional task startup argument */
		  tskIDLE_PRIORITY + 5,  /* initial priority */
		  (xTaskHandle*)NULL /* optional task handle to create */
		) != pdPASS) {
		  /*lint -e527 */
		  for(;;){}; /* error! probably out of memory */
		  /*lint +e527 */
	  }
	}
	GyroTaskStarted = 1;
}

