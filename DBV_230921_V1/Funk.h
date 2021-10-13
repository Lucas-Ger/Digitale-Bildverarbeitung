#pragma once
#include <stdio.h>

//Über diese Headerdatei werden die Funktionen ins Hauptprogramm integriert
extern int menu();

extern void dilate(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);

extern void erode(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);

extern void pixelcount(unsigned char in[MAXXDIM][MAXYDIM]);

extern int pixelcount_return(unsigned char in[MAXXDIM][MAXYDIM]);

extern void oeffnen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);

extern void schliessen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);

extern void grassfire(unsigned char in[MAXXDIM][MAXYDIM]);
