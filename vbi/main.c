/**
 * VBlank Interrupt Service Routine
 *
 * Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>
 *
 */

#include <libmindset_gfx.h>
#include <i86.h>

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

unsigned short counter;

/**
 * Because the MINDSET BIOS calls the display interrupt
 * handler as a FAR CALL, it must return with a FAR RET.
 * Thus the _interrupt macro is insufficient for our
 * purposes and we just need to take care of the function
 * return, ourselves...
 *
 * (is there a proper macro to use for this?)
 */
void vblank_handler(void)
{
  _asm("pushad")
  
  palette[0]=counter++;

  _asm("popad; leave; retf");
}

int main(int argc, char* argv[])
{
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);
  mindset_gfx_set_display_int_address(&vblank_handler);

  while (!kbhit())
    {
      mindset_gfx_set_palette(0,16,0,&palette);
    }

  mindset_gfx_set_display_int_address(0);
  
  return 0;
}
