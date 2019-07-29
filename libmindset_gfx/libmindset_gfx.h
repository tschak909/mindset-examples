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

#endif /* LIBMINDSET_GFX_H */
