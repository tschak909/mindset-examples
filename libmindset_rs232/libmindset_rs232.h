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

#ifndef LIBMINDSET_RS232_H
#define LIBMINDSET_RS232_H

typedef union comportstatus
{
  struct _comstatus
  {
    unsigned char data_ready: 1;
    unsigned char overrun_error: 1;
    unsigned char parity_error: 1;
    unsigned char framing_error: 1;
    unsigned char break_occurred: 1;
    unsigned char transmission_holding_register_empty: 1;
    unsigned char transmission_shift_register_empty: 1;
    unsigned char timeout_occurred: 1;
  };
  unsigned char flags; // Get everything as one byte.    
} ComPortStatus;

typedef union modemstatus
{
  struct _mdmstatus
  {
    unsigned char cts_changed: 1;
    unsigned char dsr_changed: 1;
    unsigned char ri_changed: 1;
    unsigned char rxd: 1;
    unsigned char cts: 1;
    unsigned char dsr: 1;
    unsigned char ri: 1;
    unsigned char line_signal: 1;
  };
  unsigned char flags; // Get everything as one byte.
} ModemStatus;

/**
 * Function: Writes one character to the RS-232-C output buffer.
 * 
 * Description: The RS-232~C SEND CHARACTER command writes one character to the
 * RS-232-C output buffer. If the buffer is full, the routine
 * waits until space becomes available and then writes the character
 * to the buffer.
 */
void mindset_rs232_send_char(unsigned short port, unsigned char c);

/**
 * Function: Returns a character from the RS-232-C input buffer.
 *
 * Description: The RS-232-C GET CHARACTER command reads one character and the
 * corresponding status byte from the RS-232-C input buffer. If
 * the buffer is empty, the routine waits until a character is
 * received.
 */
unsigned char mindset_rs232_receive_char(unsigned short port, ComPortStatus* status);

#endif /* LIBMINDSET_RS232_H */
