/**
  ******************************************************************************
  * @file	 MT_107_MELT.h
  * @author	 sidorov.a
  * @version 1.0
  * @date    24.03.2014
  * @brief   This file contains the functions prototype.
  ******************************************************************************
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2014 Milandr </center></h2>
  ******************************************************************************
  * FILE MT_107_MELT.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MT_107_MELT_H_
#define MT_107_MELT_H_

/* Includes ------------------------------------------------------------------*/


// DB0(L)-g         DB0(H)- h
// DB1(L)-e         DB1(H)- b
// DB2(L)-d         DB2(H)- c
// DB3(l)-a         DB3(H)- f
//*****************************************
//         a
//      * *** *
//    f *  g  * b
//      * *** *
//    e *     * c
//      * *** *
//        d      *í

void Display_Init(void);
void Display_Clear(void);
void Display_PutChar(uint8_t char_position, uint8_t put_char);
void Display_Lock(void );
void Display_UnLock(void);
void Delay(void );
void Display_PutDigit(uint8_t char_position, uint8_t digit);

#endif /* MT_107_MELT_H_ */

/******************* (C) COPYRIGHT 2014 Milandr ********************************
*
* END OF FILE MT_107_MELT.h */
