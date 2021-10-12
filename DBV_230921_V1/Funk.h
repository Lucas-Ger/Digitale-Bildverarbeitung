#pragma once

#pragma once
#include <stdio.h>

extern int menu();
extern void dilate(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);
extern void erode(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);
extern void pixelcount(unsigned char in[MAXXDIM][MAXYDIM]);
extern void oeffnen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);
extern void schliessen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);
extern void grassfire2(unsigned char in[MAXXDIM][MAXYDIM]);
//Über diese Headerdatei werden die Funktionen ins Hauptprogramm integriert