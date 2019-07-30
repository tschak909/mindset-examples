/** 
 * Color bars demo for Mindset
 *
 * Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 *
 * This program uses mindset_gfx_blit_copy_word() to quickly draw 16 color bars
 * using the RGBI color palette, which is approximated on the composite port.
 *
 * all 16 bars are defined at once, and are sent to the blitter as a single
 * BIOS trap. Notice it draws instantly.
 */

#include <libmindset_gfx.h>

// see the comments on mindset_gfx_set_palette() for
// information on how the palette words are defined.

unsigned short palette[16]={
  0x0000, // Black
  0x10C0, // Dark Blue
  0x2018, // Dark Green
  0x30D8, // Dark Cyan
  0x4003, // Dark Red
  0x5063, // Dark Magenta
  0x601B, // Dark Yellow (brown?)
  0x70DB, // Dark Grey
  0x8049, // Light Black
  0x91C0, // Light Blue
  0xA038, // Light Green
  0xB1F8, // Light Cyan
  0xC007, // Light Red
  0xD1C7, // Light Magenta
  0xE03F, // Light Yellow
  0xF1FF  // White
};

// word 1 - four pixels of a given color.
// word 2 - X origin position in pixels
// word 3 - Y origin position in pixels
// Word 4 - width in pixels
// Word 5 - height in pixels

unsigned short bars[]={
  0x0000,0x0000,0x0000,0x0028,0x0064,
  0x1111,0x0028,0x0000,0x0028,0x0064,
  0x2222,0x0050,0x0000,0x0028,0x0064,
  0x3333,0x0078,0x0000,0x0028,0x0064,
  0x4444,0x00A0,0x0000,0x0028,0x0064,
  0x5555,0x00C8,0x0000,0x0028,0x0064,
  0x6666,0x00F0,0x0000,0x0028,0x0064,
  0x7777,0x0118,0x0000,0x0028,0x0064,
  0x8888,0x0000,0x0064,0x0028,0x0064,
  0x9999,0x0028,0x0064,0x0028,0x0064,
  0xAAAA,0x0050,0x0064,0x0028,0x0064,
  0xBBBB,0x0078,0x0064,0x0028,0x0064,
  0xCCCC,0x00A0,0x0064,0x0028,0x0064,
  0xDDDD,0x00C8,0x0064,0x0028,0x0064,
  0xEEEE,0x00F0,0x0064,0x0028,0x0064,
  0xFFFF,0x0118,0x0064,0x0028,0x0064
};

/**
 * Main entrypoint 
 */
int main(int argc, char* argv[])
{
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  mindset_gfx_blt_copy_word(0,16,0,0,&bars);
  
  for (;;) {}
  
  return 0;
}
