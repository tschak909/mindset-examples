/**
 * fbdump
 *
 * draws a small 16x16 box at 0,0, and dumps framebuffer. Used to determine framebuffer format.
 */
#include <i86.h>
#include <libmindset_gfx.h>
#include <stdio.h>

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

int main(int argc, char* argv[])
{
  CopyWordParams cw;
  FILE* fp;
  unsigned short __far* b1;
  union REGS regs;
  
  mindset_gfx_set_mode(2);
  mindset_gfx_set_palette(0,16,0,&palette);

  cw.pattern=0x1111;
  cw.x=0;
  cw.y=0;
  cw.width=16;
  cw.height=16;

  mindset_gfx_blt_copy_word(0,1,0,0,&cw);

  regs.h.ah=0x0e;
  int86(0xEF,&regs,&regs);

  b1=MK_FP(regs.w.bx,0);
  
  fp=fopen("BUF","wb");
  fwrite(b1,sizeof(unsigned short),16384,fp);  
  fclose(fp);
  
  return 0;
}
