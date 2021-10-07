#pragma once

#pragma once
#include <stdio.h>

extern int menu();
extern void dilate(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);
extern void erode(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]);
//Über diese Headerdatei werden die Funktionen ins Hauptprogramm integriert