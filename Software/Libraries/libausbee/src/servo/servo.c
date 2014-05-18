/**
 ********************************************************************
 * @file    servo.c
 * @author  Luc PRAMPOLINI <luc.prampolini@gmail.com>
 * @version V1.1
 * @date    20-Dec-2013
 * @brief   This file provides functions for driving servomotors.
 ********************************************************************
 * @attention
 *
 * This file is part of LIBAUSBEE.
 * 
 * LIBAUSBEE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LIBAUSBEE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LIBAUSBEE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * <h2><centor>&copy;  Copyright 2013-2014 (C) EIRBOT </center></h2>
 ********************************************************************
 */

/* Includes */
#include <AUSBEE/servo.h>

/**
  * @addtogroup Libausbee
  * @{
  */

/**
  * @defgroup Servo
  * @brief Servo driver modules
  * @{
  */

/**
  * @defgroup Servo_Exported_Functions
  * @{
  */

/**
  * @brief  Initialize the servo parameters with default values.
  * @param  servo: pointer to a ausbeeServo structure that contains the
  *         configuration information for the specified servo.
  * @retval None
  */
void ausbeeInitStructServo(ausbeeServo* servo)
{
  servo->minValue = 30;
  servo->maxValue = 105;
  servo->TIMx = TIM2;
  servo->CHANx = TIM_Channel_1;
}

/**
  * @brief  Initialize the timer channel linked to the servo in PWM mode.
  * @param  servo: pointer to a ausbeeServo structure that contains the
  *         configuration information for the specified servo.
  * @retval None
  */
void ausbeeInitServo(ausbeeServo* servo)
{
  TIM_OCInitTypeDef OCInit_PWM; // Create a OCInitTypeDef for PWM

  TIM_OCStructInit(&OCInit_PWM);
  OCInit_PWM.TIM_OCMode = TIM_OCMode_PWM1;  // Set PWM Mode
  OCInit_PWM.TIM_Pulse = 50;                // Duty cycle to 5%
  OCInit_PWM.TIM_OutputState = TIM_OutputState_Enable;

  if(servo->CHANx == TIM_Channel_1)
    TIM_OC1Init(servo->TIMx, &OCInit_PWM); // Initialize OSC1
  else if(servo->CHANx == TIM_Channel_2)
    TIM_OC2Init(servo->TIMx, &OCInit_PWM); // Initialize OSC2
  else if(servo->CHANx == TIM_Channel_3)
    TIM_OC3Init(servo->TIMx, &OCInit_PWM); // Initialize OSC3
  else if(servo->CHANx == TIM_Channel_4)
    TIM_OC4Init(servo->TIMx, &OCInit_PWM); // Initialize OSC4
}

/**
  * @brief  Set the servo angle in %. Note that the angle is relative to the min
  *         and the max value set in the servo structure configuration.
  * @param  servo: pointer to a ausbeeServo structure that contains the
  *         configuration information for the specified servo.
  * @param  angle: new angle value compute as if minValue is 0% and maxValue 
  *         is 100%.
  * @retval None
  */
void ausbeeSetAngleServo(ausbeeServo* servo, uint8_t angle)
{
  uint8_t newPulse = angle*(servo->maxValue-servo->minValue)/100 + servo->minValue;  // Compute new pulse value
  if( newPulse >= servo->minValue && newPulse <= servo->maxValue ) // Verify value
    {
      if(servo->CHANx == TIM_Channel_1)
	TIM_SetCompare1(servo->TIMx, newPulse);
      else if(servo->CHANx == TIM_Channel_2)
	TIM_SetCompare2(servo->TIMx, newPulse);
      else if(servo->CHANx == TIM_Channel_3)
	TIM_SetCompare3(servo->TIMx, newPulse);
      else
	TIM_SetCompare4(servo->TIMx, newPulse);
    }
}

/**
  * @brief  Return the angle value related to the specified servo.
  * @param  servo: pointer to a ausbeeServo structure that contains the
  *         configuration information for the specified servo.
  * @retval angle: the servo angle
  */
uint8_t ausbeeGetAngleServo(ausbeeServo* servo)
{
  if(servo->CHANx == TIM_Channel_1)
    return (uint8_t)( (TIM_GetCapture1(servo->TIMx)-servo->minValue)*100/(servo->maxValue-servo->minValue));
  else if(servo->CHANx == TIM_Channel_2)
    return (uint8_t)( (TIM_GetCapture2(servo->TIMx)-servo->minValue)*100/(servo->maxValue-servo->minValue));
  else if(servo->CHANx == TIM_Channel_3)
    return (uint8_t)( (TIM_GetCapture3(servo->TIMx)-servo->minValue)*100/(servo->maxValue-servo->minValue));
    else
      return (uint8_t)( (TIM_GetCapture4(servo->TIMx)-servo->minValue)*100/(servo->maxValue-servo->minValue));
}

/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */

/************** (C) COPYRIGHT 2013-2014 Eirbot **** END OF FILE ****/
