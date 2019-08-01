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

typedef union _comportparams
{
  struct __comportparams
  {
    unsigned char data_bits: 2;
    unsigned char stop_bits: 1;
    unsigned char parity: 2;
    unsigned char baud: 3;
  };
  unsigned char params;
} ComPortParams;

/**
 * Function: Specifies initialization parameters for a selected communications
 * port.
 *
 * Description: The INITIALIZE COM PORT RS-232-C I/O command specifies the baud
 * rate, parity, stop bit, and number of data bits per character
 * for the communications port.
 */
unsigned short mindset_rs232_init_com_port(unsigned short port, ComPortParams* params, ComPortStatus* status);

/**
 * Function: Returns the status of the selected communications port.
 *
 *Description: The GET COM PORT STATUS RS-232-C 1/0 command returns the status
 * of the selected communications port.
 * The GET COM PORT STATUS routine clears the error and status
 * conditions after placing the corresponding bits in AH and AL. 
 */
void mindset_rs232_get_com_port_status(unsigned short port, ComPortStatus* cs, ModemStatus* ms);
  
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
void mindset_rs232_send_string(unsigned short port, unsigned char __far* s, unsigned short len);

/**
 * Function: Returns the status of the RS-232-C input and output buffers.
 *
 * Description: The RS-232-C GET BUFFER STATUS routine returns the number of
 * empty bytes currently in the RS-232-C input and output buffers.
 * It also returns buffer-empty and buffer-full status information.
 */
unsigned char mindset_rs232_get_buffer_status(unsigned short port, unsigned short* emptyin, unsigned short* emptyout);

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
void mindset_rs232_set_input_buffer(unsigned short port, unsigned short __far* buf, unsigned short len);

/**
 * Function: Sets up the size and location of the RS-232-C output buffer.
 * 
 * Description: The RS-232-C SET OUTPUT BUFFER command specifies the RS-232-C
 * output buffer. Unlike the input buffer, the output buffer is
 * one byte wide. This buffer is used to store outgoing characters
 * until they can be transmitted over an RS-232-C link.
 */
void mindset_rs232_set_output_buffer(unsigned short port, unsigned short __far* buf, unsigned short len);

/**
 * Function: Sets up the communications controls and interrupt enables for
 * RS-232-C communications.
 *
 * Description: The RS-232-C SET COMMUNICATIONS CONTROL routine specifies the
 * RS-232-C Request to Send (RTS) and Data Terminal Ready (DTR)
 * control lines. It also specifies the transmit and receive interrupt enables.
 */
typedef union _commctrlflags
{
  struct __commctrlflags
  {
    unsigned char dtr: 1;
    unsigned char rts: 1;
  };
  unsigned char flags;
} CommCtrlFlags;

typedef union _intenableflags
{
  struct __intenableflags
  {
    unsigned char rxd: 1;
    unsigned char txd: 1;
  };
    unsigned char flags;
} IntEnableFlags;

void mindset_rs232_set_communications_control(unsigned short port, CommCtrlFlags* ctrl, IntEnableFlags* intenab);

/**
 * Function: Returns the current specifications of the communications controls
 * and interrupt enables for RS-232-C communications.
 *
 * Description: The RS-232-C GET COMMUNICATIONS CONTROL routine returns the
 * information set in the RS-232-C SET COMMUNICATIONS CONTROL
 * command: the RS-232-C Request to Send (RTS) and Data Terminal
 * Ready (DTR) control lines, and the transmit and receive enables.
 */
void mindset_rs232_get_communications_control(unsigned short port, CommCtrlFlags* ctrl, IntEnableFlags* intenab);

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
typedef union _modemequipment
{
  struct __modemequipment
  {
    unsigned char unused: 1;
    unsigned char installed300: 1;
    unsigned short installed300port: 2;
    unsigned char installed1200: 1;
    unsigned short installed1200port: 2;
  };
  unsigned char flags;
} ModemEquipment;

void mindset_rs232_get_modem_status(ModemEquipment* me);

/**
 * Function: Sets or clears the communications break transmission enable.
 *
 * Description: The RS-232-C SET COMMUNICATIONS BREAK command controls communications
 * break transmissions. This command sets a communications
 * break enable on a specified modem module to allow break transmissions
 * to occur and clears the enable to prevent break
 * transmissions.
 */
void mindset_rs232_set_communications_break(unsigned short port, unsigned char be);

#endif /* LIBMINDSET_RS232_H */
