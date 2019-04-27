#define __IAP_BUF_SIZE__    0x2000

;***************************************
;
; Internal SRAM = 32 Kbytes
;
;***************************************
[[SRAM0]]
 Name=SRAM0
 Type=RAM
 ProtocolIndex=1
 Fixed=1

 StartAddr=0x20000000
 EndAddr  =0x20007FFF
 CodeAllowed=0


;***************************************
;
; Internal SRAM = 16 Kbytes
;
;***************************************
[[SRAM1]]
 Name=SRAM1
 Type=RAM
 ProtocolIndex=1
 Fixed=1

 StartAddr=0x20100000
 EndAddr  =0x20103FFF


