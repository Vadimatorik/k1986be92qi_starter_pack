#include <pice.h>
#include "_flash.h"

// Target MCU specific constants

ulong RamBufferAddr	= TRG_RAM_BUFFER_ADDR;
ulong IAP_MonEntryPoint = TRG_MON_ENTRY_POINT;
ulong IAP_FileLoadAddr	= TRG_FILE_LOAD_ADDR;
ulong IAP_CommandAddr	= TRG_COMMAND_ADDR;
ulong IAP_StatusAddr	= TRG_STATUS_ADDR;

//ulong IAP_DataSize	 = TRG_IAP_DATA_SIZE;
//ulong IAP_CmdStsSize	 = TRG_IAP_CMD_STS_SIZE;


char IAP_FileName[MAXPATH] = TRG_FILE_NAME;

// Static variables
uchar iap_buffer[10240]; // Buffer for Iap Monitor and Data Exchange


//---------------------------------------------------------------------------------------------------------------------

#ifdef __DEBUG__
void Dbg_DWordDump()
{
  int Row;
  int Dig_Count = sizeof(iap_buffer) / 4;
  int Addr = 0;
  _printf("iap_buffer dump\n");
  do {
    _printf(" %03X: ", Addr);
    for (Row = 0; (Row < 8) && (Dig_Count > 0); Row++) {
      _printf(" %02X%02X%02X%02X", iap_buffer[Addr + 3], iap_buffer[Addr + 2], iap_buffer[Addr + 1], iap_buffer[Addr]);
      Dig_Count--;
      Addr += 4;
    }
    _printf("\n");
  } while (Dig_Count > 0);
}

void Dbg_DWordMemDump(ulong Addr, ulong WordsNum)
{
  int Col;
  ulong err_code;
  ulong Data[8];
  ulong WSize;
  ulong BSize;
//  ulong instance = LoadLibrary("C:\\Phyton\\SPICE-A1\\Exe\\JEM-MST.dll");
  ulong instance = LoadLibrary("JEM-MST.dll");

//  _printf("instance=0x%08X: ", instance);


  if (Addr & 3) { Addr = Addr & 0xFFFFFFFC; WordsNum--; }

  _printf("\nMemory dump (%u words)\n", WordsNum);
  while (WordsNum > 0)
  {
    _printf(" %08X: ", Addr);

    if (WordsNum > 8)
      WSize = 8;
    else
      WSize = WordsNum; // Bytes

    BSize = WSize * 4;
//  Master_ReadMemory(MemType_t tmem, uint32 addr, uint32 size, void *buf)
    err_code = CallLibraryFunction(instance, "Master_ReadMemory", Data, BSize, Addr, 0);

    if ( err_code )
    {
      _printf(" Error Code: %08X\n", err_code);
    }
    else
    {
      for (Col = 0; Col < WSize; Col++)
      {
	_printf(" %08X", Data[Col]);
      }
      _printf("\n");
    }
    WordsNum -= WSize;
    Addr += BSize;
  }
  _printf("\n");
}
#endif



/***********************************************************
*		Utility Functions																		   *
***********************************************************/

long file_size;
long rd;
uchar buffer[2048];
//uchar IAP_save_code_area_buf[4096];
//ulong code_addr;

int LoadFlashProgram(char file_name[], ulong addr)
{
  char error_title[256];
  sprintf(error_title, "[%s] Error", ApplName);

  char path[MAXPATH];
  sprintf(path, "%sHardSoft\\%s", SystemDir, file_name);

#ifdef __DEBUG__
  _printf("=>	Loading Flash code %s at 0x%X\n", path, addr);
#endif

  long handle = open(path, O_RDONLY | O_BINARY);
  if (handle == -1)
  {
    MessageBoxEx(MB_OK | MB_ICONSTOP, error_title, "Unable to open file \'%s\', please contact Phyton", path);
    return FALSE;
  }

  //uchar buffer[4096];
  file_size = filelength(handle);

  if (file_size > sizeof(buffer))
  {
    close(handle);
    MessageBoxEx(MB_OK | MB_ICONSTOP, error_title, "File \'%s\' is too large, please contact Phyton", path);
    return FALSE;
  }

  rd = read(handle, buffer, file_size);
  if (rd != file_size)
  {
    close(handle);
    MessageBoxEx(MB_OK | MB_ICONSTOP, error_title, "Error %u reading file \'%s\', please contact Phyton", errno, path);
    return FALSE;
  }

  close(handle);
//  code_addr = addr;
//  GetMemory(IAP_save_code_area_buf, file_size, addr, AS_MEMORY);
  SetMemory(buffer, file_size, addr, AS_MEMORY);

  return TRUE;
}

/***********************************************************
*		Prepare MCU IAP Execution														   *
***********************************************************/

void IAP_PrepareMCU()
{
  Reset();
#ifdef __DEBUG__
  _printf("=> IAP_PrepareMCU(), RamBufferAddr = 0x%X\n", RamBufferAddr);
#endif

//		JTAG_EraseWrProtection();
//		InitSFRs();

  GetMemory(iap_buffer, sizeof(iap_buffer), TRG_RAM_START_ADDR, AS_MEMORY);

  if (!LoadFlashProgram(IAP_FileName, IAP_FileLoadAddr))
		return;

#ifdef __DEBUG__
//		_printf("=>   SetBreakSpecial() at 0x%X\n", IAP_FileLoadAddr + 4);
#endif

//		SetBreakSpecial(IAP_FileLoadAddr + 4);
  PrepareMCUStatus = 1;
}

/***********************************************************
*		Prepare MCU IAP Execution without Data Buffer Exchange *
***********************************************************/

void IAP_PrepareMCUNoBuf()
{
  Reset();
#ifdef __DEBUG__
  _printf("=> IAP_PrepareMCUNoBuf(), IAP_CommandAddr = 0x%X\n", IAP_CommandAddr);
#endif

//		JTAG_EraseWrProtection();
//		InitSFRs();

//  GetMemory(iap_buffer, IAP_CmdStsSize, IAP_CommandAddr, AS_MEMORY);
  LoadFlashProgram(IAP_FileName, IAP_FileLoadAddr);

#ifdef __DEBUG__
//		_printf("=>   SetBreakSpecial() at 0x%X\n", IAP_FileLoadAddr + 4);
#endif

//		SetBreakSpecial( IAP_FileLoadAddr + 4);
}

/***********************************************************
*		Restore MCU Resources															   *
***********************************************************/

void IAP_RestoreMCU()
{
#ifdef __DEBUG__
  _printf("=> IAP_RestoreMCU(), RamBufferAddr = 0x%X\n", RamBufferAddr);
#endif

//  SetMemory(IAP_save_code_area_buf, file_size, code_addr, AS_MEMORY);
//  SetMemory(iap_buffer, IAP_DataSize + IAP_CmdStsSize, RamBufferAddr, AS_MEMORY);
  SetMemory(iap_buffer, sizeof(iap_buffer), TRG_RAM_START_ADDR, AS_MEMORY);

//  JTAG_RestoreWrProtection();

//  RestoreBreak();

  PrepareMCUStatus = 0;
  Reset();
}

/***********************************************************
*		Restore MCU Resources without Data Buffer						   *
***********************************************************/

void IAP_RestoreMCUNoBuf()
{
#ifdef __DEBUG__
  _printf("=> IAP_RestoreMCUNoBuf(), IAP_CommandAddr = 0x%X\n", IAP_CommandAddr);
#endif

//  SetMemory(IAP_save_code_area_buf, file_size, code_addr, AS_MEMORY);
//  SetMemory(iap_buffer, IAP_CmdStsSize, IAP_CommandAddr, AS_MEMORY);

//  JTAG_RestoreWrProtection();

//  RestoreBreak();
  Reset();
}


/***********************************************************
*		Mass Erase of the Flash memory											   *
***********************************************************/
void IAP_EraseAllFlash()
{
#ifdef __DEBUG__
  _printf("=>  IAP_EraseAllFlash, Frequency / 1000 = %u\n", __Frequency / 1000);
#endif

  ulong iap_command[] = { IAP_EraseAllCmd, 0 };

  ulong status[3];

  // Run Erase All command
  SetMemory(iap_command, sizeof(iap_command), IAP_CommandAddr, AS_MEMORY);

  if (HDemo)
    {  status[0] = IAP_CMD_SUCCESS; delay(2000);  }
  else
    status[0] = 0xFFFFFFFF;

  SetDword(IAP_StatusAddr, AS_MEMORY, status[0]);

#ifdef __DEBUG__
  char	i;
  for (i = 0; i < sizeof(iap_command)/sizeof(iap_command[0]); i++)
    _printf("=>   iap_command[%d] = 0x%X\n", i, iap_command[i]);
  _printf("=>	RunSpecial() from 0x%X", IAP_MonEntryPoint);
#endif

  if (!HDemo)
  {
    RunSpecial(IAP_MonEntryPoint);
    // Read Status
    GetMemory(status, sizeof(status), IAP_StatusAddr, AS_MEMORY);
  }

#ifdef __DEBUG__
  _printf("...Status = %u  0x%02X", status[0]);
#endif

  char msg_en[1000], msg_ru[500];
  switch (status[0])
  {
    case IAP_CMD_SUCCESS:
      #ifdef __DEBUG__
	_printf("(IAP_CMD_SUCCESS)\n");
      #endif
      LastFlashStatus = TRG_STATUS_OK;
      break;

    case IAP_INIT_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_INIT_ERROR): BKP_REG_0F = 0x%08X\n", status[1]);
      #endif

      msg_en = emsgIAP_INIT_ERROR_en;
      msg_ru = emsgIAP_INIT_ERROR_ru;

      {
	char prm_str[30];
	sprintf(prm_str, "BKP_REG_0F = 0x%08X", status[1]);
	strcat(msg_en, prm_str);	      strcat(msg_ru, prm_str);
      };

      strcat(msg_en, "|");
      strcat(msg_en, msg_ru);

      MessageBoxEx(MB_OK | MB_ICONSTOP, BoxTitle, msg_en);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_ERASE_ALL_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_ERASE_ALL_ERROR)\n");
      #endif
//	MessageBoxEx(MB_OK | MB_ICONSTOP, BoxTitle_MsgEraseEr, emsgIAP_MASS_ERASE_ER);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    default:
      #ifdef __DEBUG__
	_printf("(IAP_UNKNOWN_ERROR)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageUNKNOWN, status[0]);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;
  }
}


//uint mcu_config[8] = {0x00A5,0x00FF,0x00FF,0x00FF,0x00FF,0x00FF,0x00FF,0x00FF};


/***********************************************************
*		Program Options
*********************************************************** /
void IAP_ProgramOptions()
{
#ifdef __DEBUG__
  _printf("=>  IAP_ProgramOptions()\n");
  _printf("=>	RDP  =0x%02X   USER =0x%02X\n", mcu_config[0], mcu_config[1]);
  _printf("=>	Data0=0x%02X   Data1=0x%02X\n", mcu_config[2], mcu_config[3]);
  _printf("=>	WRP0 =0x%02X   WRP1 =0x%02X\n", mcu_config[4], mcu_config[5]);
  _printf("=>	WRP2 =0x%02X   WRP3 =0x%02X\n", mcu_config[6], mcu_config[7]);
#endif
  SetMemory(mcu_config, sizeof(mcu_config), RamBufferAddr, AS_MEMORY);

  ulong iap_command[] = { IAP_ProgramOptionsCmd };

  ulong status[3];

  // Run Erase Sectors command
  SetMemory(iap_command, sizeof(iap_command), IAP_CommandAddr, AS_MEMORY);
  _printf("=>	iap_command[0] = 0x%X\n", iap_command[0]);
  _printf("=>	RunSpecial() from 0x%X", IAP_MonEntryPoint);

  if (HDemo)
    {  status[0] = IAP_CMD_SUCCESS; delay(2000);  }
  else
    status[0] = 0xFFFFFFFF;

  SetDword(IAP_StatusAddr, AS_MEMORY, status[0]);

  if (!HDemo)
  {
    RunSpecial(IAP_MonEntryPoint);
    // Read Status
    GetMemory(status, sizeof(status), IAP_StatusAddr, AS_MEMORY);
  }

#ifdef __DEBUG__
  _printf("...Status = %u  ", status[0]);
#endif
#ifdef __DEBUG__
  _printf("\n");
#endif
}
*/


/***********************************************************
*		Erase Sectors																			   *
***********************************************************/
void IAP_EraseSectors()
{
erase:
#ifdef __DEBUG__
  _printf("=>  IAP_EraseSectors(), StartFlashAddr = 0x%X, StartSectorNumber = %u, EndSectorNumber = %u, Frequency / 1000 = %u\n", StartFlashAddr, StartSectorNumber, EndSectorNumber, __Frequency / 1000);
#endif

  ulong iap_command[] = { IAP_EraseSectorCmd, 0};
  iap_command[1] = StartFlashAddr;

  ulong status[3];

  // Run Erase Sectors command
  SetMemory(iap_command, sizeof(iap_command), IAP_CommandAddr, AS_MEMORY);

  if (HDemo)
    { status[0] = IAP_CMD_SUCCESS; delay(2000); }
  else
    status[0] = 0xFFFFFFFF;

  SetDword(IAP_StatusAddr, AS_MEMORY, status[0]);

#ifdef __DEBUG__
  char	i;
  for (i = 0; i < sizeof(iap_command)/sizeof(iap_command[0]); i++)
    _printf("=>   iap_command[%d] = 0x%X\n", i, iap_command[i]);
  _printf("=>	RunSpecial() from 0x%X", IAP_MonEntryPoint);
#endif

  if (!HDemo)
  {
    RunSpecial(IAP_MonEntryPoint);
    // Read Status
    GetMemory(status, sizeof(status), IAP_StatusAddr, AS_MEMORY);
  }

#ifdef __DEBUG__
  _printf("...Status = %u  ", status[0]);
#endif

//		status[0] = IAP_LOCK_ERROR;
  char msg_en[1000], msg_ru[500];
  switch (status[0])
  {
    case IAP_CMD_SUCCESS:
      #ifdef __DEBUG__
	_printf("(IAP_CMD_SUCCESS)\n");
      #endif
      LastFlashStatus = TRG_STATUS_OK;
      break;

    case IAP_INIT_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_INIT_ERROR): BKP_REG_0F = 0x%08X\n", status[1]);
      #endif

      msg_en = emsgIAP_INIT_ERROR_en;
      msg_ru = emsgIAP_INIT_ERROR_ru;

      {
	char prm_str[30];
	sprintf(prm_str, "BKP_REG_0F = 0x%08X", status[1]);
	strcat(msg_en, prm_str);	      strcat(msg_ru, prm_str);
      };

      strcat(msg_en, "|");
      strcat(msg_en, msg_ru);

      MessageBoxEx(MB_OK | MB_ICONSTOP, BoxTitle, msg_en);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_BUSY:
      #ifdef __DEBUG__
	_printf("(IAP_BUSY)\n");
      #endif
      if (MessageBoxEx(MB_YESNO | MB_ICONQUESTION , BoxTitle, ErrorMessageBUSY) == IDYES)
	goto erase;
      else
	LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_LOCK_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_LOCK_ERROR)\n");
      #endif

      msg_en = emsgIAP_ER_LOCK_ERR_en;
      msg_ru = emsgIAP_ER_LOCK_ERR_ru;

      {
	char Address[30];
	sprintf(Address, "Address = 0x%08X", status[1]);
	strcat(msg_en, Address);	      strcat(msg_ru, Address);
      };

//	strcat(msg_en, emsgIAP_NEED_MASS_ERASE_en);
//	strcat(msg_ru, emsgIAP_NEED_MASS_ERASE_ru);

      strcat(msg_en, "|");
      strcat(msg_en, msg_ru);

      if (MessageBoxEx(MB_YESNO | MB_ICONEXCLAMATION, BoxTitle, msg_en) == IDYES)
      {
//	  IAP_ProgramOptions();
	goto erase;
      }
	LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_SECTOR_NOT_PREPARED:
      #ifdef __DEBUG__
	_printf("(IAP_SECTOR_NOT_PREPARED)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageNOT_PREPARED);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_INVALID_SECTOR:
      #ifdef __DEBUG__
	_printf("(IAP_INVALID_SECTOR)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageINVALID_SECTOR);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_UNKNOWN_FLASH:
      #ifdef __DEBUG__
	_printf("(IAP_UNKNOWN_FLASH)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageNOT_PREPARED);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    default:
      #ifdef __DEBUG__
	_printf("(IAP_UNKNOWN_ERROR)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageUNKNOWN, status[0]);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;
  }
/*
#ifdef __DEBUG__
  Dbg_DWordMemDump(StartFlashAddr, 32);
#endif
*/
}

/***********************************************************
*		Blank Check																			   *
***********************************************************/

void IAP_BlankCheck()
{
#ifdef __DEBUG__
  _printf("=> IAP_BlankCheck(), StartFlashAddr = 0x%08X, Size = 0x%08X\n", StartFlashAddr, IAP_PageSize);
#endif

  ulong iap_command[] = { IAP_BlankCheckCmd, 0, 0 };
  iap_command[1] = StartFlashAddr;
  iap_command[2] = IAP_PageSize;

  ulong status[3], offset, value;
  int key;

  // Run Blank Check Sectors command
  LastFlashStatus = 0;

loop:
  SetMemory(iap_command, sizeof(iap_command), IAP_CommandAddr, AS_MEMORY);

  if (HDemo)
    { status[0] = IAP_CMD_SUCCESS; delay(500); }
  else
    status[0] = 0xFFFFFFFF;

  SetDword(IAP_StatusAddr, AS_MEMORY, status[0]);

#ifdef __DEBUG__
  char	i;
  for (i = 0; i < sizeof(iap_command)/sizeof(iap_command[0]); i++)
    _printf("=>   iap_command[%d] = 0x%X\n", i, iap_command[i]);
  _printf("=>	RunSpecial() from 0x%X", IAP_MonEntryPoint);
#endif

  if (!HDemo)
  {
    RunSpecial(IAP_MonEntryPoint);
    // Read Status
    GetMemory(status, sizeof(status), IAP_StatusAddr, AS_MEMORY);
  }

#ifdef __DEBUG__
  _printf("...Status = %u  ", status[0]);
#endif

  char msg_en[1000], msg_ru[500];
  switch (status[0])
  {
    case IAP_CMD_SUCCESS:
      #ifdef __DEBUG__
	_printf("(IAP_CMD_SUCCESS)\n");
      #endif
      LastFlashStatus = TRG_STATUS_OK;
      break;

    case IAP_INIT_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_INIT_ERROR): BKP_REG_0F = 0x%08X\n", status[1]);
      #endif

      msg_en = emsgIAP_INIT_ERROR_en;
      msg_ru = emsgIAP_INIT_ERROR_ru;

      {
	char prm_str[30];
	sprintf(prm_str, "BKP_REG_0F = 0x%08X", status[1]);
	strcat(msg_en, prm_str);	      strcat(msg_ru, prm_str);
      };

      strcat(msg_en, "|");
      strcat(msg_en, msg_ru);

      MessageBoxEx(MB_OK | MB_ICONSTOP, BoxTitle, msg_en);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_BUSY:
      #ifdef __DEBUG__
	_printf("(IAP_BUSY)\n");
      #endif
      if (MessageBoxEx(MB_YESNO | MB_ICONQUESTION , BoxTitle, ErrorMessageBUSY) == IDYES)
	goto loop;
      else
	LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_INVALID_SECTOR:
      #ifdef __DEBUG__
	_printf("(IAP_INVALID_SECTOR)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageINVALID_SECTOR);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    // Read Result
    case IAP_SECTOR_NOT_BLANK:
      #ifdef __DEBUG__
	_printf("(IAP_SECTOR_NOT_BLANK)\n");
      #endif
      offset = status[1];
      value  = status[2];

      switch (key = MessageBoxEx(MB_ABORTRETRYIGNORE | MB_ICONQUESTION, BlankErrorTitle, ErrorMessageNOT_BLANK, offset, value))
      {
	  case IDABORT:
	  case IDCANCEL: LastFlashStatus = TRG_STATUS_FATAL;
	  case IDIGNORE: break;
	  case IDRETRY:  goto loop;
      }
      break;

    default:
      #ifdef __DEBUG__
	_printf("(IAP_UNKNOWN_ERROR)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageUNKNOWN, status[0]);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;
  }
}

#ifdef __DEBUG__
void ShowRamBuffer()
{
  _printf("\n	       DataBuffer dump:\n");
  ulong offs = 0;

  for ( ; offs < IAP_PageSize; )
  {
    _printf("	     0x%08X: ", StartFlashAddr + offs);
    ulong i;
    for ( i = 0; i < 4; i++ )
    {
      _printf(" 0x%02X%02X%02X%02X:  ", DataBuffer[offs+3], DataBuffer[offs+2], DataBuffer[offs+1], DataBuffer[offs]);
      offs+=4;
      if ( offs > IAP_PageSize ) break;
    }
    _printf("\n");
  }
  _printf("\n");
}
#endif


/***********************************************************
*		CopyRam2Flash																			   *
***********************************************************/

void IAP_CopyRam2Flash()
{
#ifdef __DEBUG__
  _printf("=> IAP_CopyRam2Flash(), StartFlashAddr = 0x%X, RamBufferAddr = 0x%X, IAP_PageSize = %u, Frequency / 1000 = %u\n", StartFlashAddr, RamBufferAddr, IAP_PageSize, __Frequency / 1000);
#endif

  ulong iap_command[] = { IAP_CopyRam2FlashCmd, 0, 0, 0};
  iap_command[1] = StartFlashAddr;
  iap_command[2] = RamBufferAddr;
  iap_command[3] = IAP_PageSize;

  ulong status[3];

  LastFlashStatus = 0;

loop:
  SetMemory(iap_command, sizeof(iap_command), IAP_CommandAddr, AS_MEMORY);

  if (HDemo)
    { status[0] = IAP_CMD_SUCCESS; delay(500); }
  else
    status[0] = 0xFFFFFFFF;

  SetDword(IAP_StatusAddr, AS_MEMORY, status[0]);

#ifdef __DEBUG__
  char	i;
  for (i = 0; i < sizeof(iap_command)/sizeof(iap_command[0]); i++)
		_printf("=>   iap_command[%d] = 0x%X\n", i, iap_command[i]);
  _printf("=>	RunSpecial() from 0x%X", IAP_MonEntryPoint);
//  ShowRamBuffer();
#endif

  if (!HDemo)
  {
    RunSpecial(IAP_MonEntryPoint);
    // Read Status
    GetMemory(status, sizeof(status), IAP_StatusAddr, AS_MEMORY);
  }

#ifdef __DEBUG__
  _printf("...Status = %u  ", status[0]);
#endif

//		status[0] = IAP_LOCK_ERROR;
  char msg_en[1000], msg_ru[500];
  switch (status[0])
  {
    case IAP_CMD_SUCCESS:
      #ifdef __DEBUG__
	_printf("(IAP_CMD_SUCCESS)\n");
      #endif
      LastFlashStatus = TRG_STATUS_OK;
      break;

    case IAP_INIT_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_INIT_ERROR): BKP_REG_0F = 0x%08X\n", status[1]);
      #endif

      msg_en = emsgIAP_INIT_ERROR_en;
      msg_ru = emsgIAP_INIT_ERROR_ru;

      {
	char prm_str[30];
	sprintf(prm_str, "BKP_REG_0F = 0x%08X", status[1]);
	strcat(msg_en, prm_str);	      strcat(msg_ru, prm_str);
      };

      strcat(msg_en, "|");
      strcat(msg_en, msg_ru);

      MessageBoxEx(MB_OK | MB_ICONSTOP, BoxTitle, msg_en);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_BUSY:
      #ifdef __DEBUG__
	_printf("(IAP_BUSY)\n");
      #endif
      if (MessageBoxEx(MB_YESNO | MB_ICONQUESTION , BoxTitle, ErrorMessageBUSY) == IDYES)
	goto loop;
      else
	LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_LOCK_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_LOCK_ERROR)\n");
      #endif
/*
      msg_en = emsgIAP_WR_LOCK_ERR_en;
      msg_ru = emsgIAP_WR_LOCK_ERR_ru;

      {
	char Address[30];
	sprintf(Address, "Address = 0x%08X", status[1]);
	strcat(msg_en, Address);	      strcat(msg_ru, Address);
      };

      strcat(msg_en, emsgIAP_NEED_MASS_ERASE_en);
      strcat(msg_ru, emsgIAP_NEED_MASS_ERASE_ru);

      strcat(msg_en, "|");
      strcat(msg_en, msg_ru);

      if (MessageBoxEx(MB_YESNO | MB_ICONEXCLAMATION, BoxTitle, msg_en) == IDYES)
*/
	LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_UNKNOWN_FLASH:
      #ifdef __DEBUG__
	_printf("(IAP_UNKNOWN_FLASH)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageNOT_PREPARED);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    default:
      #ifdef __DEBUG__
	_printf("(IAP_UNKNOWN_ERROR)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageGENERAL, status[0]);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;
  }
}

/***********************************************************
*		Compare 																						   *
***********************************************************/

void IAP_Compare()
{
#ifdef __DEBUG__
  _printf("=> IAP_Compare(), StartSectorNumber = %u, EndSectorNumber = %u, IAP_PageSize = %u\n", StartSectorNumber, EndSectorNumber, IAP_PageSize);
#endif
  ulong iap_command[] = { IAP_CompareCmd, 0, 0, 0 };
  iap_command[1] = StartFlashAddr;
  iap_command[2] = RamBufferAddr;
  iap_command[3] = IAP_PageSize;

  ulong status[2], offset;
  int key;

  LastFlashStatus = 0;

loop:
  SetMemory(iap_command, sizeof(iap_command), IAP_CommandAddr, AS_MEMORY);

  if (HDemo)
    { status[0] = IAP_CMD_SUCCESS; delay(500); }
  else
    status[0] = 0xFFFFFFFF;

  SetDword(IAP_StatusAddr, AS_MEMORY, status[0]);

#ifdef __DEBUG__
  char	i;
  for (i = 0; i < sizeof(iap_command)/sizeof(iap_command[0]); i++)
    _printf("=>   iap_command[%d] = 0x%X\n", i, iap_command[i]);
  _printf("=>	RunSpecial() from 0x%X", IAP_MonEntryPoint);
#endif

  if (!HDemo)
  {
    RunSpecial(IAP_MonEntryPoint);
    // Read Status
    GetMemory(status, sizeof(status), IAP_StatusAddr, AS_MEMORY);
  }

#ifdef __DEBUG__
  _printf("...Status = %u  ", status[0]);
#endif
  char msg_en[1000], msg_ru[500];
  switch (status[0])
  {
    case IAP_CMD_SUCCESS:
      #ifdef __DEBUG__
	_printf("(IAP_CMD_SUCCESS)\n");
      #endif
      LastFlashStatus = TRG_STATUS_OK;
      break;

    case IAP_INIT_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_INIT_ERROR): BKP_REG_0F = 0x%08X\n", status[1]);
      #endif

      msg_en = emsgIAP_INIT_ERROR_en;
      msg_ru = emsgIAP_INIT_ERROR_ru;

      {
	char prm_str[30];
	sprintf(prm_str, "BKP_REG_0F = 0x%08X", status[1]);
	strcat(msg_en, prm_str);	      strcat(msg_ru, prm_str);
      };

      strcat(msg_en, "|");
      strcat(msg_en, msg_ru);

      MessageBoxEx(MB_OK | MB_ICONSTOP, BoxTitle, msg_en);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    case IAP_COMPARE_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_COMPARE_ERROR)\n");
      #endif
      offset = GetDword(IAP_StatusAddr + 4, AS_MEMORY);

      switch (key = MessageBoxEx(MB_ABORTRETRYIGNORE | MB_ICONQUESTION, VerifyErrorTitle, ErrorMessageVERIFY, offset))
      {
	  case IDABORT:
	  case IDCANCEL: LastFlashStatus = TRG_STATUS_FATAL;
	  case IDIGNORE: break;
	  case IDRETRY:  goto loop;
      }
      break;

    default:
      #ifdef __DEBUG__
	_printf("(IAP_UNKNOWN_ERROR)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP , BoxTitle, ErrorMessageGENERAL, status[0]);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;
  }
}

/***********************************************************
*		Read Part ID																			   *
***********************************************************/

ulong IAP_ReadPartID()
{

#ifdef __DEBUG__
  _printf("=> IAP_ReadPartID()\n");
#endif
  ulong iap_command[] = { IAP_ReadPartIDCmd };
  ulong status[2];

  LastFlashStatus = 0;

  SetMemory(iap_command, sizeof(iap_command), IAP_CommandAddr, AS_MEMORY);

  if (HDemo)
    { status[0] = IAP_CMD_SUCCESS; delay(500); }
  else
    status[0] = 0xFFFFFFFF;

  SetDword(IAP_StatusAddr, AS_MEMORY, status[0]);

#ifdef __DEBUG__
  char	i;
  for (i = 0; i < sizeof(iap_command)/sizeof(iap_command[0]); i++)
    _printf("=>   iap_command[%d] = 0x%X\n", i, iap_command[i]);
  _printf("=>	RunSpecial() from 0x%X", IAP_MonEntryPoint);
#endif

  if (!HDemo)
  {
    RunSpecial(IAP_MonEntryPoint,0x4);
    // Read Status
    GetMemory(status, sizeof(status), IAP_StatusAddr, AS_MEMORY);
  }

#ifdef __DEBUG__
  _printf("...Status = %u  ", status[0]);
#endif

  char msg_en[1000], msg_ru[500];
  switch (status[0])
  {
    case IAP_CMD_SUCCESS:
      #ifdef __DEBUG__
	_printf("(IAP_CMD_SUCCESS)\n");
      #endif
      LastFlashStatus = TRG_STATUS_OK;
      break;

    case IAP_INIT_ERROR:
      #ifdef __DEBUG__
	_printf("(IAP_INIT_ERROR): BKP_REG_0F = 0x%08X\n", status[1]);
      #endif

      msg_en = emsgIAP_INIT_ERROR_en;
      msg_ru = emsgIAP_INIT_ERROR_ru;

      {
	char prm_str[30];
	sprintf(prm_str, "BKP_REG_0F = 0x%08X", status[1]);
	strcat(msg_en, prm_str);	      strcat(msg_ru, prm_str);
      };

      strcat(msg_en, "|");
      strcat(msg_en, msg_ru);

      MessageBoxEx(MB_OK | MB_ICONSTOP, BoxTitle, msg_en);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;

    default:
      #ifdef __DEBUG__
	_printf("(IAP_UNKNOWN_ERROR)\n");
      #endif
      MessageBoxEx(MB_OK | MB_ICONSTOP, BoxTitle, ErrorMessageGENERAL, status[0]);
      LastFlashStatus = TRG_STATUS_FATAL;
      break;
  }

#ifdef __DEBUG__
  ulong tmp_status = GetDword(IAP_StatusAddr + 4, AS_MEMORY);
  _printf("...Part_Id = %X\n", tmp_status);
#endif

  return GetDword(IAP_StatusAddr + 4, AS_MEMORY);
}

