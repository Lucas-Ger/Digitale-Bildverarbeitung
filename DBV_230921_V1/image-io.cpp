#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "image-io.h"


int readImage_ppm(unsigned char img[MAXXDIM][MAXYDIM])
{
	char	imagedir[128]="C:\\bv\\";
	char	fname[30];
	FILE	*fpimage;
	char	z1[3];
	char    z2[24];
	int		xdim,ydim,type,i,j,x,y;
	int		r,g,b;

    char	dirbvdir[256]="dir C:\\bv\\*.ppm /B";

 	system(dirbvdir);

	printf("--------------------\nBild lesen::Dateiname (ohne '.ppm'!) : ");
	scanf("%s",&fname);
	strcat(fname,".ppm");
	strcat(imagedir,fname);

	if ((fpimage = fopen(imagedir,"r")) == NULL) {
		printf("Kann Datei <%s> nicht oeffnen!\n",imagedir);
		return 1;
	} else {
		// Header lesen ...
		fgets(z1,3,fpimage);
		fgets(z2,24,fpimage);
		fseek(fpimage, 26, SEEK_SET);
		fscanf(fpimage,"%d",&xdim);
		fscanf(fpimage,"%d",&ydim);
		fscanf(fpimage,"%d",&type);

		printf("xdim = %d\tydim = %d\ttype = %d\n",xdim,ydim,type);

		printf("Lese Daten aus Datei: <%s>\n",imagedir);
		// Bilddaten lesen ...
			for (i=0; i < MAXXDIM;i++){
				for (j=0; j < MAXYDIM;j++){
					fscanf(fpimage,"%d",&r);
					fscanf(fpimage,"%d",&g);
					fscanf(fpimage,"%d",&b);
					img[i][j] = g;
				}
			}
	}
	fclose(fpimage);

	return 0;
}

int writeImage_ppm(unsigned char img[MAXXDIM][MAXYDIM], int xdim, int ydim)
{
	char	imagedir[128]="C:\\bv\\";
	char	fname[30];
	FILE	*fpimage;
	int		i,j;
	int		type=255;

	char	dirbvdir[256]="dir C:\\bv\\*.ppm /B";

 	system(dirbvdir);

	printf("--------------------\nBild speichern::Dateiname (ohne '.ppm'!) : ");
	scanf("%s",&fname);
	strcat(fname,".ppm");
	strcat(imagedir,fname);

	if ((fpimage = fopen(imagedir,"w+")) == NULL) {
		printf("Kann Datei <%s> nicht oeffnen!\n",imagedir);
		return 1;
	} else {
		fprintf(fpimage,"P3\n");
		fprintf(fpimage,"# Created by IrfanView\n");
		fprintf(fpimage,"%d %d\n",xdim,ydim);
		fprintf(fpimage,"%d\n",type);
	
		for (i=0;i<xdim;i++){
			for (j=0;j<ydim;j++){
				fprintf(fpimage,"%d %d %d ",img[i][j], img[i][j], img[i][j]);
			}
		}
	}
	fclose(fpimage);

	return 0;
}

//
// es wird das externe Programm irfanview als Viewer verwendet
// die Bilder muessen im Verzeichnis C:\bv\ gespeichert sein!
// bei der 64bit Version des Viewers muss der Name der exe
// entsrpechend geändert werden!
//
void viewImage_ppm(void)
{
	char	imagedir[128]="C:\\bv\\";
	// char	viewer[256]="\"C:\\Program Files\\IrfanView\\i_view32.exe\" ";
	//char	viewer[256] = "\"C:\\Program Files\\IrfanView\\i_view64.exe\" ";
	char	viewer[256] = "\"C:\\bv\\\\i_view32.exe\" ";
	char	fname[30];
	char	dirbvdir[256]="dir C:\\bv\\*.ppm /B";

 
	system(dirbvdir);

	printf("--------------------\nBildanzeige::Dateiname (ohne '.ppm'!) : ");
	scanf("%s",&fname);
	strcat(fname,".ppm");
	strcat(imagedir,fname);
	strcat(viewer,imagedir);

	system(viewer);	 
}