/*
BMP-File Demonstration
*/

#include "Textures.h"


void OpenBMPFile(char *name, int16_t x, int16_t y, MI0283QT9 *lcd)
{
	File myFile;
	uint8_t buf[40]; //read buf (min. size = sizeof(BMP_DIPHeader))
	int16_t w, h;

	//open file
	myFile = SD.open(name, O_READ);
	if (myFile)
	{
		myFile.read(&buf, sizeof(BMP_Header));
		myFile.read(&buf, sizeof(BMP_DIPHeader));
		for (h = (y + 15); h >= y; h--) //for every line
		{
			for (w = x; w < (x + 16); w++) //for every pixel in line
			{
				myFile.read(&buf, 3);
				lcd->drawPixel(w, h, RGB(buf[2], buf[1], buf[0]));
			}
		}

		myFile.close();
	}
}

void LoadBMPFile(char *name, int texture) {
	//files[texture] = SD.open(name);
}

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

uint8_t loadTextures() {
	if (!SD.begin(4))
	{
		//lcd->drawText(5, 5, "Kan SD kaart niet lezen", RGB(0, 0, 0), RGB(255, 255, 255), 1);
		return 0;
	}/*
	for (uint8_t i = 0; i < 10; i++){
		drawTexture(i);
	}*/
	return 1;
}

/*Some testing commands to test if all textures load in properly:
drawTexture(1, 0, 0);
drawTexture(2, 16, 0);
drawTexture(3, 32, 0);

drawTexture(5, 48, 0);
drawTexture(6, 64, 0);
drawTexture(7, 80, 0);
drawTexture(8, 96, 0);

drawTexture(10, 112, 0);
drawTexture(11, 128, 0);
drawTexture(12, 144, 0);

drawTexture(14, 160, 0);
drawTexture(15, 176, 0);
drawTexture(16, 192, 0);
drawTexture(17, 208, 0);
*/