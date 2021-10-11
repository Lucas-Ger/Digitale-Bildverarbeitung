#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "image-io.h"

int menu() //Menu-Funktion, gibt Möglichkeiten im Programm auf den Bildschirm aus
{
	int abfrage;
	printf("\nMenu: \nFolgendes kann getan werden : \n-Bild einlesen 1\n-Bild speichern 2\n-Bild anzeigen 3\n-Dilate 4\n-Erode 5\n-Zaehlen der Pixel die nicht schwarz sind 6\n-Oeffnen 7\n-Schliessen 8\n-GRASSFIRE 9\n-Programm beenden 0\nIhre Eingabe:");
	scanf("%i", &abfrage);		//wartet auf die Eingabe einer Zahl
	printf("\n");
	return(abfrage);		//gibt die eingegebene Zahl an die Main-Funktion zurück
}


void dilate(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}
	for (x = 1; x < MAXXDIM-1; x++) {
		for (y = 1; y < MAXYDIM-1; y++) {
			if (in[x][y] == 255) {
				out[x][y] = 255;
				out[x-1][y] = 255;
				out[x+1][y] = 255;
				out[x][y-1] = 255;
				out[x][y+1] = 255;
			}
		}
	}
}

void erode(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}
	for (x = 1; x < MAXXDIM - 1; x++) {
		for (y = 1; y < MAXYDIM - 1; y++) {
			if (in[x][y] == 255) {
				if (in[x - 1][y] == 255 && in[x + 1][y] == 255 && in[x][y - 1] == 255 && in[x][y + 1] == 255) {
					out[x][y] = 255;
				}
			}
		}
	}
}

void pixelcount(unsigned char in[MAXXDIM][MAXYDIM])
{
	int counter = 0;
	int x, y;

	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			if (in[x][y] != 0)
			{
				counter++;
			}
		}
	}

	printf("\nIm gewaehlten Bild sind %i Pixel nicht schwarz\n", counter);
}

void oeffnen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{
	int abfrage;
	int i;
	unsigned char zwischen[MAXXDIM][MAXYDIM];
	
	printf("\nWie oft soll das Bild geoeffnet werden?\nIhre Eingabe:");
	scanf("%i", &abfrage);		//wartet auf die Eingabe einer Zahl
	printf("\n");

	if (abfrage == 0)
	{
	}
	else if (abfrage == 1)
	{
		erode(in, zwischen);
		dilate(zwischen, out);
	}
	else if (abfrage != 1)
	{
		erode(in, zwischen);
		for (i = 1; i < abfrage; i++)
		{
			erode(zwischen, zwischen);
		}
		for (i = 1; i < abfrage; i++)
		{
			dilate(zwischen, zwischen);
		}
		dilate(zwischen, out);
	}
}

void schliessen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{
	int abfrage;
	int i;
	unsigned char zwischen[MAXXDIM][MAXYDIM];

	printf("\nWie oft soll das Bild geschlossen werden?\nIhre Eingabe:");
	scanf("%i", &abfrage);		//wartet auf die Eingabe einer Zahl
	printf("\n");

	if (abfrage == 0)
	{
	}
	else if (abfrage == 1)
	{
		dilate(in, zwischen);
		erode(zwischen, out);
	}
	else if (abfrage != 1)
	{

		for (i = 0; i < abfrage; i++)
		{
			dilate(in, out);
			in = out;
			erode(in, out);
			in = out;
		}

	}
}