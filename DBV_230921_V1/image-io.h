#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAXXDIM 256
#define MAXYDIM 256

extern int readImage_ppm(unsigned char img[MAXXDIM][MAXYDIM]);
extern int writeImage_ppm(unsigned char img[MAXXDIM][MAXYDIM], int xdim, int ydim);
extern void viewImage_ppm(void);