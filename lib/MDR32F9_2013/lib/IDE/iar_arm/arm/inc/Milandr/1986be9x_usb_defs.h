/**
  ******************************************************************************
  * @file    1986BE9x_usb_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    24/09/2010
  * @brief   This file contains all the Special Function Registers definitions
  *          for the USB peripheral unit used in the Milandr 1986BE9x
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
  * FILE 1986BE9x_usb_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __1986BE9X_USB_DEFS_H
#define __1986BE9X_USB_DEFS_H

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup __1986BE9x_Peripheral_Units 1986BE9x Peripheral Units
  * @{
  */

/** @defgroup Periph_USB USB
  * @{
  */

/**
  * @brief USB_SEP_TypeDef structure
  */

typedef struct
{
  __IO uint32_t CTRL;
  __IO uint32_t STS;
  __IO uint32_t TS;
  __IO uint32_t NTS;
}_USB_SEP_TypeDef;

/**
  * @brief USB_SEP_TypeDef0 structure
  */

typedef struct
{
  __IO uint32_t RXFD;
       uint32_t RESERVED0;
  __IO uint32_t RXFDC_L;
  __IO uint32_t RXFDC_H;
  __IO uint32_t RXFC;
       uint32_t RESERVED1[11];
  __IO uint32_t TXFD;
       uint32_t RESERVED2[3];
  __IO uint32_t TXFDC;
}_USB_SEP_TypeDef0;

/** @defgroup Periph_USB_Data_Structures Data Structures
  * @{
  */

/** @defgroup Periph_USB_TypeDef USB_TypeDef
  * @{
  */

typedef struct
{
  __IO uint32_t HTXC;
  __IO uint32_t HTXT;
  __IO uint32_t HTXLC;
  __IO uint32_t HTXSE;
  __IO uint32_t HTXA;
  __IO uint32_t HTXE;
  __IO uint32_t HFN_L;
  __IO uint32_t HFN_H;
  __IO uint32_t HIS;
  __IO uint32_t HIM;
  __IO uint32_t HRXS;
  __IO uint32_t HRXP;
  __IO uint32_t HRXA;
  __IO uint32_t HRXE;
  __IO uint32_t HRXCS;
  __IO uint32_t HSTM;
       uint32_t RESERVED0[16];
  __IO uint32_t HRXFD;
       uint32_t RESERVED1;
  __IO uint32_t HRXFDC_L;
  __IO uint32_t HRXFDC_H;
  __IO uint32_t HRXFC;
       uint32_t RESERVED2[11];
  __IO uint32_t HTXFD;
       uint32_t RESERVED3[3];
  __IO uint32_t HTXFDC;
       uint32_t RESERVED4[11];
  __IO uint32_t SEP0_CTRL;
  __IO uint32_t SEP0_STS;
  __IO uint32_t SEP0_TS;
  __IO uint32_t SEP0_NTS;
  __IO uint32_t SEP1_CTRL;
  __IO uint32_t SEP1_STS;
  __IO uint32_t SEP1_TS;
  __IO uint32_t SEP1_NTS;
  __IO uint32_t SEP2_CTRL;
  __IO uint32_t SEP2_STS;
  __IO uint32_t SEP2_TS;
  __IO uint32_t SEP2_NTS;
  __IO uint32_t SEP3_CTRL;
  __IO uint32_t SEP3_STS;
  __IO uint32_t SEP3_TS;
  __IO uint32_t SEP3_NTS;
  __IO uint32_t SC;
  __IO uint32_t SLS;
  __IO uint32_t SIS;
  __IO uint32_t SIM;
  __IO uint32_t SA;
  __IO uint32_t SFN_L;
  __IO uint32_t SFN_H;
       uint32_t RESERVED5[9];
  __IO uint32_t SEP0_RXFD;
       uint32_t RESERVED6;
  __IO uint32_t SEP0_RXFDC_L;
  __IO uint32_t SEP0_RXFDC_H;
  __IO uint32_t SEP0_RXFC;
       uint32_t RESERVED7[11];
  __IO uint32_t SEP0_TXFD;
       uint32_t RESERVED8[3];
  __IO uint32_t SEP0_TXFDC;
       uint32_t RESERVED9[11];
  __IO uint32_t SEP1_RXFD;
       uint32_t RESERVED10;
  __IO uint32_t SEP1_RXFDC_L;
  __IO uint32_t SEP1_RXFDC_H;
  __IO uint32_t SEP1_RXFC;
       uint32_t RESERVED11[11];
  __IO uint32_t SEP1_TXFD;
       uint32_t RESERVED12[3];
  __IO uint32_t SEP1_TXFDC;
       uint32_t RESERVED13[11];
  __IO uint32_t SEP2_RXFD;
       uint32_t RESERVED14;
  __IO uint32_t SEP2_RXFDC_L;
  __IO uint32_t SEP2_RXFDC_H;
  __IO uint32_t SEP2_RXFC;
       uint32_t RESERVED15[11];
  __IO uint32_t SEP2_TXFD;
       uint32_t RESERVED16[3];
  __IO uint32_t SEP2_TXFDC;
       uint32_t RESERVED17[11];
  __IO uint32_t SEP3_RXFD;
       uint32_t RESERVED18;
  __IO uint32_t SEP3_RXFDC_L;
  __IO uint32_t SEP3_RXFDC_H;
  __IO uint32_t SEP3_RXFC;
       uint32_t RESERVED19[11];
  __IO uint32_t SEP3_TXFD;
       uint32_t RESERVED20[3];
  __IO uint32_t SEP3_TXFDC;
       uint32_t RESERVED21[11];
  __IO uint32_t HSCR;
  __IO uint32_t HSVR;
}USB_TypeDef;

/** @} */ /* End of group Periph_USB_TypeDef */

/** @} */ /* End of group Periph_USB_Data_Structures */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_HTXC_Bits USB_HTXC
  * @{
  */

#define USB_HTXC_TREQ_Pos                       0
#define USB_HTXC_TREQ                           ((uint32_t)0x00000001)

#define USB_HTXC_SOFS_Pos                       1
#define USB_HTXC_SOFS                           ((uint32_t)0x00000002)

#define USB_HTXC_PREEN_Pos                      2
#define USB_HTXC_PREEN                          ((uint32_t)0x00000004)

#define USB_HTXC_ISOEN_Pos                      3
#define USB_HTXC_ISOEN                          ((uint32_t)0x00000008)


/** @} */ /* End of group Periph_USB_USB_HTXC_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_HTXLC_Bits USB_HTXLC
  * @{
  */

#define USB_HTXLC_Pos                           0
#define USB_HTXLC_Msk                           ((uint32_t)0x00000003)

#define USB_HTXLC_DC_Pos                        2
#define USB_HTXLC_DC                            ((uint32_t)0x00000004)

#define USB_HTXLC_FSPL_Pos                      3
#define USB_HTXLC_FSPL                          ((uint32_t)0x00000008)

#define USB_HTXLC_FSLR_Pos                      4
#define USB_HTXLC_FSLR                          ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_USB_USB_HTXLC_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_HIS_Bits USB_HIS
  * @{
  */

#define USB_HIS_TDONE_Pos                       0
#define USB_HIS_TDONE                           ((uint32_t)0x00000001)

#define USB_HIS_RESUME_Pos                      1
#define USB_HIS_RESUME                          ((uint32_t)0x00000002)

#define USB_HIS_CONEV_Pos                       2
#define USB_HIS_CONEV                           ((uint32_t)0x00000004)

#define USB_HIS_SOFS_Pos                        3
#define USB_HIS_SOFS                            ((uint32_t)0x00000008)


/** @} */ /* End of group Periph_USB_USB_HIS_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_HIM_Bits USB_HIM
  * @{
  */

#define USB_HIM_TDONEIE_Pos                     0
#define USB_HIM_TDONEIE                         ((uint32_t)0x00000001)

#define USB_HIM_RESUMEIE_Pos                    1
#define USB_HIM_RESUMEIE                        ((uint32_t)0x00000002)

#define USB_HIM_CONEVIE_Pos                     2
#define USB_HIM_CONEVIE                         ((uint32_t)0x00000004)

#define USB_HIM_SOFIE_Pos                       3
#define USB_HIM_SOFIE                           ((uint32_t)0x00000008)


/** @} */ /* End of group Periph_USB_USB_HIM_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_HRXS_Bits USB_HRXS
  * @{
  */

#define USB_HRXS_CRCERR_Pos                     0
#define USB_HRXS_CRCERR                         ((uint32_t)0x00000001)

#define USB_HRXS_BSERR_Pos                      1
#define USB_HRXS_BSERR                          ((uint32_t)0x00000002)

#define USB_HRXS_RXOF_Pos                       2
#define USB_HRXS_RXOF                           ((uint32_t)0x00000004)

#define USB_HRXS_RXTO_Pos                       3
#define USB_HRXS_RXTO                           ((uint32_t)0x00000008)

#define USB_HRXS_NAKRXED_Pos                    4
#define USB_HRXS_NAKRXED                        ((uint32_t)0x00000010)

#define USB_HRXS_STALLRXED_Pos                  5
#define USB_HRXS_STALLRXED                      ((uint32_t)0x00000020)

#define USB_HRXS_ACKRXED_Pos                    6
#define USB_HRXS_ACKRXED                        ((uint32_t)0x00000040)

#define USB_HRXS_DATASEQ_Pos                    7
#define USB_HRXS_DATASEQ                        ((uint32_t)0x00000080)


/** @} */ /* End of group Periph_USB_USB_HRXS_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_SEP_CTRL_Bits USB_SEP_CTRL
  * @{
  */

#define USB_SEP_CTRL_EPEN_Pos                   0
#define USB_SEP_CTRL_EPEN                       ((uint32_t)0x00000001)

#define USB_SEP_CTRL_EPRDY_Pos                  1
#define USB_SEP_CTRL_EPRDY                      ((uint32_t)0x00000002)

#define USB_SEP_CTRL_EPDATASEQ_Pos              2
#define USB_SEP_CTRL_EPDATASEQ                  ((uint32_t)0x00000004)

#define USB_SEP_CTRL_EPSSTALL_Pos               3
#define USB_SEP_CTRL_EPSSTALL                   ((uint32_t)0x00000008)

#define USB_SEP_CTRL_EPISOEN_Pos                4
#define USB_SEP_CTRL_EPISOEN                    ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_USB_USB_SEP_CTRL_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_SEP_STS_Bits USB_SEP_STS
  * @{
  */

#define USB_SEP_STS_SCCRCERR_Pos                0
#define USB_SEP_STS_SCCRCERR                    ((uint32_t)0x00000001)

#define USB_SEP_STS_SCBSERR_Pos                 1
#define USB_SEP_STS_SCBSERR                     ((uint32_t)0x00000002)

#define USB_SEP_STS_SCRXOF_Pos                  2
#define USB_SEP_STS_SCRXOF                      ((uint32_t)0x00000004)

#define USB_SEP_STS_SCRXTO_Pos                  3
#define USB_SEP_STS_SCRXTO                      ((uint32_t)0x00000008)

#define USB_SEP_STS_SCNAKSENT_Pos               4
#define USB_SEP_STS_SCNAKSENT                   ((uint32_t)0x00000010)

#define USB_SEP_STS_SCSTALLSENT_Pos             5
#define USB_SEP_STS_SCSTALLSENT                 ((uint32_t)0x00000020)

#define USB_SEP_STS_SCACKRXED_Pos               6
#define USB_SEP_STS_SCACKRXED                   ((uint32_t)0x00000040)

#define USB_SEP_STS_SCDATASEQ_Pos               7
#define USB_SEP_STS_SCDATASEQ                   ((uint32_t)0x00000080)


/** @} */ /* End of group Periph_USB_USB_SEP_STS_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_SC_Bits USB_SC
  * @{
  */

#define USB_SC_SCGEN_Pos                        0
#define USB_SC_SCGEN                            ((uint32_t)0x00000001)

#define USB_SC_SCTXLS_Pos                       1
#define USB_SC_SCTXLS_Msk                       ((uint32_t)0x00000006)

#define USB_SC_SCDC_Pos                         3
#define USB_SC_SCDC                             ((uint32_t)0x00000008)

#define USB_SC_SCFSP_Pos                        4
#define USB_SC_SCFSP                            ((uint32_t)0x00000010)

#define USB_SC_SCFSR_Pos                        5
#define USB_SC_SCFSR                            ((uint32_t)0x00000020)


/** @} */ /* End of group Periph_USB_USB_SC_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_SIS_Bits USB_SIS
  * @{
  */

#define USB_SIS_SCTDONE_Pos                     0
#define USB_SIS_SCTDONE                         ((uint32_t)0x00000001)

#define USB_SIS_SCRESUME_Pos                    1
#define USB_SIS_SCRESUME                        ((uint32_t)0x00000002)

#define USB_SIS_SCRESETEV_Pos                   2
#define USB_SIS_SCRESETEV                       ((uint32_t)0x00000004)

#define USB_SIS_SCSOFREC_Pos                    3
#define USB_SIS_SCSOFREC                        ((uint32_t)0x00000008)

#define USB_SIS_SCNAKSENT_Pos                   4
#define USB_SIS_SCNAKSENT                       ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_USB_USB_SIS_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_SIM_Bits USB_SIM
  * @{
  */

#define USB_SIM_SCTDONEIE_Pos                   0
#define USB_SIM_SCTDONEIE                       ((uint32_t)0x00000001)

#define USB_SIM_SCRESUMEIE_Pos                  1
#define USB_SIM_SCRESUMEIE                      ((uint32_t)0x00000002)

#define USB_SIM_SCRESETEVIE_Pos                 2
#define USB_SIM_SCRESETEVIE                     ((uint32_t)0x00000004)

#define USB_SIM_SCSOFRECIE_Pos                  3
#define USB_SIM_SCSOFRECIE                      ((uint32_t)0x00000008)

#define USB_SIM_SCNAKSENTIE_Pos                 4
#define USB_SIM_SCNAKSENTIE                     ((uint32_t)0x00000010)


/** @} */ /* End of group Periph_USB_USB_SIM_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_HSCR_Bits USB_HSCR
  * @{
  */

#define USB_HSCR_HOST_MODE_Pos                  0
#define USB_HSCR_HOST_MODE                      ((uint32_t)0x00000001)

#define USB_HSCR_RESET_CORE_Pos                 1
#define USB_HSCR_RESET_CORE                     ((uint32_t)0x00000002)

#define USB_HSCR_EN_TX_Pos                      2
#define USB_HSCR_EN_TX                          ((uint32_t)0x00000004)

#define USB_HSCR_EN_RX_Pos                      3
#define USB_HSCR_EN_RX                          ((uint32_t)0x00000008)

#define USB_HSCR_DP_PULLUP_Pos                  4
#define USB_HSCR_DP_PULLUP                      ((uint32_t)0x00000010)

#define USB_HSCR_DP_PULLDOWN_Pos                5
#define USB_HSCR_DP_PULLDOWN                    ((uint32_t)0x00000020)

#define USB_HSCR_DM_PULLUP_Pos                  6
#define USB_HSCR_DM_PULLUP                      ((uint32_t)0x00000040)

#define USB_HSCR_DM_PULLDOWN_Pos                7
#define USB_HSCR_DM_PULLDOWN                    ((uint32_t)0x00000080)


/** @} */ /* End of group Periph_USB_USB_HSCR_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @defgroup Periph_USB_Defines Defines
  * @{
  */

/** @defgroup Periph_USB_USB_HSVR_Bits USB_HSVR
  * @{
  */

#define USB_HSVR_VERSION_Pos                    0
#define USB_HSVR_VERSION_Msk                    ((uint32_t)0x0000000F)

#define USB_HSVR_REVISION_Pos                   4
#define USB_HSVR_REVISION_Msk                   ((uint32_t)0x000000F0)


/** @} */ /* End of group Periph_USB_USB_HSVR_Bits */

/** @} */ /* End of group Periph_USB_Defines */

/** @} */ /* End of group Periph_USB */

/** @} */ /* End of group __1986BE9x_Peripheral_Units */

/** @} */ /* End of group __CMSIS */

#endif /* __1986BE9X_USB_DEFS_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE 1986BE9x_usb_defs.h */
