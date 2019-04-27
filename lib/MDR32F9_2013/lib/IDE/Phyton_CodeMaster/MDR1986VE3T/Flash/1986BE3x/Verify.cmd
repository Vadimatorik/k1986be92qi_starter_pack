#include "_flash.h"

/***********************************************************
*   Verify Flash                                           *
***********************************************************/

void main()
{
  __MultiLingualStrings__ = TRUE;

#ifdef __DEBUG__
  _printf("\nRun Verify.cmd script\n");
#endif

  // Load Library Script file if it is not loaded yet
  char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT], path[MAXPATH];

  GetScriptFileName("Verify", path);
  fnsplit(path, drive, dir, name, ext);
  fnmerge(path, drive, dir, __LIB_SCRIPT_FILE__, "cmd");
  ExecScript(path, "", "", 0, ES_NOACTION | ES_EXITONMCUSELECT);

  // Check if PrepareMCU function has been executed
  if (PrepareMCUStatus == 0)
    IAP_PrepareMCU();

  // Load 512 bytes to RamBuffer
  //SetMemory(DataBuffer, sizeof(DataBuffer), RamBufferAddr, AS_MEMORY);

  // Compare Flash
  IAP_Compare();

  __MultiLingualStrings__ = FALSE;
}

