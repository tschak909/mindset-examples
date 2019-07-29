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

#endif /* LIBMINDSET_GFX_H */
