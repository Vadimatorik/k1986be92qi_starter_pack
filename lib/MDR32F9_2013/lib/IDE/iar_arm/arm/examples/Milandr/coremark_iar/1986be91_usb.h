#ifndef __1986BE91_USB_H
#define __1986BE91_USB_H

#include "cm3_macro.h"

typedef struct {
  unsigned TREQ                                 : 1;
  unsigned SOFS                                 : 1;
  unsigned PREEN                                : 1;
  unsigned ISOEN                                : 1;
  unsigned __dummy0                             : 28;
} _usb_htxc;

typedef volatile _usb_htxc _io_usb_htxc;

#define offs_USB_HTXC_TREQ                      0
#define offs_USB_HTXC_SOFS                      1
#define offs_USB_HTXC_PREEN                     2
#define offs_USB_HTXC_ISOEN                     3

#define size_USB_HTXC_TREQ                      1
#define size_USB_HTXC_SOFS                      1
#define size_USB_HTXC_PREEN                     1
#define size_USB_HTXC_ISOEN                     1

#define mask_USB_HTXC_TREQ                      ((unsigned long)0x00000001)
#define mask_USB_HTXC_SOFS                      ((unsigned long)0x00000002)
#define mask_USB_HTXC_PREEN                     ((unsigned long)0x00000004)
#define mask_USB_HTXC_ISOEN                     ((unsigned long)0x00000008)


typedef struct {
  unsigned TXLC                                 : 2;
  unsigned DC                                   : 1;
  unsigned FSPL                                 : 1;
  unsigned FSLR                                 : 1;
  unsigned __dummy0                             : 27;
} _usb_htxlc;

typedef volatile _usb_htxlc _io_usb_htxlc;

#define offs_USB_HTXLC                          0
#define offs_USB_HTXLC_DC                       2
#define offs_USB_HTXLC_FSPL                     3
#define offs_USB_HTXLC_FSLR                     4

#define size_USB_HTXLC                          2
#define size_USB_HTXLC_DC                       1
#define size_USB_HTXLC_FSPL                     1
#define size_USB_HTXLC_FSLR                     1

#define mask_USB_HTXLC                          ((unsigned long)0x00000003)
#define mask_USB_HTXLC_DC                       ((unsigned long)0x00000004)
#define mask_USB_HTXLC_FSPL                     ((unsigned long)0x00000008)
#define mask_USB_HTXLC_FSLR                     ((unsigned long)0x00000010)


typedef struct {
  unsigned TDONE                                : 1;
  unsigned RESUME                               : 1;
  unsigned CONEV                                : 1;
  unsigned SOFS                                 : 1;
  unsigned __dummy0                             : 28;
} _usb_his;

typedef volatile _usb_his _io_usb_his;

#define offs_USB_HIS_TDONE                      0
#define offs_USB_HIS_RESUME                     1
#define offs_USB_HIS_CONEV                      2
#define offs_USB_HIS_SOFS                       3

#define size_USB_HIS_TDONE                      1
#define size_USB_HIS_RESUME                     1
#define size_USB_HIS_CONEV                      1
#define size_USB_HIS_SOFS                       1

#define mask_USB_HIS_TDONE                      ((unsigned long)0x00000001)
#define mask_USB_HIS_RESUME                     ((unsigned long)0x00000002)
#define mask_USB_HIS_CONEV                      ((unsigned long)0x00000004)
#define mask_USB_HIS_SOFS                       ((unsigned long)0x00000008)


typedef struct {
  unsigned TDONEIE                              : 1;
  unsigned RESUMEIE                             : 1;
  unsigned CONEVIE                              : 1;
  unsigned SOFIE                                : 1;
  unsigned __dummy0                             : 28;
} _usb_him;

typedef volatile _usb_him _io_usb_him;

#define offs_USB_HIM_TDONEIE                    0
#define offs_USB_HIM_RESUMEIE                   1
#define offs_USB_HIM_CONEVIE                    2
#define offs_USB_HIM_SOFIE                      3

#define size_USB_HIM_TDONEIE                    1
#define size_USB_HIM_RESUMEIE                   1
#define size_USB_HIM_CONEVIE                    1
#define size_USB_HIM_SOFIE                      1

#define mask_USB_HIM_TDONEIE                    ((unsigned long)0x00000001)
#define mask_USB_HIM_RESUMEIE                   ((unsigned long)0x00000002)
#define mask_USB_HIM_CONEVIE                    ((unsigned long)0x00000004)
#define mask_USB_HIM_SOFIE                      ((unsigned long)0x00000008)


typedef struct {
  unsigned CRCERR                               : 1;
  unsigned BSERR                                : 1;
  unsigned RXOF                                 : 1;
  unsigned RXTO                                 : 1;
  unsigned NAKRXED                              : 1;
  unsigned STALLRXED                            : 1;
  unsigned ACKRXED                              : 1;
  unsigned DATASEQ                              : 1;
  unsigned __dummy0                             : 24;
} _usb_hrxs;

typedef volatile _usb_hrxs _io_usb_hrxs;

#define offs_USB_HRXS_CRCERR                    0
#define offs_USB_HRXS_BSERR                     1
#define offs_USB_HRXS_RXOF                      2
#define offs_USB_HRXS_RXTO                      3
#define offs_USB_HRXS_NAKRXED                   4
#define offs_USB_HRXS_STALLRXED                 5
#define offs_USB_HRXS_ACKRXED                   6
#define offs_USB_HRXS_DATASEQ                   7

#define size_USB_HRXS_CRCERR                    1
#define size_USB_HRXS_BSERR                     1
#define size_USB_HRXS_RXOF                      1
#define size_USB_HRXS_RXTO                      1
#define size_USB_HRXS_NAKRXED                   1
#define size_USB_HRXS_STALLRXED                 1
#define size_USB_HRXS_ACKRXED                   1
#define size_USB_HRXS_DATASEQ                   1

#define mask_USB_HRXS_CRCERR                    ((unsigned long)0x00000001)
#define mask_USB_HRXS_BSERR                     ((unsigned long)0x00000002)
#define mask_USB_HRXS_RXOF                      ((unsigned long)0x00000004)
#define mask_USB_HRXS_RXTO                      ((unsigned long)0x00000008)
#define mask_USB_HRXS_NAKRXED                   ((unsigned long)0x00000010)
#define mask_USB_HRXS_STALLRXED                 ((unsigned long)0x00000020)
#define mask_USB_HRXS_ACKRXED                   ((unsigned long)0x00000040)
#define mask_USB_HRXS_DATASEQ                   ((unsigned long)0x00000080)


typedef struct {
  unsigned EPEN                                 : 1;
  unsigned EPRDY                                : 1;
  unsigned EPDATASEQ                            : 1;
  unsigned EPSSTALL                             : 1;
  unsigned EPISOEN                              : 1;
  unsigned __dummy0                             : 27;
} _usb_sep_ctrl;

typedef volatile _usb_sep_ctrl _io_usb_sep_ctrl;

#define offs_USB_SEP_CTRL_EPEN                  0
#define offs_USB_SEP_CTRL_EPRDY                 1
#define offs_USB_SEP_CTRL_EPDATASEQ             2
#define offs_USB_SEP_CTRL_EPSSTALL              3
#define offs_USB_SEP_CTRL_EPISOEN               4

#define size_USB_SEP_CTRL_EPEN                  1
#define size_USB_SEP_CTRL_EPRDY                 1
#define size_USB_SEP_CTRL_EPDATASEQ             1
#define size_USB_SEP_CTRL_EPSSTALL              1
#define size_USB_SEP_CTRL_EPISOEN               1

#define mask_USB_SEP_CTRL_EPEN                  ((unsigned long)0x00000001)
#define mask_USB_SEP_CTRL_EPRDY                 ((unsigned long)0x00000002)
#define mask_USB_SEP_CTRL_EPDATASEQ             ((unsigned long)0x00000004)
#define mask_USB_SEP_CTRL_EPSSTALL              ((unsigned long)0x00000008)
#define mask_USB_SEP_CTRL_EPISOEN               ((unsigned long)0x00000010)


typedef struct {
  unsigned SCCRCERR                             : 1;
  unsigned SCBSERR                              : 1;
  unsigned SCRXOF                               : 1;
  unsigned SCRXTO                               : 1;
  unsigned SCNAKSENT                            : 1;
  unsigned SCSTALLSENT                          : 1;
  unsigned SCACKRXED                            : 1;
  unsigned SCDATASEQ                            : 1;
  unsigned __dummy0                             : 24;
} _usb_sep_sts;

typedef volatile _usb_sep_sts _io_usb_sep_sts;

#define offs_USB_SEP_STS_SCCRCERR               0
#define offs_USB_SEP_STS_SCBSERR                1
#define offs_USB_SEP_STS_SCRXOF                 2
#define offs_USB_SEP_STS_SCRXTO                 3
#define offs_USB_SEP_STS_SCNAKSENT              4
#define offs_USB_SEP_STS_SCSTALLSENT            5
#define offs_USB_SEP_STS_SCACKRXED              6
#define offs_USB_SEP_STS_SCDATASEQ              7

#define size_USB_SEP_STS_SCCRCERR               1
#define size_USB_SEP_STS_SCBSERR                1
#define size_USB_SEP_STS_SCRXOF                 1
#define size_USB_SEP_STS_SCRXTO                 1
#define size_USB_SEP_STS_SCNAKSENT              1
#define size_USB_SEP_STS_SCSTALLSENT            1
#define size_USB_SEP_STS_SCACKRXED              1
#define size_USB_SEP_STS_SCDATASEQ              1

#define mask_USB_SEP_STS_SCCRCERR               ((unsigned long)0x00000001)
#define mask_USB_SEP_STS_SCBSERR                ((unsigned long)0x00000002)
#define mask_USB_SEP_STS_SCRXOF                 ((unsigned long)0x00000004)
#define mask_USB_SEP_STS_SCRXTO                 ((unsigned long)0x00000008)
#define mask_USB_SEP_STS_SCNAKSENT              ((unsigned long)0x00000010)
#define mask_USB_SEP_STS_SCSTALLSENT            ((unsigned long)0x00000020)
#define mask_USB_SEP_STS_SCACKRXED              ((unsigned long)0x00000040)
#define mask_USB_SEP_STS_SCDATASEQ              ((unsigned long)0x00000080)


typedef struct {
	__io_reg CTRL;
	__io_reg STS;
	__io_reg TS;
	__io_reg NTS;
} _usb_sep;

typedef struct {
  unsigned SCGEN                                : 1;
  unsigned SCTXLS                               : 2;
  unsigned SCDC                                 : 1;
  unsigned SCFSP                                : 1;
  unsigned SCFSR                                : 1;
  unsigned __dummy0                             : 26;
} _usb_sc;

typedef volatile _usb_sc _io_usb_sc;

#define offs_USB_SC_SCGEN                       0
#define offs_USB_SC_SCTXLS                      1
#define offs_USB_SC_SCDC                        3
#define offs_USB_SC_SCFSP                       4
#define offs_USB_SC_SCFSR                       5

#define size_USB_SC_SCGEN                       1
#define size_USB_SC_SCTXLS                      2
#define size_USB_SC_SCDC                        1
#define size_USB_SC_SCFSP                       1
#define size_USB_SC_SCFSR                       1

#define mask_USB_SC_SCGEN                       ((unsigned long)0x00000001)
#define mask_USB_SC_SCTXLS                      ((unsigned long)0x00000006)
#define mask_USB_SC_SCDC                        ((unsigned long)0x00000008)
#define mask_USB_SC_SCFSP                       ((unsigned long)0x00000010)
#define mask_USB_SC_SCFSR                       ((unsigned long)0x00000020)


typedef struct {
  unsigned SCTDONE                              : 1;
  unsigned SCRESUME                             : 1;
  unsigned SCRESETEV                            : 1;
  unsigned SCSOFREC                             : 1;
  unsigned SCNAKSENT                            : 1;
  unsigned __dummy0                             : 27;
} _usb_sis;

typedef volatile _usb_sis _io_usb_sis;

#define offs_USB_SIS_SCTDONE                    0
#define offs_USB_SIS_SCRESUME                   1
#define offs_USB_SIS_SCRESETEV                  2
#define offs_USB_SIS_SCSOFREC                   3
#define offs_USB_SIS_SCNAKSENT                  4

#define size_USB_SIS_SCTDONE                    1
#define size_USB_SIS_SCRESUME                   1
#define size_USB_SIS_SCRESETEV                  1
#define size_USB_SIS_SCSOFREC                   1
#define size_USB_SIS_SCNAKSENT                  1

#define mask_USB_SIS_SCTDONE                    ((unsigned long)0x00000001)
#define mask_USB_SIS_SCRESUME                   ((unsigned long)0x00000002)
#define mask_USB_SIS_SCRESETEV                  ((unsigned long)0x00000004)
#define mask_USB_SIS_SCSOFREC                   ((unsigned long)0x00000008)
#define mask_USB_SIS_SCNAKSENT                  ((unsigned long)0x00000010)


typedef struct {
  unsigned SCTDONEIE                            : 1;
  unsigned SCRESUMEIE                           : 1;
  unsigned SCRESETEVIE                          : 1;
  unsigned SCSOFRECIE                           : 1;
  unsigned SCNAKSENTIE                          : 1;
  unsigned __dummy0                             : 27;
} _usb_sim;

typedef volatile _usb_sim _io_usb_sim;

#define offs_USB_SIM_SCTDONEIE                  0
#define offs_USB_SIM_SCRESUMEIE                 1
#define offs_USB_SIM_SCRESETEVIE                2
#define offs_USB_SIM_SCSOFRECIE                 3
#define offs_USB_SIM_SCNAKSENTIE                4

#define size_USB_SIM_SCTDONEIE                  1
#define size_USB_SIM_SCRESUMEIE                 1
#define size_USB_SIM_SCRESETEVIE                1
#define size_USB_SIM_SCSOFRECIE                 1
#define size_USB_SIM_SCNAKSENTIE                1

#define mask_USB_SIM_SCTDONEIE                  ((unsigned long)0x00000001)
#define mask_USB_SIM_SCRESUMEIE                 ((unsigned long)0x00000002)
#define mask_USB_SIM_SCRESETEVIE                ((unsigned long)0x00000004)
#define mask_USB_SIM_SCSOFRECIE                 ((unsigned long)0x00000008)
#define mask_USB_SIM_SCNAKSENTIE                ((unsigned long)0x00000010)


typedef struct {
	__io_reg RXFD;
	__io_reg __dummy0;
	__io_reg RXFDC_L;
	__io_reg RXFDC_H;
	__io_reg RXFC;
	__io_reg __dummy1[11];
	__io_reg TXFD;
	__io_reg __dummy2[3];
	__io_reg TXFDC;
} _usb_sep0;

typedef struct {
  unsigned HOST_MODE                            : 1;
  unsigned RESET_CORE                           : 1;
  unsigned EN_TX                                : 1;
  unsigned EN_RX                                : 1;
  unsigned DP_PULLUP                            : 1;
  unsigned DP_PULLDOWN                          : 1;
  unsigned DM_PULLUP                            : 1;
  unsigned DM_PULLDOWN                          : 1;
  unsigned __dummy0                             : 24;
} _usb_hscr;

typedef volatile _usb_hscr _io_usb_hscr;

#define offs_USB_HSCR_HOST_MODE                 0
#define offs_USB_HSCR_RESET_CORE                1
#define offs_USB_HSCR_EN_TX                     2
#define offs_USB_HSCR_EN_RX                     3
#define offs_USB_HSCR_DP_PULLUP                 4
#define offs_USB_HSCR_DP_PULLDOWN               5
#define offs_USB_HSCR_DM_PULLUP                 6
#define offs_USB_HSCR_DM_PULLDOWN               7

#define size_USB_HSCR_HOST_MODE                 1
#define size_USB_HSCR_RESET_CORE                1
#define size_USB_HSCR_EN_TX                     1
#define size_USB_HSCR_EN_RX                     1
#define size_USB_HSCR_DP_PULLUP                 1
#define size_USB_HSCR_DP_PULLDOWN               1
#define size_USB_HSCR_DM_PULLUP                 1
#define size_USB_HSCR_DM_PULLDOWN               1

#define mask_USB_HSCR_HOST_MODE                 ((unsigned long)0x00000001)
#define mask_USB_HSCR_RESET_CORE                ((unsigned long)0x00000002)
#define mask_USB_HSCR_EN_TX                     ((unsigned long)0x00000004)
#define mask_USB_HSCR_EN_RX                     ((unsigned long)0x00000008)
#define mask_USB_HSCR_DP_PULLUP                 ((unsigned long)0x00000010)
#define mask_USB_HSCR_DP_PULLDOWN               ((unsigned long)0x00000020)
#define mask_USB_HSCR_DM_PULLUP                 ((unsigned long)0x00000040)
#define mask_USB_HSCR_DM_PULLDOWN               ((unsigned long)0x00000080)


typedef struct {
  unsigned VERSION                              : 4;
  unsigned REVISION                             : 4;
  unsigned __dummy0                             : 24;
} _usb_hsvr;

typedef volatile _usb_hsvr _io_usb_hsvr;

#define offs_USB_HSVR_VERSION                   0
#define offs_USB_HSVR_REVISION                  4

#define size_USB_HSVR_VERSION                   4
#define size_USB_HSVR_REVISION                  4

#define mask_USB_HSVR_VERSION                   ((unsigned long)0x0000000F)
#define mask_USB_HSVR_REVISION                  ((unsigned long)0x000000F0)


typedef struct {
	__io_reg HTXC;
	__io_reg HTXT;
	__io_reg HTXLC;
	__io_reg HTXSE;
	__io_reg HTXA;
	__io_reg HTXE;
	__io_reg HFN_L;
	__io_reg HFN_H;
	__io_reg HIS;
	__io_reg HIM;
	__io_reg HRXS;
	__io_reg HRXP;
	__io_reg HRXA;
	__io_reg HRXE;
	__io_reg HRXCS;
	__io_reg HSTM;
	__io_reg __dummy0[16];
	__io_reg HRXFD;
	__io_reg __dummy1;
	__io_reg HRXFDC_L;
	__io_reg HRXFDC_H;
	__io_reg HRXFC;
	__io_reg __dummy2[11];
	__io_reg HTXFD;
	__io_reg __dummy3[3];
	__io_reg HTXFDC;
	__io_reg __dummy4[11];
	__io_reg SEP0_CTRL;
	__io_reg SEP0_STS;
	__io_reg SEP0_TS;
	__io_reg SEP0_NTS;
	__io_reg SEP1_CTRL;
	__io_reg SEP1_STS;
	__io_reg SEP1_TS;
	__io_reg SEP1_NTS;
	__io_reg SEP2_CTRL;
	__io_reg SEP2_STS;
	__io_reg SEP2_TS;
	__io_reg SEP2_NTS;
	__io_reg SEP3_CTRL;
	__io_reg SEP3_STS;
	__io_reg SEP3_TS;
	__io_reg SEP3_NTS;
	__io_reg SC;
	__io_reg SLS;
	__io_reg SIS;
	__io_reg SIM;
	__io_reg SA;
	__io_reg SFN_L;
	__io_reg SFN_H;
	__io_reg __dummy5[9];
	__io_reg SEP0_RXFD;
	__io_reg __dummy6;
	__io_reg SEP0_RXFDC_L;
	__io_reg SEP0_RXFDC_H;
	__io_reg SEP0_RXFC;
	__io_reg __dummy7[11];
	__io_reg SEP0_TXFD;
	__io_reg __dummy8[3];
	__io_reg SEP0_TXFDC;
	__io_reg __dummy9[11];
	__io_reg SEP1_RXFD;
	__io_reg __dummy10;
	__io_reg SEP1_RXFDC_L;
	__io_reg SEP1_RXFDC_H;
	__io_reg SEP1_RXFC;
	__io_reg __dummy11[11];
	__io_reg SEP1_TXFD;
	__io_reg __dummy12[3];
	__io_reg SEP1_TXFDC;
	__io_reg __dummy13[11];
	__io_reg SEP2_RXFD;
	__io_reg __dummy14;
	__io_reg SEP2_RXFDC_L;
	__io_reg SEP2_RXFDC_H;
	__io_reg SEP2_RXFC;
	__io_reg __dummy15[11];
	__io_reg SEP2_TXFD;
	__io_reg __dummy16[3];
	__io_reg SEP2_TXFDC;
	__io_reg __dummy17[11];
	__io_reg SEP3_RXFD;
	__io_reg __dummy18;
	__io_reg SEP3_RXFDC_L;
	__io_reg SEP3_RXFDC_H;
	__io_reg SEP3_RXFC;
	__io_reg __dummy19[11];
	__io_reg SEP3_TXFD;
	__io_reg __dummy20[3];
	__io_reg SEP3_TXFDC;
	__io_reg __dummy21[11];
	__io_reg HSCR;
	__io_reg HSVR;
} _usb;

#endif /* __1986BE91_USB_H */
