/*
 * driving.h
 *
 *  Created on: Feb 23, 2017
 *      Author: pirzi
 */

#ifndef DRIVING_H_
#define DRIVING_H_

/*
 * Drive stright to the stair
 * @param [in] speed, speed of the motors
 * @param [in] startupTime time from 0 to speed
 * @param [in] frontdistance drive until this range is detected
 */
void driveToStair(int8_t speed, uint8_t startupTime, uint16_t frontdistance);
void driveOverStair(uint8_t device, int8_t speed, uint8_t optRange, uint8_t kp, uint8_t ki, uint8_t kd);


#endif /* DRIVING_H_ */
