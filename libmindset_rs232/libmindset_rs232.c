/**
 * Library for communicating with Mindset
 * RS-232-C Cartridge
 *
 * Based on information in the Mindset Software
 * Developers Guide:
 *
 * http://www.bitsavers.org/pdf/mindset/Mindset_Software_Developers_Guide.pdf
 *
 * Author: Thom Cherryhomes <thom.cherryhomes@gmail.com>
 */

#include <i86.h>
#include "libmindset_rs232.h"

/**
 * Function: Writes one character to the RS-232-C output buffer.
 * 
 * Description: The RS-232~C SEND CHARACTER command writes one character to the
 * RS-232-C output buffer. If the buffer is full, the routine
 * waits until space becomes available and then writes the character
 * to the buffer.
 */
void mindset_rs232_send_char(unsigned short port, unsigned char c)
{
  union REGS regs;

  regs.h.ah=0x28;
  regs.h.al=c;
  regs.w.dx=port;

  int86(0xEE,&regs,&regs);
}

/**
 * Function: Returns a character from the RS-232-C input buffer.
 *
 * Description: The RS-232-C GET CHARACTER command reads one character and the
 * corresponding status byte from the RS-232-C input buffer. If
 * the buffer is empty, the routine waits until a character is
 * received.
 */
unsigned char mindset_rs232_receive_char(unsigned short port, ComPortStatus* status)
{
  union REGS regs;

  regs.h.ah=0x29;
  regs.w.dx=port;

  int86(0xEE,&regs,&regs);

  status->flags=regs.h.ah;

  return regs.h.al;
}
