#include <pice.h>
#include "_flash.h"

/***********************************************************
*   Erase All Flash                                        *
***********************************************************/

void main()
{
  __MultiLingualStrings__ = TRUE;
#ifdef __DEBUG__
  _printf("\nRun EraseAllFlash.cmd script\n");
#endif

  // Load Library Script file if it is not loaded yet
  char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT], path[MAXPATH];

  GetScriptFileName("EraseAllFlash", path);
  fnsplit(path, drive, dir, name, ext);
  fnmerge(path, drive, dir, __LIB_SCRIPT_FILE__, "cmd");
  ExecScript(path, "", "", 0, ES_NOACTION | ES_EXITONMCUSELECT);

  // Check if PrepareMCU function has been executed
  if ( PrepareMCUStatus == 0 )
    IAP_PrepareMCU();

  LastFlashStatus = TRG_STATUS_OK;
  IAP_EraseAllFlash();

  if (LastFlashStatus != TRG_STATUS_FATAL && BlankCheck)
  {
    IAP_BlankCheck();
  }

  RedrawScreen();

  __MultiLingualStrings__ = FALSE;
}

