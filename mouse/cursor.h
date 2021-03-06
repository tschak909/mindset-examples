/**
 * mouse cursor data
 *
 * for a 4bpp screen (16 color)
 *
 */

#ifndef CURS_H
#define CURS_H

#define CURSOR_W 12
#define CURSOR_H 19

const unsigned char cursor_0[]=
  {
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00    
  };

const unsigned char cursor[]=
  {
    0x20,0x00,0x00,0x00,0x00,0x00,
    0x22,0x00,0x00,0x00,0x00,0x00,
    0x21,0x20,0x00,0x00,0x00,0x00,
    0x21,0x12,0x00,0x00,0x00,0x00,
    0x21,0x11,0x20,0x00,0x00,0x00,
    0x21,0x11,0x12,0x00,0x00,0x00,
    0x21,0x11,0x11,0x20,0x00,0x00,
    0x21,0x11,0x11,0x12,0x00,0x00,
    0x21,0x11,0x11,0x11,0x20,0x00,
    0x21,0x11,0x11,0x11,0x12,0x00,
    0x21,0x11,0x11,0x11,0x11,0x20,
    0x21,0x11,0x11,0x11,0x11,0x12,
    0x21,0x11,0x11,0x12,0x22,0x22,
    0x21,0x11,0x21,0x12,0x00,0x00,
    0x21,0x12,0x02,0x11,0x20,0x00,
    0x21,0x20,0x02,0x11,0x20,0x00,
    0x22,0x00,0x00,0x21,0x12,0x00,
    0x00,0x00,0x00,0x21,0x12,0x00,
    0x00,0x00,0x00,0x02,0x20,0x00
  };

#endif /* CURS_H */
