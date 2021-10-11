#include"image-io.h"
#include <stdio.h>
#include "Funk.h"

void main() {
	int choice;			//Variable zur Auswahl der Funktionen
	unsigned char bildein[MAXXDIM][MAXYDIM];
	unsigned char bildaus[MAXXDIM][MAXYDIM];

	do
	{
		choice = menu();			//funktion menu wird aufgerufen und der Rückgabewert an choice übergeben

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
		else if (choice == 6)	// Zählen Pixel anders null
		{
			readImage_ppm(bildein);
			pixelcount(bildein);
		}
		else if (choice == 7)	// Öffnen
		{

		}
		else if (choice == 8)	// Schließen
		{
									
		}
		else if (choice == 9)	// GRASSFIRE
		{

		}
		else if (choice != 0)	//Gibt unteren Satz aus, falls Eingabe keine der oberen Auswahlen ist
		{
			printf("Bitte ueberpruefen sie ihre Eingabe !\n---- - \n");
		}

	} while (choice != 0);		//Beendet das Programm
}
