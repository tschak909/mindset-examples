/** 
 * Blitter objects for scene
 *
 */
#ifndef BOBS_H
#define BOBS_H

const unsigned char blank[]=
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

const unsigned char pacman_0[]=
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x11, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x11, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

const unsigned char pacman_1[]=
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x01, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00, 0x00,
    0x01, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

const unsigned char pacman_2[]=
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
    0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };

const unsigned char __far* pacman_frames[5]={pacman_0,pacman_1,pacman_2,pacman_1,pacman_0};

#endif /* BOBS_H */
