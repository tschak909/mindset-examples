/**
 * Library for communicating with Mindset
 * Graphics coprocessor
 *
 * Based on information in the Mindset Software
 * Developers Guide:
 *
 * http://www.bitsavers.org/pdf/mindset/Mindset_Software_Developers_Guide.pdf
 *
 * Author: Thom Cherryhomes <thom.cherryhomes@gmail.com>
 */

#ifndef LIBMINDSET_GFX_H
#define LIBMINDSET_GFX_H

#define INT_VIDEO 0xEF

/**
 * Set Screen mode
 *
 * Set the Mindset to a specific screen mode
 *
 * mode - The desired display mode:
 * --------------------------------
 *
 * 0 - 320x200   2 colors    single or double buffering
 * 1 - 320x200   4 colors    single or double buffering
 * 2 - 320x200  16 colors    single buffering only
 * 3 - 640x200   2 colors    single or double buffering
 * 4 - 640x200   4 colors    single buffering only
 * 5 - 320x400   4 colors    single only, interlaced
 * 6 - 640x400   2 colors    single only, interlaced
 *
 * Call this function to set up graphics mode.
 * All palette registers are cleared and save for 
 * the background color, are set to white.
 */
void mindset_gfx_set_mode(unsigned char mode);

/**
 * Get the current screen mode, video flags, and bits per pixel
 *
 * mode - The current video mode.
 * flags - The current video mode flags
 *         bit       definition
 *         --------------------------------------------------------
 *           0       System Flag
 *           1       Industry-Standard APA mode enabled.
 *           2       Industry-Standard character mode enabled.
 *           3       Double-Buffering enabled
 *           4       50Hz (PAL) mode, otherwise 60Hz NTSC
 *           5       System Flag
 *           6       current mode is interlaced.
 *           7       System
 *           8       External sync enabled
 *           9       Genlock is enabled
 *          10       Second frame buffer is on display.
 *          11       80-column character mode enabled
 *          12       System flag
 *          13       PAL mode, otherwise NTSC
 *          14       TV mode enabled, otherwise Monitor
 *          15       B&W TV mode enabled, otherwise colorburst enabled.
 *
 * bpp - The number of bits per pixel.
 *
 */
void mindset_gfx_get_mode(unsigned char* mode, unsigned short* flags, unsigned short* bpp);

/**
 * Set display Device
 * Function: Sets the display for either a television or an RGB color monitor
 * and then reloads the color palette.
 * Description: The SET DISPLAY DEVICE command changes the current display setup
 * to that for a color television, black-and-white television, or
 * color monitor. After the system changes the setup, it reloads
 * the color palette for the selected device.
 *
 * sets the display setup according to the following bits:
 *
 * Bit 0: - is a 0 for television operation, or 1 for monitor operation.
 * Bit 1: - is a 0 for color television, or a 1 for B/W television only.
 *
 */
void mindset_gfx_set_display_device(unsigned char device);

/**
 * Set screen position
 * Function: Sets the position of the screen within the screen border.
 * Description: The SET SCREEN POSITION command uses a single parameter to
 * define the position of the screen within the screen border.
 * This 1-byte parameter uses the most significant 4 bits to specify the vertical (Y-axis) location of the screen and the least
 * significant 4 bits to speoify the horizontal (X-axis) location.
 *
 * Setting (AL) to OOH places the screen at the upper left corner
 * of the border and OFFH places the screen at the lower right corner of the border.
 * The SET SCREEN POSITION command affects only the current setting. The system configuration screen defines the default
 * setting.
 * (AL) is the location of the screen. Bits 0 through 3 specify the X-coordinate of the screen, and bits 4 through
 * 7 specify the Y-coordinate.
 *
 */
void mindset_gfx_set_screen_position(unsigned char position);

/**
 * Function: Returns the position of the screen within the screen border.
 * Description: The GET SCREEN POSITION command returns a single parameter that
 * reports the current position of the screen within the screen
 * border. This 1-byte parameter uses the most significant 4 bits
 * to specify the vertical (Y-axis) location of the screen and the
 * least significant 4 bits to specify the horizontal (X-axis)
 * location.
 * 
 * A value of OOH in (AL) causes the screen to appear at the upper
 * left corner of the border and OFFH causes the screen to appear
 * at the lower right corner of the border.
 *
 */
unsigned char mindset_gfx_get_screen_position(void);

/**
 * Function: Enables or disables the use of genlock for transparent colors,
 * enables or disables interlaced sync display, and enables or
 * disables fixed-phase display.
 * 
 * Description: The SET DISPLAY SYNC FEATURES command performs three distinct
 * but related functions: enabling genlock, enabling interlaced
 * sync display, and enabling fixed-phase display. Enabling genlock makes certain colors transparent so that an external video
 * signal can show through.
 * 
 * Normally, the Mindset computer provides its own sync signal for
 * video operation (internal video synchronization is the default).
 * Using genlock, the Mindset computer can alternat·ively synchronize its output with the output from another video device such
 * as a camera or video tape recorder. The genlock enable bit
 * determines whether the Mindset computer provides its sync signal
 * independently or matches its sync signal with the sync signal of
 * an external device.
 * 
 * Genlock is normally disabled. When the user enables genlock, it
 * affects only the colors that do not have the key bit set within
 * their color palette definition; enabling genlock makes these
 * colors transparent. This feature is most useful for making the
 * background transparent so that an external video signal provides
 * the background.
 * 
 * The interlaced sync display is normally disabled. Enabled, this
 * feature uses 200 lines of display data, but displays data with
 * an interlaced sync using 400 scan lines. Using an even/odd scan
 * line pair to display each row of pixels creates a more filled-in
 * look on the display.
 * 
 * Fixed-phase synchronization, when enabled, provides more flexibility in pixel-by-pixel color mixing and prevents flashing on
 * the display. However, it also changes the television display so
 * that some pictures may appear distorted. 
 */
void mindset_gfx_set_display_sync_features(unsigned char features);

/**
 * Set Display Interrupt
 * Specifies the scan line at which the display processor causes
 * the CPU to perform a user-defined interrupt service routine.
 * This command also enables and disables a diagnostic marker that
 * appears on the specified scan line.
 * Description: The SET DISPLAY INTERRUPT command enables the user to synchronize animation with the drawing of the screen by the display
 * processor. This command controls a marker to assist the user in
 * tracing the operation of the display interrupt. This diagnostic
 * Input
 * j marker is a horizontal line that appears on the scan line that
 * triggers the display interrupt.
 * The display interrupt operates only in the graphics mode of the
 * Mindset computer.
 * 
 * A scan line is comprised of a row of pixels. The top scan line
 * on the screen is line 0 and the bottom scan line is line 199.
 * In interlaced graphics modes, the bottom scan line is effectively the 398th (on even line passes) or 399th (on odd line
 * passes) line displayed, but is still referred to as line 199 in
 * this command because it is the 199th line scanned on each pass.
 * If the user does not define a scan line with the SET DISPLAY
 * INTERRUPT command, the system uses line 199 as the default scan
 * line for calling the user-defined interrupt routine.
 * Use the SET DISPLAY INT ADDRESS command to specify the address
 * of the user-defined service routine (see "Graphics Coprocessor
 * Operation" later in this section). The default value for this
 * vector is zero. If the vector is zero, the system does not call
 * a user-defined interrupt service routine. ':'(
 * 
 * line - Scanline to trigger display interrupt (0-199)
 * marker - enable/disable diagnostic marker for display interrupt line
 *
 */
void mindset_gfx_set_display_interrupt(unsigned char line, unsigned char marker);

/**
 * Set Palette
 *
 * Specifies the contents of the color palette and selects the
 * color of the screen border.
 * Description: The SET PALETTE command specifies all or part of the contents of
 * the color palette and selects the screen border color. The user
 * must supply a color data array in memory that the SET PALETTE
 * command copies into the color palette.
 *
 * The SET PALETTE command includes a BORDER color parameter, an
 * offset into the color palette, a count of the number of words to
 * be copied to the color palette (N), and an ARRAY parameter that
 * is a pointer to the first word of the user-supplied color data.
 *
 * The BORDER parameter of the SET PALETTE command is an index
 * that selects an entry from the color palette as the screen
 * border color. The system ignores BORDER values greater than
 * decimal 15.
 * 
 * The offset parameter is an index value from 0 to 15 that specifies a word within the color palette. Beginning with this
 * word, the system copies the user-specified color data into the
 * color palette.
 * The num parameter specifies the number of words to copy from the
 * user array to the color palette. This value must be from 0 to
 * 16. The system does not alter the color palette if the value of
 * num is 0.
 *
 * The palette parameter is the address of the first word to be copied from the user array to the color palette. 
 *
 * Each 16-bit word of the palette is arranged thusly:
 * ---------------------------------
 * |M|M|M|M|U|U|T|T|T|T|T|T|T|T|T|T|
 * |I|R|G|B|U|U|K|B|B|B|G|G|G|R|R|R|
 * ---------------------------------
 * The most significant four bits are used for RGBI in monitor mode
 * The least significant 9 bits are used for TV mode, thus one 16-bit
 * palette entry defines colors for both modes independently.
 *
 * M - Monitor color
 * T - Television color
 * R - Red
 * G - Green
 * B - Blue
 * I - Intensity
 * K - Key onto external video
 * U - Unused
 *
 */
void mindset_gfx_set_palette(unsigned char border, unsigned short num, unsigned short offset, unsigned long* palette);

/**
 * Get Color Palette
 * Function: Returns the value of the screen border color and the contents of
 * the color palette.
 *
 * Description: The GET PALETTE command returns all or part of the contents of
 * the color palette and the index into the color palette that
 * selects the screen border color. The user must provide an area
 * in memory to receive the color data from the color palette.
 *
 * The input parameters for the GET PALETTE command include an offset into the color palette, a count of the number of words to be
 * copied from the color palette (N), and an ARRAY parameter that
 * is a pointer to the area of memory receiving the color palette
 * data.
 *
 * The offset parameter is an index value from 0 to 15 that specifies a word within the color palette. Beginning with this
 * word, the system copies the color palette data into the userspecified area of memory.
 * The N parameter specifies the number of words to copy from the
 * color palette to the user array. This value must be from 0 to
 * 16. The system does not copy any color palette data if the
 * value of N is zero.
 * 
 * The palette parameter is the user-specified address of the area
 * that is to receive the color palette data.
 *
 * The output parameters include a border color parameter and the
 * user-specified area of memory that receives the requested data
 * from the color palette.

 * The BORDER parameter of the GET PALETTE command returns the
 * color index of the border. The ARRAY parameter is a pOinter to
 * the data area that receives the color palette data. 
 *
 * For palette format information, see mindset_gfx_set_palette() above.
 *
 */
void mindset_gfx_get_palette(unsigned short num, unsigned short offset, unsigned char* border, unsigned short* palette);

/**
 * Get Buffer Info
 * Returns the addresses and size of the system frame buffers.
 * Description: The GET BUFFER INFO command returns the addresses and size of
 * the system frame buffers.
 *
 * The parameters returned by this command are FRAME BUFFER 1,
 * FRAME BUFFER 2, and SIZE.
 *
 * FRAME BUFFER 1 and FRAME BUFFER 2 are the paragraph addresses of
 * the two system frame buffers; these buffers are always paragraph
 * aligned.
 *
 * In some cases, FRAME BUFFER 1 and FRAME BUFFER 2 may not be contiguous. Therefore, you should not use the difference between
 * the two buffer addresses to calculate the buffer size.
 * SIZE is the length in bytes of each frame buffer. SIZE is a
 * constant value that is independent of the current display mode.
 * The SIZE value is one half of the actual buffer size for the
 * graphics modes that do not permit double buffering.
 * In display modes where double buffering is not possible (such as
 * 320 x 200 x 4), the FRAME BUFFER 1 address is the address of the
 * single frame buffer. The actual size of the single frame buffer
 * is 2*SIZE. 
 */
unsigned short mindset_gfx_get_buffer_info(void __far *buffer1, unsigned short __far *buffer2);

/**
 * Set Display Int Address
 *
 * Specifies the address of the user-defined display interrupt service
 * routine.
 *
 * Description: The SET DISPLAY INT ADDRESS command specifies the paragraph and
 * offset addresses of a user-defined interrupt service routine.
 * The system calls this routine each time it finishes writing the
 * frame buffer image to the screen, or when the GCP reaches the
 * scan line selected by the SET DISPLAY INTERRUPT command (see SET
 * DISPLAY INTERRUPT earlier in this section). Specifying an
 * address of 0 informs the system that there is no user-defined
 * interrupt routine to service.
 *
 * The last scan line on the screen is the default scan line for
 * the display interrupt. This scan line coincides with early
 * VBLANK. In this case, the user's interrupt routine has approximately
 * 1 millisecond before late VBLANK occurs. The system
 * interrupts the user's routine at this time to perform its late
 * VBLANK procedures, and then returns to the user's routine.
 * The system uses the late VBLANK interrupt to change the color
 * palette and to switch the active frame buffer. Therefore, if
 * the user-defined display interrupt service routine makes changes
 * to the color palette or switches the active frame buffer, these
 * changes appear following the next late VBLANK interrupt.
 * Because the system interrupt handler ~nvokes the user-defined
 * service routine with a FAR CALL instruction, this routine must
 * terminate with a FAR RET instruction instead of an IRET
 * instruction.
 *
 * The user's main program must disable the
 * tor before the main program terminates.
 * display interrupt would cause the system
 * existent service routine.
 * display interrupt vecOtherwise,
 * the next
 * to jump to a non-exitent service routine.
 *
 */
void mindset_gfx_set_display_int_address(void __far *p);

/**
 * Returns the current address of the user-defined display interrupt
 * service routine.
 *
 * Description: The GET DISPLAY INT ADDRESS command returns the paragraph and
 * offset addresses last set by the SET DISPLAY INT ADDRESS
 * command.
 *
 * If the address of the display interrupt routine is other than
 * zero, the system uses this address as the beginning of a userdefined
 * display interrupt service routine. If this address is
 * zero, the system does not call a user-defined interrupt routine
 * when the display interrupt occurs.
 *
 */
void *mindset_gfx_get_display_int_address(void);

/**
 * Switch Active Buffer
 *
 * Function: Causes the system to switch active frame buffers.
 *
 * Description: The SWITCH ACTIVE BUFFER command operates in modes with double
 * buffering to switch the active frame buffer with the hidden
 * frame buffer. This command has no effect in modes restricted to
 * single buffering such as 320 x 200 x 4.
 *
 */
void mindset_gfx_switch_active_buffer(void);

/**
 * Set Transfer Mode
 * 
 * Function: Specifies how the GCP modifies the destination data with the
 * source data.
 *
 * Description: The SET TRANSFER MODE command selects two modes for GCP operations.
 * The visibility mode can be either opaque or transparent.
 * The logical transfer mode can be one of eight possible logical
 * operations for combining the source and destination data.
 * The opaque visibility mode transfers all data from the source to
 * the destination.
 *
 * When operating in the transparent mode, the GCP does not transfer
 * any pixel whose bits are all 0. Other than ignoring any
 * pixel with all 0 bits, the transparent mode operates the same as
 * the opaque mode.
 *
 * The logical transfer modes determine how the data from each
 * source pixel modifies the data of each destination pixel. The
 * modes that include NOT source data read the source data into a
 * register, complement it, and then perform the AND, OR, exclusive-
 * OR, or replace operation with the destination data. Transparency
 * applies only to pixels that are ° before the NOT
 * operation.
 *
 * The SET SCREEN MODE command automatically resets the visibility
 * mode to opaque and the logical transfer mode to replace the destination
 * data with the source data.
 *
 * visibility_mode - Sets either opaque or transparent visibility mode
 *                   0 transfers all bits from source to destination
 *                   1 Does not transfer any source pixels with all zero bits.
 *
 * logical_combination_mode - selects the logical operation to apply to pixels
 *                            ------------------------------------------------
 *                            0     COPY source to destination
 *                            1     AND source to destination
 *                            2     OR source to destination
 *                            3     XOR source to destination
 *                            4     NOT COPY source to destination
 *                            5     NOT AND source to destination
 *                            6     NOT OR source to destination
 *                            7     NOT XOR source to destination
 *
 */
void mindset_gfx_set_transfer_mode(unsigned char visibility_mode, unsigned char logical_combination_mode);

/**
 * Get Transfer Mode
 *
 * Function: Returns the current transfer mode parameters.
 *
 * Description: The GET TRANSFER MODE command returns the current values for the
 * visibility mode and the logical transfer mode.
 *
 */
void mindset_gfx_get_transfer_mode(unsigned char* visibility_mode, unsigned char* logical_combination_mode);

/**
 * Set Destination Buffer
 *
 * Function: Specifies the address and size of the destination buffer for all
 * subsequent GCP operations.
 *
 * Description: The SET DESTINATION BUFFER command prepares the system for GCP
 * operations by defining the destination buffer for all subsequent
 * data transfers originating from any source buffer. This command
 * automatically resets the clip rectangle to match the bounds of
 * the new destination buffer.
 *
 * The destination buffer may reside within any segment of the
 * 1-megabyte address space of the Mindset computer as long as the
 * buffer begins on a word boundary.
 *
 */
void mindset_gfx_set_destination_buffer(unsigned short width, unsigned short height, unsigned short __far *buffer);

/**
 * Get Destination Buffer
 *
 * Function: Returns the current destination buffer parameters.
 *
 * Description: The GET DESTINATION BUFFER command returns the address and size
 * of the area of memory currently designated as the destination
 * buffer.
 *
 */
void mindset_get_destination_buffer(unsigned short* width, unsigned short* height, unsigned short __far *buffer);

/**
 * Function: Sets the write mask for all subsequent GCP operations.
 *
 * Description: The SET WRITE MASK command defines a 16-bit write mask. The GCP
 * examines the write mask before transferring data to the destination
 * buffer. The bit positions of the write mask correspond
 * to the bit positions of the words within the destination buffer.
 *
 * A a bit in the write mask prevents the GCP from modifying the
 * corresponding bit in a word within the destination buffer. The
 * GCP can modify only those bits that have a 1 in the same bitposition
 * in the write mask.
 * 
 * As a result, a mask of OFFFFH specifies that all bits within
 * each word of the destination buffer may be modified. Conversely,
 * a mask of OOOOH prevents a GCP operation from having
 * any effect because this mask protects all destination bits from
 * modification.
 *
 * The SET SCREEN MODE command automatically resets the write mask
 * to OFFFFH.
 *
 */
void mindset_gfx_set_write_mask(unsigned short write_mask);

/**
 * Get Write Mask
 *
 * Function: Returns the value of the current write mask.
 * 
 * Description: The GET WRITE MASK command returns the write mask last set by
 * the SET WRITE MASK command (unless modified by the SET SCREEN
 * MODE routine). Each 1 bit within the write mask enables the GCP
 * to modify the corresponding bit of the words within the destination
 * buffer. A 0 bit within the write mask prevents the GCP
 * from modifying that bit in a word.
 *
 * The SET SCREEN MODE command automatically resets the write mask
 * to OFFFFH.
 */
unsigned short mindset_gfx_get_write_mask(void);

/**
 * BLT Copy
 *
 * Function: Transfers data from the source buffer to the destination buffer.
 *
 * (figure 4-3 omitted, see developers guide)
 *
 * Description: Each BLT COpy command specifies a series of block transfer operations
 * from one or more source buffers to a common destination
 * buffer. The object definitions are stored in memory as an array
 * of parameter groups. The user must supply a BLT COpy parameter
 * group for each separate object to be transferred.
 * 
 * The BLT COPY command includes a BLT ID number, a destination
 * X-ORIGIN, a destination Y-ORIGIN, a BLT COPY parameter group
 * count (N), and the PARAMETER POINTER, which is the location of
 * the first byte of the first 20-byte BLT COPY parameter group.
 * 
 * The BLT ID number is a user-defined 8-bit value. The GCP
 * returns this ID number to the user's interrupt routine in the
 * event that this BLT COPY operation causes a clip or a collision.
 * 
 * The 16-bit X-ORIGIN and Y-ORIGIN values are signed offsets (in
 * pixels) that provide a common point of reference within the destination
 * buffer for all block transfers specified by a single
 * BLT COpy command. The pixel at location (0,0) occupies the
 * upper left corner of the destination buffer. The X-ORIGIN and
 * Y-ORIGIN values are positive to the right of and below this
 * pixel, respectively.
 * 
 * The 16-bit BLT COPY parameter group count N specifies the number
 * of transfer operations that are part of a single BLT COPY command.
 * This value should not exceed 16 if the user intends to
 * use the GCP WAIT command to poll for collision and clipping
 * information.
 *
 * The PARAMETER POINTER is the address of the first byte of the
 * first BLT COpy parameter group. Each BLT COPY parameter group
 * specifies a separate block transfer operation.
 * The 20-byte BLT COPY parameter group for each block transfer
 * includes the SOURCE ADDRESS offset, the SOURCE ADDRESS PARAGRAPH,
 * the SOURCE WIDTH, an X-SOURCE value, a Y-SOURCE value, an
 * X-SIZE value, a Y-SIZE value, an X-DESTINATION value, a
 * Y-DESTINATION value, and a SOURCE MASK.
 *
 * The SOURCE ADDRESS offset and the SOURCE ADDRESS PARAGRAPH specify
 * the word that represents the upper left corner of the rectangular
 * source buffer. They are both 16-bit values.
 *
 * The 16-bit SOURCE WIDTH value within the BLT COPY parameter
 * group specifies the number of bytes per scan line of the source
 * buffer. This value must be an even number.
 *
 * Although the GCP requires that both the source and destination
 * buffers be word-aligned and a multiple of 16 bits in width, the
 * rectangular region that the hardware transfers may begin on any
 * pixel boundary and use any (even or odd) number of pixels as the
 * horizontal or vertical size.
 *
 * The 16-bit X-SOURCE and Y-SOURCE values are signed offsets (in
 * pixels) from the pixel at the upper left corner of the source
 * buffer. These values define the upper left corner of the region
 * of the source buffer that theGCP transfers.
 *
 * The 16-bit X-SIZE and Y-SIZE values are dimensions (in pixels).
 * These values define the width and length of the region of the
 * source buffer that the GCP transfers. If either the X-SIZE or
 * Y-SIZE value is zero, the GCP does not perform the transfer.
 * The GCP does not perform clipping on the source buffer, so the
 * user must make sure that the specified rectangle lies within the
 * source buffer.
 *
 * The 16-bit X-DESTINATION and Y-DESTINATION values are signed
 * offsets (in pixels) from the pixel specified by the X-ORIGIN and
 * Y-ORIGIN values. The GCP adds the (X,Y) destination values to
 * the (X,Y) origin values to specify the location of the first
 * destination pixel in a BLT COPY operation. (The (X,Y) origin
 * values are themselves offsets.)
 *
 * The SOURCE MASK is a 16-bit value that the GCP ANDs with each
 * word of the source data before it transfers the data to the destination
 * buffer. By selectively turning off bits in each pixel,
 * the SOURCE MASK can display an object in a color different from
 * the color in which it was defined. (Note that this operation is
 * different from BLT WRITE MASK, which determines which destination
 * bits may be modified by a BLT COPY operation.)
 *
 * The following example shows one way to use the BLT COPY command:
 * 1. Use SET SCREEN MODE to specify the screen resolution, to
 *   select single- or double-buffered operation, and to select
 *   interlaced or non-interlaced output.
 *
 * 2. Use SET DESTINATION BUFFER to specify the location and size
 *   of the destination buffer that is to receive the information.
 *   To display the transferred information, the destination
 *   buffer must be a frame buffer.
 *
 * 3. Use SET TRANSFER MODE to specify the type of transfer.
 *
 * 4. Use SET WRITE MASK to determine which bits within the destination
 *    buffer may be modified.
 *
 * 5. Use BLT COPY to specify the following information, which may
 *    vary each time BLT COPY is called:
 *
 *  a. The BLT ID number used for collision and clip detection
 *     (BLT ID).
 *
 *  b. The (X,Y) origin within the destination buffer (X-ORIGIN
 *     and Y-ORIGIN). The data transferred by each BLT COPY
 *     parameter group is relative to this origin.
 *
 *  c. The number of BLT COpy parameter groups to be
 *     processed (N).
 *  d. Certain modes of operation (see input parameter (DX)
 *      below)
 *  e. The location of the first BLT COPY parameter group
 *      (PARAMETER POINTER).
 * 6. Use each BLT COPY parameter group to specify the following
 *    information relating to a single block transfer:
 *    a. The location of the source buffer (SOURCE ADDRESS offset
 *       and SOURCE ADDRESS PARAGRAPH).
 *    b. The width (in an even number of bytes) of the source
 *       buffer (SOURCE WIDTH).
 *    c. X and Y offsets (in pixels) into the source buffer
 *       (X-SOURCE and Y-SOURCE). These values determine the
 *       upper left corner of the rectangular region of the
 *       source buffer to be transferred.
 *    d. The width and height (in pixels) of the portion of the
 *       source buffer that is to be transferred (X-SIZE and
 *       Y-SIZE)
 *    e. X and Y offsets (in pixels) into the destination buffer
 *       (X-DESTINATION and Y-DESTINATION). These offset values
 *       are relative to X-ORIGIN and Y-ORIGIN.
 *    f. The mask that the system ANDs with each source word
 *       before it transfers the word to the destination buffer
 *       (SOURCE MASK).
 *    g. The offset to the next parameter group (optional; see
 *       the SET PARAM BLOCK MODE command).
 * 7. Use SET COLLISION/CLIP/DONE DETECT to specify collision and
 *    clip operations.
 * 8. Use SET CLIP RECTANGLE to specify the clipping bounds if
 *    necessary.
 *
 * Parameters: blt_id       User specified 8-bit BLT ID that the GCP returns
 *                          to the user's interrupt routine, if this BLT COPY
 *                          operation results in a collision or a clip.
 *       
 *             len          Number of parameter groups in this BLT COPY operation.
 *             
 *             mode         Specify mode command flags:
 *                          ---------------------------------------------------
 *                          bit    bit value     definition
 *                          ---------------------------------------------------
 *                            0            0     Read source from top to bottom
 *                                         1     Read source from bottom to top
 *                            1            0     Write Destination from top to bottom
 *                                         1     Write Destination from bottom to top
 *                            2            0     Read/Write from Left to Right
 *                                         1     Read/Write from Right to Left
 *                            3            "     Reserved (must match bit 2)
 *                            4            0     Normal BLT mode.
 *                                         1     Fast BLT mode--Provided to enhance
 *                                               master/slave double buffering. In fast
 *                                               BLT mode, the system moves data from
 *                                               the source to destination as quickly
 *                                               as possible, by:
 *                                                 
 *                                               1. Ignoring the current setting of
 *                                                  the transfer mode (opaque or replace
 *                                                  is used instead.)
 *                                               2. Ignoring the current setting of collision
 *                                                  detect (it is suspended.)
 * 
 *                                               Clipping, if enabled, is performed
 *                                               as usual. The user must ensure
 *                                               that, after clipping:
 * 
 *                                               1. (DX) bits 0 through 3 are zero.
 *                                               2. The width of the transferred rectangle
 *                                                  is an integer number of words.
 *
 *                         5-15                  Reserved, must be zero.
 *
 *             x           The X origin within the destination buffer
 * 
 *             y           The Y origin within the destination buffer.
 *
 *             params      The parameter pointer, which is the address of the first byte
 *                         of the first 20-byte BLT COPY parameter group. The BLT COPY parameter
 *                         groups can be consective, or in the form of a linked list (see
 *                         mindset_gfx_set_param_block_mode() command description.) The GCP
 *                         services each BLT COPY parameter group in sequence until it performs
 *                         the number of transfer operations in the BLT COPY parameter group
 *                         count.
 *
 *                         Each 20-byte parameter group contains the followingt parameters
 *                         (listed by their array offsets):
 *
 *                         Offset        Parameter
 *                         ---------------------------------------------------------------------
 *                              0        Source address offset
 *                              1        Source address segment
 *                              2        Source width in bytes
 *                              3        X offset from source address in pixels
 *                              4        Y offset from source address in pixels
 *                              5        X destination offset from origin in pixels
 *                              6        Y destination offset from origin in pixels
 *                              7        X Width in pixels
 *                              8        Y height in pixels
 *                              9        source mask to and with source data during transfer
 *                              10       Offset to next parameter block. ONLY SPECIFY IF 
 *                                       SET PARAM BLOCK IS SET TO LINKED LIST!
 *                                       The end of the list is specified with 0xFFFF word value.
 *
 */
void mindset_gfx_blt_copy(unsigned char blt_id, unsigned short len, unsigned short flags, short x, short y, unsigned short __far *params);

/**
 * BLT Copy Word
 *
 * Function: Fills rectangular regions of the destination buffer with a
 * 16-bit pixel pattern.
 *
 * Description: Each BLT COPY WORD command specifies a series of block fill
 * operations within the destination buffer. The definitions of
 * the regions to be filled and the fill patterns are stored as an
 * array of parameter groups in memory. The user must supply a BLT
 * COPY WORD parameter group for each filled block in the destination
 * buffer.
 *
 * The BLT COpy WORD command includes a BLT ID number, a destination
 * X-ORIGIN, a destination Y-ORIGIN, a BLT COpy WORD parameter
 * group count (N), and the PARAMETER POINTER, which is the location
 * of the first byte of the first 10-byte BLT COpy WORD parameter
 * group.
 *
 * The BLT ID number is a user-defined 8-bit value. The GCP
 * returns this ID number to the user's interrupt routine if this
 * BLT COPY WORD operation causes a clip or a collision.
 * 
 * The 16-bit X-ORIGIN and Y-ORIGIN values are signed offsets in
 * pixels. They provide a common point of reference within the
 * destination buffer for all rectangles filled by a single BLT
 * COPY WORD command. The pixel at location (0,0) occupies the
 * upper left corner of the destination buffer; the X-ORIGIN and
 * Y-ORIGIN values are relative to this pixel.
 *
 * The 16-bit BLT COpy WORD parameter group count N specifies the
 * number of fill operations that are part of a single BLT COpy
 * WORD command. This value should not exceed 16 if the user
 * intends to use the GCP WAIT command to poll for collision and
 * clipping information.
 *
 * The PARAMETER POINTER is the address of the first byte of the
 * first BLT COpy WORD parameter group. Each BLT COPY WORD parameter
 * group specifies a separate fill operation~
 *
 * The 10-byte BLT COPY WORD parameter group for each fill operation
 * includes an X-DESTINATION value, a Y-DESTINATION value, an
 * X-SIZE value, a Y-SIZE value, and a FILL PATTERN.
 *
 * The 16-bit X-DESTINATION and Y-DESTINATION values are signed
 * offsets (in pixels) from the pixel specified by the X-ORIGIN and
 * Y-ORIGIN values. The GCP adds the (X,Y) destination values to
 * the (X,Y) origin values to specify the location of the first
 * destination pixel in a fill operation. (The (X,Y) origin values
 * are themselves offsets.)
 *
 * The 16-bit X-SIZE and Y-SIZE values define, in pixels, the width
 * and height of the filled area. The 16-bit FILL PATTERN is a bit
 * pattern that the GCP uses to fill the target rectangle within
 * the destination buffer. The GCP begins filling each line of the
 * target rectangle .with the left-most bits of the FILL PATTERN.
 * If necessary, the GCP truncates the pattern at the right edge of
 * the target region.
 *
 * The SET DESTINATION BUFFER command specifies the area of memory
 * in which the BLT COPY WORD command can create filled rectangles.
 * The flags set with the SET TRANSFER MODE command determine the
 * type of transfer.
 *
 * Array Offset      Parameter
 * ----------------------------------------------------------------
 *            0      FILL PATTERN Word
 *            1      X Destination offset from X Origin in Pixels
 *            2      Y Destination offset from Y Origin in Pixels
 *            3      X size width in pixels
 *            4      Y size height in pixels
 *            5      Offset to the next parameter group, ONLY USE
 *                   IF SET PARAM BLOCK IS SET TO LINKED LIST!
 *                   If so, last entry in list should have 0xFFFF
 *
 */
void mindset_gfx_blt_copy_word(unsigned char blt_id, unsigned short len, short x, short y, unsigned short __far *params);

/**
 * Function: Draws a collection of points of the same color into the destination
 * buffer.
 * 
 * Description: The BLT POLYPOINT command draws a collection of points at locations
 * that the user specifies as a list of coordinates.
 *
 * The BLT POLYPOINT command includes a BLT ID number, a destination
 * buffer X-ORIGIN and Y-ORIGIN, a color index value, the number
 * of points to be drawn (N), and a pointer.
 *
 * The BLT ID number is a user-defined 8-bit value. The GCP
 * returns this ID number to the user's interrupt routine if this
 * BLT POLYPOINT command causes a clip or a collision.
 *
 * The 16-bit X-ORIGIN and Y-ORIGIN values are signed offsets (in
 * pixels) from the pixel occupying the upper left corner of the
 * destination buffer. The X-ORIGIN and Y-ORIGIN values are positive
 * relative to this pixel~ all point coordinates are relative
 * to X-ORIGIN and Y-ORIGIN.
 *
 * The color index is an index into the color palette that selects
 * the color for all points drawn in a single BLT POLYPOINT command.
 * (See the SET PALETTE command for more color information.)
 * 
 * The 16-bit coordinate set count N specifies the number of points
 * to be drawn. This value should not exceed 16 if the user
 * intends to use the GCP WAIT command to poll for collision and
 * clipping information. BLT POLYPOINT does nothing if N is O.
 *
 * The pointer in the BLT POLYPOINT command is the address of the
 * first byte of the first 4-byte coordinate set. Each coordinate
 * set specifies a signed 16-bit X-coordinate value and a signed
 * .16-bit Y-coordinate value. The X and Y coordinates are
 * described in pixels.
 *
 * Parameter:     Description:
 * -----------------------------------------------------------------
 * blt_id         The 8-bit BLT ID number that GCP returns if 
 *                collision or clip occurs.
 *
 * len            Number of points to be drawn.
 *
 * c              color index for these sets of points
 *
 * x              x-origin within destination buffer
 *
 * y              y-origin within destination buffer
 * 
 * params         far pointer to first 4-byte parameter.
 *
 */
void mindset_gfx_blt_polypoint(unsigned char blt_id, unsigned short len, unsigned char c, short x, short y, unsigned short __far *params);

/**
 * Function:
 * Draws a collection of straight lines of the same color into the
 * destination buffer.
 *
 * Description: The BLT POLYLINE command draws a collection of lines in paired
 * or chained format. The chained format uses the end of one line
 * segment as the beginning of the next line segment. The paired
 * format uses a pair of point coordinates to define an isolated
 * line segment. The list of user-defined point coordinates
 * resides in memory.
 * 
 * BLT POLYLINE draws horizontal and vertical line
 * faster than diagonal line segments. Horizontal
 * line segments require only one call to the GCP.
 * segments, however, require a calculation (using
 * algorithm) and a call to the GCP for each pixel
 * segment.
 *
 * The BLT POLYLINE command includes a BLT ID number, a destination
 * buffer X-ORIGIN and Y-ORIGIN, a color index value, a parameter
 * group count (N), a pointer to the first 4-byte parameter group,
 * and a chained/paired mode specification.
 *
 * The BLT ID number is a user-defined 8-bit value. The GCP
 * returns this ID number to the user's interrupt routine if this
 * BLT POLYLINE command causes a clip or a collision.
 *
 * The 16-bit X-ORIGIN and Y-ORIGIN values are Signed offsets (in
 * pixels) from the pixel occupying the upper left corner of the
 * destination buffer. The X-ORIGIN and Y-ORIGIN values are positive
 * relative to this pixel; all point coordinates are relative
 * to X-ORIGIN and Y-ORIGIN.
 *
 * The color index is an index into the color palette that selects
 * the color for all points drawn in a single BLT POLYLINE command.
 * (See the SET PALETTE command description for more color
 * information.)
 *
 * The 16-bit parameter group count N specifies the number of
 * parameter groups in the list. BLT POLYLINE draws a point if N
 * is 1 or if the endpoints of a segment are coincident.
 *
 * The BLT POLYLINE command produces N/2 line segments in paired
 * mode and N-1 line segments in chained mode. N should not specify
 * more than 16 line segments if the user intends to use the
 * GCP WAIT command to poll for collision and clipping information.
 *
 * The pointer parameter for the BLT POLYLINE command is the
 * address of the first byte of the first 4-byte parameter group.
 * Each parameter group specifies a 16-bit X-coordinate value and a
 * 16-bit Y-coordinate value. The X and Y coordinates are
 * described in signed pixels.
 *
 * The chained/paired mode specification determines the line drawing
 * format. In chained mode the first two parameter groups
 * specify the first line segment, the second and third parameter
 * groups specify the second line segment, and so on. In paired
 * mode the first two parameter groups specify the first line segment,
 * the third and fourth parameter groups specify the second
 * line segment, and so on.
 *
 * Parameters:
 * -------------------------------------------------------------------------
 * blt_id         The 8-bit BLT ID erturned by GCP upon collision or clip.
 *
 * len            Number of parameter groups in params
 *
 * c              color for this collection of lines
 * 
 * mode           chained or paired mode for params
 *
 * x              x origin within destination buffer
 *
 * y              y origin within destination buffer
 *
 * params         far pointer to parameters
 *
 * -------------------------------------------------------------------------
 * Format of params:
 *
 * Offset         Description
 * -------------------------------------------------------------------------
 * params[0]      X Coordinate (in pixels)
 * params[1]      Y Coordinate (in pixels)
 *
 */
void mindset_gfx_blt_polyline(unsigned char blt_id, unsigned short len, unsigned char c, unsigned char mode, short x, short y, unsigned short __far *params);

/**
 * Function: Defines the criteria for collision detection.
 *
 * Description: The SET COLLISION PATTERN command specifies a bit pattern that
 * indicates, when matched, that the preceding BLT operation caused
 * a collision.
 *
 * SET COLLISION PATTERN includes a pixel pattern and a don't-care
 * bit mask.
 *
 * The pattern parameter of this command defines the bit pattern
 * that indicates a collision when it matches the bit pattern of a
 * pixel in the destination buffer. The number of bits in the pattern
 * is equal to the number of bits in a single pixel in the
 * current display mode.
 *
 * The don't-care bit mask parameter includes a a bit for each bit
 * position in the pattern that the system should ignore when
 * checking for collisions. A value of a for all bits in the mask
 * causes the system to detect a collision after every BLT operation.
 * The number of bits in the mask is equal to the number of
 * bits in a single pixel in the current display mode.
 *
 * pattern     8 bit pattern for collision detection
 *
 * mask        8 bit don't care bit mask
 *
 */
void mindset_gfx_set_collision_pattern(unsigned char pattern, unsigned char mask);

/**
 * Get Collision Pattern
 *
 * Returns the current criteria for collision detection.
 * 
 * Description: The GET COLLISION PATTERN command returns the pattern last set
 * by the SET COLLISION PATTERN command. This bit pattern, when
 * matched, indicates that the preceding BLT operation caused a
 * collision.
 * 
 * GET COLLISION PATTERN includes a pixel pattern and a don't-care
 * bit mask.
 * 
 * The pattern parameter of this command defines the bit pattern
 * that indicates a collision. The collision bit pattern matches
 * the bit pattern of a pixel in the destination buffer. The number
 * of bits in the pattern is equal to the number of bits in a
 * single pixel in the current display mode.
 * 
 * The don't-care bit mask parameter includes a 0 bit for each bit
 * position in the pattern that the system should ignore when
 * checking for collisions. A value of 0 for all bits in the mask
 * causes the system to detect a collision after every BLT operation.
 * 
 * The number of bits in the mask is equal to the number of
 * bits in a single pixel in the current display mode.
 *
 * pattern      Current bit pattern for collision detection.
 *
 * mask         Current don't care bit mask.
 *
 */
void mindset_get_collision_pattern(unsigned char* pattern, unsigned char* mask);

/**
 * Function: Specifies the clipping rectangle for all BLT operations.
 *
 * Description: The SET CLIP RECTANGLE command defines the clipping rectangle.
 * The clipping rectangle specifies the region of the destination
 * buffer in which a BLT operation may display pixels. The system
 * clips all points specified in a BLT operation that exceed the
 * clipping rectangle.
 *
 * The ROM BIOS software performs clipping before calling the GCP.
 * The GCP then performs a BLT or draw to the destination buffer.
 * If the user does not specify a clipping rectangle, the default
 * clipping rectangle is the same as the boundaries of the destination
 * buffer.
 *
 * The user can disable clipping. !n this case, the user is
 * responsible for guaranteeing that the GCP does not write outside
 * the bounds of the destination buffer.
 *
 * The SET CLIP RECTANGLE command includes X-LEFT, X-RIGHT, Y-TOP,
 * and Y-BOTTOM parameters to define the boundaries of the clipping
 * rectangle. These boundaries are specified in pixels. The
 * boundaries are relative to location (0,0), the pixel at the
 * upper left corner of the destination buffer.

 * For example, to define a clipping rectangle that includes the
 * entire frame buffer in 320 x 200 mode, specify 0, 319, 0, 199 as
 * X-LEFT, X-RIGHT, Y-TOP, Y-BOTTOM parameter values, respectively.
 * If the user-defined boundaries of the clipping rectangle exceed
 * the size of the destination buffer, the system truncates the
 * clipping rectangle to match the boundaries of the destination
 * buffer.
 *
 * l    - Left boundary in pixels
 *
 * r    - Right boundary in pixels
 * 
 * t    - Top boundary in pixels
 *
 * b    - Bottom boundary in pixels
 *
 */
void mindset_gfx_set_clip_rectangle(unsigned short l, unsigned short r, unsigned short t, unsigned short b);

/**
 * Get Clip Rectangle
 * Function: Returns the current clipping rectangle boundaries.
 *
 * Description: The GET CLIP RECTANGLE command returns the current boundaries of
 * the clipping rectangle. The clipping rectangle specifies the
 * region of the destination buffer in which a BLT operation may
 * display pixels. The system clips all points specified in a BLT
 * operation that exceed the clipping rectangle.
 *
 * The GET CLIP RECTANGLE command returns the X-LEFT, X-RIGHT,
 * Y-TOP, and Y-BOTTOM parameters that define the boundaries of the
 * clipping rectangle. These boundaries are specified in pixels.
 * The boundaries are relative to location (0,0), the pixel at the
 * upper left corner of the destination buffer.
 */
void mindset_gfx_get_clip_rectangle(unsigned short* l, unsigned short* r, unsigned short* t, unsigned short* b);

/**
 * Set Collision/Clip/Done Detect
 *
 * Function: Enables and disables collision and clip detection and the GCPtask-
 * done interrupt. Also specifies the address of the
 * collision/clip/done interrupt service routine.
 *
 * Description: The SET COLLISION/CLIP/DONE DETECT command enables and disables
 * collision and clip detection and the GCP-task-done interrupt for
 * future BLT operations. This command also specifies the address
 * of the user-defined service routine for the interrupt that
 * occurs when the system detects a collision, clip, or GCP-taskdone
 * condition.
 *
 * Disabling collision/clip/done detection improves system performance.
 * The user should disable collision detection whenever
 * collisions are not possible or not important. The user should
 * also disable the GCP-task-done interrupt when not needed. Disabling
 * clipping, however, is highly discouraged. When clipping
 * is disabled, it is possible for the GCP to write data outside
 * the destination buffer, yielding unpredictable results (including
 * potential system crashes).
 *
 * The SET COLLISION/CLIP/DONE DETECT command includes two parameters:
 * DETECT-ENABLE, to enable and disable detection modes,
 * and ADDRESS, to point to a user-defined collision/clip/done
 * interrupt service routine.
 *
 * Three DETECT-ENABLE flags specify the enabled/disabled status of
 * collision detect, clip detect, and GCP-task-done interrupt
 * independently.
 *
 * The ADDRESS pointer serves two functions. If the value of
 * ADDRESS is zero, the system does not call a user-specified
 * interrupt service routine when it detects a collision, clip, or
 * GCP-task-done condition. If the value of ADDRESS is other than
 * zero and detection is enabled, the system interrupt handler
 * calls the service routine at ADDRESS when a collision, clip, or
 * GCP-task-done condition occurs.
 *
 * The system makes a collision interrupt call at the end of a BLT
 * operation that caused a collision. The system makes a clip
 * interrupt call when the operation of the current BLT command is
 * started. The system calls the interrupt routine for each parameter
 * group that causes a collision, clip, or GCP-task-done
 * condition.
 *
 * The system passes the following information to the user-defined
 * interrupt service routine:
 *
 * Parameter    Function
 * -------------------------------------------------------------------
 * ID (AL)      Returns the 8-bit BLT ID number that the user
 *              specified with the command that caused the
 *              collision or the clip.
 *
 * N (CX)       Returns the number of the parameter group that caused
 *              a collision, clip, or done condition to occur. 
 *              (for BLT polyline N refers to the line segments, for
 *              BLT polygon, N is always 1.)
 *
 * CLIP (AH)    Bit 3 returns 1 if a clip triggered the interrupt.
 *              Bit 4 returns 1 if a collision triggered the interrupt
 *              Bit 6 returns 1 if a gcp-task-done triggered the interrupt
 *
 * The system interrupt handler invokes the user-defined interrupt
 * service routine with a FAR CALL instruction. Therefore, this
 * routine must terminate with a FAR RET instruction instead of an
 * IRET instruction.
 * 
 * The user's main program must disable the interrupt vector before
 * terminating. Otherwise, a future collision or clip could cause
 * the system to jump to a non-existent routine.
 * 
 * As an alternative to using interrupts, the user can employ the
 * GCP WAIT command to poll for the collision/clip/done status
 * after each BLT or draw command.
 *
 * Parameters:
 * 
 * mode        bit 0   Enable clip detection.
 *             bit 1   Enable collision detection.
 *             bit 2   Enable gcp-task-done interrupt.
 *
 * p           Far pointer to desired interrupt service routine
 *
 */
void mindset_gfx_set_collision_clip_done_detect(unsigned char mode, void __far *p);

/**
 * Get Collision/Clip/Done/Detect
 *
 * Function: Returns the values last set with the SET COLLISION/CLIP/DONE
 * DETECT command.
 *
 * Description: The GET COLLISION/CLIP/DONE DETECT command returns the value of
 * the DETECT-ENABLE flags and the ADDRESS pointer to the userdefined
 * interrupt service routine.
 *
 * The DETECT-ENABLE flags are three single-bit flags that regulate
 * collision and clip detection and the GCP-task-done interrupt.
 * 
 * The ADDRESS pointer serves two functions. If the value of
 * ADDRESS is zero, the system does not call a user-specified
 * interrupt service routine when it detects a collision, clip, or
 * GCP-task-done condition. If the value of ADDRESS is other than
 * zero and detection is enabled, the system interrupt handler
 * calls the service routine at ADDRESS when a collision, clip, or
 * GCP-task-done condition occurs.
 *
 * mode     Bit 0  Enable clip detection
 *          Bit 1  Enable collision detection
 *          Bit 2  Enable gcp task-done interrupt
 *
 * p        Pointer to current ISR
 *
 */
void mindset_gfx_get_collision_clip_done_detect(unsigned char* mode, void __far *p);

/**
 * GCP Wait
 *
 * Function: Returns the collision/clip status as soon as the GCP is not
 * busy.
 * 
 * Description: The GCP WAIT command provides a method of obtaining the
 * collision/clip status without the use of a user-defined
 * collision/clip interrupt service routine. The system waits
 * until the GCP is idle before returning the collision/clip
 * status, enabling the user to synchronize program execution with
 * the GCP, if desired.
 * 
 * The GCP WAIT command returns a BLT ID number, a COLLISION STATUS
 * word, and a CLIP STATUS word.
 *
 * The BLT ID number is the ID number that the user supplies for
 * all BLT and draw operations. This number enables the user to
 * determine which BLT operation caused the collision or clip.
 * 
 * The COLLISION STATUS word returns the collision status for the
 * first 16 BLT operations within a single BLT command. Likewise,
 * the CLIP STATUS word returns the clip status for the first 16
 * BLT operations within a single BLT command.
 * 
 * Because the status words contain only 16 bits, it is recommended
 * (when using GCP WAIT) that BLT commands be restricted to 16 or
 * fewer operations (parameter groups). The contents of the status
 * words are unpredictable if the number of objects in a BLT operation
 * exceeds 16.
 * 
 * For both of the status words, the first BLT operation sets bit
 * 0, the second BLT operation sets bit 1, and so on. A bit value
 * of 1 indicates that a collision or clip occurred during the BLT
 * operation corresponding to that bit position. A bit value of 0
 * indicates that a collision or clip did not occur.
 */
void mindset_gfx_gcp_wait(unsigned char* blt_id, unsigned short* collision_status, unsigned short* clip_status);

/**
 * BLT Polygon
 *
 * Function: Draws a filled polygon into the destination buffer.
 *
 * Description: The BLT POLYGON command draws a filled polygon. A list of userdefined
 * point coordinates in memory specifies the "corners" of
 * the polygon. The BLT POLYGON command automatically completes
 * the polygon by connecting the last point to the first point.
 *
 * The BLT POLYGON filling algorithm fills the interior and the
 * boundary of the polygon. This algorithm can fill any polygon
 * whose boundary (ignoring horizontal lines) does not intersect
 * any horizontal line at more than two points. For example, the
 * algorithm can properly fill an upright hourglass-shaped polygon
 * but not an hourglass-shaped polygon lying on its side.
 *
 * The BLT POLYGON command includes a BLT ID number, a destination
 * buffer X-ORIGIN and Y-ORIGIN, two color index values, a parameter
 * group count (N), and a pointer to the first 4-byte parameter
 * group.
 *
 * The BLT ID number is a user-defined a-bit value. The GCP
 * returns this ID number to the user's interrupt routine if this
 * BLT POLYGON command causes a clip or a collision.
 *
 * The 16-bit X-ORIGIN and Y-ORIGIN values are signed offsets (in
 * pixels) from the pixel occupying the upper left corner of the
 * destination buffer. The X-ORIGIN and Y-ORIGIN values are positive
 * relative to this pixel; all point coordinates are relative
 * to X-ORIGIN and Y-ORIGIN.
 *
 * The BLT POLYGON command includes an even color index parameter
 * and an odd color index parameter. The terms even and odd refer
 * to the sum of the X- and Y-coordinate values for each pixel in
 * the polygon. For example, a pixel at (5,5) uses the even color
 * index because 5 + 5 = 10, an even value.
 *
 * This technique is called dithering; it enables the user to combine
 * two colors to create a third. Dithering is primarily for
 * use with a monitor; it has unpredictable effects when used with
 * a television. (See the SET PALETTE command description for more
 * color information.)
 *
 * The 16-bit parameter group count N specifies the number of
 * parameter groups in the list. BLT POLYGON draws a pOint if N is
 * 1 or if all point coordinates for the polygon are coincident.
 * BLT POLYGON draws a line if N is 2 or if there are only two distinct
 * point coordinates.
 *
 * The pOinter parameter for the BLT POLYGON command is the address
 * of the first byte of the first 4-byte parameter group. Each
 * parameter group specifies a 16-bit X-coordinate value and a
 * 16-bit Y-coordinate value. The X and Y coordinates are
 * described in signed pixels.
 *
 * The algorithm for drawing polygons may draw some points more
 * than once. This may cause undesirable effects when combined
 * with exclusive-OR specifications.
 *
 * Each 4-byte parameter contains the following:
 * ---------------------------------------------
 * params[0]    X coordinate (in pixels)
 * params[1]    Y coordinate (in pixels)
 *
 */
void mindset_gfx_blt_polygon(unsigned char blt_id, unsigned short len, unsigned char ce, unsigned char co, short x, short y, unsigned short __far *params);

/**
 * BLT Filled Elipses
 *
 * Function: Draws one or more filled ellipses or ellipse sectors.
 * Description: The BLT FILLED ELLIPSES command draws a series of filled ellipses
 * or elliptical sectors. The ellipses (or the ellipses on
 * which the elliptical sectors are based) can be oriented either
 * horizontally or vertically within the destination buffer (see
 * Figure 4-4).
 *
 * (figure 4-4 omitted, please see Software Developers guide)
 *
 * The BLT FILLED ELLIPSES command includes a BLT ID number, a destination
 * buffer X-ORIGIN and Y-ORIGIN, two color index values, a
 * parameter group count (N), a filled/hollow/segment mode specification,
 * and a pointer to the first 16-byte parameter group.
 *
 * The BLT ID number is a user-defined a-bit value. The GCP
 * returns this ID number to the user's interrupt routine if this
 * BLT FILLED ELLIPSES command causes a clip or a collision.
 *
 * The 16-bit X-ORIGIN and Y-ORIGIN values are offsets (in pixels)
 * from the pixel occupying the upper left corner of the destination
 * buffer. The X-ORIGIN and Y-ORIGIN values are positive
 * relative to this pixel, and all elliptical coordinates are relative
 * to X-ORIGIN and Y-ORIGIN.
 *
 * As with the BLT POLYGON command, the BLT FILLED ELLIPSES command
 * includes an even color index parameter and an odd color index
 * parameter to permit dithering. The terms even and odd refer to
 * the sum of the X- and Y-coordinate values for each pixel in the
 * ellipse. Dithering is primarily for use with a monitor; it has
 * unpredictable effects when used with a television. (See the SET
 * PALETTE command description for more color information.)
 *
 * The 16-bit parameter group count N specifies the number of
 * parameter groups in the list. The value of N should not exceed
 * 16 ellipses if the user intends to use the GCP WAIT command to
 * poll for collision and clipping information.
 *
 * The pointer parameter for the BLT FILLED ELLIPSES command is the
 * address of the first byte of the first 16-byte parameter group.
 * Each parameter group includes an X-CENTER, a Y-CENTER, an
 * X-RADIUS, a Y-RADIUS, an X-BEGIN, a Y-BEGIN, an X-END, and a
 * Y-END. All X and Y values are in signed pixels. X-CENTER and
 * Y-CENTER are relative to X-ORIGIN and Y-ORIGIN.
 *
 * The X-CENTER and Y-CENTER parameters specify the center of the
 * ellipse. The X-RADIUS and Y-RADIUS parameters specify the magnitude
 * of the horizontal and vertical dimensions of the ellipse,
 * respectively. The GCP converts negative radius values to positive
 * values. BLT FILLED ELLIPSES draws a point if both the
 * X-RADIUS and Y-RADIUS values are O. BLT FILLED ELLIPSES draws a
 * line if either the X-RADIUS or Y-RADIUS value is O.
 *
 * The X-BEGIN,. Y-BEGIN, X-END, and Y-END parameters specify two
 * points through which the system draws radial vectors. The system
 * draws a "begin-arc" vector from (X-CENTER, Y-CENTER) through
 * (X-BEGIN, Y-BEGIN) and an "end-arc" vector from (X-CENTER,
 * Y-CENTER) through (X-CENTER + X-BEGIN, Y-CENTER + Y-BEGIN). The
 * magnitudes of these vectors are not important.
 *
 * The begin-arc and end-arc vectors determine whether the BLT
 * FILLED ELLIPSES routine uses an intermediate circle to draw an
 * ellipse or not. If the circle is used, the routine adjusts the
 * points of the circle so that they fallon the ellipse. Thus,
 * the begin-arc and end-arc vectors determine the bounds of the
 * ellipse indirectly through the definition of an intermediate
 * circle.
 *
 * The BLT FILLED ELLIPSES command defines an arc sector as the
 * "pie-shaped" segment created by sweeping visually clockwise from
 * the begin-arc vector to the end-arc vector. (Mathematically,
 * the sweep is counterclockwise in a left-handed coordinate
 * system.)
 * 
 * BLT FILLED ELLIPSES draws the entire ellipse if the begin-arc
 * vector and the end-arc vector are the same. BLT FILLED ELLIPSES
 * also draws the entire ellipse if X-BEGIN and Y-BEGIN are 0 or if
 * X-END and Y-END are O. The results are undefined if the begin
 * and end-arc vectors point in the same direction but have unequal
 * lengths.
 *
 * Due to the "nonsquare" aspect ratio of the screen, equating the
 * X-RADIUS and the Y-RADIUS of the ellipse does not produce a
 * circle. For example, to create a circle in 320 x 200 mode, use
 * a Y-RADIUS to X-RADIUS ratio of 5 to 6 (4/3 x Y/X = 4/3 x
 * 200/320 = 5/6).
 * 
 * The algorithm for drawing ellipses may draw some points more
 * than once. This may cause undesirable effects when combined
 * with exclusive-OR specifications.
 *
 * Each 16-byte parameter group contains the following parameters:
 *
 * offset        description
 * ---------------------------------------------------------------
 * params[0]     X-CENTER (in pixels)
 * params[1]     Y-CENTER (in pixels)
 * params[2]     X-RADIUS (in pixels)
 * params[3]     Y-RADIUS (in pixels)
 * params[4]     X-BEGIN (in pixels) (for arc)
 * params[5]     Y-BEGIN (in pixels) (for arc)
 * params[6]     X-END (in pixels)(for arc)
 * params[7]     Y-END (in pixels)(for arC)
 * params[8]     Offset to next parameter group. This must be in-
 *               cluded if mindset_gfx_set_param_block_mode() is
 *               used to specify the linked list mode. The offset
 *               must NOT be included when mindset_gfx_set_param_block_mode()
 *               is used to specify the contiguous parameter block
 *               representation mode. An offset value of 0xFFFF 
 *               indicates the end of the list. This terminates on
 *               the first occurance of len BLTs or an 0xFFFF value here.
 *
 */
void mindset_gfx_blt_filled_elipses(unsigned char blt_id, unsigned short len, unsigned char ce, unsigned char co, short x, short y, unsigned short __far *params);

/**
 * BLT Hollow Elipses
 * Function: Draws one or more hollow ellipses or elliptical arcs.
 *
 * Description: The BLT HOLLOW ELLIPSES command draws a series of hollow ellipses
 * or elliptical arcs. The ellipses (or the ellipses on which
 * the arcs are based) can be oriented either horizontally or vertically
 * within the destination buffer (see Figure 4-4 in the BLT
 * FILLED ELLIPSES command description).
 * The BLT HOLLOW ELLIPSES command includes the same parameters as
 * the BLT FILLED ELLIPSES command with the exception that all
 * pixels are drawn with the color index in (DH)--(DL) is ignored.
 *
 * Each 16-byte parameter group contains the following parameters:
 *
 * offset        description
 * ---------------------------------------------------------------
 * params[0]     X-CENTER (in pixels)
 * params[1]     Y-CENTER (in pixels)
 * params[2]     X-RADIUS (in pixels)
 * params[3]     Y-RADIUS (in pixels)
 * params[4]     X-BEGIN (in pixels) (for arc)
 * params[5]     Y-BEGIN (in pixels) (for arc)
 * params[6]     X-END (in pixels)(for arc)
 * params[7]     Y-END (in pixels)(for arC)
 * params[8]     Offset to next parameter group. This must be in-
 *               cluded if mindset_gfx_set_param_block_mode() is
 *               used to specify the linked list mode. The offset
 *               must NOT be included when mindset_gfx_set_param_block_mode()
 *               is used to specify the contiguous parameter block
 *               representation mode. An offset value of 0xFFFF 
 *               indicates the end of the list. This terminates on
 *               the first occurance of len BLTs or an 0xFFFF value here.
 */
void mindset_gfx_blt_hollow_elipses(unsigned char blt_id, unsigned short len, unsigned char c, short x, short y, unsigned short __far *params);

/**
 * Save GCP
 * Function:
 * Saves the current state of the GCP in a user-specified area of
 * memory.
 *
 * Description: The SAVE GCP command enables the user to save the state of the
 * GCP before the GCP is used by an interrupt service routine.
 * The user should employ the SAVE GCP command when using the GCP
 * in normal and interrupt routines simultaneously. The userspecified
 * data area should be on the stack to ensure that all
 * routines can return normally.
 *
 * The SAVE GCP command includes one output parameter and two input
 * parameters. The output parameter returns the current size of
 * the BLT data.
 *
 * The first input parameter is a flag bit. If this flag bit is 1,
 * the system saves the data and returns the size of the data. If
 * this flag bit is 0, the system does not save the data, but still
 * returns the size of the data.
 *
 * The second input parameter is a user-specified pointer to the
 * area in which the system saves the GCP data. This area is normally
 * on the stack.
 */
unsigned short mindset_gfx_save_gcp(unsigned char save, unsigned char __far* data);

/**
 * Restore GCP
 * Function: Restores the data previously saved by the SAVE GCP command.
 * Description: The RESTORE GCP command enables the user to restore the GCP to
 * the state it was in before the GCP operations were interrupted.
 *
 * The only parameter for the RESTORE GCP command is a pointer to
 * the user-specified data area used in a previous SAVE GCP
 * command.
 */
void mindset_gfx_restore_gcp(unsigned char __far* data);

/**
 * Fill Dest Buffer
 * Function: Fills the entire destination buffer with specified data.
 *
 * Description: The FILL DEST BUFFER command fills the destination buffer wordby-
 * word with the data in pattern. This command provides a simple
 * method of quickly clearing the screen.
 *
 * The parameters set by the SET TRANSFER MODE and SET CLIP RECTANGLE
 * commands do not affect the operation of the FILL DEST
 * BUFFER command. This command always fills the entire destination
 * buffer with the exact data in pattern.
 *
 */
void mindset_gfx_fill_dest_buffer(unsigned short pattern);

/**
 * Set Font Pointer
 *
 * Function: Sets the font information pointer used by the BLT STRING command.
 *
 * Description: The Set Font Pointer command specifies a pointer 
 * to a data area that determines font characteristics for the BLT STRING
 * command. The data area includes the following font data:
 *
 * Parameter         Description
 * ---------------------------------------------------------------------------
 * Font Type         One byte wide. A value of 0 indicates a fixed 
 *                   width font. A value of 1 indicates a proportional font.
 *
 * Excess White      One byte wide. Specifies excess inter-character width
 *                   in pixels. This parameter is unused if proportional font
 *                   is specified. Signed value -128 to +127
 *
 * Nominal Width     One word wide. Specifies nominal character width in pixels.
 *                   This parameter is unused if proportional font is set.
 *
 * Nominal Height    One word wide. Specifies nominal character height in pixels.
 *                   which is also the raster height in pixels.
 *
 * Bitmap Width      One word wide. Specifies the bitmap raster width in bytes;
 *                   the raster width must be an even number.
 *
 * Bitmap address    One doubleword wide. Specifies the bitmap address, which must
 *                   be word aligned.
 *
 * First ASCII       Specifies the ASCII value of the first char in bitmap.
 *
 * Last ASCII        Specifies the ASCII value of the last char in bitmap.
 *
 * The rema~n~ng parameters are required only if the Font Type
 * selected is proportional font. These parameters, which constitute
 * a 4-byte block, are repeated for each of the characters
 * defined in the bitmap. The number of characters in the bitmap
 * is:
 *       Last ASCII - First ASCII + 1
 *
 * Bitmap Offset     One doubleword wide. Specifies the offset in pixels of the
 *                   character into the bitmap. Use a value of -1 if the character
 *                   is not in the bitmap.
 *
 * Char Wid          One Byte Wide. Specifies the character width in pixels, from
 *                   -128 to +127
 *
 * Char Height       One byte wide. Specifies the character height in pixels. 
 *                   Char width and Char Ht are used to move to the next 
 *                   character position if Bitmap Offset is -1.
 *
 */
void mindset_gfx_set_font_pointer(unsigned char __far* fontp);

/**
 * Get Font Pointer
 *
 * Function: Returns a pointer to the current font information.
 *
 * Description: The GET FONT POINTER command returns the pointer that was set
 * using the SET FONT POINTER command. See SET FONT POINTER for a
 * description of the font pointer and font data information.
 */
void mindset_gfx_get_font_pointer(unsigned char __far* fontp);

/**
 * BLT String
 *
 * Function: Transfers a character string to the destination buffer.
 *
 * Description: The BLT STRING command transfers a character string into the
 * destination buffer as directed by the input parameters.
 *
 * For each string, the upper left (DH=0,2), upper right (DH=1),
 * and lower left (DH=3) corner of the first character drawn is at
 * location (X-DESTINATION + X-ORIGIN, Y-DESTINATION + Y-ORIGIN).
 * Succeeding characters will be drawn at a location depending on
 * the value of DH.
 *
 * The SET FONT POINTER command must be called before using BLT
 * STRING.
 *
 * blt_id     The BLT identification number.
 * 
 * len        The number of character strings to print
 *
 * c_offset   the number of characters to ignore at beginning of
 *            each string.
 *
 * direction  Direction to draw each string on screen:
 *            __DH____DIRECTION_______________________
 *               0    Left to right
 *               1    Right to Left
 *               2    Top to bottom
 *               3    Bottom to top
 *
 * c          The color to print with.
 *
 * x          X-ORIGIN in pixels
 *
 * y          Y-ORIGIN in pixels
 *
 * params     Pointer to a list of string descriptor blocks
 *            each 10 or 12 bytes long. Each descriptor block
 *            contains the following parameters:
 * __________________________________________________________
 * params[0]  X Destination in Pixels relative to origin
 * params[1]  Y Destination in Pixels relative to origin
 * params[2]  String length
 * params[3]  Address offset of first character
 * params[4]  Address segment of first character
 * params[5]  Optional: Address offset of next parmaeter field.
 *            This offset must be included if SET PARAM BLOCK
 *            MODE is used to specify the linked list mode.
 *            This offset must NOT be used when SET PARAM BLOCK
 *            MODE is used to specify the contiguous parameter
 *            block representation mode. An offset value of 
 *            0xFFFF indicates the end of the list. BLT String
 *            terminaltes on the first occurance of len BLTs, or 
 *            or a value of 0xFFFF in this field.
 *
 */
void mindset_gfx_blt_string(unsigned char blt_id, unsigned short len, unsigned char c_offset, unsigned char direction, unsigned char c, short x, short y, unsigned short __far* params);

/**
 * Set Param Block Mode
 *
 * Function:
 * Specifies contiguous or linked list representation for parameter
 * blocks used by BLT COPY, BLT COPY WORD, BLT STRING, and BLT
 * ELLIPSES.
 *
 * Description: The SET PARAM BLOCK MODE command enables the user to specify
 * contiguous or linked list representation for the parameter
 * blocks required by BLT COPY, BLT COpy WORD, BLT STRING, and BLT
 * ELLIPSES. The parameter block mode is reset to contiguous
 * representation whenever SET SCREEN MODE is called.
 *
 * mode      0 to specify contiguous parameter blocks. 1 for linked list
 *
 */
void mindset_gfx_set_param_block_mode(unsigned char mode);

/**
 * Get Param Block Mode
 *
 * Function: Returns the current parameter plock representation mode.
 *
 * Description: The GET PARAM BLOCK MODE command returns the ~urrent parameter
 * block representation mode--contiguous or linked list. The SET
 * PARAM BLOCK MODE specifies which mode is in effect, except that
 * the parameter block mode is reset to contiguous whenever SET
 * SCREEN MODE is called.
 */
unsigned char mindset_gfx_get_param_block_mode(void);

/**
 * Function: Returns the current GCP status word.
 *
 * Description: The GET GCP STATUS command returns status bits that indicate
 * whether the GCP is idle, whether vertical flyback (late VBLANK)
 * is occurring, and whether a collision was detected during the
 * last GCP task.
 * 
 * Bit 0 - GCP is idle
 * Bit 1 - SYstem flag
 * Bit 2 - Collision was detected
 */
unsigned char mindset_gfx_get_gcp_status(void);

/**
 * Get Char Bitmap Address
 *
 * Function: Returns the addresses of the two system character bitmaps.
 *
 * Description: The GET CHAR BITMAP ADDR command returns the addresses of the
 * two system character bitmaps. One address points to the bitmap
 * for ASCII values 0 through 127 and the other address to ASCII
 * values 128 through 255.
 *
 * char_seg     The address segment for both bitmaps.
 * char_off_lo  The address offset for ASCII values 0 to 127
 * char_off_hi  The address offset for ASCII values 128 to 255.
 *
 */
void mindset_get_char_bitmap_addr(unsigned short* char_seg, unsigned short* char_off_lo, unsigned short* char_off_hi);

/**
 * Get BLT Memory Bounds
 *
 * Function: Returns the bounds of memory available for block transfers
 * (BLTs).
 *
 * Description: The GET MEMORY BOUNDS command returns the bounds of the memory
 * available for block transfers CBLTs). The bounds returned consist
 * of the beginning and ending addresses of memory available
 * for block transfers. The addresses returned may not reflect the
 * actual memory configuration of your system; GET MEMORY BOUNDS
 * may return an address for memory that is not actually installed
 * in your system.
 */
void mindset_get_blt_memory_bounds(unsigned char* all, unsigned short* first_segment, unsigned short* last_segment);



#endif /* LIBMINDSET_GFX_H */
