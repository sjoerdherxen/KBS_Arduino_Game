#include "Textures.h"

//open een bmp en teken deze op het scherm
void OpenBMPFile(char *name, int16_t x, int16_t y, MI0283QT9 *lcd)
{
	File myFile;
	uint8_t buf[40]; //read buf (min. size = sizeof(BMP_DIPHeader))
	int16_t w, h;

	//open file
	myFile = SD.open(name, O_READ);
	if (myFile)
	{
		// skip eerste informatie van een bestand // standaard info
		myFile.read(&buf, sizeof(BMP_Header));
		myFile.read(&buf, sizeof(BMP_DIPHeader));
		for (h = (y + 15); h >= y; h--) //for every line
		{
			for (w = x; w < (x + 16); w++) //for every pixel in line
			{
				myFile.read(&buf, 3); //lees 1 pixel
				lcd->drawPixel(w, h, RGB(buf[2], buf[1], buf[0])); // teken de pixel
			}
		}

		myFile.close();
	}
}

// testcode
void LoadBMPFile(char *name, int texture){
	//files[texture] = SD.open(name);
}

// teken een texture op basis van int waarde 
void drawTexture(int texture, int16_t x, int16_t y, MI0283QT9 *lcd) {
	switch (texture) {
	case 1:
		OpenBMPFile("Bomb.bmp", x, y, lcd);
		break;
	case 2:
		OpenBMPFile("Crate1.bmp", x, y, lcd);
		break;
	case 3:
		OpenBMPFile("static1.bmp", x, y, lcd);
		break;

	case 5:
		OpenBMPFile("Player1.bmp", x, y, lcd);
		break;
	case 6:
		OpenBMPFile("Player2.bmp", x, y, lcd);
		break;
	case 7:
		OpenBMPFile("Player3.bmp", x, y, lcd);
		break;
	case 8:
		OpenBMPFile("Player4.bmp", x, y, lcd);
		break;

	case 10:
		OpenBMPFile("Ex1.bmp", x, y, lcd);
		break;
	case 11:
		OpenBMPFile("Ex2.bmp", x, y, lcd);
		break;
	case 12:
		OpenBMPFile("Ex3.bmp", x, y, lcd);
		break;

	case 14:
		OpenBMPFile("EPPU.bmp", x, y, lcd);
		break;
	case 15:
		OpenBMPFile("ERPU.bmp", x, y, lcd);
		break;
	case 16:
		OpenBMPFile("MBPU.bmp", x, y, lcd);
		break;
	case 17:
		OpenBMPFile("WFPU.bmp", x, y, lcd);
		break;
	}
}

// sd kaart openen 
uint8_t loadTextures() {
	if (!SD.begin(4))
	{
		return 0;
	}
	return 1; 
}
