#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include<stdlib.h>
#include "image-io.h"

int menu() //Menu-Funktion, gibt Möglichkeiten im Programm auf den Bildschirm aus
{
	int choice;
	printf("\nMenu: \nFolgendes kann getan werden : ");
	printf("\n-Bild einlesen 1");
	printf("\n-Bild speichern 2");
	printf("\n-Bild anzeigen 3");
	printf("\n-Dilate 4");
	printf("\n-Erode 5");
	printf("\n-Zaehlen der Pixel die nicht schwarz sind 6");
	printf("\n-Oeffnen 7");
	printf("\n-Schliessen 8");
	printf("\n-GRASSFIRE 9");
	printf("\n-Histogramm 10");
	printf("\n-Grauwert dehnung 11");
	printf("\n-Grauwert aequalisation 12");
	printf("\n-Faltung 13");
	printf("\n-Median 14");
	printf("\n-Sobel 15");
	printf("\n-Laplace 16");
	printf("\n-DoG 17");
	printf("\n-Laws 18");
	printf("\n-Coocurrence 19");
	printf("\n-Blob-coloring 20");
	printf("\n-Programm beenden 0");
	printf("\nIhre Eingabe:");
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

//Funktion Histogrammerstellung
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
	for (i = 0; i <= 255; i++) {
		if (grauwertzahl[i] > maxgrauwertzahl) {
			maxgrauwertzahl = grauwertzahl[i];
		}
	}
	//histogramm schreiben
	for (y = 0; y < MAXYDIM; y++) {
		wert = (grauwertzahl[y] * 255.0 / maxgrauwertzahl );
		for (x = MAXXDIM; x > (MAXXDIM - wert); x--) {
			out[x][y] = 255;
		}
	}
}

//Funktion Grauwertdehnung
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
	if (E_min < 0 || E_min > 255) { printf("/nUnzulaessige Eingabe/n"); return; }
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
		if (E_max < E_min || E_max > 255) { printf("/nUnzulaessige Eingabe/n"); return; }
	}

	//Grauwertdehnung nach Formel
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			value = 255.0 / (E_max - E_min) * (in[x][y] - E_min);
			out[x][y] = int(value);
		}
	}
}

//Funktion Grauwertäqualisation
void GW_aequalisation(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {
	//Variablendeklaration
	int x, y;
	int anzahl;
	float distance, pixel_gw;
	int gw, n;
	int search_gw = -1;

	//gesetzte Pixel bestimmen
	int pixel = 256 * 256;//pixelcount_return(in);

	//Abfrage Grauwertabstand
	printf("Anzahl der Grauwerte (1-256): ");
	scanf("%i", &anzahl);
	if (anzahl < 1 || anzahl > 256) { printf("/nUnzulaessige Eingabe/n"); return; }
	//distanz der Grauwerte
	distance = 256 / anzahl;
	distance = int(distance);
	//anzahl an pixeln je Grauwert in Ausgabebild
	pixel_gw = pixel / 256 * distance;
	//in integer formatieren
	pixel_gw = int(pixel_gw);


	//out-array nullen (schwarz stellen)
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}

	//in-Bild durchgehen
	for (gw = 0; gw <= 255; gw = gw + distance) {
		n = 0;
		search_gw = 0;
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

//Funktion Falten (Glättung) mit verschiedenen 3x3 und 5x5 Matritzen
void Faltung(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {

	int matrix [5][5];
	int eingabe;
	printf("\nMittelwert:\t1");
	printf("\nGauss:\t2");
	printf("\ngewichteter Mittelwert 3x3:\t3");
	printf("\ngewichteter Mittelwert 5x5:\t4\n");
	scanf("%i", &eingabe);

	//out-array nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}

	//Matritzen setzen
	if (eingabe == 1) {
		matrix[0][0] = 1;	matrix[1][0] = 1;	matrix[2][0] = 1;
		matrix[0][1] = 1;	matrix[1][1] = 1;	matrix[2][1] = 1;
		matrix[0][2] = 1;	matrix[1][2] = 1;	matrix[2][2] = 1;
	}
	else if (eingabe == 2) {
		matrix[0][0] = 1;	matrix[1][0] = 2;	matrix[2][0] = 1;
		matrix[0][1] = 2;	matrix[1][1] = 4;	matrix[2][1] = 2;
		matrix[0][2] = 1;	matrix[1][2] = 2;	matrix[2][2] = 1;
	}
	else if (eingabe == 3) {
		matrix[0][0] = 1;	matrix[1][0] = 1;	matrix[2][0] = 1;
		matrix[0][1] = 1;	matrix[1][1] = 2;	matrix[2][1] = 1;
		matrix[0][2] = 1;	matrix[1][2] = 1;	matrix[2][2] = 1;
	}
	else if (eingabe == 4) {
		matrix[0][0] = 1;	matrix[1][0] = 1;	matrix[2][0] = 1;	matrix[3][0] = 1;	matrix[4][0] = 1;
		matrix[0][1] = 1;	matrix[1][1] = 2;	matrix[2][1] = 2;	matrix[3][1] = 2;	matrix[4][1] = 1;
		matrix[0][2] = 1;	matrix[1][2] = 2;	matrix[2][2] = 4;	matrix[3][2] = 2;	matrix[4][2] = 1;
		matrix[0][3] = 1;	matrix[1][3] = 2;	matrix[2][3] = 2;	matrix[3][3] = 2;	matrix[4][3] = 1;
		matrix[0][4] = 1;	matrix[1][4] = 1;	matrix[2][4] = 1;	matrix[3][4] = 1;	matrix[4][4] = 1;
	}


	//Faltung 3x3
	if (eingabe == 1 || eingabe == 2 || eingabe == 3) {
		for (x = 1; x < MAXXDIM - 1; x++) {
			for (y = 1; y < MAXYDIM - 1; y++) {

				out[x][y] = int((	matrix[0][0] * in[x - 1][y - 1] +	matrix[1][0] * in[x][y - 1] +	matrix[2][0] * in[x + 1][y - 1]
								+	matrix[0][1] * in[x - 1][y] +		matrix[1][1] * in[x][y] +		matrix[2][1] * in[x + 1][y]
								+	matrix[0][2] * in[x - 1][y + 1] +	matrix[1][2] * in[x][y + 1] +	matrix[2][2] * in[x + 1][y + 1]
					) / (matrix[0][0] + matrix[1][0] + matrix[2][0] + matrix[0][1] + matrix[1][1] + matrix[2][1] + matrix[0][2] + matrix[1][2] + matrix[2][2]));
			}
		}
	}
	//Faltung 5x5
	else if (eingabe == 4){
		for (x = 2; x < MAXXDIM - 2; x++) {
			for (y = 2; y < MAXYDIM - 2; y++) {

				out[x][y] = int((	matrix[0][0] * in[x - 2][y - 2] +	matrix[1][0] * in[x - 1][y - 2] +	matrix[2][0] * in[x][y - 2] +	matrix[3][0] * in[x + 1][y - 2] +	matrix[4][0] * in[x + 2][y - 2]
								+	matrix[0][1] * in[x - 2][y - 1] +	matrix[1][1] * in[x - 1][y - 1] +	matrix[2][1] * in[x][y - 1] +	matrix[3][1] * in[x + 1][y - 1] +	matrix[4][1] * in[x + 2][y - 1]
								+	matrix[0][2] * in[x - 2][y]		+	matrix[1][2] * in[x - 1][y]		+	matrix[2][2] * in[x][y]		+	matrix[3][2] * in[x + 1][y]		+	matrix[4][2] * in[x + 2][y]
								+	matrix[0][3] * in[x - 2][y + 1] +	matrix[1][3] * in[x - 1][y + 1] +	matrix[2][3] * in[x][y + 1] +	matrix[3][3] * in[x + 1][y + 1] +	matrix[4][3] * in[x + 2][y + 1]
								+	matrix[0][4] * in[x - 2][y + 2] +	matrix[1][4] * in[x - 1][y + 2] +	matrix[2][4] * in[x][y + 2] +	matrix[3][4] * in[x + 1][y + 2] +	matrix[4][4] * in[x + 2][y + 2]) 
							/	(	matrix[0][0] + matrix[1][0] + matrix[2][0] + matrix[3][0] + matrix[4][0] 
								+	matrix[0][1] + matrix[1][1] + matrix[2][1] + matrix[3][1] + matrix[4][1] 
								+	matrix[0][2] + matrix[1][2] + matrix[2][2] + matrix[3][2] + matrix[4][2]
								+	matrix[0][3] + matrix[1][3] + matrix[2][3] + matrix[3][3] + matrix[4][3]
								+	matrix[0][4] + matrix[1][4] + matrix[2][4] + matrix[3][4] + matrix[4][4]	));
			}
		}
	}

}

//Funktion bubble sort von array a[] mit Anzahl N (für Medianbildung)
void bubble_sort(int a[], int N) {
	int i, j, t;
	for (i = N-1; i >= 1; i--) {
		for (j = 1; j <= i; j++) {
			if (a[j - 1] > a[j]) {
				t = a[j - 1];
				a[j - 1] = a[j];
				a[j] = t;

			}
		}
	}
}

//Median-Glättung
void Median(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {
	int wert[25];
	int eingabe;
	printf("\n3x3\t1");
	printf("\n5x5\t2\n");
	scanf("%i", &eingabe);

	//out-array nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}

	//Median 3x3
	if (eingabe == 1) {
		for (x = 1; x < MAXXDIM-1; x++) {
			for (y = 1; y < MAXYDIM-1; y++) {
				wert[0] = in[x - 1][y - 1];		wert[1] = in[x - 1][y];		wert[2] = in[x - 1][y + 1];
				wert[3] = in[x][y - 1];			wert[4] = in[x][y];			wert[5] = in[x][y + 1];
				wert[6] = in[x + 1][y - 1];		wert[7] = in[x + 1][y];		wert[8] = in[x + 1][y + 1];

				bubble_sort(wert, 9);
				out[x][y] = wert[4];
			}
		}
	}

	//median 5x5
	if (eingabe == 2) {
		for (x = 2; x < MAXXDIM-2; x++) {
			for (y = 2; y < MAXYDIM-2; y++) {
				wert[0] = in[x - 2][y - 2];		wert[1] = in[x - 2][y - 1];		wert[2] = in[x - 2][y];		wert[3] = in[x + 2][y + 1];		wert[4] = in[x + 2][y + 2];
				wert[5] = in[x - 1][y - 2];		wert[6] = in[x - 1][y - 1];		wert[7] = in[x - 1][y];		wert[8] = in[x + 1][y + 1];		wert[9] = in[x + 1][y + 2];
				wert[10] = in[x][y - 2];		wert[11] = in[x][y - 1];		wert[12] = in[x][y];		wert[13] = in[x][y + 1];		wert[14] = in[x][y + 2];
				wert[15] = in[x + 1][y - 2];	wert[16] = in[x + 1][y - 1];	wert[17] = in[x + 1][y];	wert[18] = in[x - 1][y + 1];	wert[19] = in[x - 1][y + 2];
				wert[20] = in[x + 2][y - 2];	wert[21] = in[x + 2][y - 1];	wert[22] = in[x + 2][y];	wert[23] = in[x - 2][y + 1];	wert[24] = in[x - 2][y + 2];

				bubble_sort(wert, 25);
				out[x][y] = wert[12];
			}
		}
	}

}

//Sobel Kantendetektion | nicht binarisiert
void Sobel(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {
	int temp[2][MAXXDIM][MAXYDIM];
	int matrix[3][3];

	//out und temp-arrays nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
			temp[0][x][y] = 0;
			temp[1][x][y] = 0;
		}
	}

	//x = 0, Y = 1 durchgehen
	for (int i = 0; i <= 1; i++) {
		//Matritzen setzen
		if (i == 0) {//X-Matrix Setzen
			matrix[0][0] = 1;	matrix[1][0] = 0;	matrix[2][0] = -1;
			matrix[0][1] = 2;	matrix[1][1] = 0;	matrix[2][1] = -2;
			matrix[0][2] = 1;	matrix[1][2] = 0;	matrix[2][2] = -1;
		}
		else if (i == 1) {//Y Matrix setzen
			matrix[0][0] = 1;	matrix[1][0] = 2;	matrix[2][0] = 1;
			matrix[0][1] = 0;	matrix[1][1] = 0;	matrix[2][1] = 0;
			matrix[0][2] = -1;	matrix[1][2] = -2;	matrix[2][2] = -1;
		}


		//Faltung 3x3

		for (x = 1; x < MAXXDIM - 1; x++) {
			for (y = 1; y < MAXYDIM - 1; y++) {

				temp[i][x][y] = int(	matrix[0][0] * in[x - 1][y - 1]	+	matrix[1][0] * in[x][y - 1] +	 matrix[2][0] * in[x + 1][y - 1]
									+	matrix[0][1] * in[x - 1][y]		+	matrix[1][1] * in[x][y]		+	 matrix[2][1] * in[x + 1][y]
									+	matrix[0][2] * in[x - 1][y + 1] +	matrix[1][2] * in[x][y + 1] +	 matrix[2][2] * in[x + 1][y + 1]
									);
			}
		}

	}

	for (x = 1; x < MAXXDIM - 1; x++) {
		for (y = 1; y < MAXYDIM - 1; y++) {
			out[x][y] = unsigned char ( sqrt((temp[0][x][y] * temp[0][x][y]) + (temp[1][x][y] * temp[1][x][y])));
		}
	}

}

//Laplace (4er Bereich) Kantendetektion | nicht binarisiert
void Laplace(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {
	int matrix[3][3];

	//out-array nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}

	//Matritzen setzen
	if (true) {
		matrix[0][0] = 0;	matrix[1][0] = 1;	matrix[2][0] = 0;
		matrix[0][1] = 1;	matrix[1][1] = -4;	matrix[2][1] = 1;
		matrix[0][2] = 0;	matrix[1][2] = 1;	matrix[2][2] = 0;
	}



//Faltung 3x3

	for (x = 1; x < MAXXDIM - 1; x++) {
		for (y = 1; y < MAXYDIM - 1; y++) {

			out[x][y] = 127 + int(	matrix[0][0] * in[x - 1][y - 1] + matrix[1][0] * in[x][y - 1]	+ matrix[2][0] * in[x + 1][y - 1]
								+	matrix[0][1] * in[x - 1][y]		+ matrix[1][1] * in[x][y]		+ matrix[2][1] * in[x + 1][y]
								+	matrix[0][2] * in[x - 1][y + 1] + matrix[1][2] * in[x][y + 1]	+ matrix[2][2] * in[x + 1][y + 1]
								);
		}
	}

}

//DoG
//Funktionen zur berechnung eines Binomialkoeffitienten
int fac(int x)            // Compute n!
{
	if ((x == 0) || (x == 1))
		return 1;
	else
		return (x*fac(x - 1));    // recusive call
} // fac
unsigned int binCoeff(int n, int k)
{
	if (k == 0 || k == n)
		return 1;
	else if (n == 0 || k > n)
		return 0;
	else
		return fac(n) / (fac(n - k)*fac(k));
}
//Funktion
void DoG(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {

	float temp[2][MAXXDIM][MAXYDIM];

	//out nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
			temp[0][x][y] = 0;
			temp[1][x][y] = 0;
		}
	}

	//2 Mal Gaussmatrix anwenden
	for (int a = 0; a < 2; a++){

		//Gaussmatrix Initialisieren
		int dim = 0;
		//größe der Gaussmatritzen definieren
		if(a == 0) dim = 7;
		else if (a == 1) dim = 9
;
		int matrix[9][9];

		//Quersumme berechnen
		int cksum = 0;

		//Matrix füllen mit Pascallschem Dreieck (Binomialkoeffitienten)
		int i, j;
		for (i = 0; i < dim; i++) {
			cksum = cksum + binCoeff(dim - 1, i);
			for (j = 0; j < dim; j++) {
				matrix[i][j] = binCoeff(dim - 1, i) * binCoeff(dim - 1, j);
			}
		}
		//Umrechnung Quersumme in Normierungsfaktor
		float f = (cksum)*(cksum);

		//Berechnung vom Rand m
		int m = int(dim / 2 - 0.5);

		//Faltung mit Gaussmatrix
		for (x = m; x < MAXXDIM - m; x++) {
			for (y = m; y < MAXYDIM - m; y++) {

				int value = 0;
				//Faltungsmatrix eintrag für eintrag durchgehen
				for (i = 0; i < dim; i++) {
					for (j = 0; j < dim; j++) {
						//xi und yj sind die in aktuell betrachteten Pixel
						int xi = x - m + i;
						int yj = y - m + j;
						//Einzelne Werte mit ihren gewichtungen aufmultiplizieren
						value = value + (in[xi][yj] * matrix[i][j]);
					}
				}
				//Im Ausgabepixel Faltungssumme / Normierung schreiben
				temp[a][x][y] = value / f;
				//fortführung mit nächstem Ausgabepixel
			}
		}

	}//2x Faltung mit Gauss fertig. Temp[0] = 7x7, Temp[1] = 9x9

	//7x7 von 9x9 Matrix abziehen
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = int( temp[1][x][y] - temp[0][x][y]);
		}
	}


}

//
void Laws(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {

	int matrix[9][5][5];
	float erg[9];
	float temp[MAXXDIM][MAXYDIM];
	
	int eingabe;

	printf("\n 3x3:\t1");
	printf("\n 5x5:\t2\n");
	scanf("%i", &eingabe);
	
	//out-array nullen (schwarz stellen)
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 0;
		}
	}

	//Matritzen setzen
	if (eingabe == 1) {
		int i = 0;
		matrix[i][0][0] = 1;	matrix[i][1][0] = 2;	matrix[i][2][0] = 1;
		matrix[i][0][1] = 2;	matrix[i][1][1] = 4;	matrix[i][2][1] = 2;
		matrix[i][0][2] = 1;	matrix[i][1][2] = 2;	matrix[i][2][2] = 1;
		i = 1;
		matrix[i][0][0] = -1;	matrix[i][1][0] = 0;	matrix[i][2][0] = 1;
		matrix[i][0][1] = -2;	matrix[i][1][1] = 0;	matrix[i][2][1] = 2;
		matrix[i][0][2] = -1;	matrix[i][1][2] = 0;	matrix[i][2][2] = 1;
		i = 2;
		matrix[i][0][0] = -1;	matrix[i][1][0] = 2;	matrix[i][2][0] = -1;
		matrix[i][0][1] = -2;	matrix[i][1][1] = 4;	matrix[i][2][1] = -2;
		matrix[i][0][2] = -1;	matrix[i][1][2] = 2;	matrix[i][2][2] = -1;
		i = 3;
		matrix[i][0][0] = -1;	matrix[i][1][0] = -2;	matrix[i][2][0] = -1;
		matrix[i][0][1] = 0;	matrix[i][1][1] = 0;	matrix[i][2][1] = 0;
		matrix[i][0][2] = 1;	matrix[i][1][2] = 2;	matrix[i][2][2] = 1;
		i = 4;
		matrix[i][0][0] = 1;	matrix[i][1][0] = 0;	matrix[i][2][0] = -1;
		matrix[i][0][1] = 0;	matrix[i][1][1] = 0;	matrix[i][2][1] = 0;
		matrix[i][0][2] = -1;	matrix[i][1][2] = 0;	matrix[i][2][2] = 1;
		i = 5;
		matrix[i][0][0] = 1;	matrix[i][1][0] = -2;	matrix[i][2][0] = 1;
		matrix[i][0][1] = 0;	matrix[i][1][1] = 0;	matrix[i][2][1] = 0;
		matrix[i][0][2] = -1;	matrix[i][1][2] = 2;	matrix[i][2][2] = -1;
		i = 6;
		matrix[i][0][0] = -1;	matrix[i][1][0] = -2;	matrix[i][2][0] = -1;
		matrix[i][0][1] = 2;	matrix[i][1][1] = 4;	matrix[i][2][1] = 2;
		matrix[i][0][2] = -1;	matrix[i][1][2] = -2;	matrix[i][2][2] = -1;
		i = 7;
		matrix[i][0][0] = 1;	matrix[i][1][0] = 0;	matrix[i][2][0] = -1;
		matrix[i][0][1] = -2;	matrix[i][1][1] = 0;	matrix[i][2][1] = 2;
		matrix[i][0][2] = 1;	matrix[i][1][2] = 0;	matrix[i][2][2] = -1;
		i = 8;
		matrix[i][0][0] = 1;	matrix[i][1][0] = -2;	matrix[i][2][0] = 1;
		matrix[i][0][1] = -2;	matrix[i][1][1] = 4;	matrix[i][2][1] = -2;
		matrix[i][0][2] = 1;	matrix[i][1][2] = -2;	matrix[i][2][2] = 1;
	}
	else if (eingabe == 2) {
		int i = 0;
		matrix[i][0][0] = -1;	matrix[i][1][0] = -2;	matrix[i][2][0] = 0;	matrix[i][3][0] = 2;	matrix[i][4][0] = 1;
		matrix[i][0][1] = -4;	matrix[i][1][1] = -8;	matrix[i][2][1] = 0;	matrix[i][3][1] = 8;	matrix[i][4][1] = 4;
		matrix[i][0][2] = -6;	matrix[i][1][2] = -12;	matrix[i][2][2] = 0;	matrix[i][3][2] = 12;	matrix[i][4][2] = 6;
		matrix[i][0][3] = -4;	matrix[i][1][3] = -8;	matrix[i][2][3] = 0;	matrix[i][3][3] = 8;	matrix[i][4][3] = 4;
		matrix[i][0][4] = -1;	matrix[i][1][4] = -2;	matrix[i][2][4] = 0;	matrix[i][3][4] = 2;	matrix[i][4][4] = 1;
		i = 1;
		matrix[i][0][0] = -1;	matrix[i][1][0] = 0;	matrix[i][2][0] = 2;	matrix[i][3][0] = 0;	matrix[i][4][0] = -1;
		matrix[i][0][1] = -2;	matrix[i][1][1] = 0;	matrix[i][2][1] = 4;	matrix[i][3][1] = 0;	matrix[i][4][1] = -2;
		matrix[i][0][2] = 0;	matrix[i][1][2] = 0;	matrix[i][2][2] = 0;	matrix[i][3][2] = 0;	matrix[i][4][2] = 0;
		matrix[i][0][3] = 2;	matrix[i][1][3] = 0;	matrix[i][2][3] = -4;	matrix[i][3][3] = 0;	matrix[i][4][3] = 2;
		matrix[i][0][4] = 1;	matrix[i][1][4] = 0;	matrix[i][2][4] = -2;	matrix[i][3][4] = 0;	matrix[i][4][4] = 1;
		i = 2;
		matrix[i][0][0] = -1;	matrix[i][1][0] = 0;	matrix[i][2][0] = 2;	matrix[i][3][0] = 0;	matrix[i][4][0] = -1;
		matrix[i][0][1] = -4;	matrix[i][1][1] = 0;	matrix[i][2][1] = 8;	matrix[i][3][1] = 0;	matrix[i][4][1] = -4;
		matrix[i][0][2] = -6;	matrix[i][1][2] = 0;	matrix[i][2][2] = 12;	matrix[i][3][2] = 0;	matrix[i][4][2] = -6;
		matrix[i][0][3] = -4;	matrix[i][1][3] = 0;	matrix[i][2][3] = 8;	matrix[i][3][3] = 0;	matrix[i][4][3] = -4;
		matrix[i][0][4] = -1;	matrix[i][1][4] = 0;	matrix[i][2][4] = 2;	matrix[i][3][4] = 0;	matrix[i][4][4] = -1;
		i = 3;
		matrix[i][0][0] = 1;	matrix[i][1][0] = -4;	matrix[i][2][0] = 6;	matrix[i][3][0] = -4;	matrix[i][4][0] = 1;
		matrix[i][0][1] = -4;	matrix[i][1][1] = 16;	matrix[i][2][1] = -24;	matrix[i][3][1] = 16;	matrix[i][4][1] = -4;
		matrix[i][0][2] = 6;	matrix[i][1][2] = -24;	matrix[i][2][2] = 36;	matrix[i][3][2] = -24;	matrix[i][4][2] = 6;
		matrix[i][0][3] = -4;	matrix[i][1][3] = 16;	matrix[i][2][3] = -24;	matrix[i][3][3] = 16;	matrix[i][4][3] = -4;
		matrix[i][0][4] = 1;	matrix[i][1][4] = -4;	matrix[i][2][4] = 6;	matrix[i][3][4] = -4;	matrix[i][4][4] = 1;
		
	}

	//Faltung 3x3
	if (eingabe == 1) {
		for (x = 1; x < MAXXDIM - 1; x++) {
			for (y = 1; y < MAXYDIM - 1; y++) {
				for (int i = 0; i < 9; i++) {
					erg[i] = matrix[i][0][0] * in[x - 1][y - 1] + matrix[i][1][0] * in[x][y - 1] + matrix[i][2][0] * in[x + 1][y - 1]
						+ matrix[i][0][1] * in[x - 1][y] + matrix[i][1][1] * in[x][y] + matrix[i][2][1] * in[x + 1][y]
						+ matrix[i][0][2] * in[x - 1][y + 1] + matrix[i][1][2] * in[x][y + 1] + matrix[i][2][2] * in[x + 1][y + 1];
					if (i == 0) erg[i] = erg[i] / 16;
				}

				temp[x][y] = sqrt(/*erg[0] * erg[0] +*/ erg[1] * erg[1] + erg[2] * erg[2] + erg[3] * erg[3] + erg[4] * erg[4] + erg[5] * erg[5] + erg[6] * erg[6] + erg[7] * erg[7] + erg[8] * erg[8]);

			}
		}
	}

	//Faltung 5x5
	else if (eingabe == 2) {
		for (x = 2; x < MAXXDIM - 2; x++) {
			for (y = 2; y < MAXYDIM - 2; y++) {
				for (int i = 0; i < 9; i++) {
					erg[i] = matrix[i][0][0] * in[x - 2][y - 2] + matrix[i][1][0] * in[x - 1][y - 2] + matrix[i][2][0] * in[x][y - 2] + matrix[i][3][0] * in[x + 1][y - 2] + matrix[i][4][0] * in[x + 2][y - 2]
						+ matrix[i][0][1] * in[x - 2][y - 1] + matrix[i][1][1] * in[x - 1][y - 1] + matrix[i][2][1] * in[x][y - 1] + matrix[i][3][1] * in[x + 1][y - 1] + matrix[i][4][1] * in[x + 2][y - 1]
						+ matrix[i][0][2] * in[x - 2][y] + matrix[i][1][2] * in[x - 1][y] + matrix[i][2][2] * in[x][y] + matrix[i][3][2] * in[x + 1][y] + matrix[i][4][2] * in[x + 2][y]
						+ matrix[i][0][3] * in[x - 2][y + 1] + matrix[i][1][3] * in[x - 1][y + 1] + matrix[i][2][3] * in[x][y + 1] + matrix[i][3][3] * in[x + 1][y + 1] + matrix[i][4][3] * in[x + 2][y + 1]
						+ matrix[i][0][4] * in[x - 2][y + 2] + matrix[i][1][4] * in[x - 1][y + 2] + matrix[i][2][4] * in[x][y + 2] + matrix[i][3][4] * in[x + 1][y + 2] + matrix[i][4][4] * in[x + 2][y + 2];
				}

				temp[x][y] = sqrt(erg[0] * erg[0] + erg[1] * erg[1] + erg[2] * erg[2] + erg[3] * erg[3]);
			}
		}
	}






	//maximale Grauwertzahl suchen
	float maxgrauwertzahl = 0;
	for (x = 0; x <= MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			if (temp[x][y] > maxgrauwertzahl) {
				maxgrauwertzahl = temp[x][y];
			}
		}
	}

	for (x = 0; x <= MAXXDIM; x++) {
		for (y = 1; y < MAXYDIM - 1; y++) {
			out[x][y] = int(temp[x][y] / maxgrauwertzahl * 255);
		}
	}


}


void Coocurrence(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]){

	unsigned char matrix[5][MAXXDIM][MAXYDIM];
	unsigned char gw, gw0, gw45, gw90, gw135;


	//out-array auf 255, andere nullen
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 255;
			//0°
			matrix[0][x][y] = 0;
			//45°
			matrix[1][x][y] = 0;
			//90°
			matrix[2][x][y] = 0;
			//135°
			matrix[3][x][y] = 0;
			//
			matrix[4][x][y] = 0;
		}
	}


	//Coocurrencematrix für die 4 Richtungen aufnehmen
	for (x = 1; x < MAXXDIM - 1; x++) {
		for (y = 1; y < MAXYDIM - 1; y++) {
			gw = in[x][y];
			gw0 = in[x + 1][y];
			gw45 = in[x + 1][y - 1];
			gw90 = in[x][y - 1];
			gw135 = in[x - 1][y - 1];


			//0°
			matrix[0][gw][gw0] = matrix[0][gw][gw0] + 1;
			//45°
			matrix[1][gw][gw45] = matrix[1][gw][gw45] + 1;
			//90°
			matrix[2][gw][gw90] = matrix[2][gw][gw90] + 1;
			//135°
			matrix[3][gw][gw135] = matrix[3][gw][gw135] + 1;
			
		}
	}


	//Nachbargrauwert mitteln
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			
			matrix[4][x][y] = int((matrix[0][x][y] + matrix[1][x][y] + matrix[2][x][y] + matrix[3][x][y]) / 4);
			
		}
	}

	//Ausgeben
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {

			out[x][y] = 255 - matrix[4][x][y];
			
		}
	}
	
	//Kontrastberechnung
	//zunächst normieren
	int s = 0;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			s = s + matrix[4][x][y];
		}
	}
	float normmatrix[MAXXDIM][MAXYDIM];
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			normmatrix[x][y] = float(matrix[4][x][y]) / float(s);
		}
	}

	//Kontrast berechnen
	float kontrast = 0;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {


			kontrast = kontrast + (x - y)*(x - y) * normmatrix[x][y];
		}
	}

	printf("\nKontrast: %f\n\n", kontrast);


	//Ausgabe an sich fertig
	//Skalierung der Ausgabe
/*

	//Minimalen Grauwert ermitteln
	unsigned char mingrauwertzahl = 255;
	for (x = 0; x <= MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			if (out[x][y] < mingrauwertzahl) {
				mingrauwertzahl = out[x][y];
			}
		}
	}
	//auf minimalen Grauwert skalieren
	for (x = 0; x <= MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			if (out[x][y] != 255) {
				out[x][y] = int((out[x][y] - mingrauwertzahl) * 255 / (1 - mingrauwertzahl));
			}
		}
	}
*/
}


void  blob_coloring(unsigned char in[MAXXDIM][MAXYDIM], unsigned char out[MAXXDIM][MAXYDIM]) {
	


	int mark[MAXXDIM][MAXYDIM];
	
	int x, y;
	for (x = 0; x < MAXXDIM; x++) {
		for (y = 0; y < MAXYDIM; y++) {
			out[x][y] = 255;
			mark[x][y] = 0;
			//Reihe 1 und Spalte 1 ist Region 1
			//mark[x][0] = 1;
			//mark[0][y] = 1;
		}
	}

	int regionzahl = 0;
	int oben = 0, links = 0, erg;
	int schwelle;

	printf("\nSchwelle: ");
	scanf("%i", &schwelle);

	for (x = 1; x < MAXXDIM; x++) {
		for (y = 1; y < MAXYDIM; y++) {


			int xcxu = in[x][y] - in[x - 1][y];
			int xcxl = in[x][y] - in[x][y - 1];


			if ((-schwelle < xcxu) && (xcxu < schwelle)) {
				oben = mark[x - 1][y];
				if ((-schwelle < xcxl) && (xcxl < schwelle)) {
					links = mark[x][y - 1];
				}
			}
			else if ((-schwelle < xcxl) && (xcxl < schwelle)) {
				links = mark[x][y - 1];
				oben = 0;
			} 
			else {
				links = 0;
				oben = 0;
			}


			if (oben == links && oben != 0 && links != 0) {
				mark[x][y] = oben;
			}
			else if (oben > 0 && links == 0) {
				mark[x][y] = oben;
			}
			else if (oben == 0 && links > 0) {
				mark[x][y] = links;
			}
			else if (oben == 0 && links == 0) {
				regionzahl++;
				mark[x][y] = regionzahl;
			}
			else{
				mark[x][y] = oben;
				int i, j;
				i = x;
				bool merker = false;
					for (j = y - 1; j > 0; j--) {
						if ((-schwelle < (in[x][y] - in[i][j])) && ((in[x][y] - in[i][j]) < schwelle)) {
							mark[i][j] = oben;
							if (merker == false) {
								regionzahl--;
								merker = true;
							}
						}
						else break;
					}
			}

		}
	}

	printf("Regionenanzahl: %i\n\n", regionzahl);
	int i;
	float gw = 0;
	for (i = 1; i <= regionzahl; i++) {
		gw = 0;
		int n = 0;
		for (x = 0; x < MAXXDIM; x++) {
			for (y = 0; y < MAXYDIM; y++) {
				if (mark[x][y] == i) {
					gw = gw + in[x][y];
					n++;
				}
			}
		}

		gw = gw / n;

		for (x = 0; x < MAXXDIM; x++) {
			for (y = 0; y < MAXYDIM; y++) {
				if (mark[x][y] == i) {
					out[x][y] = int (gw);
				}
			}
		}


	}


}