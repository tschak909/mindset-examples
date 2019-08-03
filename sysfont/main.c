/** 
 * Dump system font to file
 */

#include <stdio.h>
#include <i86.h>
#include <libmindset_gfx.h>

void font_dump(const char* fn, unsigned short __far* p)
{
  FILE *fp;

  fp=fopen(fn,"wb");
  fwrite(p,sizeof(unsigned short),512,fp);
  fclose(fp);
}

int main(int argc, char* argv[])
{
  union REGS regs;
  struct SREGS sregs;

  segread(&sregs);
  
  regs.h.ah=0x25;
  int86x(0xEF,&regs,&regs,&sregs);

  printf(" Seg: 0x%04x\n",sregs.es);
  printf("Off1: 0x%04x\n",regs.w.si);
  printf("Off2: 0x%04x\n",regs.w.di);

  printf("\n\n");

  printf("Writing LO...");
  font_dump("LO",MK_FP(sregs.es,regs.w.si));
  printf("done\n");

  printf("Writing HI...");
  font_dump("HI",MK_FP(sregs.es,regs.w.di));
  printf("done\n");

  printf("bye.\n\n");
  
  return 0;
}
