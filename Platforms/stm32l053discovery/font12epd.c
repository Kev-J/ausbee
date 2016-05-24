/**
  ******************************************************************************
  * @file    Font12epd.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    27-July-2015
  * @brief   This file provides text Font12 for STM32L0538-DISCO's EPD driver. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fontsepd.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32L0538_DISCOVERY
  * @{
  */

/** @addtogroup FONTS
  * @brief      This file provides text Font12 for STM32L0538-Discovery's EPD driver.
  * @{
  */  

/** @defgroup FONTS_Private_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup FONTS_Private_Defines
  * @{
  */
/**
  * @}
  */ 


/** @defgroup FONTS_Private_Macros
  * @{
  */
/**
  * @}
  */ 
  

/** @defgroup FONTS_Private_Variables
  * @{
  */
// 
//  Font data for Courier New 12pt
// 

const uint8_t Font12_Table[] = 
{
	// @0 ' ' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	                  //        
	                  //        
	                  //        
	                  //        
	                  //        

	// @21 '!' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	0xfc, 0xf0, 0x03, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //        
	                  //        
                    //    #   
                    //        
	                  //        
	                  //        

	// @63 '"' (7 lines)
	0xfc, 0xf0, 0x03, //        
	0xfc, 0xf0, 0x03, //  ## ## 
	0xfc, 0xf0, 0x03, //  #  #  
	0xfc, 0xf0, 0x03, //  #  #  
	0xfc, 0xf0, 0x03, //        
	0xfc, 0xf0, 0x03, //        
	0xfc, 0xf0, 0x03, //        
	                  //        
	                  //        
	                  //        
	                  //        
	                  //        

	// @84 '#' (7 lines)
	0xff, 0xff, 0xff, //        
	0xf0, 0xcc, 0xff, //    # # 
	0xff, 0x00, 0x3f, //    # # 
	0xf0, 0xcc, 0xc3, //   # #  
	0xff, 0x00, 0x3f, //  ##### 
	0xf0, 0xcc, 0xc3, //   # # 
	0xff, 0xff, 0xff, //  ##### 
	                  //   # #  
	                  //  # #   
	                  //  # #   
	                  //        
	                  //        

	// @105 '$' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x0c, 0x3f, //    #   
	0xff, 0x33, 0xcf, //   ###  
	0xf0, 0x33, 0xc3, //  #     
	0xff, 0xc3, 0xcf, //  #     
	0xff, 0xff, 0xff, //   ###  
	0xff, 0xff, 0xff, //  #  #  
                    //  ###   
                    //    #   
                    //    #   
	                  //        
	                  //        

	// @126 '%' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xf3, 0xcf, //   #    
	0xff, 0xf3, 0x33, //  # #   
	0xff, 0x33, 0xcf, //   #    
	0xfc, 0xcc, 0xff, //     ## 
	0xff, 0x3c, 0xff, //  ###   
	0xff, 0xff, 0xff, //     #  
	                  //    # # 
	                  //     #  
	                  //        
	                  //        
	                  //        

	// @147 '&' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x0f, 0xff, //        
	0xfc, 0xf0, 0xff, //        
	0xfc, 0xcf, 0x3f, //    ##  
	0xff, 0x3f, 0x3f, //   #    
	0xfc, 0xcf, 0xff, //   #    
	0xff, 0xff, 0xff, //  # # # 
                          //  #  #  
                          //   ## # 
	                  //        
	                  //        
	                  //        

	// @168 ''' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xfc, 0xf3, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
                          //        
	                  //        
                          //        
	                  //        
	                  //        

	// @189 '(' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //     #  
	0xff, 0xff, 0xff, //     #  
	0xfc, 0xff, 0x3f, //    #   
	0xc3, 0xff, 0xc3, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	                  //    #   
	                  //    #   
                          //     #  
	                  //     #  
	                  //        

	// @210 ')' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //   #    
	0xc3, 0xff, 0xc3, //   #    
	0xfc, 0xff, 0x3f, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	                  //    #   
	                  //    #   
                          //   #    
                          //   #    
	                  //        

	// @231 '*' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xcf, //    #   
	0xff, 0xf0, 0xcf, //  ##### 
	0xff, 0xff, 0x03, //    #   
	0xff, 0xf0, 0xcf, //   # #  
	0xff, 0xff, 0xcf, //   # #  
	0xff, 0xff, 0xff, //        
	                  //        
	                  //        
	                  //        
	                  //        
	                  //        

	// @252 '+' (7 lines)
	0xff, 0xf3, 0xff, //        
	0xff, 0xf3, 0xff, //        
	0xff, 0xf3, 0xff, //    #   
	0xfc, 0x00, 0x0f, //    #   
	0xff, 0xf3, 0xff, //    #   
	0xff, 0xf3, 0xff, // #######
	0xff, 0xf3, 0xff, //    #   
	                  //    #   
	                  //    #   
	                  //        
	                  //        
	                  //        

	// @273 ',' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xc3, 0xff, 0xff, //        
	0xf0, 0x3f, 0xff, //        
	0xff, 0x3f, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
                          //    ##  
	                  //    #   
	                  //   ##   
	                  //   #    
	                  //        

	// @294 '-' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xf3, 0xff, //        
	0xff, 0xf3, 0xff, //        
	0xff, 0xf3, 0xff, //        
	0xff, 0xf3, 0xff, //        
	0xff, 0xf3, 0xff, //  ##### 
	0xff, 0xff, 0xff, //        
	                  //        
	                  //        
	                  //        
	                  //        
	                  //        

	// @315 '.' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xfc, 0x3f, 0xff, //        
	0xfc, 0x3f, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	                  //   ##   
	                  //   ##   
	                  //        
	                  //        
	                  //        

	// @336 '/' (7 lines)
	0xff, 0xff, 0xff, //        
	0xf3, 0xff, 0xff, //      # 
	0xfc, 0x3f, 0xff, //      # 
	0xff, 0xc3, 0xff, //     #  
	0xff, 0xfc, 0x3f, //     #  
	0xff, 0xff, 0xc3, //    #   
	0xff, 0xff, 0xff, //    #   
	                  //   #    
	                  //   #    
	                  //  #     
	                  //        
	                  //        

	// @357 '0' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0x0f, //   ###  
	0xfc, 0xff, 0xf3, //  #   # 
	0xfc, 0xff, 0xf3, //  #   # 
	0xfc, 0xff, 0xf3, //  #   # 
	0xff, 0x00, 0x0f, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        
	                  //        

	// @378 '1' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0xff, //   ##   
	0xfc, 0xff, 0xf3, //    #   
	0xfc, 0x00, 0x03, //    #   
	0xfc, 0xff, 0xff, //    #   
	0xfc, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	                  //    #   
	                  //  ##### 
	                  //        
	                  //        
                    //        

	// @399 '2' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0x3f, 0xcf, //   ###  
	0xfc, 0xcf, 0xf3, //  #   # 
	0xfc, 0xf3, 0xf3, //      # 
	0xfc, 0xfc, 0xf3, //     #  
	0xfc, 0x3f, 0x0f, //    #   
	0xff, 0xff, 0xff, //   #    
	                  //  #   # 
                          //  ##### 
                          //        
	                  //        
	                  //        

	// @420 '3' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x3f, 0xcf, //   ###  
	0xfc, 0xff, 0xf3, //  #   # 
	0xfc, 0xfc, 0xf3, //      # 
	0xfc, 0xfc, 0xf3, //    ##  
	0xff, 0x03, 0x0f, //      # 
	0xff, 0xff, 0xff, //      # 
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        
	                  //        

	// @441 '4' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xc3, 0xff, //     ## 
	0xff, 0xcc, 0xff, //    # # 
	0xff, 0xcf, 0x0f, //    # # 
	0xfc, 0xcf, 0xf3, //   #  # 
	0xfc, 0x00, 0x03, //  #   # 
	0xfc, 0xcf, 0xff, //  ######
	                  //      # 
	                  //     ###
	                  //        
	                  //        
	                  //        

	// @462 '5' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x3f, 0xff, //   #### 
	0xfc, 0xfc, 0x03, //   #    
	0xfc, 0xfc, 0xf3, //   #    
	0xfc, 0xfc, 0xf3, //   ###  
	0xff, 0x03, 0xf3, //      # 
	0xff, 0xff, 0xff, //      # 
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        
	                  //        

	// @483 '6' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0x3f, //    ### 
	0xfc, 0xfc, 0xcf, //   #    
	0xfc, 0xfc, 0xf3, //  #     
	0xfc, 0xfc, 0xf3, //  ####  
	0xff, 0x03, 0xf3, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        
	                  //        

	// @504 '7' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xc3, //  ##### 
	0xff, 0xff, 0xf3, //  #   # 
	0xfc, 0x3f, 0xf3, //      # 
	0xff, 0xc0, 0xf3, //     #  
	0xff, 0xff, 0x03, //     #  
	0xff, 0xff, 0xff, //     #  
	                  //    #   
	                  //    #   
	                  //        
                          //        
	                  //        

	// @525 '8' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x03, 0x0f, //   ###  
	0xfc, 0xfc, 0xf3, //  #   # 
	0xfc, 0xfc, 0xf3, //  #   # 
	0xfc, 0xfc, 0xf3, //   ###  
	0xff, 0x03, 0x0f, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        
	                  //        

	// @546 '9' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xfc, 0x0f, //   ###  
	0xfc, 0xf3, 0xf3, //  #   # 
	0xfc, 0xf3, 0xf3, //  #   # 
	0xff, 0x33, 0xf3, //  #   # 
	0xff, 0xc0, 0x0f, //   #### 
	0xff, 0xff, 0xff, //      # 
	                  //     #  
	                  //  ###   
	                  //        
	                  //        
	                  //        

	// @567 ':' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xfc, 0x3c, 0x3f, //        
	0xfc, 0x3c, 0x3f, //   ##   
        0xff, 0xff, 0xff, //   ##   
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	                  //   ##   
	                  //   ##   
	                  //        
	                  //        
	                  //        

	// @588 ';' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xf0, 0xff, 0xff, //        
	0xfc, 0x3c, 0xcf, //    ##  
	0xff, 0x3c, 0xcf, //    ##  
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	                  //    ##  
	                  //   ##   
	                  //   #    
	                  //        
	                  //        

	// @609 '<' (7 lines)
	0xff, 0xf3, 0xff, //        
	0xff, 0xcc, 0xff, //        
	0xff, 0xcc, 0xff, //     ## 
	0xff, 0x3f, 0x3f, //    #   
	0xfc, 0xff, 0xcf, //  ##    
	0xfc, 0xff, 0xcf, // #      
	0xff, 0xff, 0xff, //  ##    
	                  //    #   
	                  //     ## 
	                  //        
	                  //        
	                  //        

	// @630 '=' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xcc, 0xff, //        
	0xff, 0xcc, 0xff, //        
	0xff, 0xcc, 0xff, //        
	0xff, 0xcc, 0xff, //  ##### 
	0xff, 0xcc, 0xff, //        
	0xff, 0xff, 0xff, //  ##### 
	                  //        
	                  //        
	                  //        
	                  //        
	                  //        

	// @651 '>' (7 lines)
	0xfc, 0xff, 0xcf, //        
	0xfc, 0xff, 0xcf, //        
	0xff, 0x3f, 0x3f, // ##     
	0xff, 0xcc, 0xff, //   #    
	0xff, 0xcc, 0xff, //    ##  
	0xff, 0xf3, 0xff, //      # 
	0xff, 0xff, 0xff, //    ##  
	                  //   #    
	                  // ##     
	                  //        
	                  //        
	                  //        

	// @672 '?' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0x3f, //    ##  
	0xfc, 0xff, 0xcf, //   #  # 
	0xff, 0xf3, 0xcf, //      # 
	0xff, 0xfc, 0x3f, //     #  
	0xff, 0xff, 0xff, //    #   
	                  //        
	                  //   ##   
	                  //        
	                  //        
	                  //        

	// @714 '@' (7 lines)
	0xff, 0xff, 0xff, //   ###  
	0xfc, 0x00, 0x03, //  #   # 
	0xf3, 0xff, 0xfc, //  #   # 
	0xf3, 0xf0, 0xfc, //  #  ## 
	0xf3, 0xcf, 0x3c, //  # # # 
	0xfc, 0xc0, 0x03, //  # # # 
	0xff, 0xff, 0xff, //  #  ## 
	                  //  #     
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        

	// @735 'A' (7 lines)
	0xfc, 0xff, 0xff, //        
	0xfc, 0x0f, 0xff, //   ##   
	0xfc, 0xc0, 0x33, //    #   
	0xff, 0xcf, 0xc3, //   # #  
	0xfc, 0xc0, 0x3f, //   # #  
	0xfc, 0x0f, 0xff, //   # #  
	0xfc, 0xff, 0xff, //  ##### 
                    //  #   # 
	                  // ### ###
	                  //        
	                  //        
	                  //        

	// @756 'B' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // #####  
	0xfc, 0xfc, 0xf3, //  #   # 
	0xfc, 0xfc, 0xf3, //  #   # 
	0xfc, 0xfc, 0xf3, //  ####  
	0xff, 0x03, 0x0f, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  // #####  
	                  //        
	                  //        
	                  //        

	// @777 'C' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0x0f, //   #### 
	0xfc, 0xff, 0xf3, //  #   # 
	0xfc, 0xff, 0xf3, //  #     
	0xfc, 0xff, 0xf3, //  #     
	0xff, 0x3f, 0xc3, //  #     
	0xff, 0xff, 0xff, //  #     
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        
	                  //        

	// @798 'D' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // ####   
	0xfc, 0xff, 0xf3, //  #  #  
	0xfc, 0xff, 0xf3, //  #   # 
	0xff, 0x3f, 0xcf, //  #   # 
	0xff, 0xc0, 0x3f, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
	                  //  #  #  
	                  // ####   
	                  //        
                    //        
	                  //        

	// @819 'E' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // ###### 
	0xfc, 0xfc, 0xf3, //  #   # 
	0xfc, 0xf0, 0x33, //  # #   
	0xfc, 0xff, 0xf3, //  ###   
	0xfc, 0x3f, 0xc3, //  # #   
	0xff, 0xff, 0xff, //  #     
	                  //  #   # 
	                  // ###### 
                    //        
	                  //        
                    //        

	// @840 'F' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0xf3, //  ######
	0xfc, 0x00, 0x03, //   #   #
	0xfc, 0xfc, 0xf3, //   # #  
	0xff, 0xf0, 0x33, //   ###  
	0xff, 0xff, 0xf3, //   # #  
	0xff, 0xff, 0xc3, //   #    
	                  //   #    
	                  //  ###   
                    //        
	                  //        
	                  //        

	// @861 'G' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0x0f, //   #### 
	0xfc, 0xff, 0xf3, //  #   # 
	0xfc, 0xf3, 0xf3, //  #     
	0xff, 0x03, 0xc3, //  #     
	0xff, 0xf3, 0xff, //  #  ###
	0xff, 0xff, 0xff, //  #   # 
                    //  #   # 
                    //   ###  
	                  //        
                    //        
                    //        

	// @882 'H' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // ### ###
	0xfc, 0xfc, 0xf3, //  #   # 
	0xff, 0xfc, 0xff, //  #   # 
	0xfc, 0xfc, 0xf3, //  ##### 
	0xfc, 0x00, 0x03, //  #   # 
	0xfc, 0xff, 0xf3, //  #   # 
	                  //  #   # 
	                  // ### ###
	                  //        
                    //        
	                  //        

	// @903 'I' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0xf3, //  ##### 
	0xfc, 0xff, 0xf3, //    #   
	0xfc, 0x00, 0x03, //    #   
	0xfc, 0xff, 0xf3, //    #   
	0xfc, 0xff, 0xf3, //    #   
	0xff, 0xff, 0xff, //    #   
	                  //    #   
	                  //  ##### 
	                  //        
	                  //        
	                  //        

	// @924 'J' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x03, 0xff, //   #### 
	0xfc, 0xff, 0xf3, //     #  
	0xfc, 0xff, 0xf3, //     #  
	0xff, 0x00, 0x03, //     #  
	0xff, 0xff, 0xf3, //  #  #  
	0xff, 0xff, 0xff, //  #  #  
	                  //  #  #  
	                  //   ##   
                    //        
                    //        
                    //        

	// @945 'K' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // ### ###
	0xfc, 0xf3, 0xf3, //  #   # 
	0xff, 0xf0, 0xff, //  #  #  
	0xff, 0xcf, 0x33, //  # #   
	0xfc, 0x3f, 0xc3, //  ###   
	0xfc, 0xff, 0xf3, //  #  #  
	                  //  #   # 
	                  // ###  ##
                    //        
                    //        
	                  //        

	// @966 'L' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0xf3, //  ###   
	0xfc, 0x00, 0x03, //   #    
	0xfc, 0xff, 0xf3, //   #    
	0xfc, 0xff, 0xff, //   #    
	0xfc, 0x0f, 0xff, //   #    
	0xff, 0xff, 0xff, //   #  # 
	                  //   #  # 
	                  //  ##### 
	                  //        
	                  //        
	                  //        

	// @987 'M' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // ### ###
	0xfc, 0xff, 0x03, //  ## ## 
	0xff, 0xf0, 0xff, //  ## ## 
	0xfc, 0xff, 0x03, //  # # # 
	0xfc, 0x00, 0x03, //  # # # 
	0xfc, 0xff, 0xf3, //  #   # 
	                  //  #   # 
	                  // ### ###
                    //        
                    //        
	                  //        

	// @1008 'N' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // ### ###
	0xfc, 0xff, 0x03, //  ##  # 
	0xff, 0xc0, 0xff, //  ##  # 
	0xfc, 0x3f, 0xf3, //  # # # 
	0xfc, 0x00, 0x03, //  # # # 
	0xff, 0xff, 0xf3, //  # # # 
	                  //  #  ## 
	                  // ### ## 
	                  //        
	                  //        
	                  //        

	// @1029 'O' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0x0f, //   ###  
	0xfc, 0xff, 0xf3, //  #   # 
	0xfc, 0xff, 0xf3, //  #   # 
	0xfc, 0xff, 0xf3, //  #   # 
	0xff, 0x00, 0x0f, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        
                    //        

	// @1050 'P' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0xf3, //  ####  
	0xfc, 0x00, 0x03, //   #  # 
	0xfc, 0xf3, 0xf3, //   #  # 
	0xff, 0xf3, 0xf3, //   #  # 
	0xff, 0xfc, 0x0f, //   ###  
	0xff, 0xff, 0xff, //   #    
	                  //   #    
	                  //  ###   
	                  //        
	                  //        
	                  //        

	// @1071 'Q' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0x0f, //   ###  
	0xfc, 0xff, 0xf3, //  #   # 
	0xf0, 0xff, 0xf3, //  #   # 
	0xf0, 0xff, 0xf3, //  #   # 
	0xf3, 0x00, 0x0f, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  //   ###  
	                  //    ### 
	                  //        
	                  //        

	// @1092 'R' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // #####  
	0xfc, 0xf3, 0xf3, //  #   # 
	0xff, 0xf3, 0xf3, //  #   # 
	0xff, 0xc3, 0xf3, //  #   # 
	0xff, 0x3c, 0x0f, //  ####  
	0xfc, 0xff, 0xff, //  #  #  
	                  //  #   # 
	                  // ###   #
	                  //        
	                  //        
	                  //        

	// @1113 'S' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0x3f, 0x0f, //   ## # 
	0xff, 0x3c, 0xf3, //  #  ## 
	0xfc, 0xfc, 0xf3, //  #     
	0xfc, 0xfc, 0xcf, //   ###  
	0xff, 0x03, 0xc3, //      # 
	0xff, 0xff, 0xff, //      # 
	                  //  ##  # 
	                  //  # ##  
	                  //        
	                  //        
	                  //        

	// @1134 'T' (7 lines)
	0xff, 0xff, 0xc3, //        
	0xff, 0xff, 0xf3, // #######
	0xfc, 0xff, 0xf3, // #  #  #
	0xfc, 0x00, 0x03, //    #   
	0xfc, 0xff, 0xf3, //    #   
	0xff, 0xff, 0xf3, //    #   
	0xff, 0xff, 0xc3, //    #   
	                  //    #   
	                  //   ###  
	                  //        
                    //        
	                  //        

	// @1155 'U' (7 lines)
	0xff, 0xff, 0xf3, //        
	0xff, 0x00, 0x03, // ### ###
	0xfc, 0xff, 0xf3, //  #   # 
	0xfc, 0xff, 0xff, //  #   # 
	0xfc, 0xff, 0xf3, //  #   # 
	0xff, 0x00, 0x03, //  #   # 
	0xff, 0xff, 0xf3, //  #   # 
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        
                    //        

	// @1176 'V' (7 lines)
	0xff, 0xff, 0xf3, //        
	0xff, 0xff, 0x03, // ### ###
	0xff, 0xc0, 0xf3, //  #   # 
	0xfc, 0x3f, 0xff, //  #   # 
	0xff, 0xc0, 0xf3, //   # #  
	0xff, 0xff, 0x03, //   # #  
	0xff, 0xff, 0xf3, //   # #  
	                  //    #   
	                  //    #   
	                  //        
	                  //        
	                  //        

	// @1197 'W' (7 lines)
	0xff, 0xff, 0xf3, //        
	0xff, 0x00, 0x03, // ### ###
	0xfc, 0xff, 0xf3, //  #   # 
	0xff, 0x00, 0xff, //  #   # 
	0xfc, 0xff, 0xf3, //  # # # 
	0xff, 0x00, 0x03, //  # # # 
	0xff, 0xff, 0xf3, //  # # # 
	                  //  # # # 
	                  //   # #  
	                  //        
	                  //        
	                  //        

	// @1218 'X' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x3f, 0xc3, // ##   ##
	0xff, 0xcf, 0x3f, //  #   # 
	0xff, 0xf0, 0xff, //   # #  
	0xff, 0xcf, 0x3f, //    #   
	0xfc, 0x3f, 0xc3, //    #   
	0xfc, 0xff, 0xf3, //   # #  
	                  //  #   # 
	                  // ##   ##
                    //        
	                  //        
	                  //        

	// @1239 'Y' (7 lines)
	0xff, 0xff, 0xf3, //        
	0xff, 0xff, 0xc3, // ### ###
	0xfc, 0xfc, 0x33, //  #   # 
	0xfc, 0x03, 0xff, //   # #  
	0xfc, 0xfc, 0x33, //   # #  
	0xff, 0xff, 0xc3, //    #   
	0xff, 0xff, 0xf3, //    #   
	                  //    #   
	                  //   ###  
	                  //        
	                  //        
                    //        

	// @1260 'Z' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0x3f, 0xc3, //  ##### 
	0xfc, 0xcf, 0xf3, //  #   # 
	0xfc, 0xf0, 0xf3, //     #  
	0xfc, 0xff, 0x33, //    #   
	0xfc, 0x3f, 0xc3, //    #   
	0xff, 0xff, 0xff, //   #    
	                  //  #   # 
	                  //  ##### 
	                  //        
                    //        
	                  //        

	// @1281 '[' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //   ###  
	0xc0, 0x00, 0x03, //   #    
	0xcf, 0xff, 0xf3, //   #    
	0xcf, 0xff, 0xf3, //   #    
	0xff, 0xff, 0xff, //   #    
	0xff, 0xff, 0xff, //   #    
	                  //   #    
	                  //   #    
	                  //   #    
	                  //   ###  
	                  //        

	// @1302 '\' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xf3, //  #     
	0xff, 0xfc, 0x0f, //   #    
	0xff, 0xc3, 0xff, //   #    
	0xf0, 0x3f, 0xff, //   #    
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	                  //     #  
	                  //     #  
	                  //     #  
	                  //        
	                  //        

	// @1323 ']' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //   ###  
	0xcf, 0xff, 0xf3, //     #  
	0xcf, 0xff, 0xf3, //     #  
	0xc0, 0x00, 0x03, //     #  
	0xff, 0xff, 0xff, //     #  
	0xff, 0xff, 0xff, //     #  
	                  //     #  
	                  //     #  
	                  //     #  
	                  //   ###  
	                  //        

	// @1344 '^' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xfc, 0xff, //    #   
	0xff, 0xff, 0x3f, //    #   
	0xff, 0xff, 0xc3, //   # #  
	0xff, 0xff, 0x3f, //  #   # 
	0xff, 0xfc, 0xff, //        
	0xff, 0xff, 0xff, //        
	                  //        
	                  //        
	                  //        
	                  //        
                    //        

	// @1365 '_' (7 lines)
	0x3f, 0xff, 0xff, //        
	0x3f, 0xff, 0xff, //        
	0x3f, 0xff, 0xff, //        
	0x3f, 0xff, 0xff, //        
	0x3f, 0xff, 0xff, //        
	0x3f, 0xff, 0xff, //        
	0x3f, 0xff, 0xff, //        
	                  //        
	                  //        
	                  //        
	                  //        
	                  // #######

	// @1386 '`' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //     #  
	0xff, 0xff, 0xf3, //        
	0xff, 0xff, 0xcf, //        
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //        
	                  //        
	                  //        
	                  //        
	                  //        
	                  //        

	// @1407 'a' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x0c, 0xff, //        
	0xfc, 0xf3, 0x3f, //        
	0xfc, 0xf3, 0x3f, //   ###  
	0xfc, 0xf3, 0x3f, //  #   # 
	0xfc, 0x00, 0xff, //   #### 
	0xfc, 0xff, 0xff, //  #   # 
	                  //  #   # 
                    //   #####
	                  //        
	                  //        
	                  //        

	// @1428 'b' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // ##     
	0xfc, 0xfc, 0xff, //  #     
	0xfc, 0xff, 0x3f, //  # ##  
	0xfc, 0xff, 0x3f, //  ##  # 
	0xff, 0x00, 0xff, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  // #####  
	                  //        
	                  //        
	                  //        

	// @1449 'c' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0xff, //        
	0xfc, 0xff, 0x3f, //        
	0xfc, 0xff, 0x3f, //   #### 
	0xfc, 0xff, 0x3f, //  #   # 
	0xff, 0x3c, 0x3f, //  #     
	0xff, 0xff, 0xff, //  #     
	                  //  #   # 
	                  //   ###  
	                  //        
	                  //        
	                  //        

	// @1470 'd' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0xff, //     ## 
	0xfc, 0xff, 0x3f, //      # 
	0xfc, 0xff, 0x3f, //   ## # 
	0xfc, 0xfc, 0xf3, //  #  ## 
	0xfc, 0x00, 0x03, //  #   # 
	0xfc, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  //   #####
                    //        
	                  //        
	                  //        

	// @1491 'e' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0xff, //        
	0xfc, 0xf3, 0x3f, //        
	0xfc, 0xf3, 0x3f, //   ###  
	0xfc, 0xf3, 0x3f, //  #   # 
	0xfc, 0xf0, 0xff, //  ##### 
	0xff, 0xff, 0xff, //  #     
	                  //  #     
	                  //   #### 
	                  //        
	                  //        
	                  //        

	// @1512 'f' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0x3f, //    ### 
	0xfc, 0x00, 0x0f, //   #    
	0xfc, 0xff, 0x33, //  ##### 
	0xfc, 0xff, 0x33, //   #    
	0xfc, 0xff, 0x33, //   #    
	0xff, 0xff, 0xff, //   #    
	                  //   #    
	                  //  ##### 
                    //        
	                  //        
	                  //        

	// @1533 'g' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0xff, //        
	0xcc, 0xff, 0x3f, //        
	0xcc, 0xff, 0x3f, //   ## ##
	0xcc, 0xfc, 0xff, //  #  ## 
	0xf0, 0x00, 0x3f, //  #   # 
	0xff, 0xff, 0x3f, //  #   # 
	                  //  #   # 
	                  //   #### 
	                  //      # 
	                  //   ###  
	                  //        

	// @1554 'h' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // ##     
	0xfc, 0xfc, 0xff, //  #     
	0xff, 0xff, 0x3f, //  # ##  
	0xfc, 0xff, 0x3f, //  ##  # 
	0xfc, 0x00, 0xff, //  #   # 
	0xfc, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  // ### ###
	                  //        
                    //        
	                  //        

	// @1575 'i' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0x3f, //    #   
	0xfc, 0xff, 0x3f, //        
	0xfc, 0x00, 0x33, //  ###   
	0xfc, 0xff, 0xff, //    #   
	0xfc, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
                    //    #   
	                  //  ##### 
	                  //        
	                  //        
	                  //        

	// @1596 'j' (7 lines)
	0xff, 0xff, 0xff, //        
	0xcf, 0xff, 0x3f, //    #   
	0xcf, 0xff, 0x3f, //        
	0xcf, 0xff, 0x33, //  ####  
	0xf0, 0x00, 0x3f, //     #  
	0xff, 0xff, 0xff, //     #  
	0xff, 0xff, 0xff, //     #  
	                  //     #  
	                  //     #  
	                  //     #  
	                  //  ###   
	                  //        

	// @1617 'k' (7 lines)
	0xfc, 0xff, 0xf3, //        
	0xfc, 0x00, 0x03, // ##     
	0xff, 0xf3, 0xff, //  #     
	0xfc, 0xc3, 0x3f, //  # ### 
	0xfc, 0x3c, 0x3f, //  #  #  
	0xfc, 0xff, 0x3f, //  ###   
	0xff, 0xff, 0xff, //  # #   
                    //  #  #  
	                  // ## ### 
	                  //        
                    //        
                    //        

	// @1638 'l' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0xff, //   ##   
	0xfc, 0xff, 0xf3, //    #   
	0xfc, 0x00, 0x03, //    #   
	0xfc, 0xff, 0xff, //    #   
	0xfc, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	                  //    #   
                    //  ##### 
	                  //        
	                  //        
                    //        

	// @1659 'm' (7 lines)
	0xfc, 0xff, 0x3f, //        
	0xfc, 0x00, 0x3f, //        
	0xfc, 0xff, 0x3f, //        
	0xfc, 0x00, 0xff, // ### #  
	0xfc, 0xff, 0x3f, //  # # # 
	0xfc, 0x00, 0xff, //  # # # 
	0xfc, 0xff, 0xff, //  # # # 
	                  //  # # # 
	                  // #######
	                  //        
	                  //        
	                  //        

	// @1680 'n' (7 lines)
	0xfc, 0xff, 0x3f, //        
	0xfc, 0x00, 0x3f, //        
	0xfc, 0xfc, 0xff, //        
	0xff, 0xff, 0x3f, // ## ##  
	0xfc, 0xff, 0x3f, //  ##  # 
	0xfc, 0x00, 0xff, //  #   # 
	0xfc, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  // ### ###
	                  //        
	                  //        
	                  //        

	// @1701 'o' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0xff, //        
	0xfc, 0xff, 0x3f, //        
	0xfc, 0xff, 0x3f, //   ###  
	0xfc, 0xff, 0x3f, //  #   # 
	0xff, 0x00, 0xff, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
                    //  #   # 
	                  //   ###  
	                  //        
	                  //        
	                  //        

	// @1722 'p' (7 lines)
	0xcf, 0xff, 0x3f, //        
	0xc0, 0x00, 0x3f, //        
	0xcc, 0xfc, 0xff, //        
	0xfc, 0xff, 0x3f, // ## ##  
	0xfc, 0xff, 0x3f, //  ##  # 
	0xff, 0x00, 0xff, //  #   # 
	0xff, 0xff, 0xff, //  #   # 
	                  //  #   # 
	                  //  ####  
	                  //  #     
	                  // ###    
	                  //        

	// @1743 'q' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0x00, 0xff, //        
	0xfc, 0xff, 0x3f, //        
	0xfc, 0xff, 0x3f, //   ## ##
	0xcc, 0xfc, 0xff, //  #  ## 
	0xc0, 0x00, 0x3f, //  #   # 
	0xcf, 0xff, 0x3f, //  #   # 
	                  //  #   # 
	                  //   #### 
	                  //      # 
                    //     ###
	                  //        

	// @1764 'r' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0xff, 0x3f, //        
	0xfc, 0x00, 0x3f, //        
	0xfc, 0xfc, 0xff, //  ## ## 
	0xfc, 0xff, 0x3f, //   ##   
	0xfc, 0xff, 0x3f, //   #    
	0xff, 0xff, 0xff, //   #    
	                  //   #    
	                  //  ##### 
                    //        
	                  //        
	                  //        

	// @1785 's' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0x3c, 0xff, //        
	0xfc, 0xf3, 0x3f, //        
	0xfc, 0xf3, 0x3f, //   #### 
	0xfc, 0xf3, 0x3f, //  #   # 
	0xff, 0x0c, 0x3f, //   ###  
	0xff, 0xff, 0xff, //      # 
                    //  #   # 
	                  //  ####  
	                  //        
	                  //        
	                  //        

	// @1806 't' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0x3f, //        
	0xff, 0x00, 0x0f, //   #    
	0xfc, 0xff, 0x3f, //  ##### 
	0xfc, 0xff, 0x3f, //   #    
	0xfc, 0xff, 0x3f, //   #    
	0xff, 0x3f, 0xff, //   #    
	                  //   #   #
	                  //    ### 
	                  //        
	                  //        
	                  //        

	// @1827 'u' (7 lines)
	0xff, 0xff, 0x3f, //        
	0xff, 0x00, 0x3f, //        
	0xfc, 0xff, 0xff, //        
	0xfc, 0xff, 0xff, // ##  ## 
	0xff, 0x3f, 0x3f, //  #   # 
	0xfc, 0x00, 0x3f, //  #   # 
	0xfc, 0xff, 0xff, //  #   # 
	                  //  #  ## 
	                  //   ## ##
	                  //        
	                  //        
	                  //        

	// @1848 'v' (7 lines)
	0xff, 0xff, 0x3f, //        
	0xff, 0xf0, 0x3f, //        
	0xff, 0x0f, 0x3f, //        
	0xfc, 0xff, 0xff, // ### ###
	0xff, 0x0f, 0x3f, //  #   # 
	0xff, 0xf0, 0x3f, //  #   # 
	0xff, 0xff, 0x3f, //   # #  
	                  //   # #  
	                  //    #   
	                  //        
	                  //        
	                  //        

	// @1869 'w' (7 lines)
	0xff, 0xff, 0x3f, //        
	0xff, 0x00, 0x3f, //        
	0xfc, 0xff, 0x3f, //        
	0xff, 0x03, 0xff, // ### ###
	0xfc, 0xff, 0x3f, //  #   # 
	0xff, 0x00, 0x3f, //  # # # 
	0xff, 0xff, 0x3f, //  # # # 
	                  //  # # # 
	                  //   # #  
	                  //        
	                  //        
	                  //        

	// @1890 'x' (7 lines)
	0xfc, 0xff, 0x3f, //        
	0xfc, 0x3c, 0x3f, //        
	0xff, 0xc3, 0xff, //        
	0xff, 0xc3, 0xff, // ##  ## 
	0xfc, 0x3c, 0x3f, //  #  #  
	0xfc, 0xff, 0x3f, //   ##   
	0xff, 0xff, 0xff, //   ##   
	                  //  #  #  
                    // ##  ## 
	                  //        
	                  //        
	                  //        

	// @1911 'y' (7 lines)
	0xff, 0xff, 0x3f, //        
	0xcf, 0xfc, 0x3f, //        
	0xcf, 0xc3, 0x3f, //        
	0xc0, 0x3f, 0xff, // ### ###
	0xcf, 0x0f, 0x3f, //  #   # 
	0xff, 0xf0, 0x3f, //   #  # 
	0xff, 0xff, 0x3f, //   # #  
	                  //    ##  
	                  //    #   
	                  //    #   
	                  //  ####  
	                  //        

	// @1932 'z' (7 lines)
	0xff, 0xff, 0xff, //        
	0xfc, 0x3c, 0x3f, //        
	0xfc, 0xcf, 0x3f, //        
	0xfc, 0xf3, 0x3f, //  ##### 
	0xfc, 0xfc, 0x3f, //  #  #  
	0xfc, 0x3f, 0x3f, //    #   
	0xff, 0xff, 0xff, //   #    
	                  //  #   # 
	                  //  ##### 
	                  //        
	                  //        
	                  //        

	// @1953 '{' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //     #  
	0xff, 0xcf, 0xff, //    #   
	0xf0, 0x30, 0x0f, //    #   
	0xcf, 0xff, 0xf3, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //   #    
                    //    #   
                    //    #   
                    //    #   
                    //     #  
                    //        

	// @1974 '|' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	0xf0, 0x00, 0x03, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	                  //    #   
	                  //    #   
	                  //    #   
                    //        
                    //        

	// @1995 '}' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xff, 0xff, //   #    
	0xcf, 0xff, 0xf3, //    #   
	0xf0, 0x30, 0x0f, //    #   
	0xff, 0xcf, 0xff, //    #   
	0xff, 0xff, 0xff, //    #   
	0xff, 0xff, 0xff, //     #  
	                  //    #   
	                  //    #   
	                  //    #   
	                  //   #    
	                  //        

	// @2016 '~' (7 lines)
	0xff, 0xff, 0xff, //        
	0xff, 0xcf, 0xff, //        
	0xff, 0xf3, 0xff, //        
	0xff, 0xcf, 0xff, //        
	0xff, 0xcf, 0xff, //        
	0xff, 0xf3, 0xff, //   #  # 
	0xff, 0xff, 0xff, //  # ##  
	                  //        
	                  //        
	                  //        
	                  //        
	                  //        
};

sFONT Font12 = {
  Font12_Table,
  7, /* Width */    // (7 lines)
  3, /* Height */   // (3 bytes/12pixels)
};

/**
  * @}
  */ 


/** @defgroup FONTS_Private_Function_Prototypes
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup FONTS_Private_Functions
  * @{
  */
    
/**
  * @}
  */
  
/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
