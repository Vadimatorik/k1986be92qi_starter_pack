#include "_flash.h"

/***********************************************************
*   Program Flash                                          *
***********************************************************/

void main()
{
  __MultiLingualStrings__ = TRUE;
#ifdef __DEBUG__
  _printf("\nRun Program.cmd script\n");
#endif

  // Load Library Script file if it is not loaded yet
  char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT], path[MAXPATH];

  GetScriptFileName("Program", path);
  fnsplit(path, drive, dir, name, ext);
  fnmerge(path, drive, dir, __LIB_SCRIPT_FILE__, "cmd");
  ExecScript(path, "", "", 0, ES_NOACTION | ES_EXITONMCUSELECT);

  // Check if PrepareMCU function has been executed
  if (PrepareMCUStatus == 0)
    IAP_PrepareMCU();

  // Load words to RamBuffer
  SetMemory(DataBuffer, IAP_PageSize, RamBufferAddr, AS_MEMORY);


  // Program Flash
  if (LastFlashStatus == TRG_STATUS_OK)
  {
    IAP_CopyRam2Flash();
    if (LastFlashStatus != TRG_STATUS_FATAL && VerifyData)
      IAP_Compare();
  }

  __MultiLingualStrings__ = FALSE;
}

