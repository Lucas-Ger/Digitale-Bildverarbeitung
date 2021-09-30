#include <stdio.h>
#include <string.h>

int menu() //Menu-Funktion, gibt Möglichkeiten im Programm auf den Bildschirm aus
{
	int abfrage;
	printf("Menu: \nFolgendes kann getan werden : \n-Datensatz eingeben 1\n-Daten anzeigen 2\n-Datensatz suchen 3\n-Datensatz loeschen oder bearbeiten 4\n-Daten speichern 5\n-Programm benden 0\nIhre Eingabe:");
	scanf("%i", &abfrage);		//wartet auf die Eingabe einer Zahl
	return(abfrage);		//gibt die eingegebene Zahl an die Main-Funktion zurück
}