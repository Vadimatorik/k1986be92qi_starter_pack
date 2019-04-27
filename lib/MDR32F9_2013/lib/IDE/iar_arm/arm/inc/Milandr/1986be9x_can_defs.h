/**
  ******************************************************************************
  * @file    1986BE9x_can_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the CAN peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_can_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_CAN_DEFS_H
#define __1986BE9X_CAN_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_CAN CAN
  * @{
  */

/**
  * @brief CAN_BUF_TypeDef structure
  */

typedef struct
{
  __IO uint32_t ID;
  __IO uint32_t DLC;
  __IO uint32_t DATAL;
  __IO uint32_t DATAH;
}_CAN_BUF_TypeDef;

/**
  * @brief CAN_BUF_TypeDef0 structure
  */

typedef struct
{
  __IO uint32_t MASK;
  __IO uint32_t FILTER;
}_CAN_BUF_TypeDef0;

/** @defgroup Periph_CAN_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_CAN_TypeDef CAN_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t CONTROL;
  __IO uint32_t STATUS;
  __IO uint32_t BITTMNG;
       uint32_t RESERVED0;
  __IO uint32_t INT_EN;
       uint32_t RESERVED1[2];
  __IO uint32_t OVER;
  __IO uint32_t RXID;
  __IO uint32_t RXDLC;
  __IO uint32_t RXDATAL;
  __IO uint32_t RXDATAH;
  __IO uint32_t TXID;
  __IO uint32_t TXDLC;
  __IO uint32_t DATAL;
  __IO uint32_t DATAH;
  __IO uint32_t BUF_01_CON;
  __IO uint32_t BUF_02_CON;
  __IO uint32_t BUF_03_CON;
  __IO uint32_t BUF_04_CON;
  __IO uint32_t BUF_05_CON;
  __IO uint32_t BUF_06_CON;
  __IO uint32_t BUF_07_CON;
  __IO uint32_t BUF_08_CON;
  __IO uint32_t BUF_09_CON;
  __IO uint32_t BUF_10_CON;
  __IO uint32_t BUF_11_CON;
  __IO uint32_t BUF_12_CON;
  __IO uint32_t BUF_13_CON;
  __IO uint32_t BUF_14_CON;
  __IO uint32_t BUF_15_CON;
  __IO uint32_t BUF_16_CON;
  __IO uint32_t BUF_17_CON;
  __IO uint32_t BUF_18_CON;
  __IO uint32_t BUF_19_CON;
  __IO uint32_t BUF_20_CON;
  __IO uint32_t BUF_21_CON;
  __IO uint32_t BUF_22_CON;
  __IO uint32_t BUF_23_CON;
  __IO uint32_t BUF_24_CON;
  __IO uint32_t BUF_25_CON;
  __IO uint32_t BUF_26_CON;
  __IO uint32_t BUF_27_CON;
  __IO uint32_t BUF_28_CON;
  __IO uint32_t BUF_29_CON;
  __IO uint32_t BUF_30_CON;
  __IO uint32_t BUF_31_CON;
  __IO uint32_t BUF_32_CON;
  __IO uint32_t INT_RX;
  __IO uint32_t RX;
  __IO uint32_t INT_TX;
  __IO uint32_t TX;
       uint32_t RESERVED2[76];
  __IO uint32_t BUF_01_ID;
  __IO uint32_t BUF_01_DLC;
  __IO uint32_t BUF_01_DATAL;
  __IO uint32_t BUF_01_DATAH;
  __IO uint32_t BUF_02_ID;
  __IO uint32_t BUF_02_DLC;
  __IO uint32_t BUF_02_DATAL;
  __IO uint32_t BUF_02_DATAH;
  __IO uint32_t BUF_03_ID;
  __IO uint32_t BUF_03_DLC;
  __IO uint32_t BUF_03_DATAL;
  __IO uint32_t BUF_03_DATAH;
  __IO uint32_t BUF_04_ID;
  __IO uint32_t BUF_04_DLC;
  __IO uint32_t BUF_04_DATAL;
  __IO uint32_t BUF_04_DATAH;
  __IO uint32_t BUF_05_ID;
  __IO uint32_t BUF_05_DLC;
  __IO uint32_t BUF_05_DATAL;
  __IO uint32_t BUF_05_DATAH;
  __IO uint32_t BUF_06_ID;
  __IO uint32_t BUF_06_DLC;
  __IO uint32_t BUF_06_DATAL;
  __IO uint32_t BUF_06_DATAH;
  __IO uint32_t BUF_07_ID;
  __IO uint32_t BUF_07_DLC;
  __IO uint32_t BUF_07_DATAL;
  __IO uint32_t BUF_07_DATAH;
  __IO uint32_t BUF_08_ID;
  __IO uint32_t BUF_08_DLC;
  __IO uint32_t BUF_08_DATAL;
  __IO uint32_t BUF_08_DATAH;
  __IO uint32_t BUF_09_ID;
  __IO uint32_t BUF_09_DLC;
  __IO uint32_t BUF_09_DATAL;
  __IO uint32_t BUF_09_DATAH;
  __IO uint32_t BUF_10_ID;
  __IO uint32_t BUF_10_DLC;
  __IO uint32_t BUF_10_DATAL;
  __IO uint32_t BUF_10_DATAH;
  __IO uint32_t BUF_11_ID;
  __IO uint32_t BUF_11_DLC;
  __IO uint32_t BUF_11_DATAL;
  __IO uint32_t BUF_11_DATAH;
  __IO uint32_t BUF_12_ID;
  __IO uint32_t BUF_12_DLC;
  __IO uint32_t BUF_12_DATAL;
  __IO uint32_t BUF_12_DATAH;
  __IO uint32_t BUF_13_ID;
  __IO uint32_t BUF_13_DLC;
  __IO uint32_t BUF_13_DATAL;
  __IO uint32_t BUF_13_DATAH;
  __IO uint32_t BUF_14_ID;
  __IO uint32_t BUF_14_DLC;
  __IO uint32_t BUF_14_DATAL;
  __IO uint32_t BUF_14_DATAH;
  __IO uint32_t BUF_15_ID;
  __IO uint32_t BUF_15_DLC;
  __IO uint32_t BUF_15_DATAL;
  __IO uint32_t BUF_15_DATAH;
  __IO uint32_t BUF_16_ID;
  __IO uint32_t BUF_16_DLC;
  __IO uint32_t BUF_16_DATAL;
  __IO uint32_t BUF_16_DATAH;
  __IO uint32_t BUF_17_ID;
  __IO uint32_t BUF_17_DLC;
  __IO uint32_t BUF_17_DATAL;
  __IO uint32_t BUF_17_DATAH;
  __IO uint32_t BUF_18_ID;
  __IO uint32_t BUF_18_DLC;
  __IO uint32_t BUF_18_DATAL;
  __IO uint32_t BUF_18_DATAH;
  __IO uint32_t BUF_19_ID;
  __IO uint32_t BUF_19_DLC;
  __IO uint32_t BUF_19_DATAL;
  __IO uint32_t BUF_19_DATAH;
  __IO uint32_t BUF_20_ID;
  __IO uint32_t BUF_20_DLC;
  __IO uint32_t BUF_20_DATAL;
  __IO uint32_t BUF_20_DATAH;
  __IO uint32_t BUF_21_ID;
  __IO uint32_t BUF_21_DLC;
  __IO uint32_t BUF_21_DATAL;
  __IO uint32_t BUF_21_DATAH;
  __IO uint32_t BUF_22_ID;
  __IO uint32_t BUF_22_DLC;
  __IO uint32_t BUF_22_DATAL;
  __IO uint32_t BUF_22_DATAH;
  __IO uint32_t BUF_23_ID;
  __IO uint32_t BUF_23_DLC;
  __IO uint32_t BUF_23_DATAL;
  __IO uint32_t BUF_23_DATAH;
  __IO uint32_t BUF_24_ID;
  __IO uint32_t BUF_24_DLC;
  __IO uint32_t BUF_24_DATAL;
  __IO uint32_t BUF_24_DATAH;
  __IO uint32_t BUF_25_ID;
  __IO uint32_t BUF_25_DLC;
  __IO uint32_t BUF_25_DATAL;
  __IO uint32_t BUF_25_DATAH;
  __IO uint32_t BUF_26_ID;
  __IO uint32_t BUF_26_DLC;
  __IO uint32_t BUF_26_DATAL;
  __IO uint32_t BUF_26_DATAH;
  __IO uint32_t BUF_27_ID;
  __IO uint32_t BUF_27_DLC;
  __IO uint32_t BUF_27_DATAL;
  __IO uint32_t BUF_27_DATAH;
  __IO uint32_t BUF_28_ID;
  __IO uint32_t BUF_28_DLC;
  __IO uint32_t BUF_28_DATAL;
  __IO uint32_t BUF_28_DATAH;
  __IO uint32_t BUF_29_ID;
  __IO uint32_t BUF_29_DLC;
  __IO uint32_t BUF_29_DATAL;
  __IO uint32_t BUF_29_DATAH;
  __IO uint32_t BUF_30_ID;
  __IO uint32_t BUF_30_DLC;
  __IO uint32_t BUF_30_DATAL;
  __IO uint32_t BUF_30_DATAH;
  __IO uint32_t BUF_31_ID;
  __IO uint32_t BUF_31_DLC;
  __IO uint32_t BUF_31_DATAL;
  __IO uint32_t BUF_31_DATAH;
  __IO uint32_t BUF_32_ID;
  __IO uint32_t BUF_32_DLC;
  __IO uint32_t BUF_32_DATAL;
  __IO uint32_t BUF_32_DATAH;
       uint32_t RESERVED3[64];
  __IO uint32_t BUF_01_MASK;
  __IO uint32_t BUF_01_FILTER;
  __IO uint32_t BUF_02_MASK;
  __IO uint32_t BUF_02_FILTER;
  __IO uint32_t BUF_03_MASK;
  __IO uint32_t BUF_03_FILTER;
  __IO uint32_t BUF_04_MASK;
  __IO uint32_t BUF_04_FILTER;
  __IO uint32_t BUF_05_MASK;
  __IO uint32_t BUF_05_FILTER;
  __IO uint32_t BUF_06_MASK;
  __IO uint32_t BUF_06_FILTER;
  __IO uint32_t BUF_07_MASK;
  __IO uint32_t BUF_07_FILTER;
  __IO uint32_t BUF_08_MASK;
  __IO uint32_t BUF_08_FILTER;
  __IO uint32_t BUF_09_MASK;
  __IO uint32_t BUF_09_FILTER;
  __IO uint32_t BUF_10_MASK;
  __IO uint32_t BUF_10_FILTER;
  __IO uint32_t BUF_11_MASK;
  __IO uint32_t BUF_11_FILTER;
  __IO uint32_t BUF_12_MASK;
  __IO uint32_t BUF_12_FILTER;
  __IO uint32_t BUF_13_MASK;
  __IO uint32_t BUF_13_FILTER;
  __IO uint32_t BUF_14_MASK;
  __IO uint32_t BUF_14_FILTER;
  __IO uint32_t BUF_15_MASK;
  __IO uint32_t BUF_15_FILTER;
  __IO uint32_t BUF_16_MASK;
  __IO uint32_t BUF_16_FILTER;
  __IO uint32_t BUF_17_MASK;
  __IO uint32_t BUF_17_FILTER;
  __IO uint32_t BUF_18_MASK;
  __IO uint32_t BUF_18_FILTER;
  __IO uint32_t BUF_19_MASK;
  __IO uint32_t BUF_19_FILTER;
  __IO uint32_t BUF_20_MASK;
  __IO uint32_t BUF_20_FILTER;
  __IO uint32_t BUF_21_MASK;
  __IO uint32_t BUF_21_FILTER;
  __IO uint32_t BUF_22_MASK;
  __IO uint32_t BUF_22_FILTER;
  __IO uint32_t BUF_23_MASK;
  __IO uint32_t BUF_23_FILTER;
  __IO uint32_t BUF_24_MASK;
  __IO uint32_t BUF_24_FILTER;
  __IO uint32_t BUF_25_MASK;
  __IO uint32_t BUF_25_FILTER;
  __IO uint32_t BUF_26_MASK;
  __IO uint32_t BUF_26_FILTER;
  __IO uint32_t BUF_27_MASK;
  __IO uint32_t BUF_27_FILTER;
  __IO uint32_t BUF_28_MASK;
  __IO uint32_t BUF_28_FILTER;
  __IO uint32_t BUF_29_MASK;
  __IO uint32_t BUF_29_FILTER;
  __IO uint32_t BUF_30_MASK;
  __IO uint32_t BUF_30_FILTER;
  __IO uint32_t BUF_31_MASK;
  __IO uint32_t BUF_31_FILTER;
  __IO uint32_t BUF_32_MASK;
  __IO uint32_t BUF_32_FILTER;
}CAN_TypeDef;

/** @} */ /* End of group Periph_CAN_TypeDef */

/** @} */ /* End of group Periph_CAN_Data_Structures */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_CONTROL_Bits CAN_CONTROL
  * @{
  */

#define CAN_CONTROL_CAN_EN_Pos                  0
#define CAN_CONTROL_CAN_EN                      ((uint32_t)0x00000001)

#define CAN_CONTROL_ROM_Pos                     1
#define CAN_CONTROL_ROM                         ((uint32_t)0x00000002)

#define CAN_CONTROL_STM_Pos                     2
#define CAN_CONTROL_STM                         ((uint32_t)0x00000004)

#define CAN_CONTROL_SAP_Pos                     3
#define CAN_CONTROL_SAP                         ((uint32_t)0x00000008)

#define CAN_CONTROL_ROP_Pos                     4
#define CAN_CONTROL_ROP                         ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_CAN_CAN_CONTROL_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_STATUS_Bits CAN_STATUS
  * @{
  */

#define CAN_STATUS_RX_READY_Pos                 0
#define CAN_STATUS_RX_READY                     ((uint32_t)0x00000001)

#define CAN_STATUS_TX_READY_Pos                 1
#define CAN_STATUS_TX_READY                     ((uint32_t)0x00000002)

#define CAN_STATUS_ERROR_OVER_Pos               2
#define CAN_STATUS_ERROR_OVER                   ((uint32_t)0x00000004)

#define CAN_STATUS_BIT_ERR_Pos                  3
#define CAN_STATUS_BIT_ERR                      ((uint32_t)0x00000008)

#define CAN_STATUS_BIT_STUFF_ERR_Pos            4
#define CAN_STATUS_BIT_STUFF_ERR                ((uint32_t)0x00000010)

#define CAN_STATUS_CRC_ERR_Pos                  5
#define CAN_STATUS_CRC_ERR                      ((uint32_t)0x00000020)

#define CAN_STATUS_FRAME_ERR_Pos                6
#define CAN_STATUS_FRAME_ERR                    ((uint32_t)0x00000040)

#define CAN_STATUS_ACK_ERR_Pos                  7
#define CAN_STATUS_ACK_ERR                      ((uint32_t)0x00000080)

#define CAN_STATUS_IDLOWER_Pos                  8
#define CAN_STATUS_IDLOWER                      ((uint32_t)0x00000100)

#define CAN_STATUS_ERR_STATUS_Pos               9
#define CAN_STATUS_ERR_STATUS_Msk               ((uint32_t)0x00000600)

#define CAN_STATUS_RX_ERR_CNT8_Pos              11
#define CAN_STATUS_RX_ERR_CNT8                  ((uint32_t)0x00000800)

#define CAN_STATUS_TX_ERR_CNT8_Pos              12
#define CAN_STATUS_TX_ERR_CNT8                  ((uint32_t)0x00001000)

#define CAN_STATUS_RX_ERR_CNT_Pos               16
#define CAN_STATUS_RX_ERR_CNT_Msk               ((uint32_t)0x00FF0000)

#define CAN_STATUS_TX_ERR_CNT_Pos               24
#define CAN_STATUS_TX_ERR_CNT_Msk               ((uint32_t)0xFF000000)


/** @} */ /* End of group Periph_CAN_CAN_STATUS_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_BITTMNG_Bits CAN_BITTMNG
  * @{
  */

#define CAN_BITTMNG_BRP_Pos                     0
#define CAN_BITTMNG_BRP_Msk                     ((uint32_t)0x0000FFFF)

#define CAN_BITTMNG_PSEG_Pos                    16
#define CAN_BITTMNG_PSEG_Msk                    ((uint32_t)0x00070000)

#define CAN_BITTMNG_SEG1_Pos                    19
#define CAN_BITTMNG_SEG1_Msk                    ((uint32_t)0x00380000)

#define CAN_BITTMNG_SEG2_Pos                    22
#define CAN_BITTMNG_SEG2_Msk                    ((uint32_t)0x01C00000)

#define CAN_BITTMNG_SJW_Pos                     25
#define CAN_BITTMNG_SJW_Msk                     ((uint32_t)0x06000000)

#define CAN_BITTMNG_SB_Pos                      27
#define CAN_BITTMNG_SB                          ((uint32_t)0x08000000)


/** @} */ /* End of group Periph_CAN_CAN_BITTMNG_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_INT_EN_Bits CAN_INT_EN
  * @{
  */

#define CAN_INT_EN_GLB_INT_EN_Pos               0
#define CAN_INT_EN_GLB_INT_EN                   ((uint32_t)0x00000001)

#define CAN_INT_EN_RX_INT_EN_Pos                1
#define CAN_INT_EN_RX_INT_EN                    ((uint32_t)0x00000002)

#define CAN_INT_EN_TX_INT_EN_Pos                2
#define CAN_INT_EN_TX_INT_EN                    ((uint32_t)0x00000004)

#define CAN_INT_EN_ERR_INT_EN_Pos               3
#define CAN_INT_EN_ERR_INT_EN                   ((uint32_t)0x00000008)

#define CAN_INT_EN_ERR_OVER_INT_EN_Pos          4
#define CAN_INT_EN_ERR_OVER_INT_EN              ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_CAN_CAN_INT_EN_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_RXID_Bits CAN_RXID
  * @{
  */

#define CAN_RXID_EID_Pos                        0
#define CAN_RXID_EID_Msk                        ((uint32_t)0x0003FFFF)

#define CAN_RXID_SID_Pos                        18
#define CAN_RXID_SID_Msk                        ((uint32_t)0x1FFC0000)


/** @} */ /* End of group Periph_CAN_CAN_RXID_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_RXDLC_Bits CAN_RXDLC
  * @{
  */

#define CAN_RXDLC_Pos                           0
#define CAN_RXDLC_Msk                           ((uint32_t)0x0000000F)

#define CAN_RXDLC_RTR_Pos                       8
#define CAN_RXDLC_RTR                           ((uint32_t)0x00000100)

#define CAN_RXDLC_R1_Pos                        9
#define CAN_RXDLC_R1                            ((uint32_t)0x00000200)

#define CAN_RXDLC_R0_Pos                        10
#define CAN_RXDLC_R0                            ((uint32_t)0x00000400)

#define CAN_RXDLC_SSR_Pos                       11
#define CAN_RXDLC_SSR                           ((uint32_t)0x00000800)

#define CAN_RXDLC_IDE_Pos                       12
#define CAN_RXDLC_IDE                           ((uint32_t)0x00001000)


/** @} */ /* End of group Periph_CAN_CAN_RXDLC_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_RXDATAL_Bits CAN_RXDATAL
  * @{
  */

#define CAN_RXDATAL_DB0_Pos                     0
#define CAN_RXDATAL_DB0_Msk                     ((uint32_t)0x000000FF)

#define CAN_RXDATAL_DB1_Pos                     8
#define CAN_RXDATAL_DB1_Msk                     ((uint32_t)0x0000FF00)

#define CAN_RXDATAL_DB2_Pos                     16
#define CAN_RXDATAL_DB2_Msk                     ((uint32_t)0x00FF0000)

#define CAN_RXDATAL_DB3_Pos                     24
#define CAN_RXDATAL_DB3_Msk                     ((uint32_t)0xFF000000)


/** @} */ /* End of group Periph_CAN_CAN_RXDATAL_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_RXDATAH_Bits CAN_RXDATAH
  * @{
  */

#define CAN_RXDATAH_DB4_Pos                     0
#define CAN_RXDATAH_DB4_Msk                     ((uint32_t)0x000000FF)

#define CAN_RXDATAH_DB5_Pos                     8
#define CAN_RXDATAH_DB5_Msk                     ((uint32_t)0x0000FF00)

#define CAN_RXDATAH_DB6_Pos                     16
#define CAN_RXDATAH_DB6_Msk                     ((uint32_t)0x00FF0000)

#define CAN_RXDATAH_DB7_Pos                     24
#define CAN_RXDATAH_DB7_Msk                     ((uint32_t)0xFF000000)


/** @} */ /* End of group Periph_CAN_CAN_RXDATAH_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_TXID_Bits CAN_TXID
  * @{
  */

#define CAN_TXID_EID_Pos                        0
#define CAN_TXID_EID_Msk                        ((uint32_t)0x0003FFFF)

#define CAN_TXID_SID_Pos                        18
#define CAN_TXID_SID_Msk                        ((uint32_t)0x1FFC0000)


/** @} */ /* End of group Periph_CAN_CAN_TXID_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_TXDLC_Bits CAN_TXDLC
  * @{
  */

#define CAN_TXDLC_Pos                           0
#define CAN_TXDLC_Msk                           ((uint32_t)0x0000000F)

#define CAN_TXDLC_RTR_Pos                       8
#define CAN_TXDLC_RTR                           ((uint32_t)0x00000100)

#define CAN_TXDLC_R1_Pos                        9
#define CAN_TXDLC_R1                            ((uint32_t)0x00000200)

#define CAN_TXDLC_R0_Pos                        10
#define CAN_TXDLC_R0                            ((uint32_t)0x00000400)

#define CAN_TXDLC_SSR_Pos                       11
#define CAN_TXDLC_SSR                           ((uint32_t)0x00000800)

#define CAN_TXDLC_IDE_Pos                       12
#define CAN_TXDLC_IDE                           ((uint32_t)0x00001000)


/** @} */ /* End of group Periph_CAN_CAN_TXDLC_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_DATAL_Bits CAN_DATAL
  * @{
  */

#define CAN_DATAL_DB0_Pos                       0
#define CAN_DATAL_DB0_Msk                       ((uint32_t)0x000000FF)

#define CAN_DATAL_DB1_Pos                       8
#define CAN_DATAL_DB1_Msk                       ((uint32_t)0x0000FF00)

#define CAN_DATAL_DB2_Pos                       16
#define CAN_DATAL_DB2_Msk                       ((uint32_t)0x00FF0000)

#define CAN_DATAL_DB3_Pos                       24
#define CAN_DATAL_DB3_Msk                       ((uint32_t)0xFF000000)


/** @} */ /* End of group Periph_CAN_CAN_DATAL_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_DATAH_Bits CAN_DATAH
  * @{
  */

#define CAN_DATAH_DB4_Pos                       0
#define CAN_DATAH_DB4_Msk                       ((uint32_t)0x000000FF)

#define CAN_DATAH_DB5_Pos                       8
#define CAN_DATAH_DB5_Msk                       ((uint32_t)0x0000FF00)

#define CAN_DATAH_DB6_Pos                       16
#define CAN_DATAH_DB6_Msk                       ((uint32_t)0x00FF0000)

#define CAN_DATAH_DB7_Pos                       24
#define CAN_DATAH_DB7_Msk                       ((uint32_t)0xFF000000)


/** @} */ /* End of group Periph_CAN_CAN_DATAH_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_BUF_CON_Bits CAN_BUF_CON
  * @{
  */

#define CAN_BUF_CON_EN_Pos                      0
#define CAN_BUF_CON_EN                          ((uint32_t)0x00000001)

#define CAN_BUF_CON_RX_TXn_Pos                  1
#define CAN_BUF_CON_RX_TXn                      ((uint32_t)0x00000002)

#define CAN_BUF_CON_OVER_EN_Pos                 2
#define CAN_BUF_CON_OVER_EN                     ((uint32_t)0x00000004)

#define CAN_BUF_CON_RTR_EN_Pos                  3
#define CAN_BUF_CON_RTR_EN                      ((uint32_t)0x00000008)

#define CAN_BUF_CON_PRIOR_0_Pos                 4
#define CAN_BUF_CON_PRIOR_0                     ((uint32_t)0x00000010)

#define CAN_BUF_CON_TX_REQ_Pos                  5
#define CAN_BUF_CON_TX_REQ                      ((uint32_t)0x00000020)

#define CAN_BUF_CON_RX_FULL_Pos                 6
#define CAN_BUF_CON_RX_FULL                     ((uint32_t)0x00000040)

#define CAN_BUF_CON_OVER_WR_Pos                 7
#define CAN_BUF_CON_OVER_WR                     ((uint32_t)0x00000080)


/** @} */ /* End of group Periph_CAN_CAN_BUF_CON_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_BUF_ID_Bits CAN_BUF_ID
  * @{
  */

#define CAN_BUF_ID_EID_Pos                      0
#define CAN_BUF_ID_EID_Msk                      ((uint32_t)0x0003FFFF)

#define CAN_BUF_ID_SID_Pos                      18
#define CAN_BUF_ID_SID_Msk                      ((uint32_t)0x1FFC0000)


/** @} */ /* End of group Periph_CAN_CAN_BUF_ID_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_BUF_DLC_Bits CAN_BUF_DLC
  * @{
  */

#define CAN_BUF_DLC_Pos                         0
#define CAN_BUF_DLC_Msk                         ((uint32_t)0x0000000F)

#define CAN_BUF_DLC_RTR_Pos                     8
#define CAN_BUF_DLC_RTR                         ((uint32_t)0x00000100)

#define CAN_BUF_DLC_R1_Pos                      9
#define CAN_BUF_DLC_R1                          ((uint32_t)0x00000200)

#define CAN_BUF_DLC_R0_Pos                      10
#define CAN_BUF_DLC_R0                          ((uint32_t)0x00000400)

#define CAN_BUF_DLC_SSR_Pos                     11
#define CAN_BUF_DLC_SSR                         ((uint32_t)0x00000800)

#define CAN_BUF_DLC_IDE_Pos                     12
#define CAN_BUF_DLC_IDE                         ((uint32_t)0x00001000)


/** @} */ /* End of group Periph_CAN_CAN_BUF_DLC_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_BUF_DATAL_Bits CAN_BUF_DATAL
  * @{
  */

#define CAN_BUF_DATAL_DB0_Pos                   0
#define CAN_BUF_DATAL_DB0_Msk                   ((uint32_t)0x000000FF)

#define CAN_BUF_DATAL_DB1_Pos                   8
#define CAN_BUF_DATAL_DB1_Msk                   ((uint32_t)0x0000FF00)

#define CAN_BUF_DATAL_DB2_Pos                   16
#define CAN_BUF_DATAL_DB2_Msk                   ((uint32_t)0x00FF0000)

#define CAN_BUF_DATAL_DB3_Pos                   24
#define CAN_BUF_DATAL_DB3_Msk                   ((uint32_t)0xFF000000)


/** @} */ /* End of group Periph_CAN_CAN_BUF_DATAL_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @defgroup Periph_CAN_Defines Defines
  * @{
  */

/** @defgroup Periph_CAN_CAN_BUF_DATAH_Bits CAN_BUF_DATAH
  * @{
  */

#define CAN_BUF_DATAH_DB4_Pos                   0
#define CAN_BUF_DATAH_DB4_Msk                   ((uint32_t)0x000000FF)

#define CAN_BUF_DATAH_DB5_Pos                   8
#define CAN_BUF_DATAH_DB5_Msk                   ((uint32_t)0x0000FF00)

#define CAN_BUF_DATAH_DB6_Pos                   16
#define CAN_BUF_DATAH_DB6_Msk                   ((uint32_t)0x00FF0000)

#define CAN_BUF_DATAH_DB7_Pos                   24
#define CAN_BUF_DATAH_DB7_Msk                   ((uint32_t)0xFF000000)


/** @} */ /* End of group Periph_CAN_CAN_BUF_DATAH_Bits */

/** @} */ /* End of group Periph_CAN_Defines */

/** @} */ /* End of group Periph_CAN */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_CAN_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_can_defs.h */
