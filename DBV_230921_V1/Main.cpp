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
		else if (choice == 10)		//Auswahl 10 ist Histogramm
		{
			readImage_ppm(in);
			histogramm(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 11)		//Auswahl 11 ist Grauwert dehnung
		{
			readImage_ppm(in);
			GW_dehnung(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 12)		//Auswahl 12 ist Grauwert äqualisation
		{
			readImage_ppm(in);
			GW_aequalisation(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 13)		//Auswahl 13 ist Glätten durch Faltung
		{
			readImage_ppm(in);
			Faltung(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 14)		//Auswahl 14 ist Glätten durch Medianbildung
		{
			readImage_ppm(in);
			Median(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 15)		//Auswahl 15 ist Sobel Kantendetektion
		{
			readImage_ppm(in);
			Sobel(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 16)		//Auswahl 16 ist Laplace Kantendetektion
		{
			readImage_ppm(in);
			Laplace(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 17)		//Auswahl 17 ist DoG Kantendetektion
		{
			readImage_ppm(in);
			DoG(in, out);
			writeImage_ppm(out, 256, 256);
			viewImage_ppm();
		}
		else if (choice == 18)		//Auswahl 18 ist Laws
		{
		readImage_ppm(in);
		Laws(in, out);
		writeImage_ppm(out, 256, 256);
		viewImage_ppm();
		}
		else if (choice == 19)		//Auswahl 19 ist Coocurrence
		{
		readImage_ppm(in);
		Coocurrence(in, out);
		writeImage_ppm(out, 256, 256);
		viewImage_ppm();
		}
		else if (choice != 0)		//an sonsten falsche Eingabe: Gibt unteren Satz aus
		{
			printf("Bitte ueberpruefen sie ihre Eingabe !\n---- - \n");
		}

	} while (choice != 0);			//0 Beendet das Programm
}
