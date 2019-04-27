#include "_flash.h"

/***********************************************************
*   Erase Flash                                            *
***********************************************************/

void main()
{
  __MultiLingualStrings__ = TRUE;
#ifdef __DEBUG__
  _printf("\nRun Erase.cmd script\n");
#endif

  // Load Library Script file if it is not loaded yet
  char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT], path[MAXPATH];

  GetScriptFileName("Erase", path);
  fnsplit(path, drive, dir, name, ext);
  fnmerge(path, drive, dir, __LIB_SCRIPT_FILE__, "cmd");
  ExecScript(path, "", "", 0, ES_NOACTION | ES_EXITONMCUSELECT);

  // Check if PrepareMCU function has been executed
  if (PrepareMCUStatus == 0)
    IAP_PrepareMCU();

//  JTAG_ReadConfiguration();

  // Erase Flash
  LastFlashStatus = TRG_STATUS_OK;
  IAP_EraseSectors();

  if (LastFlashStatus != TRG_STATUS_FATAL && BlankCheck)
    IAP_BlankCheck();

  __MultiLingualStrings__ = FALSE;
}

