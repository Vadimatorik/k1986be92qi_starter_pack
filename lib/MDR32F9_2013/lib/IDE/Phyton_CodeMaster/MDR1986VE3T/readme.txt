Инструкция по дабовления нового контроллера в среду Phyton CodeMaster.
1. Добавляем в файл CPU.DEF описание микроконтроллера:
	[Milandr 1986BE3T]
	  FamilyId       = 1986BE3
	  AOPmask        = 0xFFFFFFFF
	  SDriver        = m3
	  adasm          = cortex.dsm
	  prcOption      = arm7tdmi
	  mcaOption      = M1
	  stup_suffix    = M0
	  MEMfile        = Milandr\\1986BE3
	  REMAPfile      = 1986BE3
	  LDfile         = arm7tdmi
	  SFRfile        = Milandr\\1986BE3\\1986be3t
	  CmcStartupFile = Milandr\\1986BE1\\startup_MDR1986VE3
	  PDW            = Generic ARM7TDMI
	  FPU_enabled    = 0

2. Скопировать файлы 1986BE3.mem, 1986BE3_flash_128K.inc, 1986BE3_ram_32K_16K.inc 
   в дерикторию MEM/Milandr.

3. Скопировать файлы 1986be3t.sfr, CortexM0.SFR в дерикторию SFR/Milandr.

4. Добавить в файл POD/JEM-ARM-V2/Milandr/FAMILY_CM1.CGF:
	[[Milandr 1986BE3]]
	 ScriptFolder=Flash/Milandr/1986BE3x
	 FamilyId=1986BE3

5. Добавить в файл POD/JEM-ARM-V2/Milandr/CHIPS_CM1.INC:
	DEFINE_CHIP(0x00000000,Milandr 1986BE3T)
	  ConfFields=Milandr\\1986BE3\\1986BE3x.fld

6. Скопировать в папку POD/JEM-ARM-V2/Milandr/ каталог FLD/1986BE3.

7. Скопировать в папку Flash/Milandr каталог Flash/1986BE3.




