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

/**
 * Function: Writes a character string to the RS-232-C output buffer.
 *
 * Description: The RS-232-C SEND CHARACTER STRING command writes a string of
 * characters to the RS-232-C character output buffer. If the output
 * buffer does not have sufficient space for all the characters,
 * the routine waits for transmission over the line to empty
 * the buffer. As each byte opens up in the output buffer, the
 * routine writes another character to it until all the characters
 * are written.
 */
void mindset_rs232_send_string(unsigned short port, unsigned char __far* s, unsigned short len)
{
  union REGS regs;
  struct SREGS sregs;

  segread(&sregs);
  
  regs.h.ah=0x2A;
  regs.w.dx=port;
  regs.w.bx=FP_OFF(s);
  sregs.es=FP_SEG(s);

  int86x(0xEE,&regs,&regs,&sregs);
}

/**
 * Function: Returns the status of the RS-232-C input and output buffers.
 *
 * Description: The RS-232-C GET BUFFER STATUS routine returns the number of
 * empty bytes currently in the RS-232-C input and output buffers.
 * It also returns buffer-empty and buffer-full status information.
 */
unsigned char mindset_rs232_get_buffer_status(unsigned short port, unsigned short* emptyin, unsigned short* emptyout)
{
  union REGS regs;

  regs.h.ah=0x2B;

  int86(0xEE,&regs,&regs);

  *emptyin=regs.w.bx;
  *emptyout=regs.w.cx;
  
  return regs.h.ah; // Return status byte.
}

/**
 * Function: Specifies the size and location of the RS-232-C input buffer.
 *
 * Description: The RS-232-C SET INPUT BUFFER command specifies the RS-232-C
 * input buffer. The RS-232-C input buffer stores one byte of data
 * and one byte of status bits for each- character received. Thus,
 * one word (two bytes) is required for each character that is
 * stored in the input buffer. The input buffer stores incoming
 * characters until they are read by a user program.
 */
void mindset_rs232_set_input_buffer(unsigned short port, unsigned short __far* buf, unsigned short len)
{
  union REGS regs;
  struct SREGS sregs;

  segread(&sregs);

  regs.h.ah=0x2C;
  regs.w.cx=len;
  regs.w.dx=port;
  regs.w.bx=FP_OFF(buf);
  sregs.es=FP_SEG(buf);

  int86x(0xEE,&regs,&regs,&sregs);
}

/**
 * Function: Sets up the size and location of the RS-232-C output buffer.
 * 
 * Description: The RS-232-C SET OUTPUT BUFFER command specifies the RS-232-C
 * output buffer. Unlike the input buffer, the output buffer is
 * one byte wide. This buffer is used to store outgoing characters
 * until they can be transmitted over an RS-232-C link.
 */
void mindset_rs232_set_output_buffer(unsigned short port, unsigned short __far* buf, unsigned short len)
{
  union REGS regs;
  struct SREGS sregs;

  segread(&sregs);

  regs.h.ah=0x2D;
  regs.w.cx=len;
  regs.w.dx=port;
  regs.w.bx=FP_OFF(buf);
  sregs.es=FP_SEG(buf);

  int86x(0xEE,&regs,&regs,&sregs);  
}

/**
 * Function: Sets up the communications controls and interrupt enables for
 * RS-232-C communications.
 *
 * Description: The RS-232-C SET COMMUNICATIONS CONTROL routine specifies the
 * RS-232-C Request to Send (RTS) and Data Terminal Ready (DTR)
 * control lines. It also specifies the transmit and receive interrupt enables.
 */
void mindset_rs232_set_communications_control(unsigned short port, CommCtrlFlags* ctrl, IntEnableFlags* intenab)
{
  union REGS regs;
  regs.h.ah=0x2E;
  regs.h.al=ctrl->flags;
  regs.h.bl=intenab->flags;
  regs.w.dx=port;

  int86(0xEE,&regs,&regs);
}

/**
 * Function: Returns the current specifications of the communications controls
 * and interrupt enables for RS-232-C communications.
 *
 * Description: The RS-232-C GET COMMUNICATIONS CONTROL routine returns the
 * information set in the RS-232-C SET COMMUNICATIONS CONTROL
 * command: the RS-232-C Request to Send (RTS) and Data Terminal
 * Ready (DTR) control lines, and the transmit and receive enables.
 */
void mindset_rs232_get_communications_control(unsigned short port, CommCtrlFlags* ctrl, IntEnableFlags* intenab)
{
  union REGS regs;
  regs.h.ah=0x2F;
  regs.w.dx=port;
  
  int86(0xEE,&regs,&regs);
  ctrl->flags=regs.h.al;
  intenab->flags=regs.h.bl;
}

/**
 * Function: Returns information on which modem modules are installed.
 *
 * Description: The RS-232-C GET MODEM STATUS command indicates whether a
 * 300-baud modem module, 1200-baud modem module, or both modem
 * modules are installed in the Mindset computer. This command
 * also returns the RS-232-C index associated with each modem module.
 * The index is the value placed in DX for all RS-232-C
 * commands.
 */
void mindset_rs232_get_modem_status(ModemEquipment* me)
{
  union REGS regs;
  regs.h.ah=0x30;

  int86(0xEE,&regs,&regs);
  me->flags=regs.h.al;
}

/**
 * Function: Sets or clears the communications break transmission enable.
 *
 * Description: The RS-232-C SET COMMUNICATIONS BREAK command controls communications
 * break transmissions. This command sets a communications
 * break enable on a specified modem module to allow break transmissions
 * to occur and clears the enable to prevent break
 * transmissions.
 */
void mindset_rs232_set_communications_break(unsigned short port, unsigned char be)
{
  union REGS regs;
  regs.h.ah=0x31;
  regs.h.al=be;
  regs.w.dx=port;
  int86(0xEE,&regs,&regs);
}

