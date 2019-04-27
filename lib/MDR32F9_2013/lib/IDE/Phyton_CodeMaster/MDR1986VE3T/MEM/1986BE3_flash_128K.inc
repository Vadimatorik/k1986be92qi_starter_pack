[[FLASH]]
 Name=Flash
 Type=Flash
 ProtocolIndex=1
 Fixed=1
 StartAddr=0x00000000
 EndAddr  =0x0001FFFF
 DisableHWRead=1

[[[Erase Sectors]]]
 S0=0x00000000,0x0001FFFF,0x00001000
 _StartSectorNumber0=0

[[[Write Sectors]]]
 S0=0x00000000,0x0001FFFF,__IAP_BUF_SIZE__


