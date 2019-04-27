#include "_flash.h"

/***********************************************************
*   Restore MCU Resources                                  *
***********************************************************/

void main()
{
  __MultiLingualStrings__ = TRUE;
#ifdef __DEBUG__
  _printf("\nRun RestoreMCU.cmd script\n");
#endif

  // Load Library Script file if it is not loaded yet
  char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT], path[MAXPATH];

  GetScriptFileName("RestoreMCU", path);
  fnsplit(path, drive, dir, name, ext);
  fnmerge(path, drive, dir, __LIB_SCRIPT_FILE__, "cmd");
  ExecScript(path, "", "", 0, ES_NOACTION | ES_EXITONMCUSELECT);

  // Check if PrepareMCU function has been executed
  if (PrepareMCUStatus != 0)
  {
    IAP_RestoreMCU();
    PrepareMCUStatus = 0;
  }

  __MultiLingualStrings__ = FALSE;

  TerminateScript(__LIB_SCRIPT_FILE__);
}

