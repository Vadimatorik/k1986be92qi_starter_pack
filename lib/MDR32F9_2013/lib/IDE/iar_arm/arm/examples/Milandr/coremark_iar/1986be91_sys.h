#ifndef __1986BE91_SYS_H
#define __1986BE91_SYS_H

#include "cm3_macro.h"

typedef struct {
  unsigned ENABLE                               : 1;
  unsigned TICKINT                              : 1;
  unsigned CLKSOURCE                            : 1;
  unsigned __dummy0                             : 13;
  unsigned COUNTFLAG                            : 1;
  unsigned __dummy1                             : 15;
} _sys_stcsr;

typedef volatile _sys_stcsr _io_sys_stcsr;

#define offs_SYS_STCSR_ENABLE                   0
#define offs_SYS_STCSR_TICKINT                  1
#define offs_SYS_STCSR_CLKSOURCE                2
#define offs_SYS_STCSR_COUNTFLAG                16

#define size_SYS_STCSR_ENABLE                   1
#define size_SYS_STCSR_TICKINT                  1
#define size_SYS_STCSR_CLKSOURCE                1
#define size_SYS_STCSR_COUNTFLAG                1

#define mask_SYS_STCSR_ENABLE                   ((unsigned long)0x00000001)
#define mask_SYS_STCSR_TICKINT                  ((unsigned long)0x00000002)
#define mask_SYS_STCSR_CLKSOURCE                ((unsigned long)0x00000004)
#define mask_SYS_STCSR_COUNTFLAG                ((unsigned long)0x00010000)


typedef struct {
  unsigned TENMS                                : 24;
  unsigned __dummy0                             : 6;
  unsigned SKEW                                 : 1;
  unsigned NOREF                                : 1;
} _sys_stcr;

typedef volatile _sys_stcr _io_sys_stcr;

#define offs_SYS_STCR_TENMS                     0
#define offs_SYS_STCR_SKEW                      30
#define offs_SYS_STCR_NOREF                     31

#define size_SYS_STCR_TENMS                     24
#define size_SYS_STCR_SKEW                      1
#define size_SYS_STCR_NOREF                     1

#define mask_SYS_STCR_TENMS                     ((unsigned long)0x00FFFFFF)
#define mask_SYS_STCR_SKEW                      ((unsigned long)0x40000000)
#define mask_SYS_STCR_NOREF                     ((unsigned long)0x80000000)


typedef struct {
  unsigned PRI_N                                : 8;
  unsigned PRI_N1                               : 8;
  unsigned PRI_N2                               : 8;
  unsigned PRI_N3                               : 8;
} _sys_ipr;

typedef volatile _sys_ipr _io_sys_ipr;

#define offs_SYS_IPR_PRI_N                      0
#define offs_SYS_IPR_PRI_N1                     8
#define offs_SYS_IPR_PRI_N2                     16
#define offs_SYS_IPR_PRI_N3                     24

#define size_SYS_IPR_PRI_N                      8
#define size_SYS_IPR_PRI_N1                     8
#define size_SYS_IPR_PRI_N2                     8
#define size_SYS_IPR_PRI_N3                     8

#define mask_SYS_IPR_PRI_N                      ((unsigned long)0x000000FF)
#define mask_SYS_IPR_PRI_N1                     ((unsigned long)0x0000FF00)
#define mask_SYS_IPR_PRI_N2                     ((unsigned long)0x00FF0000)
#define mask_SYS_IPR_PRI_N3                     ((unsigned long)0xFF000000)


typedef struct {
  unsigned REVISION                             : 4;
  unsigned PARTNO                               : 12;
  unsigned Const_0xF                            : 4;
  unsigned VARIANT                              : 4;
  unsigned IMPLEMENTER                          : 8;
} _sys_cpuid;

typedef volatile _sys_cpuid _io_sys_cpuid;

#define offs_SYS_CPUID_REVISION                 0
#define offs_SYS_CPUID_PARTNO                   4
#define offs_SYS_CPUID_Const_0xF                16
#define offs_SYS_CPUID_VARIANT                  20
#define offs_SYS_CPUID_IMPLEMENTER              24

#define size_SYS_CPUID_REVISION                 4
#define size_SYS_CPUID_PARTNO                   12
#define size_SYS_CPUID_Const_0xF                4
#define size_SYS_CPUID_VARIANT                  4
#define size_SYS_CPUID_IMPLEMENTER              8

#define mask_SYS_CPUID_REVISION                 ((unsigned long)0x0000000F)
#define mask_SYS_CPUID_PARTNO                   ((unsigned long)0x0000FFF0)
#define mask_SYS_CPUID_Const_0xF                ((unsigned long)0x000F0000)
#define mask_SYS_CPUID_VARIANT                  ((unsigned long)0x00F00000)
#define mask_SYS_CPUID_IMPLEMENTER              ((unsigned long)0xFF000000)


typedef struct {
  unsigned VECTACTIVE                           : 9;
  unsigned __dummy0                             : 2;
  unsigned RETTOBASE                            : 1;
  unsigned VECTPENDING                          : 9;
  unsigned __dummy1                             : 1;
  unsigned ISRPENDING                           : 1;
  unsigned ISRPREEMPT                           : 1;
  unsigned __dummy2                             : 1;
  unsigned PENDSTCLR                            : 1;
  unsigned PENDSTSET                            : 1;
  unsigned PENDSVCLR                            : 1;
  unsigned PENDSVSET                            : 1;
  unsigned __dummy3                             : 2;
  unsigned NMIPENDSET                           : 1;
} _sys_icsr;

typedef volatile _sys_icsr _io_sys_icsr;

#define offs_SYS_ICSR_VECTACTIVE                0
#define offs_SYS_ICSR_RETTOBASE                 11
#define offs_SYS_ICSR_VECTPENDING               12
#define offs_SYS_ICSR_ISRPENDING                22
#define offs_SYS_ICSR_ISRPREEMPT                23
#define offs_SYS_ICSR_PENDSTCLR                 25
#define offs_SYS_ICSR_PENDSTSET                 26
#define offs_SYS_ICSR_PENDSVCLR                 27
#define offs_SYS_ICSR_PENDSVSET                 28
#define offs_SYS_ICSR_NMIPENDSET                31

#define size_SYS_ICSR_VECTACTIVE                9
#define size_SYS_ICSR_RETTOBASE                 1
#define size_SYS_ICSR_VECTPENDING               9
#define size_SYS_ICSR_ISRPENDING                1
#define size_SYS_ICSR_ISRPREEMPT                1
#define size_SYS_ICSR_PENDSTCLR                 1
#define size_SYS_ICSR_PENDSTSET                 1
#define size_SYS_ICSR_PENDSVCLR                 1
#define size_SYS_ICSR_PENDSVSET                 1
#define size_SYS_ICSR_NMIPENDSET                1

#define mask_SYS_ICSR_VECTACTIVE                ((unsigned long)0x000001FF)
#define mask_SYS_ICSR_RETTOBASE                 ((unsigned long)0x00000800)
#define mask_SYS_ICSR_VECTPENDING               ((unsigned long)0x001FF000)
#define mask_SYS_ICSR_ISRPENDING                ((unsigned long)0x00400000)
#define mask_SYS_ICSR_ISRPREEMPT                ((unsigned long)0x00800000)
#define mask_SYS_ICSR_PENDSTCLR                 ((unsigned long)0x02000000)
#define mask_SYS_ICSR_PENDSTSET                 ((unsigned long)0x04000000)
#define mask_SYS_ICSR_PENDSVCLR                 ((unsigned long)0x08000000)
#define mask_SYS_ICSR_PENDSVSET                 ((unsigned long)0x10000000)
#define mask_SYS_ICSR_NMIPENDSET                ((unsigned long)0x80000000)


typedef struct {
  unsigned TBLOFF                               : 22;
  unsigned TBLBASE                              : 1;
  unsigned __dummy0                             : 2;
} _sys_vtor;

typedef volatile _sys_vtor _io_sys_vtor;

#define offs_SYS_VTOR_TBLOFF                    0
#define offs_SYS_VTOR_TBLBASE                   22

#define size_SYS_VTOR_TBLOFF                    22
#define size_SYS_VTOR_TBLBASE                   1

#define mask_SYS_VTOR_TBLOFF                    ((unsigned long)0x003FFFFF)
#define mask_SYS_VTOR_TBLBASE                   ((unsigned long)0x00400000)


typedef struct {
  unsigned VECTRESET                            : 1;
  unsigned VECTCLRACTIVE                        : 1;
  unsigned SYSRESETREQ                          : 1;
  unsigned __dummy0                             : 5;
  unsigned PRIGROUP                             : 3;
  unsigned __dummy1                             : 4;
  unsigned ENDIANESS                            : 1;
  unsigned VECTKEYSTAT                          : 16;
} _sys_aircr;

typedef volatile _sys_aircr _io_sys_aircr;

#define offs_SYS_AIRCR_VECTRESET                0
#define offs_SYS_AIRCR_VECTCLRACTIVE            1
#define offs_SYS_AIRCR_SYSRESETREQ              2
#define offs_SYS_AIRCR_PRIGROUP                 8
#define offs_SYS_AIRCR_ENDIANESS                15
#define offs_SYS_AIRCR_VECTKEYSTAT              16

#define size_SYS_AIRCR_VECTRESET                1
#define size_SYS_AIRCR_VECTCLRACTIVE            1
#define size_SYS_AIRCR_SYSRESETREQ              1
#define size_SYS_AIRCR_PRIGROUP                 3
#define size_SYS_AIRCR_ENDIANESS                1
#define size_SYS_AIRCR_VECTKEYSTAT              16

#define mask_SYS_AIRCR_VECTRESET                ((unsigned long)0x00000001)
#define mask_SYS_AIRCR_VECTCLRACTIVE            ((unsigned long)0x00000002)
#define mask_SYS_AIRCR_SYSRESETREQ              ((unsigned long)0x00000004)
#define mask_SYS_AIRCR_PRIGROUP                 ((unsigned long)0x00000700)
#define mask_SYS_AIRCR_ENDIANESS                ((unsigned long)0x00008000)
#define mask_SYS_AIRCR_VECTKEYSTAT              ((unsigned long)0xFFFF0000)


typedef struct {
  unsigned SLEEPONEXIT                          : 1;
  unsigned SLEEPDEEP                            : 1;
  unsigned __dummy0                             : 1;
  unsigned SEVONPEND                            : 1;
  unsigned __dummy1                             : 27;
} _sys_scr;

typedef volatile _sys_scr _io_sys_scr;

#define offs_SYS_SCR_SLEEPONEXIT                0
#define offs_SYS_SCR_SLEEPDEEP                  1
#define offs_SYS_SCR_SEVONPEND                  3

#define size_SYS_SCR_SLEEPONEXIT                1
#define size_SYS_SCR_SLEEPDEEP                  1
#define size_SYS_SCR_SEVONPEND                  1

#define mask_SYS_SCR_SLEEPONEXIT                ((unsigned long)0x00000001)
#define mask_SYS_SCR_SLEEPDEEP                  ((unsigned long)0x00000002)
#define mask_SYS_SCR_SEVONPEND                  ((unsigned long)0x00000008)


typedef struct {
  unsigned NONBASETHRDENA                       : 1;
  unsigned USERSETMPEND                         : 1;
  unsigned __dummy0                             : 1;
  unsigned UNALIGN_TRP                          : 1;
  unsigned DIV_0_TRP                            : 1;
  unsigned __dummy1                             : 3;
  unsigned BFHFNMIGN                            : 1;
  unsigned STKALIGN                             : 1;
  unsigned __dummy2                             : 22;
} _sys_ccr;

typedef volatile _sys_ccr _io_sys_ccr;

#define offs_SYS_CCR_NONBASETHRDENA             0
#define offs_SYS_CCR_USERSETMPEND               1
#define offs_SYS_CCR_UNALIGN_TRP                3
#define offs_SYS_CCR_DIV_0_TRP                  4
#define offs_SYS_CCR_BFHFNMIGN                  8
#define offs_SYS_CCR_STKALIGN                   9

#define size_SYS_CCR_NONBASETHRDENA             1
#define size_SYS_CCR_USERSETMPEND               1
#define size_SYS_CCR_UNALIGN_TRP                1
#define size_SYS_CCR_DIV_0_TRP                  1
#define size_SYS_CCR_BFHFNMIGN                  1
#define size_SYS_CCR_STKALIGN                   1

#define mask_SYS_CCR_NONBASETHRDENA             ((unsigned long)0x00000001)
#define mask_SYS_CCR_USERSETMPEND               ((unsigned long)0x00000002)
#define mask_SYS_CCR_UNALIGN_TRP                ((unsigned long)0x00000008)
#define mask_SYS_CCR_DIV_0_TRP                  ((unsigned long)0x00000010)
#define mask_SYS_CCR_BFHFNMIGN                  ((unsigned long)0x00000100)
#define mask_SYS_CCR_STKALIGN                   ((unsigned long)0x00000200)


typedef struct {
  unsigned PRI_4                                : 8;
  unsigned PRI_5                                : 8;
  unsigned PRI_6                                : 8;
  unsigned PRI_7                                : 8;
} _sys_shpr1;

typedef volatile _sys_shpr1 _io_sys_shpr1;

#define offs_SYS_SHPR1_PRI_4                    0
#define offs_SYS_SHPR1_PRI_5                    8
#define offs_SYS_SHPR1_PRI_6                    16
#define offs_SYS_SHPR1_PRI_7                    24

#define size_SYS_SHPR1_PRI_4                    8
#define size_SYS_SHPR1_PRI_5                    8
#define size_SYS_SHPR1_PRI_6                    8
#define size_SYS_SHPR1_PRI_7                    8

#define mask_SYS_SHPR1_PRI_4                    ((unsigned long)0x000000FF)
#define mask_SYS_SHPR1_PRI_5                    ((unsigned long)0x0000FF00)
#define mask_SYS_SHPR1_PRI_6                    ((unsigned long)0x00FF0000)
#define mask_SYS_SHPR1_PRI_7                    ((unsigned long)0xFF000000)


typedef struct {
  unsigned PRI_8                                : 8;
  unsigned PRI_9                                : 8;
  unsigned PRI_10                               : 8;
  unsigned PRI_11                               : 8;
} _sys_shpr2;

typedef volatile _sys_shpr2 _io_sys_shpr2;

#define offs_SYS_SHPR2_PRI_8                    0
#define offs_SYS_SHPR2_PRI_9                    8
#define offs_SYS_SHPR2_PRI_10                   16
#define offs_SYS_SHPR2_PRI_11                   24

#define size_SYS_SHPR2_PRI_8                    8
#define size_SYS_SHPR2_PRI_9                    8
#define size_SYS_SHPR2_PRI_10                   8
#define size_SYS_SHPR2_PRI_11                   8

#define mask_SYS_SHPR2_PRI_8                    ((unsigned long)0x000000FF)
#define mask_SYS_SHPR2_PRI_9                    ((unsigned long)0x0000FF00)
#define mask_SYS_SHPR2_PRI_10                   ((unsigned long)0x00FF0000)
#define mask_SYS_SHPR2_PRI_11                   ((unsigned long)0xFF000000)


typedef struct {
  unsigned PRI_12                               : 8;
  unsigned PRI_13                               : 8;
  unsigned PRI_14                               : 8;
  unsigned PRI_15                               : 8;
} _sys_shpr3;

typedef volatile _sys_shpr3 _io_sys_shpr3;

#define offs_SYS_SHPR3_PRI_12                   0
#define offs_SYS_SHPR3_PRI_13                   8
#define offs_SYS_SHPR3_PRI_14                   16
#define offs_SYS_SHPR3_PRI_15                   24

#define size_SYS_SHPR3_PRI_12                   8
#define size_SYS_SHPR3_PRI_13                   8
#define size_SYS_SHPR3_PRI_14                   8
#define size_SYS_SHPR3_PRI_15                   8

#define mask_SYS_SHPR3_PRI_12                   ((unsigned long)0x000000FF)
#define mask_SYS_SHPR3_PRI_13                   ((unsigned long)0x0000FF00)
#define mask_SYS_SHPR3_PRI_14                   ((unsigned long)0x00FF0000)
#define mask_SYS_SHPR3_PRI_15                   ((unsigned long)0xFF000000)


typedef struct {
  unsigned MEMFAULTACT                          : 1;
  unsigned BUSFAULTACT                          : 1;
  unsigned __dummy0                             : 1;
  unsigned USGFAULTACT                          : 1;
  unsigned __dummy1                             : 3;
  unsigned SVCALLACT                            : 1;
  unsigned MONITORACT                           : 1;
  unsigned __dummy2                             : 1;
  unsigned PENDSVACT                            : 1;
  unsigned SYSTICKACT                           : 1;
  unsigned USGFAULTPENDED                       : 1;
  unsigned MEMFAULTPENDED                       : 1;
  unsigned BUSFAULTPENDED                       : 1;
  unsigned SVCALLPENDED                         : 1;
  unsigned MEMFAULTENA                          : 1;
  unsigned BUSFAULTENA                          : 1;
  unsigned USGFAULTENA                          : 1;
  unsigned __dummy3                             : 13;
} _sys_shcsr;

typedef volatile _sys_shcsr _io_sys_shcsr;

#define offs_SYS_SHCSR_MEMFAULTACT              0
#define offs_SYS_SHCSR_BUSFAULTACT              1
#define offs_SYS_SHCSR_USGFAULTACT              3
#define offs_SYS_SHCSR_SVCALLACT                7
#define offs_SYS_SHCSR_MONITORACT               8
#define offs_SYS_SHCSR_PENDSVACT                10
#define offs_SYS_SHCSR_SYSTICKACT               11
#define offs_SYS_SHCSR_USGFAULTPENDED           12
#define offs_SYS_SHCSR_MEMFAULTPENDED           13
#define offs_SYS_SHCSR_BUSFAULTPENDED           14
#define offs_SYS_SHCSR_SVCALLPENDED             15
#define offs_SYS_SHCSR_MEMFAULTENA              16
#define offs_SYS_SHCSR_BUSFAULTENA              17
#define offs_SYS_SHCSR_USGFAULTENA              18

#define size_SYS_SHCSR_MEMFAULTACT              1
#define size_SYS_SHCSR_BUSFAULTACT              1
#define size_SYS_SHCSR_USGFAULTACT              1
#define size_SYS_SHCSR_SVCALLACT                1
#define size_SYS_SHCSR_MONITORACT               1
#define size_SYS_SHCSR_PENDSVACT                1
#define size_SYS_SHCSR_SYSTICKACT               1
#define size_SYS_SHCSR_USGFAULTPENDED           1
#define size_SYS_SHCSR_MEMFAULTPENDED           1
#define size_SYS_SHCSR_BUSFAULTPENDED           1
#define size_SYS_SHCSR_SVCALLPENDED             1
#define size_SYS_SHCSR_MEMFAULTENA              1
#define size_SYS_SHCSR_BUSFAULTENA              1
#define size_SYS_SHCSR_USGFAULTENA              1

#define mask_SYS_SHCSR_MEMFAULTACT              ((unsigned long)0x00000001)
#define mask_SYS_SHCSR_BUSFAULTACT              ((unsigned long)0x00000002)
#define mask_SYS_SHCSR_USGFAULTACT              ((unsigned long)0x00000008)
#define mask_SYS_SHCSR_SVCALLACT                ((unsigned long)0x00000080)
#define mask_SYS_SHCSR_MONITORACT               ((unsigned long)0x00000100)
#define mask_SYS_SHCSR_PENDSVACT                ((unsigned long)0x00000400)
#define mask_SYS_SHCSR_SYSTICKACT               ((unsigned long)0x00000800)
#define mask_SYS_SHCSR_USGFAULTPENDED           ((unsigned long)0x00001000)
#define mask_SYS_SHCSR_MEMFAULTPENDED           ((unsigned long)0x00002000)
#define mask_SYS_SHCSR_BUSFAULTPENDED           ((unsigned long)0x00004000)
#define mask_SYS_SHCSR_SVCALLPENDED             ((unsigned long)0x00008000)
#define mask_SYS_SHCSR_MEMFAULTENA              ((unsigned long)0x00010000)
#define mask_SYS_SHCSR_BUSFAULTENA              ((unsigned long)0x00020000)
#define mask_SYS_SHCSR_USGFAULTENA              ((unsigned long)0x00040000)


typedef struct {
  unsigned IACCVIOL                             : 1;
  unsigned DACCVIOL                             : 1;
  unsigned __dummy0                             : 1;
  unsigned MUNSTKERR                            : 1;
  unsigned MSTKERR                              : 1;
  unsigned __dummy1                             : 2;
  unsigned MMARVALID                            : 1;
  unsigned IBUSERR                              : 1;
  unsigned PRECISERR                            : 1;
  unsigned IMPRECISERR                          : 1;
  unsigned UNSTKERR                             : 1;
  unsigned STKERR                               : 1;
  unsigned __dummy2                             : 2;
  unsigned BFARVALID                            : 1;
  unsigned UNDEFINSTR                           : 1;
  unsigned INVSTATE                             : 1;
  unsigned INVPC                                : 1;
  unsigned NOCP                                 : 1;
  unsigned __dummy3                             : 4;
  unsigned UNALIGNED                            : 1;
  unsigned DIVBYZERO                            : 1;
  unsigned __dummy4                             : 6;
} _sys_cfsr;

typedef volatile _sys_cfsr _io_sys_cfsr;

#define offs_SYS_CFSR_IACCVIOL                  0
#define offs_SYS_CFSR_DACCVIOL                  1
#define offs_SYS_CFSR_MUNSTKERR                 3
#define offs_SYS_CFSR_MSTKERR                   4
#define offs_SYS_CFSR_MMARVALID                 7
#define offs_SYS_CFSR_IBUSERR                   8
#define offs_SYS_CFSR_PRECISERR                 9
#define offs_SYS_CFSR_IMPRECISERR               10
#define offs_SYS_CFSR_UNSTKERR                  11
#define offs_SYS_CFSR_STKERR                    12
#define offs_SYS_CFSR_BFARVALID                 15
#define offs_SYS_CFSR_UNDEFINSTR                16
#define offs_SYS_CFSR_INVSTATE                  17
#define offs_SYS_CFSR_INVPC                     18
#define offs_SYS_CFSR_NOCP                      19
#define offs_SYS_CFSR_UNALIGNED                 24
#define offs_SYS_CFSR_DIVBYZERO                 25

#define size_SYS_CFSR_IACCVIOL                  1
#define size_SYS_CFSR_DACCVIOL                  1
#define size_SYS_CFSR_MUNSTKERR                 1
#define size_SYS_CFSR_MSTKERR                   1
#define size_SYS_CFSR_MMARVALID                 1
#define size_SYS_CFSR_IBUSERR                   1
#define size_SYS_CFSR_PRECISERR                 1
#define size_SYS_CFSR_IMPRECISERR               1
#define size_SYS_CFSR_UNSTKERR                  1
#define size_SYS_CFSR_STKERR                    1
#define size_SYS_CFSR_BFARVALID                 1
#define size_SYS_CFSR_UNDEFINSTR                1
#define size_SYS_CFSR_INVSTATE                  1
#define size_SYS_CFSR_INVPC                     1
#define size_SYS_CFSR_NOCP                      1
#define size_SYS_CFSR_UNALIGNED                 1
#define size_SYS_CFSR_DIVBYZERO                 1

#define mask_SYS_CFSR_IACCVIOL                  ((unsigned long)0x00000001)
#define mask_SYS_CFSR_DACCVIOL                  ((unsigned long)0x00000002)
#define mask_SYS_CFSR_MUNSTKERR                 ((unsigned long)0x00000008)
#define mask_SYS_CFSR_MSTKERR                   ((unsigned long)0x00000010)
#define mask_SYS_CFSR_MMARVALID                 ((unsigned long)0x00000080)
#define mask_SYS_CFSR_IBUSERR                   ((unsigned long)0x00000100)
#define mask_SYS_CFSR_PRECISERR                 ((unsigned long)0x00000200)
#define mask_SYS_CFSR_IMPRECISERR               ((unsigned long)0x00000400)
#define mask_SYS_CFSR_UNSTKERR                  ((unsigned long)0x00000800)
#define mask_SYS_CFSR_STKERR                    ((unsigned long)0x00001000)
#define mask_SYS_CFSR_BFARVALID                 ((unsigned long)0x00008000)
#define mask_SYS_CFSR_UNDEFINSTR                ((unsigned long)0x00010000)
#define mask_SYS_CFSR_INVSTATE                  ((unsigned long)0x00020000)
#define mask_SYS_CFSR_INVPC                     ((unsigned long)0x00040000)
#define mask_SYS_CFSR_NOCP                      ((unsigned long)0x00080000)
#define mask_SYS_CFSR_UNALIGNED                 ((unsigned long)0x01000000)
#define mask_SYS_CFSR_DIVBYZERO                 ((unsigned long)0x02000000)


typedef struct {
  unsigned VECTTBL                              : 1;
  unsigned __dummy0                             : 28;
  unsigned FORCED                               : 1;
  unsigned DEBUGEVT                             : 1;
} _sys_hfsr;

typedef volatile _sys_hfsr _io_sys_hfsr;

#define offs_SYS_HFSR_VECTTBL                   0
#define offs_SYS_HFSR_FORCED                    29
#define offs_SYS_HFSR_DEBUGEVT                  30

#define size_SYS_HFSR_VECTTBL                   1
#define size_SYS_HFSR_FORCED                    1
#define size_SYS_HFSR_DEBUGEVT                  1

#define mask_SYS_HFSR_VECTTBL                   ((unsigned long)0x00000001)
#define mask_SYS_HFSR_FORCED                    ((unsigned long)0x20000000)
#define mask_SYS_HFSR_DEBUGEVT                  ((unsigned long)0x40000000)


typedef struct {
  unsigned SEPARATE                             : 1;
  unsigned __dummy0                             : 7;
  unsigned DREGION                              : 8;
  unsigned IREGION                              : 8;
  unsigned __dummy1                             : 8;
} _sys_mputr;

typedef volatile _sys_mputr _io_sys_mputr;

#define offs_SYS_MPUTR_SEPARATE                 0
#define offs_SYS_MPUTR_DREGION                  8
#define offs_SYS_MPUTR_IREGION                  16

#define size_SYS_MPUTR_SEPARATE                 1
#define size_SYS_MPUTR_DREGION                  8
#define size_SYS_MPUTR_IREGION                  8

#define mask_SYS_MPUTR_SEPARATE                 ((unsigned long)0x00000001)
#define mask_SYS_MPUTR_DREGION                  ((unsigned long)0x0000FF00)
#define mask_SYS_MPUTR_IREGION                  ((unsigned long)0x00FF0000)


typedef struct {
  unsigned ENABLE                               : 1;
  unsigned HFNMIENA                             : 1;
  unsigned PRIVDEFENA                           : 1;
  unsigned __dummy0                             : 29;
} _sys_mpucr;

typedef volatile _sys_mpucr _io_sys_mpucr;

#define offs_SYS_MPUCR_ENABLE                   0
#define offs_SYS_MPUCR_HFNMIENA                 1
#define offs_SYS_MPUCR_PRIVDEFENA               2

#define size_SYS_MPUCR_ENABLE                   1
#define size_SYS_MPUCR_HFNMIENA                 1
#define size_SYS_MPUCR_PRIVDEFENA               1

#define mask_SYS_MPUCR_ENABLE                   ((unsigned long)0x00000001)
#define mask_SYS_MPUCR_HFNMIENA                 ((unsigned long)0x00000002)
#define mask_SYS_MPUCR_PRIVDEFENA               ((unsigned long)0x00000004)


typedef struct {
  unsigned REGION                               : 4;
  unsigned VALID                                : 1;
  unsigned ADDR                                 : 27;
} _sys_mpurbar;

typedef volatile _sys_mpurbar _io_sys_mpurbar;

#define offs_SYS_MPURBAR_REGION                 0
#define offs_SYS_MPURBAR_VALID                  4
#define offs_SYS_MPURBAR_ADDR                   5

#define size_SYS_MPURBAR_REGION                 4
#define size_SYS_MPURBAR_VALID                  1
#define size_SYS_MPURBAR_ADDR                   27

#define mask_SYS_MPURBAR_REGION                 ((unsigned long)0x0000000F)
#define mask_SYS_MPURBAR_VALID                  ((unsigned long)0x00000010)
#define mask_SYS_MPURBAR_ADDR                   ((unsigned long)0xFFFFFFE0)


typedef struct {
  unsigned ENABLE                               : 1;
  unsigned SIZE                                 : 5;
  unsigned __dummy0                             : 2;
  unsigned SRD                                  : 8;
  unsigned ATTRS                                : 16;
} _sys_mpurasr;

typedef volatile _sys_mpurasr _io_sys_mpurasr;

#define offs_SYS_MPURASR_ENABLE                 0
#define offs_SYS_MPURASR_SIZE                   1
#define offs_SYS_MPURASR_SRD                    8
#define offs_SYS_MPURASR_ATTRS                  16

#define size_SYS_MPURASR_ENABLE                 1
#define size_SYS_MPURASR_SIZE                   5
#define size_SYS_MPURASR_SRD                    8
#define size_SYS_MPURASR_ATTRS                  16

#define mask_SYS_MPURASR_ENABLE                 ((unsigned long)0x00000001)
#define mask_SYS_MPURASR_SIZE                   ((unsigned long)0x0000003E)
#define mask_SYS_MPURASR_SRD                    ((unsigned long)0x0000FF00)
#define mask_SYS_MPURASR_ATTRS                  ((unsigned long)0xFFFF0000)


typedef struct {
	__io_reg __dummy0;
	__io_reg ICTR;
	__io_reg ACTLR;
	__io_reg __dummy1;
	__io_reg STCSR;
	__io_reg STRVR;
	__io_reg STCVR;
	__io_reg STCR;
	__io_reg __dummy2[56];
	__io_reg ISER00;
	__io_reg ISER01;
	__io_reg ISER02;
	__io_reg ISER03;
	__io_reg ISER04;
	__io_reg ISER05;
	__io_reg ISER06;
	__io_reg ISER07;
	__io_reg ISER08;
	__io_reg ISER09;
	__io_reg ISER10;
	__io_reg ISER11;
	__io_reg ISER12;
	__io_reg ISER13;
	__io_reg ISER14;
	__io_reg ISER15;
	__io_reg ISER16;
	__io_reg ISER17;
	__io_reg ISER18;
	__io_reg ISER19;
	__io_reg ISER20;
	__io_reg ISER21;
	__io_reg ISER22;
	__io_reg ISER23;
	__io_reg ISER24;
	__io_reg ISER25;
	__io_reg ISER26;
	__io_reg ISER27;
	__io_reg ISER28;
	__io_reg ISER29;
	__io_reg ISER30;
	__io_reg ISER31;
	__io_reg ICER00;
	__io_reg ICER01;
	__io_reg ICER02;
	__io_reg ICER03;
	__io_reg ICER04;
	__io_reg ICER05;
	__io_reg ICER06;
	__io_reg ICER07;
	__io_reg ICER08;
	__io_reg ICER09;
	__io_reg ICER10;
	__io_reg ICER11;
	__io_reg ICER12;
	__io_reg ICER13;
	__io_reg ICER14;
	__io_reg ICER15;
	__io_reg ICER16;
	__io_reg ICER17;
	__io_reg ICER18;
	__io_reg ICER19;
	__io_reg ICER20;
	__io_reg ICER21;
	__io_reg ICER22;
	__io_reg ICER23;
	__io_reg ICER24;
	__io_reg ICER25;
	__io_reg ICER26;
	__io_reg ICER27;
	__io_reg ICER28;
	__io_reg ICER29;
	__io_reg ICER30;
	__io_reg ICER31;
	__io_reg ISPR00;
	__io_reg ISPR01;
	__io_reg ISPR02;
	__io_reg ISPR03;
	__io_reg ISPR04;
	__io_reg ISPR05;
	__io_reg ISPR06;
	__io_reg ISPR07;
	__io_reg ISPR08;
	__io_reg ISPR09;
	__io_reg ISPR10;
	__io_reg ISPR11;
	__io_reg ISPR12;
	__io_reg ISPR13;
	__io_reg ISPR14;
	__io_reg ISPR15;
	__io_reg ISPR16;
	__io_reg ISPR17;
	__io_reg ISPR18;
	__io_reg ISPR19;
	__io_reg ISPR20;
	__io_reg ISPR21;
	__io_reg ISPR22;
	__io_reg ISPR23;
	__io_reg ISPR24;
	__io_reg ISPR25;
	__io_reg ISPR26;
	__io_reg ISPR27;
	__io_reg ISPR28;
	__io_reg ISPR29;
	__io_reg ISPR30;
	__io_reg ISPR31;
	__io_reg ICPR00;
	__io_reg ICPR01;
	__io_reg ICPR02;
	__io_reg ICPR03;
	__io_reg ICPR04;
	__io_reg ICPR05;
	__io_reg ICPR06;
	__io_reg ICPR07;
	__io_reg ICPR08;
	__io_reg ICPR09;
	__io_reg ICPR10;
	__io_reg ICPR11;
	__io_reg ICPR12;
	__io_reg ICPR13;
	__io_reg ICPR14;
	__io_reg ICPR15;
	__io_reg ICPR16;
	__io_reg ICPR17;
	__io_reg ICPR18;
	__io_reg ICPR19;
	__io_reg ICPR20;
	__io_reg ICPR21;
	__io_reg ICPR22;
	__io_reg ICPR23;
	__io_reg ICPR24;
	__io_reg ICPR25;
	__io_reg ICPR26;
	__io_reg ICPR27;
	__io_reg ICPR28;
	__io_reg ICPR29;
	__io_reg ICPR30;
	__io_reg ICPR31;
	__io_reg IABR00;
	__io_reg IABR01;
	__io_reg IABR02;
	__io_reg IABR03;
	__io_reg IABR04;
	__io_reg IABR05;
	__io_reg IABR06;
	__io_reg IABR07;
	__io_reg IABR08;
	__io_reg IABR09;
	__io_reg IABR10;
	__io_reg IABR11;
	__io_reg IABR12;
	__io_reg IABR13;
	__io_reg IABR14;
	__io_reg IABR15;
	__io_reg IABR16;
	__io_reg IABR17;
	__io_reg IABR18;
	__io_reg IABR19;
	__io_reg IABR20;
	__io_reg IABR21;
	__io_reg IABR22;
	__io_reg IABR23;
	__io_reg IABR24;
	__io_reg IABR25;
	__io_reg IABR26;
	__io_reg IABR27;
	__io_reg IABR28;
	__io_reg IABR29;
	__io_reg IABR30;
	__io_reg IABR31;
	__io_reg IPR00;
	__io_reg IPR01;
	__io_reg IPR02;
	__io_reg IPR03;
	__io_reg IPR04;
	__io_reg IPR05;
	__io_reg IPR06;
	__io_reg IPR07;
	__io_reg IPR08;
	__io_reg IPR09;
	__io_reg IPR10;
	__io_reg IPR11;
	__io_reg IPR12;
	__io_reg IPR13;
	__io_reg IPR14;
	__io_reg IPR15;
	__io_reg IPR16;
	__io_reg IPR17;
	__io_reg IPR18;
	__io_reg IPR19;
	__io_reg IPR20;
	__io_reg IPR21;
	__io_reg IPR22;
	__io_reg IPR23;
	__io_reg IPR24;
	__io_reg IPR25;
	__io_reg IPR26;
	__io_reg IPR27;
	__io_reg IPR28;
	__io_reg IPR29;
	__io_reg IPR30;
	__io_reg IPR31;
	__io_reg __dummy3[576];
	__io_reg CPUID;
	__io_reg ICSR;
	__io_reg VTOR;
	__io_reg AIRCR;
	__io_reg SCR;
	__io_reg CCR;
	__io_reg SHPR1;
	__io_reg SHPR2;
	__io_reg SHPR3;
	__io_reg SHCSR;
	__io_reg CFSR;
	__io_reg HFSR;
	__io_reg __dummy4;
	__io_reg MMAR;
	__io_reg BFAR;
	__io_reg __dummy5[19];
	__io_reg CAR;
	__io_reg __dummy6;
	__io_reg MPUTR;
	__io_reg MPUCR;
	__io_reg MPURNR;
	__io_reg MPURBAR;
	__io_reg MPURASR;
	__io_reg __dummy7[87];
	__io_reg STIR;
} _sys;

#endif /* __1986BE91_SYS_H */
