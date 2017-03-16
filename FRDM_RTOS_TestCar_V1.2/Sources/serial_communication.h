/*
 * serial_communication.h
 *
 *  Created on: Feb 23, 2017
 *      Author: pirzi
 */

#ifndef SERIAL_COMMUNICATION_H_
#define SERIAL_COMMUNICATION_H_

#include <stdlib.h>
#include "CLS1.h"


static const CLS1_ParseCommandCallback CmdParserTable[];


void startCommunication(void);

void refreshTasks(void);
void taskDone(uint8_t taskNbr);
void readGyro(void);
static uint8_t ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
uint8_t initAllDevices(void);
void sendStatus(void);
void readValues(void);
uint8_t comGetState();


#endif /* SERIAL_COMMUNICATION_H_ */
