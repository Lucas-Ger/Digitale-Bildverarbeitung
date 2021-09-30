#include"image-io.h"



void main()
{

	unsigned char bildein[MAXXDIM][MAXYDIM];

	readImage_ppm(bildein);

	viewImage_ppm();
}