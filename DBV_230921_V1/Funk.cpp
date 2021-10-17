#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "image-io.h"

int menu() //Menu-Funktion, gibt Möglichkeiten im Programm auf den Bildschirm aus
{
	int choice;
	printf("\nMenu: \nFolgendes kann getan werden : \n-Bild einlesen 1\n-Bild speichern 2\n-Bild anzeigen 3\n-Dilate 4\n-Erode 5\n-Zaehlen der Pixel die nicht schwarz sind 6\n-Oeffnen 7\n-Schliessen 8\n-GRASSFIRE 9\n-Histogramm 10\n-Grauwert dehnung 11\n-Grauwert äqualisation 12\n-Programm beenden 0\nIhre Eingabe:");
	scanf("%i", &choice);		//wartet auf die Eingabe einer Zahl
	printf("\n");
	return(choice);		//gibt die eingegebene Zahl an die Main-Funktion zurück
}

//Funktion dilatieren
void dilate(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{	//out-array nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}
	//an allen weißen Pixeln die ganze Elementarraute setzen
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

//Funktion erodieren
void erode(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{	//out-array nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}
	//an allen weißen Pixeln auf Elementarraute prüfen und ausgangsbit setzen
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

//Funktion Pixel-zählen mit direkter Ausgabe
void pixelcount(unsigned char in[MAXXDIM][MAXYDIM])
{
	int counter = 0;
	int x, y;
	//für alle nicht schwarzen Pixel den counter um 1 erhöhen
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

//Funktion Pixel-zählen mit Anzahl als Rückgabe
int pixelcount_return(unsigned char in[MAXXDIM][MAXYDIM])
{
	int counter = 0;
	int x, y;
	//für alle nicht schwarzen Pixel den counter um 1 erhöhen
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


//Funktion öffnen - eingegebene Anzahl erst erodieren, dann dilatieren
void oeffnen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{
	int choice;
	int i;
	unsigned char temp1 [MAXXDIM][MAXYDIM];
	unsigned char temp2 [MAXXDIM][MAXYDIM];

	//out- und temp-arrays nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
			temp1[x][y] = 0;
			temp2[x][y] = 0;
		}
	}
	
	printf("\nWie oft soll das Bild geoeffnet werden?\nIhre Eingabe:");
	scanf("%i", &choice);		//wartet auf die Eingabe einer Zahl
	printf("\n");

	//wenn null mal - skip
	if (choice == 0){}
	//ein Mal
	else if (choice == 1){
		erode(in, temp1);
		dilate(temp1, out);
	}
	//mehrere Male
	else if (choice != 1){
		//erst erodieren
		erode(in, temp1);
		for (i = 1; i < choice; i++)
		{
			erode(temp1, temp2);
			for (int x = 0; x < MAXXDIM; x++) {
				for (int y = 0; y < MAXYDIM; y++) {
					temp1[x][y] = temp2[x][y];
				}
			}
		}
		//dann dilatieren
		for (i = 1; i < choice; i++)
		{
			dilate(temp1, temp2);
			for (int x = 0; x < MAXXDIM; x++) {
				for (int y = 0; y < MAXYDIM; y++) {
					temp1[x][y] = temp2[x][y];
				}
			}
		}
		dilate(temp1, out);
	}
}


//Funktion schließen - eingegebene Anzahl erst dilatieren, dann erodieren
void schliessen(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM])
{
	int choice;
	int i;
	unsigned char temp1[MAXXDIM][MAXYDIM];
	unsigned char temp2[MAXXDIM][MAXYDIM];

	//out- und temp-arrays nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
			temp1[x][y] = 0;
			temp2[x][y] = 0;
		}
	}

	printf("\nWie oft soll das Bild geschlossen werden?\nIhre Eingabe:");
	scanf("%i", &choice);		//wartet auf die Eingabe einer Zahl
	printf("\n");

	//wenn null mal - skip
	if (choice == 0){}
	//ein Mal
	else if (choice == 1){
		dilate(in, temp1);
		erode(temp1, out);
	}
	//mehrere Male
	else if (choice != 1){
		//erst dilatieren
		dilate(in, temp1);
		for (i = 1; i < choice; i++)
		{
			dilate(temp1, temp2);
			for (int x = 0; x < MAXXDIM; x++) {
				for (int y = 0; y < MAXYDIM; y++) {
					temp1[x][y] = temp2[x][y];
				}
			}
		}
		//dann erodieren
		for (i = 1; i < choice; i++)
		{
			erode(temp1, temp2);
			for (int x = 0; x < MAXXDIM; x++) {
				for (int y = 0; y < MAXYDIM; y++) {
					temp1[x][y] = temp2[x][y];
				}
			}
		}
		erode(temp1, out);
	}
}


//Funktion grassfire algorythmus
void grassfire(unsigned char in[MAXXDIM][MAXYDIM]) {

	//Variablendeklaration
	int objektzahl = 0;
	int n1 = 0, n2 = 0;
	unsigned char out[MAXXDIM][MAXYDIM];
	unsigned char temp[MAXXDIM][MAXYDIM];
	int x, y;
	bool zündpunktfund = false;
	int xfound;

	//out- und temp-array nullen (schwarz stellen)
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
			temp[x][y] = 0;
		}
	}

	//einmal durch das gesammte Bild durchgehen
	for (x = 1; x < MAXXDIM-1; x++){
		for (y = 1; y < MAXYDIM-1; y++) {

			//sobald ein Pixel nicht schwarz ist:
			if (in[x][y] != 0) {

				//im temporären-array die elementarraute setzen
				temp[x][y] = 255;
				temp[x - 1][y] = 255;
				temp[x + 1][y] = 255;
				temp[x][y - 1] = 255;
				temp[x][y + 1] = 255;

				//temp mit in addieren und ergebnis in out schreiben
				if (in[x][y] != 0 && temp[x][y] != 0) { out[x][y] = 255; }
				if (in[x - 1][y] != 0 && temp[x - 1][y] != 0) { out[x - 1][y] = 255; }
				if (in[x + 1][y] != 0 && temp[x + 1][y] != 0) { out[x + 1][y] = 255; }
				if (in[x][y - 1] != 0 && temp[x][y - 1] != 0) { out[x][y - 1] = 255; }
				if (in[x][y + 1] != 0 && temp[x][y + 1] != 0) { out[x][y + 1] = 255; }
			
				zündpunktfund = true;
				//alte anzahl gesetzter Pixel abspeichern und neu zählen
				n2 = n1;
				n1 = pixelcount_return(out);
				xfound = x;	
			}

			//Wenn sich die pixelzahl nicht mehr ändert und ein Zündpunkt identifiziert wurde
			//noch die aktuelle Zeite weiter analysieren um schräge konturen abzufangen
			if (n1 == n2 && zündpunktfund == true  && x > xfound+1) {
				//objektzahl erhöhen
				objektzahl++;
				//das out-bild vom in-bild abziehen
				int x1, y1;
				for (x1 = 0; x1 < MAXXDIM; x1++) {
					for (y1 = 0; y1 < MAXYDIM; y1++) {
						if (out[x1][y1] != 0) {
							in[x1][y1] = 0;
						}
					}
				}
				//nach neuem zündpunkt suchen
				zündpunktfund = false;
			}

		}//ende for Y
	}//ende for X

	//endet wenn das komplette Bild bearbeitet wurde und gibt die Objektzahl aus

	printf("%i\n", objektzahl);

}//ende fkt



void histogramm(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {

	unsigned int grauwertzahl[256];
	unsigned int maxgrauwertzahl = 0;
	float wert;
	int x, y, i;

	//out- und temp-array nullen (schwarz stellen)
	for (x = 0; x < MAXXDIM; x++) {
		grauwertzahl[x] = 0;
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}
	//grauwerte aufnehmen
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			grauwertzahl[in[x][y]] ++;
		}
	}
	//maximale grauwertzahl suchen
	for (i = 0; i < 255; i++) {
		if (grauwertzahl[i] > maxgrauwertzahl) {
			maxgrauwertzahl = grauwertzahl[i];
		}
	}
	//histogramm schreiben
	for (y = 0; y < MAXYDIM; y++) {
		wert = (grauwertzahl[y] * 255 / maxgrauwertzahl );
		for (x = MAXXDIM; x > (MAXXDIM - wert); x--) {
			out[x][y] = 255;
		}
	}
}


void GW_dehnung(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {
	//Variablendeklaration
	int x, y;
	int E_min = 255, E_max = 0;
	float value;

	//out-array nullen (schwarz stellen)
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}

	//Abfrage E_min & E_max
	printf("\nDehnung der Grauwertstala\n 0 - fuer automatische Einstellung\n E min: ");
	scanf("%i", &E_min);
	if (E_min == 0) {
		E_min = 255;
		//maximalen und minimalen grauwert suchen
		for (x = 0; x < MAXXDIM; x++) {
			for (y = 0; y < MAXYDIM; y++) {
				if (in[x][y] < E_min) { E_min = in[x][y]; }
				if (in[x][y] > E_max) { E_max = in[x][y]; }
			}
		}
	}
	else {
		printf(" E max: ");
		scanf("%i", &E_max);
	}

	//Grauwertdehnung nach Formel
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			value = 255.0 / (E_max - E_min) * (in[x][y] - E_min);
			out[x][y] = int(value);
		}
	}
}

void GW_äqualisation(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {
	//Variablendeklaration
	int x, y;
	int distance;
	int gw, n;
	int search_gw = 0;

	//gesetzte Pixel bestimmen
	int pixel = pixelcount_return(in);

	//Abfrage Grauwertabstand
	printf("abstand der Grauwerte (1-254): ");
	scanf("%i", &distance);
	if (distance < 1 || distance > 254) { return; }
	//anzahl an pixeln je Grauwert in Ausgabebild
	float pixel_gw = pixel / 256 * distance;
	pixel_gw = int(pixel_gw);

	//out-array nullen (schwarz stellen)
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}

	//in-Bild durchgehen
	for (gw = 0; gw < 255; gw = gw + distance) {
		n = 0;
		while (n < pixel_gw) {
			search_gw++;

			for (x = 0; x < MAXXDIM; x++) {
				for (y = 0; y < MAXYDIM; y++) {
					//abbruch wenn pixelzahl erreicht ist
					if (n >= pixel_gw) {
						x = 255; y = 255; break;
					}
					if (search_gw > 255) {
						return;
					}

					//grauwerte durchsuchen
					if (in[x][y] == search_gw) {
						out[x][y] = gw;
						in[x][y] = 0;
						n++;
					}

				}
			}//end for

		}//end while per GW

	}//end for over all GW

}//end of function