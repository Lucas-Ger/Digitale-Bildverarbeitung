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

int pixelcount_return(unsigned char in[MAXXDIM][MAXYDIM])
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

	return counter;
}

void oeffnen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{
	int abfrage;
	int i;
	unsigned char zwischen1 [MAXXDIM][MAXYDIM];
	unsigned char zwischen2 [MAXXDIM][MAXYDIM];
	
	printf("\nWie oft soll das Bild geoeffnet werden?\nIhre Eingabe:");
	scanf("%i", &abfrage);		//wartet auf die Eingabe einer Zahl
	printf("\n");

	if (abfrage == 0)
	{
	}
	else if (abfrage == 1)
	{
		erode(in, zwischen1);
		dilate(zwischen1, out);
	}
	else if (abfrage != 1)
	{
		erode(in, zwischen1);
		for (i = 1; i < abfrage; i++)
		{
			erode(zwischen1, zwischen2);
			for (int x = 0; x < MAXXDIM; x++) {
				for (int y = 0; y < MAXYDIM; y++) {
					zwischen1[x][y] = zwischen2[x][y];
				}
			}
		}
		for (i = 1; i < abfrage; i++)
		{
			dilate(zwischen1, zwischen2);
			for (int x = 0; x < MAXXDIM; x++) {
				for (int y = 0; y < MAXYDIM; y++) {
					zwischen1[x][y] = zwischen2[x][y];
				}
			}
		}
		dilate(zwischen1, out);
	}
}

void schliessen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{
	int abfrage;
	int i;
	unsigned char zwischen1[MAXXDIM][MAXYDIM];
	unsigned char zwischen2[MAXXDIM][MAXYDIM];

	printf("\nWie oft soll das Bild geschlossen werden?\nIhre Eingabe:");
	scanf("%i", &abfrage);		//wartet auf die Eingabe einer Zahl
	printf("\n");

	if (abfrage == 0)
	{
	}
	else if (abfrage == 1)
	{
		dilate(in, zwischen1);
		erode(zwischen1, out);
	}
	else if (abfrage != 1)
	{
		dilate(in, zwischen1);
		for (i = 1; i < abfrage; i++)
		{
			dilate(zwischen1, zwischen2);
			for (int x = 0; x < MAXXDIM; x++) {
				for (int y = 0; y < MAXYDIM; y++) {
					zwischen1[x][y] = zwischen2[x][y];
				}
			}
		}
		for (i = 1; i < abfrage; i++)
		{
			erode(zwischen1, zwischen2);
			for (int x = 0; x < MAXXDIM; x++) {
				for (int y = 0; y < MAXYDIM; y++) {
					zwischen1[x][y] = zwischen2[x][y];
				}
			}
		}
		erode(zwischen1, out);
	}
}



void grassfire(unsigned char in[MAXXDIM][MAXYDIM]) {

	bool check = false;
	int objektzahl = 0;
	int n1 = 0, n2 = 0;
	unsigned char out[MAXXDIM][MAXYDIM];
	unsigned char temp[MAXXDIM][MAXYDIM];
	int x, y;
	bool zündpunktfund = false;
	bool zeile = false;
	int xfound;

	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
			temp[x][y] = 0;
		}
	}


	for (x = 1; x < MAXXDIM-1; x++){
		for (y = 1; y < MAXYDIM-1; y++) {

			if (in[x][y] != 0) {

				temp[x][y] = 255;
				temp[x - 1][y] = 255;
				temp[x + 1][y] = 255;
				temp[x][y - 1] = 255;
				temp[x][y + 1] = 255;

				if (in[x][y] != 0 && temp[x][y] != 0) { out[x][y] = 255; }
				if (in[x - 1][y] != 0 && temp[x - 1][y] != 0) { out[x - 1][y] = 255; }
				if (in[x + 1][y] != 0 && temp[x + 1][y] != 0) { out[x + 1][y] = 255; }
				if (in[x][y - 1] != 0 && temp[x][y - 1] != 0) { out[x][y - 1] = 255; }
				if (in[x][y + 1] != 0 && temp[x][y + 1] != 0) { out[x][y + 1] = 255; }
			
				zündpunktfund = true;
				n2 = n1;
				n1 = pixelcount_return(out);
				zeile = true;
				xfound = x;
				
			}

			if (zeile == true && in[x][y] == 0) { x++; y = 0; zeile = false; }


			if (n1 == n2 && zündpunktfund == true && in[x][y] == 0 && x > xfound+1) {
				objektzahl++;
				int x1, y1;
				for (x1 = 0; x1 < MAXXDIM; x1++) {
					for (y1 = 0; y1 < MAXYDIM; y1++) {
						if (out[x1][y1] != 0) {
							in[x1][y1] = 0;
						}
					}
				}
				zündpunktfund = false;
			}



		}//ende for Y
	}//ende for X
	printf("%i\n", objektzahl);


}//ende fkt
	