/**
  ******************************************************************************
  * @file    1986BE9x_comp_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the COMP peripheral unit used in the Milandr 1986BE9x
  *          microcontrollers.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  ******************************************************************************
  * FILE 1986BE9x_comp_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_COMP_DEFS_H
#define __1986BE9X_COMP_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_COMP COMP
  * @{
  */

/** @defgroup Periph_COMP_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_COMP_TypeDef COMP_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t CFG;
  __IO uint32_t RESULT;
  __IO uint32_t RESULT_LATCH;
}COMP_TypeDef;

/** @} */ /* End of group Periph_COMP_TypeDef */

/** @} */ /* End of group Periph_COMP_Data_Structures */

/** @defgroup Periph_COMP_Defines Defines
  * @{
  */

/** @defgroup Periph_COMP_COMP_CFG_Bits COMP_CFG
  * @{
  */

#define COMP_CFG_ON_Pos                         0
#define COMP_CFG_ON                             ((uint32_t)0x00000001)

#define COMP_CFG_CVRR_Pos                       1
#define COMP_CFG_CVRR                           ((uint32_t)0x00000002)

#define COMP_CFG_CVRSS_Pos                      2
#define COMP_CFG_CVRSS                          ((uint32_t)0x00000004)

#define COMP_CFG_CVREN_Pos                      3
#define COMP_CFG_CVREN                          ((uint32_t)0x00000008)

#define COMP_CFG_CVR_Pos                        4
#define COMP_CFG_CVR_Msk                        ((uint32_t)0x000000F0)

#define COMP_CFG_CREF_Pos                       8
#define COMP_CFG_CREF                           ((uint32_t)0x00000100)

#define COMP_CFG_CCH_Pos                        9
#define COMP_CFG_CCH_Msk                        ((uint32_t)0x00000600)

#define COMP_CFG_INV_Pos                        11
#define COMP_CFG_INV                            ((uint32_t)0x00000800)

#define COMP_CFG_Ready_Pos                      12
#define COMP_CFG_Ready                          ((uint32_t)0x00001000)

#define COMP_CFG_CMPIE_Pos                      13
#define COMP_CFG_CMPIE                          ((uint32_t)0x00002000)


/** @} */ /* End of group Periph_COMP_COMP_CFG_Bits */

/** @} */ /* End of group Periph_COMP_Defines */

/** @defgroup Periph_COMP_Defines Defines
  * @{
  */

/** @defgroup Periph_COMP_COMP_RESULT_Bits COMP_RESULT
  * @{
  */

#define COMP_RESULT_Rslt_Sy_Pos                 0
#define COMP_RESULT_Rslt_Sy                     ((uint32_t)0x00000001)

#define COMP_RESULT_Rslt_As_Pos                 1
#define COMP_RESULT_Rslt_As                     ((uint32_t)0x00000002)

#define COMP_RESULT_Rst_lch_Pos                 2
#define COMP_RESULT_Rst_lch                     ((uint32_t)0x00000004)


/** @} */ /* End of group Periph_COMP_COMP_RESULT_Bits */

/** @} */ /* End of group Periph_COMP_Defines */

/** @} */ /* End of group Periph_COMP */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_COMP_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_comp_defs.h */
