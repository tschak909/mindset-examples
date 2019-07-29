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

#endif /* LIBMINDSET_GFX_H */
