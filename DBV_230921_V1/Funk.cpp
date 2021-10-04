#include <stdio.h>
#include <string.h>

int menu() //Menu-Funktion, gibt Möglichkeiten im Programm auf den Bildschirm aus
{
	int abfrage;
	printf("Menu: \nFolgendes kann getan werden : \n-Bild kopieren 1\n-Platzhalter 2\n-Bilder anzeigen 3\n-Bild speichern 4\n-Platzhalter 5\n-Programm benden 0\nIhre Eingabe:");
	scanf("%i", &abfrage);		//wartet auf die Eingabe einer Zahl
	return(abfrage);		//gibt die eingegebene Zahl an die Main-Funktion zurück
}