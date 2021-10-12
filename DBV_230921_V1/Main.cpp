#include"image-io.h"
#include <stdio.h>
#include "Funk.h"

void main() {
	int choice;			//Variable zur Auswahl der Funktionen
	unsigned char bildein[MAXXDIM][MAXYDIM];
	unsigned char bildaus[MAXXDIM][MAXYDIM];

	do
	{
		choice = menu();			//funktion menu wird aufgerufen und der R�ckgabewert an choice �bergeben

		if (choice == 1)			//Auswahl 1 ist readImage_ppm(bildein)
		{
			readImage_ppm(bildein);
		}
		else if (choice == 2)		//Auswahl 2 ist writeImage_ppm(bildein, 256, 256)
		{
			writeImage_ppm(bildein, 256, 256);
		}
		else if (choice == 3)		//Auswahl 3 ist viewImage_ppm();		
		{
			viewImage_ppm();
		}
		else if (choice == 4)		
		{
			readImage_ppm(bildein);
			dilate(bildein, bildaus);
			writeImage_ppm(bildaus, 256, 256);
		}
		else if (choice == 5)		
		{
			readImage_ppm(bildein);
			erode(bildein, bildaus);
			writeImage_ppm(bildaus, 256, 256);
		}
		else if (choice == 6)	// Z�hlen Pixel anders null
		{
			readImage_ppm(bildein);
			pixelcount(bildein);
		}
		else if (choice == 7)	// �ffnen
		{
			readImage_ppm(bildein);
			oeffnen(bildein, bildaus);
			writeImage_ppm(bildaus, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 8)	// Schlie�en
		{
			readImage_ppm(bildein);
			schliessen(bildein, bildaus);
			writeImage_ppm(bildaus, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 9)	// GRASSFIRE
		{
			readImage_ppm(bildein);
			grassfire2(bildein);
		}
		else if (choice != 0)	//Gibt unteren Satz aus, falls Eingabe keine der oberen Auswahlen ist
		{
			printf("Bitte ueberpruefen sie ihre Eingabe !\n---- - \n");
		}

	} while (choice != 0);		//Beendet das Programm
}
