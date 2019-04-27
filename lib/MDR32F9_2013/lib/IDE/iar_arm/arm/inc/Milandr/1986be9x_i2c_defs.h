/**
  ******************************************************************************
  * @file    1986BE9x_i2c_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the I2C peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_i2c_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_I2C_DEFS_H
#define __1986BE9X_I2C_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_I2C I2C
  * @{
  */

/** @defgroup Periph_I2C_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_I2C_TypeDef I2C_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t PRL;
  __IO uint32_t PRP;
  __IO uint32_t CTR;
  __IO uint32_t RXD;
  __IO uint32_t STA;
  __IO uint32_t TXD;
  __IO uint32_t CMD;
}I2C_TypeDef;

/** @} */ /* End of group Periph_I2C_TypeDef */

/** @} */ /* End of group Periph_I2C_Data_Structures */

/** @defgroup Periph_I2C_Defines Defines
  * @{
  */

/** @defgroup Periph_I2C_I2C_CTR_Bits I2C_CTR
  * @{
  */

#define I2C_CTR_S_I2C_Pos                       0
#define I2C_CTR_S_I2C                           ((uint32_t)0x00000001)

#define I2C_CTR_EN_INT_Pos                      1
#define I2C_CTR_EN_INT                          ((uint32_t)0x00000002)

#define I2C_CTR_EN_I2C_Pos                      2
#define I2C_CTR_EN_I2C                          ((uint32_t)0x00000004)


/** @} */ /* End of group Periph_I2C_I2C_CTR_Bits */

/** @} */ /* End of group Periph_I2C_Defines */

/** @defgroup Periph_I2C_Defines Defines
  * @{
  */

/** @defgroup Periph_I2C_I2C_STA_Bits I2C_STA
  * @{
  */

#define I2C_STA_INT_Pos                         0
#define I2C_STA_INT                             ((uint32_t)0x00000001)

#define I2C_STA_TR_PROG_Pos                     1
#define I2C_STA_TR_PROG                         ((uint32_t)0x00000002)

#define I2C_STA_LOST_ARB_Pos                    5
#define I2C_STA_LOST_ARB                        ((uint32_t)0x00000020)

#define I2C_STA_BUSY_Pos                        6
#define I2C_STA_BUSY                            ((uint32_t)0x00000040)

#define I2C_STA_Rx_ACK_Pos                      7
#define I2C_STA_Rx_ACK                          ((uint32_t)0x00000080)


/** @} */ /* End of group Periph_I2C_I2C_STA_Bits */

/** @} */ /* End of group Periph_I2C_Defines */

/** @defgroup Periph_I2C_Defines Defines
  * @{
  */

/** @defgroup Periph_I2C_I2C_CMD_Bits I2C_CMD
  * @{
  */

#define I2C_CMD_CLRINT_Pos                      0
#define I2C_CMD_CLRINT                          ((uint32_t)0x00000001)

#define I2C_CMD_ACK_Pos                         3
#define I2C_CMD_ACK                             ((uint32_t)0x00000008)

#define I2C_CMD_WR_Pos                          4
#define I2C_CMD_WR                              ((uint32_t)0x00000010)

#define I2C_CMD_RD_Pos                          5
#define I2C_CMD_RD                              ((uint32_t)0x00000020)

#define I2C_CMD_STOP_Pos                        6
#define I2C_CMD_STOP                            ((uint32_t)0x00000040)

#define I2C_CMD_START_Pos                       7
#define I2C_CMD_START                           ((uint32_t)0x00000080)


/** @} */ /* End of group Periph_I2C_I2C_CMD_Bits */

/** @} */ /* End of group Periph_I2C_Defines */

/** @} */ /* End of group Periph_I2C */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_I2C_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_i2c_defs.h */
