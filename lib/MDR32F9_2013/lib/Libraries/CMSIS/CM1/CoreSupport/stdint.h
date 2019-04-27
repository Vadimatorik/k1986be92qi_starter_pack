/*********************************************************************/
/*                                                                   */
/*             stdint.h standard header                              */
/*                                                                   */
/*                (c) 2010, Phyton                                   */
/*********************************************************************/

#ifndef __STDINT_H
#define __STDINT_H


   typedef   signed          char int8_t;
   typedef   signed short     int int16_t;
   typedef   signed           int int32_t;

   typedef unsigned          char uint8_t;
   typedef unsigned short     int uint16_t;
   typedef unsigned           int uint32_t;

   typedef   signed          char int_least8_t;
   typedef   signed short     int int_least16_t;
   typedef   signed           int int_least32_t;

   typedef unsigned          char uint_least8_t;
   typedef unsigned short     int uint_least16_t;
   typedef unsigned           int uint_least32_t;

   typedef   signed           int int_fast8_t;
   typedef   signed           int int_fast16_t;
   typedef   signed           int int_fast32_t;

   typedef unsigned           int uint_fast8_t;
   typedef unsigned           int uint_fast16_t;
   typedef unsigned           int uint_fast32_t;

   typedef   signed           int intptr_t;
   typedef unsigned           int uintptr_t;

   #define INT8_MIN           (-127-1)
   #define INT16_MIN          (-32767-1)
   #define INT32_MIN          (-2147483647-1)

   #define INT8_MAX           +127
   #define INT16_MAX          +32767
   #define INT32_MAX          +2147483647

   #define UINT8_MAX          255
   #define UINT16_MAX         65535U
   #define UINT32_MAX         4294967295U

   #define INT_LEAST8_MIN     (-127-1)
   #define INT_LEAST16_MIN    (-32767-1)
   #define INT_LEAST32_MIN    (-2147483647-1)

   #define INT_LEAST8_MAX     +127
   #define INT_LEAST16_MAX    +32767
   #define INT_LEAST32_MAX    +2147483647

   #define UINT_LEAST8_MAX    255
   #define UINT_LEAST16_MAX   65535U
   #define UINT_LEAST32_MAX   4294967295U


   #define INT_FAST8_MIN      INT32_MIN
   #define INT_FAST16_MIN     INT32_MIN
   #define INT_FAST32_MIN     INT32_MIN

   #define INT_FAST8_MAX      INT32_MAX
   #define INT_FAST16_MAX     INT32_MAX
   #define INT_FAST32_MAX     INT32_MAX

   #define UINT_FAST8_MAX     UINT32_MAX
   #define UINT_FAST16_MAX    UINT32_MAX
   #define UINT_FAST32_MAX    UINT32_MAX

   #define INTPTR_MIN         INT32_MIN
   #define INTPTR_MAX         INT32_MAX
   #define UINTPTR_MAX        UINT32_MAX

   #define PTRDIFF_MIN        INT32_MIN
   #define PTRDIFF_MAX        INT32_MAX

   #define SIG_ATOMIC_MIN     INT32_MIN
   #define SIG_ATOMIC_MAX     INT32_MAX

   #define SIZE_MAX           UINT32_MAX

   #define WCHAR_MIN          0
   #define WCHAR_MAX          UINT16_MAX

   #define WINT_MIN           INT32_MIN
   #define WINT_MAX           INT32_MAX

   #define INT8_C(x)          (x)
   #define INT16_C(x)         (x)
   #define INT32_C(x)         (x)

   #define UINT8_C(x)         (x ## u)
   #define UINT16_C(x)        (x ## u)
   #define UINT32_C(x)        (x ## u)

#endif /* __STDINT_H */

/* end of stdint.h */


