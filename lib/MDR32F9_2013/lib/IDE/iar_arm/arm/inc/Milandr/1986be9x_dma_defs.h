/**
  ******************************************************************************
  * @file    1986BE9x_dma_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the DMA peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_dma_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_DMA_DEFS_H
#define __1986BE9X_DMA_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_DMA DMA
  * @{
  */

/** @defgroup Periph_DMA_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_DMA_TypeDef DMA_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t STATUS;
  __IO uint32_t CFG;
  __IO uint32_t CTRL_BASE_PTR;
  __IO uint32_t ALT_CTRL_BASE_PTR;
  __IO uint32_t WAITONREQ_STATUS;
  __IO uint32_t CHNL_SW_REQUEST;
  __IO uint32_t CHNL_USEBURST_SET;
  __IO uint32_t CHNL_USEBURST_CLR;
  __IO uint32_t CHNL_REQ_MASK_SET;
  __IO uint32_t CHNL_REQ_MASK_CLR;
  __IO uint32_t CHNL_ENABLE_SET;
  __IO uint32_t CHNL_ENABLE_CLR;
  __IO uint32_t CHNL_PRI_ALT_SET;
  __IO uint32_t CHNL_PRI_ALT_CLR;
  __IO uint32_t CHNL_PRIORITY_SET;
  __IO uint32_t CHNL_PRIORITY_CLR;
       uint32_t RESERVED0[3];
  __IO uint32_t ERR_CLR;
}DMA_TypeDef;

/** @} */ /* End of group Periph_DMA_TypeDef */

/** @} */ /* End of group Periph_DMA_Data_Structures */

/** @defgroup Periph_DMA_Defines Defines
  * @{
  */

/** @defgroup Periph_DMA_DMA_STATUS_Bits DMA_STATUS
  * @{
  */

#define DMA_STATUS_MASTER_ENABLE_Pos            0
#define DMA_STATUS_MASTER_ENABLE                ((uint32_t)0x00000001)

#define DMA_STATUS_STATE_Pos                    4
#define DMA_STATUS_STATE_Msk                    ((uint32_t)0x000000F0)

#define DMA_STATUS_CHNLS_MINUS1_Pos             16
#define DMA_STATUS_CHNLS_MINUS1_Msk             ((uint32_t)0x001F0000)

#define DMA_STATUS_TEST_STATUS_Pos              28
#define DMA_STATUS_TEST_STATUS_Msk              ((uint32_t)0xF0000000)


/** @} */ /* End of group Periph_DMA_DMA_STATUS_Bits */

/** @} */ /* End of group Periph_DMA_Defines */

/** @defgroup Periph_DMA_Defines Defines
  * @{
  */

/** @defgroup Periph_DMA_DMA_CFG_Bits DMA_CFG
  * @{
  */

#define DMA_CFG_MASTER_ENABLE_Pos               0
#define DMA_CFG_MASTER_ENABLE                   ((uint32_t)0x00000001)

#define DMA_CFG_CHNL_PROT_CTRL_Pos              5
#define DMA_CFG_CHNL_PROT_CTRL_Msk              ((uint32_t)0x000000E0)


/** @} */ /* End of group Periph_DMA_DMA_CFG_Bits */

/** @} */ /* End of group Periph_DMA_Defines */

/** @} */ /* End of group Periph_DMA */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_DMA_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_dma_defs.h */
