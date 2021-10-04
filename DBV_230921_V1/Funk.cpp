#include <stdio.h>
#include <string.h>

int menu() //Menu-Funktion, gibt Möglichkeiten im Programm auf den Bildschirm aus
{
	int abfrage;
	printf("\nMenu: \nFolgendes kann getan werden : \n-Bild einlesen 1\n-Bild speichern 2\n-Bild anzeigen 3\n-Programm benden 0\nIhre Eingabe:");// \n-Platzhalter 4\n-Platzhalter 5 
	scanf("%i", &abfrage);		//wartet auf die Eingabe einer Zahl
	printf("\n");
	return(abfrage);		//gibt die eingegebene Zahl an die Main-Funktion zurück
}