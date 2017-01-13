#include "Textures.h"

/* the SD-card contains .bmp files (bitmapping files), in this function the files are opened
and used to draw on the lcd-screen */
void OpenBMPFile(char *name, int16_t x, int16_t y, MI0283QT9 *lcd)
{
#if UseTextures == 1
	File myFile;

	/* read buffer with a minimum size of (min. size = sizeof(BMP_DIPHeader) */
	uint8_t buf[40];
	int16_t w, h;

	/* the file is opened and read */
	myFile = SD.open(name, O_READ);
	if (myFile)
	{
		/* this skips the first information of the file, because it contains information that is useless to us */
		myFile.read(&buf, sizeof(BMP_Header));
		myFile.read(&buf, sizeof(BMP_DIPHeader));

		/* for every line in the file the for-loop is used */
		for (h = (y + 15); h >= y; h--)
		{
			/* for every pixel in the line the for-loop is used */
			for (w = x; w < (x + 16); w++)
			{
				/* this reads one pixel */
				myFile.read(&buf, 3);

				/* then that pixel is drawn on the lcd-screen, using the colors from the buffer
				and the location that is found in the two for-loops above */
				lcd->drawPixel(w, h, RGB(buf[2], buf[1], buf[0]));
			}
		}

		/* at the end the file is closed */
		myFile.close();
	}
#endif
}

/* function used to draw textures, the function gets an integer with the value of the texture that has to be drawn.
the function also gets x and y coordinates of where the texture has to be drawn, and the lcd-screen that is used */
void drawTexture(int texture, int16_t x, int16_t y, MI0283QT9 *lcd) {
#if UseTextures == 1
	/* switch case to determine which texture is selected */
	switch (texture) {
	case 1:
		/* texture of the bomb */
		OpenBMPFile(files[1], x, y, lcd);
		break;
	case 2:
		/* texture of the crate */
		OpenBMPFile(files[2], x, y, lcd);
		break;
	case 3:
		/* texture of the static block */
		OpenBMPFile("static1.bmp", x, y, lcd);
		break;

	case 5:
		/* texture of player 1 */
		OpenBMPFile(files[5], x, y, lcd);
		break;
	case 6:
		/* texture of player 2 */
		OpenBMPFile(files[6], x, y, lcd);
		break;
	case 7:
		/* texture of player 3 */
		OpenBMPFile("Player3.bmp", x, y, lcd);
		break;
	case 8:
		/* texture of player 4 */
		OpenBMPFile("Player4.bmp", x, y, lcd);
		break;

	case 10:
		/* first texture of the explosion */
		OpenBMPFile("Ex1.bmp", x, y, lcd);
		break;
	case 11:
		/* second texture of the explosion */
		OpenBMPFile("Ex2.bmp", x, y, lcd);
		break;
	case 12:
		/* third texture of the explosion */
		OpenBMPFile("Ex3.bmp", x, y, lcd);
		break;

	case 14:
		/* texture of the "Extra Points" power-up */
		OpenBMPFile("EPPU.bmp", x, y, lcd);
		break;
	case 15:
		/* texture of the "Extra Range" power-up */
		OpenBMPFile("ERPU.bmp", x, y, lcd);
		break;
	case 16:
		/* texture of the "More Bombs" power-up */
		OpenBMPFile("MBPU.bmp", x, y, lcd);
		break;
	case 17:
		/* texture of the "Walk Faster" power-up */
		OpenBMPFile("WFPU.bmp", x, y, lcd);
		break;
	}
#endif
}

/* loadTextures() is used to load the textures that are on the
SD-card onto the Arduino, to use in further programs */
uint8_t loadTextures() {
#if UseTextures == 1
	if (!SD.begin(4))
	{
		return 0;
	}
	return 1; 
#else 
	return 0;
#endif
}
