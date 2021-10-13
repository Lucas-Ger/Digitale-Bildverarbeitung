#include"image-io.h"
#include <stdio.h>
#include "Funk.h"

void main() {
	int choice;			//Variable zur Auswahl der Funktionen
	unsigned char in[MAXXDIM][MAXYDIM];
	unsigned char out[MAXXDIM][MAXYDIM];


	do
	{
		choice = menu();			//funktion menu wird aufgerufen und der Rückgabewert an choice übergeben

		if (choice == 1)			//Auswahl 1 ist readImage_ppm(in)
		{
			readImage_ppm(in);
		}
		else if (choice == 2)		//Auswahl 2 ist writeImage_ppm(in, 256, 256)
		{
			writeImage_ppm(in, 256, 256);
		}
		else if (choice == 3)		//Auswahl 3 ist viewImage_ppm();		
		{
			viewImage_ppm();
		}
		else if (choice == 4)		//Auswahl 4 ist dilatieren	
		{
			readImage_ppm(in);
			dilate(in, out);
			writeImage_ppm(out, 256, 256);
		}
		else if (choice == 5)		//Auswahl 5 ist erodieren			
		{
			readImage_ppm(in);
			erode(in, out);
			writeImage_ppm(out, 256, 256);
		}
		else if (choice == 6)		//Auswahl 6 zählt die Pixel ungleich null
		{
			readImage_ppm(in);
			pixelcount(in);
		}
		else if (choice == 7)		//Auswahl 7 ist Öffnen (erodieren - dilatieren)
		{
			readImage_ppm(in);
			oeffnen(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 8)		//Auswahl 8 ist Schließen (dilatieren - erodieren)
		{
			readImage_ppm(in);
			schliessen(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 9)		//Auswahl 9 ist GRASSFIRE Algorythmus
		{
			readImage_ppm(in);
			grassfire(in);
		}
		else if (choice != 0)		//an sonsten falsche Eingabe: Gibt unteren Satz aus
		{
			printf("Bitte ueberpruefen sie ihre Eingabe !\n---- - \n");
		}

	} while (choice != 0);			//0 Beendet das Programm
}
