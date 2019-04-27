/**
  ******************************************************************************
  * @file    1986BE9x_uart_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the UART peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_uart_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_UART_DEFS_H
#define __1986BE9X_UART_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_UART UART
  * @{
  */

/** @defgroup Periph_UART_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_UART_TypeDef UART_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t DR;
  __IO uint32_t RSR_ECR;
       uint32_t RESERVED0[4];
  __IO uint32_t FR;
       uint32_t RESERVED1;
  __IO uint32_t ILPR;
  __IO uint32_t IBRD;
  __IO uint32_t FBRD;
  __IO uint32_t LCR_H;
  __IO uint32_t CR;
  __IO uint32_t IFLS;
  __IO uint32_t IMSC;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t ICR;
  __IO uint32_t DMACR;
}UART_TypeDef;

/** @} */ /* End of group Periph_UART_TypeDef */

/** @} */ /* End of group Periph_UART_Data_Structures */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_DR_Bits UART_DR
  * @{
  */

#define UART_DR_DATA_Pos                        0
#define UART_DR_DATA_Msk                        ((uint32_t)0x000000FF)

#define UART_DR_FE_Pos                          8
#define UART_DR_FE                              ((uint32_t)0x00000100)

#define UART_DR_PE_Pos                          9
#define UART_DR_PE                              ((uint32_t)0x00000200)

#define UART_DR_BE_Pos                          10
#define UART_DR_BE                              ((uint32_t)0x00000400)

#define UART_DR_OE_Pos                          11
#define UART_DR_OE                              ((uint32_t)0x00000800)


/** @} */ /* End of group Periph_UART_UART_DR_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_RSR_ECR_Bits UART_RSR_ECR
  * @{
  */

#define UART_RSR_ECR_FE_Pos                     0
#define UART_RSR_ECR_FE                         ((uint32_t)0x00000001)

#define UART_RSR_ECR_PE_Pos                     1
#define UART_RSR_ECR_PE                         ((uint32_t)0x00000002)

#define UART_RSR_ECR_BE_Pos                     2
#define UART_RSR_ECR_BE                         ((uint32_t)0x00000004)

#define UART_RSR_ECR_OE_Pos                     3
#define UART_RSR_ECR_OE                         ((uint32_t)0x00000008)


/** @} */ /* End of group Periph_UART_UART_RSR_ECR_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_FR_Bits UART_FR
  * @{
  */

#define UART_FR_CTS_Pos                         0
#define UART_FR_CTS                             ((uint32_t)0x00000001)

#define UART_FR_DSR_Pos                         1
#define UART_FR_DSR                             ((uint32_t)0x00000002)

#define UART_FR_DCD_Pos                         2
#define UART_FR_DCD                             ((uint32_t)0x00000004)

#define UART_FR_BUSY_Pos                        3
#define UART_FR_BUSY                            ((uint32_t)0x00000008)

#define UART_FR_RXFE_Pos                        4
#define UART_FR_RXFE                            ((uint32_t)0x00000010)

#define UART_FR_TXFF_Pos                        5
#define UART_FR_TXFF                            ((uint32_t)0x00000020)

#define UART_FR_RXFF_Pos                        6
#define UART_FR_RXFF                            ((uint32_t)0x00000040)

#define UART_FR_TXFE_Pos                        7
#define UART_FR_TXFE                            ((uint32_t)0x00000080)

#define UART_FR_RI_Pos                          8
#define UART_FR_RI                              ((uint32_t)0x00000100)


/** @} */ /* End of group Periph_UART_UART_FR_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_LCR_H_Bits UART_LCR_H
  * @{
  */

#define UART_LCR_H_BRK_Pos                      0
#define UART_LCR_H_BRK                          ((uint32_t)0x00000001)

#define UART_LCR_H_PEN_Pos                      1
#define UART_LCR_H_PEN                          ((uint32_t)0x00000002)

#define UART_LCR_H_EPS_Pos                      2
#define UART_LCR_H_EPS                          ((uint32_t)0x00000004)

#define UART_LCR_H_STP2_Pos                     3
#define UART_LCR_H_STP2                         ((uint32_t)0x00000008)

#define UART_LCR_H_FEN_Pos                      4
#define UART_LCR_H_FEN                          ((uint32_t)0x00000010)

#define UART_LCR_H_WLEN_Pos                     5
#define UART_LCR_H_WLEN_Msk                     ((uint32_t)0x00000060)

#define UART_LCR_H_SPS_Pos                      7
#define UART_LCR_H_SPS                          ((uint32_t)0x00000080)


/** @} */ /* End of group Periph_UART_UART_LCR_H_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_CR_Bits UART_CR
  * @{
  */

#define UART_CR_UARTEN_Pos                      0
#define UART_CR_UARTEN                          ((uint32_t)0x00000001)

#define UART_CR_SIREN_Pos                       1
#define UART_CR_SIREN                           ((uint32_t)0x00000002)

#define UART_CR_SIRLP_Pos                       2
#define UART_CR_SIRLP                           ((uint32_t)0x00000004)

#define UART_CR_LBE_Pos                         7
#define UART_CR_LBE                             ((uint32_t)0x00000080)

#define UART_CR_TXE_Pos                         8
#define UART_CR_TXE                             ((uint32_t)0x00000100)

#define UART_CR_RXE_Pos                         9
#define UART_CR_RXE                             ((uint32_t)0x00000200)

#define UART_CR_DTR_Pos                         10
#define UART_CR_DTR                             ((uint32_t)0x00000400)

#define UART_CR_RTS_Pos                         11
#define UART_CR_RTS                             ((uint32_t)0x00000800)

#define UART_CR_Out1_Pos                        12
#define UART_CR_Out1                            ((uint32_t)0x00001000)

#define UART_CR_Out2_Pos                        13
#define UART_CR_Out2                            ((uint32_t)0x00002000)

#define UART_CR_RTSEn_Pos                       14
#define UART_CR_RTSEn                           ((uint32_t)0x00004000)

#define UART_CR_CTSEn_Pos                       15
#define UART_CR_CTSEn                           ((uint32_t)0x00008000)


/** @} */ /* End of group Periph_UART_UART_CR_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_IFLS_Bits UART_IFLS
  * @{
  */

#define UART_IFLS_TXIFLSEL_Pos                  0
#define UART_IFLS_TXIFLSEL_Msk                  ((uint32_t)0x00000007)

#define UART_IFLS_RXIFLSEL_Pos                  3
#define UART_IFLS_RXIFLSEL_Msk                  ((uint32_t)0x00000038)


/** @} */ /* End of group Periph_UART_UART_IFLS_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_IMSC_Bits UART_IMSC
  * @{
  */

#define UART_IMSC_RIMIM_Pos                     0
#define UART_IMSC_RIMIM                         ((uint32_t)0x00000001)

#define UART_IMSC_CTSMIM_Pos                    1
#define UART_IMSC_CTSMIM                        ((uint32_t)0x00000002)

#define UART_IMSC_DCDMIM_Pos                    2
#define UART_IMSC_DCDMIM                        ((uint32_t)0x00000004)

#define UART_IMSC_DSRMIM_Pos                    3
#define UART_IMSC_DSRMIM                        ((uint32_t)0x00000008)

#define UART_IMSC_RXIM_Pos                      4
#define UART_IMSC_RXIM                          ((uint32_t)0x00000010)

#define UART_IMSC_TXIM_Pos                      5
#define UART_IMSC_TXIM                          ((uint32_t)0x00000020)

#define UART_IMSC_RTIM_Pos                      6
#define UART_IMSC_RTIM                          ((uint32_t)0x00000040)

#define UART_IMSC_FEIM_Pos                      7
#define UART_IMSC_FEIM                          ((uint32_t)0x00000080)

#define UART_IMSC_PEIM_Pos                      8
#define UART_IMSC_PEIM                          ((uint32_t)0x00000100)

#define UART_IMSC_BEIM_Pos                      9
#define UART_IMSC_BEIM                          ((uint32_t)0x00000200)

#define UART_IMSC_OEIM_Pos                      10
#define UART_IMSC_OEIM                          ((uint32_t)0x00000400)


/** @} */ /* End of group Periph_UART_UART_IMSC_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_RIS_Bits UART_RIS
  * @{
  */

#define UART_RIS_RIRMIS_Pos                     0
#define UART_RIS_RIRMIS                         ((uint32_t)0x00000001)

#define UART_RIS_CTSRMIS_Pos                    1
#define UART_RIS_CTSRMIS                        ((uint32_t)0x00000002)

#define UART_RIS_DCDRMIS_Pos                    2
#define UART_RIS_DCDRMIS                        ((uint32_t)0x00000004)

#define UART_RIS_DSRRMIS_Pos                    3
#define UART_RIS_DSRRMIS                        ((uint32_t)0x00000008)

#define UART_RIS_RXRIS_Pos                      4
#define UART_RIS_RXRIS                          ((uint32_t)0x00000010)

#define UART_RIS_TXRIS_Pos                      5
#define UART_RIS_TXRIS                          ((uint32_t)0x00000020)

#define UART_RIS_RTRIS_Pos                      6
#define UART_RIS_RTRIS                          ((uint32_t)0x00000040)

#define UART_RIS_FERIS_Pos                      7
#define UART_RIS_FERIS                          ((uint32_t)0x00000080)

#define UART_RIS_PERIS_Pos                      8
#define UART_RIS_PERIS                          ((uint32_t)0x00000100)

#define UART_RIS_BERIS_Pos                      9
#define UART_RIS_BERIS                          ((uint32_t)0x00000200)

#define UART_RIS_OERIS_Pos                      10
#define UART_RIS_OERIS                          ((uint32_t)0x00000400)


/** @} */ /* End of group Periph_UART_UART_RIS_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_MIS_Bits UART_MIS
  * @{
  */

#define UART_MIS_RIMMIS_Pos                     0
#define UART_MIS_RIMMIS                         ((uint32_t)0x00000001)

#define UART_MIS_CTSMMIS_Pos                    1
#define UART_MIS_CTSMMIS                        ((uint32_t)0x00000002)

#define UART_MIS_DCDMMIS_Pos                    2
#define UART_MIS_DCDMMIS                        ((uint32_t)0x00000004)

#define UART_MIS_DSRMMIS_Pos                    3
#define UART_MIS_DSRMMIS                        ((uint32_t)0x00000008)

#define UART_MIS_RXMIS_Pos                      4
#define UART_MIS_RXMIS                          ((uint32_t)0x00000010)

#define UART_MIS_TXMIS_Pos                      5
#define UART_MIS_TXMIS                          ((uint32_t)0x00000020)

#define UART_MIS_RTMIS_Pos                      6
#define UART_MIS_RTMIS                          ((uint32_t)0x00000040)

#define UART_MIS_FEMIS_Pos                      7
#define UART_MIS_FEMIS                          ((uint32_t)0x00000080)

#define UART_MIS_PEMIS_Pos                      8
#define UART_MIS_PEMIS                          ((uint32_t)0x00000100)

#define UART_MIS_BEMIS_Pos                      9
#define UART_MIS_BEMIS                          ((uint32_t)0x00000200)

#define UART_MIS_OEMIS_Pos                      10
#define UART_MIS_OEMIS                          ((uint32_t)0x00000400)


/** @} */ /* End of group Periph_UART_UART_MIS_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_ICR_Bits UART_ICR
  * @{
  */

#define UART_ICR_RIMIC_Pos                      0
#define UART_ICR_RIMIC                          ((uint32_t)0x00000001)

#define UART_ICR_CTSMIC_Pos                     1
#define UART_ICR_CTSMIC                         ((uint32_t)0x00000002)

#define UART_ICR_DCDMIC_Pos                     2
#define UART_ICR_DCDMIC                         ((uint32_t)0x00000004)

#define UART_ICR_DSRMIC_Pos                     3
#define UART_ICR_DSRMIC                         ((uint32_t)0x00000008)

#define UART_ICR_RXIC_Pos                       4
#define UART_ICR_RXIC                           ((uint32_t)0x00000010)

#define UART_ICR_TXIC_Pos                       5
#define UART_ICR_TXIC                           ((uint32_t)0x00000020)

#define UART_ICR_RTIC_Pos                       6
#define UART_ICR_RTIC                           ((uint32_t)0x00000040)

#define UART_ICR_FEIC_Pos                       7
#define UART_ICR_FEIC                           ((uint32_t)0x00000080)

#define UART_ICR_PEIC_Pos                       8
#define UART_ICR_PEIC                           ((uint32_t)0x00000100)

#define UART_ICR_BEIC_Pos                       9
#define UART_ICR_BEIC                           ((uint32_t)0x00000200)

#define UART_ICR_OEIC_Pos                       10
#define UART_ICR_OEIC                           ((uint32_t)0x00000400)


/** @} */ /* End of group Periph_UART_UART_ICR_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @defgroup Periph_UART_Defines Defines
  * @{
  */

/** @defgroup Periph_UART_UART_DMACR_Bits UART_DMACR
  * @{
  */

#define UART_DMACR_RXDMAE_Pos                   0
#define UART_DMACR_RXDMAE                       ((uint32_t)0x00000001)

#define UART_DMACR_TXDMAE_Pos                   1
#define UART_DMACR_TXDMAE                       ((uint32_t)0x00000002)

#define UART_DMACR_DMAONERR_Pos                 2
#define UART_DMACR_DMAONERR                     ((uint32_t)0x00000004)


/** @} */ /* End of group Periph_UART_UART_DMACR_Bits */

/** @} */ /* End of group Periph_UART_Defines */

/** @} */ /* End of group Periph_UART */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_UART_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_uart_defs.h */
