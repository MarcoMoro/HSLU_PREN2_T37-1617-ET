/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PWM_RIGHT.h
**     Project     : FRDM_RTOS_TestCar_V1.2
**     Processor   : MKL25Z128VLK4
**     Component   : PWM
**     Version     : Component 02.240, Driver 01.01, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-05-12, 23:58, # CodeGen: 246
**     Abstract    :
**         This component implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
**     Settings    :
**         Used output pin             : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       15            |  ADC0_DP3/ADC0_SE3/PTE22/TPM2_CH0/UART2_TX
**             ----------------------------------------------------
**
**         Timer name                  : TPM2_CNT [16-bit]
**         Counter                     : TPM2_CNT  [0x4003A004]
**         Mode register               : TPM2_SC   [0x4003A000]
**         Run register                : TPM2_SC   [0x4003A000]
**         Prescaler                   : TPM2_SC   [0x4003A000]
**         Compare register            : TPM2_C0V  [0x4003A010]
**         Flip-flop register          : TPM2_C0SC [0x4003A00C]
**
**         Interrupt name              : INT_TPM2
**         Interrupt enable reg.       : TPM2_C1SC [0x4003A014]
**         Priority                    : 2
**         User handling procedure     : PWM_RIGHT_OnEnd
**         This event is called when the 1 of cycles is generated
**
**         Port name                   : PTE
**         Bit number (in port)        : 22
**         Bit mask of the port        : 0x00400000
**         Port data register          : GPIOE_PDOR [0x400FF100]
**         Port control register       : GPIOE_PDDR [0x400FF114]
**
**         Initialization:
**              Output level           : low
**              Timer                  : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-[driven by slave component]
**             Clock                   : [driven by slave component] Hz
**           Initial value of            period     pulse width
**             Xtal ticks              : ---        ---
**             microseconds            : ---        0
**             milliseconds            : 12         ---
**             seconds                 : ---        ---
**             seconds (real)          : 12.5       0
**
**     Contents    :
**         SetRatio8  - byte PWM_RIGHT_SetRatio8(byte Ratio);
**         SetRatio16 - byte PWM_RIGHT_SetRatio16(word Ratio);
**         SetDutyUS  - byte PWM_RIGHT_SetDutyUS(word Time);
**         SetDutyMS  - byte PWM_RIGHT_SetDutyMS(word Time);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file PWM_RIGHT.h
** @version 01.01
** @brief
**         This component implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
*/         
/*!
**  @addtogroup PWM_RIGHT_module PWM_RIGHT module documentation
**  @{
*/         

#ifndef __PWM_RIGHT_H
#define __PWM_RIGHT_H

/* MODULE PWM_RIGHT. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "PwmLdd1.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 


#define PWM_RIGHT_PERIOD_VALUE PwmLdd1_PERIOD_VALUE /* Initial period value in ticks of the timer. It is available only if the bean is enabled in high speed mode. */
#define PWM_RIGHT_PERIOD_VALUE_HIGH PwmLdd1_PERIOD_VALUE_0 /* Period value in ticks of the timer in high speed mode. It is available only if the bean is enabled in high speed mode. */


/*
** ===================================================================
**     Method      :  PWM_RIGHT_OnEnd (component PWM)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PwmLdd1_OnEnd(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  PWM_RIGHT_SetRatio8 (component PWM)
**     Description :
**         This method sets a new duty-cycle ratio. Ratio is expressed
**         as an 8-bit unsigned integer number. 0 - FF value is
**         proportional to ratio 0 - 100%. The method is available
**         only if it is not selected list of predefined values in
**         <Starting pulse width> property. 
**         Note: Calculated duty depends on the timer capabilities and
**         on the selected period.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Ratio           - Ratio to set. 0 - 255 value is
**                           proportional to ratio 0 - 100%
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
#define PWM_RIGHT_SetRatio8(Ratio) (PwmLdd1_SetRatio8(PwmLdd1_DeviceData, Ratio))

/*
** ===================================================================
**     Method      :  PWM_RIGHT_SetRatio16 (component PWM)
**     Description :
**         This method sets a new duty-cycle ratio. Ratio is expressed
**         as a 16-bit unsigned integer number. 0 - FFFF value is
**         proportional to ratio 0 - 100%. The method is available
**         only if it is not selected list of predefined values in
**         <Starting pulse width> property. 
**         Note: Calculated duty depends on the timer possibilities and
**         on the selected period.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Ratio           - Ratio to set. 0 - 65535 value is
**                           proportional to ratio 0 - 100%
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
#define PWM_RIGHT_SetRatio16(Ratio) (PwmLdd1_SetRatio16(PwmLdd1_DeviceData, Ratio))

/*
** ===================================================================
**     Method      :  PWM_RIGHT_SetDutyUS (component PWM)
**     Description :
**         This method sets the new duty value of the output signal.
**         The duty is expressed in microseconds as a 16-bit
**         unsigned integer number.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Duty to set [in microseconds]
**                      (0 to --- us in high speed mode)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
#define PWM_RIGHT_SetDutyUS(Time) (PwmLdd1_SetDutyUS(PwmLdd1_DeviceData, Time))

/*
** ===================================================================
**     Method      :  PWM_RIGHT_SetDutyMS (component PWM)
**     Description :
**         This method sets the new duty value of the output signal.
**         The duty is expressed in milliseconds as a 16-bit
**         unsigned integer number.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Duty to set [in milliseconds]
**                      (0 to 12 ms in high speed mode)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
#define PWM_RIGHT_SetDutyMS(Time) (PwmLdd1_SetDutyMS(PwmLdd1_DeviceData, Time))

/* END PWM_RIGHT. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __PWM_RIGHT_H */
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
