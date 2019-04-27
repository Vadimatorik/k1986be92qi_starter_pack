/**
  ******************************************************************************
  * @file    1986BE9x_spi_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the SPI peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_spi_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_SPI_DEFS_H
#define __1986BE9X_SPI_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_SPI SPI
  * @{
  */

/** @defgroup Periph_SPI_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_SPI_TypeDef SPI_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t SSPx_CR0;
  __IO uint32_t SSPx_CR1;
  __IO uint32_t SSPx_DR;
  __IO uint32_t SSPx_SR;
  __IO uint32_t SSPx_CPSR;
  __IO uint32_t SSPx_IMSC;
  __IO uint32_t SSPx_RIS;
  __IO uint32_t SSPx_MIS;
  __IO uint32_t SSPx_ICR;
  __IO uint32_t SSPx_DMACR;
}SPI_TypeDef;

/** @} */ /* End of group Periph_SPI_TypeDef */

/** @} */ /* End of group Periph_SPI_Data_Structures */

/** @defgroup Periph_SPI_Defines Defines
  * @{
  */

/** @defgroup Periph_SPI_SPI_SSPX_CR0_Bits SPI_SSPX_CR0
  * @{
  */

#define SPI_SSPx_CR0_DSS_Pos                    0
#define SPI_SSPx_CR0_DSS_Msk                    ((uint32_t)0x0000000F)

#define SPI_SSPx_CR0_FRF_Pos                    4
#define SPI_SSPx_CR0_FRF_Msk                    ((uint32_t)0x00000030)

#define SPI_SSPx_CR0_SPO_Pos                    6
#define SPI_SSPx_CR0_SPO                        ((uint32_t)0x00000040)

#define SPI_SSPx_CR0_SPH_Pos                    7
#define SPI_SSPx_CR0_SPH                        ((uint32_t)0x00000080)

#define SPI_SSPx_CR0_SCR_Pos                    8
#define SPI_SSPx_CR0_SCR_Msk                    ((uint32_t)0x0000FF00)


/** @} */ /* End of group Periph_SPI_SPI_SSPX_CR0_Bits */

/** @} */ /* End of group Periph_SPI_Defines */

/** @defgroup Periph_SPI_Defines Defines
  * @{
  */

/** @defgroup Periph_SPI_SPI_SSPX_CR1_Bits SPI_SSPX_CR1
  * @{
  */

#define SPI_SSPx_CR1_LBM_Pos                    0
#define SPI_SSPx_CR1_LBM                        ((uint32_t)0x00000001)

#define SPI_SSPx_CR1_SSE_Pos                    1
#define SPI_SSPx_CR1_SSE                        ((uint32_t)0x00000002)

#define SPI_SSPx_CR1_MS_Pos                     2
#define SPI_SSPx_CR1_MS                         ((uint32_t)0x00000004)

#define SPI_SSPx_CR1_SOD_Pos                    3
#define SPI_SSPx_CR1_SOD                        ((uint32_t)0x00000008)


/** @} */ /* End of group Periph_SPI_SPI_SSPX_CR1_Bits */

/** @} */ /* End of group Periph_SPI_Defines */

/** @defgroup Periph_SPI_Defines Defines
  * @{
  */

/** @defgroup Periph_SPI_SPI_SSPX_SR_Bits SPI_SSPX_SR
  * @{
  */

#define SPI_SSPx_SR_TFE_Pos                     0
#define SPI_SSPx_SR_TFE                         ((uint32_t)0x00000001)

#define SPI_SSPx_SR_TNF_Pos                     1
#define SPI_SSPx_SR_TNF                         ((uint32_t)0x00000002)

#define SPI_SSPx_SR_RNE_Pos                     2
#define SPI_SSPx_SR_RNE                         ((uint32_t)0x00000004)

#define SPI_SSPx_SR_RFF_Pos                     3
#define SPI_SSPx_SR_RFF                         ((uint32_t)0x00000008)

#define SPI_SSPx_SR_BSY_Pos                     4
#define SPI_SSPx_SR_BSY                         ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_SPI_SPI_SSPX_SR_Bits */

/** @} */ /* End of group Periph_SPI_Defines */

/** @defgroup Periph_SPI_Defines Defines
  * @{
  */

/** @defgroup Periph_SPI_SPI_SSPX_IMSC_Bits SPI_SSPX_IMSC
  * @{
  */

#define SPI_SSPx_IMSC_RORIM_Pos                 0
#define SPI_SSPx_IMSC_RORIM                     ((uint32_t)0x00000001)

#define SPI_SSPx_IMSC_RTIM_Pos                  1
#define SPI_SSPx_IMSC_RTIM                      ((uint32_t)0x00000002)

#define SPI_SSPx_IMSC_RXIM_Pos                  2
#define SPI_SSPx_IMSC_RXIM                      ((uint32_t)0x00000004)

#define SPI_SSPx_IMSC_TXIM_Pos                  3
#define SPI_SSPx_IMSC_TXIM                      ((uint32_t)0x00000008)


/** @} */ /* End of group Periph_SPI_SPI_SSPX_IMSC_Bits */

/** @} */ /* End of group Periph_SPI_Defines */

/** @defgroup Periph_SPI_Defines Defines
  * @{
  */

/** @defgroup Periph_SPI_SPI_SSPX_RIS_Bits SPI_SSPX_RIS
  * @{
  */

#define SPI_SSPx_RIS_RORRIS_Pos                 0
#define SPI_SSPx_RIS_RORRIS                     ((uint32_t)0x00000001)

#define SPI_SSPx_RIS_RTRIS_Pos                  1
#define SPI_SSPx_RIS_RTRIS                      ((uint32_t)0x00000002)

#define SPI_SSPx_RIS_RXRIS_Pos                  2
#define SPI_SSPx_RIS_RXRIS                      ((uint32_t)0x00000004)

#define SPI_SSPx_RIS_TXRIS_Pos                  3
#define SPI_SSPx_RIS_TXRIS                      ((uint32_t)0x00000008)


/** @} */ /* End of group Periph_SPI_SPI_SSPX_RIS_Bits */

/** @} */ /* End of group Periph_SPI_Defines */

/** @defgroup Periph_SPI_Defines Defines
  * @{
  */

/** @defgroup Periph_SPI_SPI_SSPX_MIS_Bits SPI_SSPX_MIS
  * @{
  */

#define SPI_SSPx_MIS_RORMIS_Pos                 0
#define SPI_SSPx_MIS_RORMIS                     ((uint32_t)0x00000001)

#define SPI_SSPx_MIS_RTMIS_Pos                  1
#define SPI_SSPx_MIS_RTMIS                      ((uint32_t)0x00000002)

#define SPI_SSPx_MIS_RXMIS_Pos                  2
#define SPI_SSPx_MIS_RXMIS                      ((uint32_t)0x00000004)

#define SPI_SSPx_MIS_TXMIS_Pos                  3
#define SPI_SSPx_MIS_TXMIS                      ((uint32_t)0x00000008)


/** @} */ /* End of group Periph_SPI_SPI_SSPX_MIS_Bits */

/** @} */ /* End of group Periph_SPI_Defines */

/** @defgroup Periph_SPI_Defines Defines
  * @{
  */

/** @defgroup Periph_SPI_SPI_SSPX_ICR_Bits SPI_SSPX_ICR
  * @{
  */

#define SPI_SSPx_ICR_RORIC_Pos                  0
#define SPI_SSPx_ICR_RORIC                      ((uint32_t)0x00000001)

#define SPI_SSPx_ICR_RTIC_Pos                   1
#define SPI_SSPx_ICR_RTIC                       ((uint32_t)0x00000002)


/** @} */ /* End of group Periph_SPI_SPI_SSPX_ICR_Bits */

/** @} */ /* End of group Periph_SPI_Defines */

/** @defgroup Periph_SPI_Defines Defines
  * @{
  */

/** @defgroup Periph_SPI_SPI_SSPX_DMACR_Bits SPI_SSPX_DMACR
  * @{
  */

#define SPI_SSPx_DMACR_RXDMAE_Pos               0
#define SPI_SSPx_DMACR_RXDMAE                   ((uint32_t)0x00000001)

#define SPI_SSPx_DMACR_TXDMAE_Pos               1
#define SPI_SSPx_DMACR_TXDMAE                   ((uint32_t)0x00000002)


/** @} */ /* End of group Periph_SPI_SPI_SSPX_DMACR_Bits */

/** @} */ /* End of group Periph_SPI_Defines */

/** @} */ /* End of group Periph_SPI */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_SPI_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_spi_defs.h */
