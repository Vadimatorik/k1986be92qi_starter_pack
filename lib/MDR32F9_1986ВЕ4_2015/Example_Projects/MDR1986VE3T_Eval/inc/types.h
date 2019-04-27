/**
  ******************************************************************************
  * @file    types.h
  * @author  Phyton Application Team
  * @version V2.0.0
  * @date    09.09.2010
  * @brief   This file contains some auxiliary type definitions.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TYPES_H
#define __TYPES_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

typedef unsigned char const    ucint8_t;
typedef volatile unsigned char vuint8_t;
typedef volatile unsigned long vuint32_t;

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

#endif /* __TYPES_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE types.h */

