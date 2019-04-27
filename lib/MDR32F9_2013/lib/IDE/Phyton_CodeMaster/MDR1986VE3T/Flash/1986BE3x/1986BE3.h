// Target MCU specific constants
// 1986BE91 General
//#define TRG_PART_ID		  0x04570041

#define TRG_RAM_START_ADDR	0x20100000
#define TRG_RAM_BUFFER_ADDR	0x20100800

#define TRG_PAGE_SIZE_PROGRAM	0x800
#define TRG_FILE_LOAD_ADDR	(TRG_RAM_START_ADDR + 0x00)
#define TRG_COMMAND_ADDR	(TRG_RAM_START_ADDR + 0x20)
#define TRG_STATUS_ADDR 	(TRG_RAM_START_ADDR + 0x34)
#define TRG_MON_ENTRY_POINT	(TRG_RAM_START_ADDR + 0x40)


//#define TRG_IAP_DATA_SIZE	  (TRG_COMMAND_ADDR - TRG_RAM_BUFFER_ADDR)
//#define TRG_IAP_CMD_STS_SIZE	  (TRG_FILE_LOAD_ADDR - TRG_COMMAND_ADDR)


//#define IAP_ProgramOptionsCmd   58

#define EXPT_NMI		0x100
#define EXPT_HARD_FAULT 	0x101
#define EXPT_MEM_MANAGE 	0x102
#define EXPT_BUS_FAULT		0x103
#define EXPT_USAGE_FAULT	0x104

#define IAP_WRITE_ERROR 	14
#define IAP_UNKNOWN_FLASH	15
#define IAP_ERASE_ALL_ERROR	16
#define IAP_INIT_ERROR		17


#define emsgIAP_INIT_ERROR_en	"JEM-ARM can not initialise HSI Clock.				 \n\n"

#define emsgIAP_INIT_ERROR_ru	"JEM-ARM не смог проинициализировать генератор HSI.		 \n\n"


#define emsgIAP_ER_LOCK_ERR_en	"Flash is erase protected at address:				    \n\n"
#define emsgIAP_WR_LOCK_ERR_en	"Flash is write protected at address:				    \n\n"
#define emsgIAP_NEED_MASS_ERASE_en "\n\n\
				 To allow JEM to download your program to\n\
				 the Flash memory you should erase it yourself\n\
				 by means of the menu:\n\n\
				 Main menu\\Debug\\Erase Flash Memory.\n\n\
				 Are you agree to erase all the Flash memory?"

#define emsgIAP_ER_LOCK_ERR_ru	"Произошла попытка стирания защищенного 		      \n\
				 участка флэш-памяти по адресу:\n\n"
#define emsgIAP_WR_LOCK_ERR_ru	"Произошла попытка записи в защищенный			      \n\
				 участок флэш-памяти по адресу:\n\n"


#define TRG_FILE_NAME		"1986BE3.iap"

#define __LIB_SCRIPT_FILE__	"flash_1986BE3"

