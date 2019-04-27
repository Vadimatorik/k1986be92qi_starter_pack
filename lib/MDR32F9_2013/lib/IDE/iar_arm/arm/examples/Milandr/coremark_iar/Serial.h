/*----------------------------------------------------------------------------
 * Name:    Serial.h
 *----------------------------------------------------------------------------*/

#ifndef __SERIAL_H
#define __SERIAL_H

extern void SER_init      (void);
extern int  SER_getChar   (void);
extern int  SER_getChar_nb(void);
extern int  SER_putChar   (unsigned char c);
extern void SER_putString (unsigned char *s);

#endif
