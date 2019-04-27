#ifndef __1986BE91_DMA_H
#define __1986BE91_DMA_H

#include "cm3_macro.h"

typedef struct {
  unsigned MASTER_ENABLE                        : 1;
  unsigned __dummy0                             : 3;
  unsigned STATE                                : 4;
  unsigned __dummy1                             : 8;
  unsigned CHNLS_MINUS1                         : 5;
  unsigned __dummy2                             : 7;
  unsigned TEST_STATUS                          : 4;
} _dma_status;

typedef volatile _dma_status _io_dma_status;

#define offs_DMA_STATUS_MASTER_ENABLE           0
#define offs_DMA_STATUS_STATE                   4
#define offs_DMA_STATUS_CHNLS_MINUS1            16
#define offs_DMA_STATUS_TEST_STATUS             28

#define size_DMA_STATUS_MASTER_ENABLE           1
#define size_DMA_STATUS_STATE                   4
#define size_DMA_STATUS_CHNLS_MINUS1            5
#define size_DMA_STATUS_TEST_STATUS             4

#define mask_DMA_STATUS_MASTER_ENABLE           ((unsigned long)0x00000001)
#define mask_DMA_STATUS_STATE                   ((unsigned long)0x000000F0)
#define mask_DMA_STATUS_CHNLS_MINUS1            ((unsigned long)0x001F0000)
#define mask_DMA_STATUS_TEST_STATUS             ((unsigned long)0xF0000000)


typedef struct {
  unsigned MASTER_ENABLE                        : 1;
  unsigned __dummy0                             : 4;
  unsigned CHNL_PROT_CTRL                       : 3;
  unsigned __dummy1                             : 24;
} _dma_cfg;

typedef volatile _dma_cfg _io_dma_cfg;

#define offs_DMA_CFG_MASTER_ENABLE              0
#define offs_DMA_CFG_CHNL_PROT_CTRL             5

#define size_DMA_CFG_MASTER_ENABLE              1
#define size_DMA_CFG_CHNL_PROT_CTRL             3

#define mask_DMA_CFG_MASTER_ENABLE              ((unsigned long)0x00000001)
#define mask_DMA_CFG_CHNL_PROT_CTRL             ((unsigned long)0x000000E0)


typedef struct {
	__io_reg STATUS;
	__io_reg CFG;
	__io_reg CTRL_BASE_PTR;
	__io_reg ALT_CTRL_BASE_PTR;
	__io_reg WAITONREQ_STATUS;
	__io_reg CHNL_SW_REQUEST;
	__io_reg CHNL_USEBURST_SET;
	__io_reg CHNL_USEBURST_CLR;
	__io_reg CHNL_REQ_MASK_SET;
	__io_reg CHNL_REQ_MASK_CLR;
	__io_reg CHNL_ENABLE_SET;
	__io_reg CHNL_ENABLE_CLR;
	__io_reg CHNL_PRI_ALT_SET;
	__io_reg CHNL_PRI_ALT_CLR;
	__io_reg CHNL_PRIORITY_SET;
	__io_reg CHNL_PRIORITY_CLR;
	__io_reg __dummy0[3];
	__io_reg ERR_CLR;
} _dma;

#endif /* __1986BE91_DMA_H */
