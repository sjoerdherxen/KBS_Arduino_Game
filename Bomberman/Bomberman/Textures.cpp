/*
BMP-File Demonstration
*/

#include <Wire.h>
#include <SPI.h>
#include <digitalWriteFast.h>
#include <GraphicsLib.h>
#include <MI0283QT2.h>
#include <MI0283QT9.h>
#include <DisplaySPI.h>
#include <DisplayI2C.h>
#include <SD.h>
#include <BMPheader.h>


//Declare only one display !
// MI0283QT2 lcd;  //MI0283QT2 Adapter v1
MI0283QT9 lcd;  //MI0283QT9 Adapter v1
				// DisplaySPI lcd; //SPI (GLCD-Shield or MI0283QT Adapter v2)
				//DisplayI2C lcd; //I2C (GLCD-Shield or MI0283QT Adapter v2)


uint8_t OpenBMPFile(char *file, int16_t x, int16_t y)
{
	File myFile;
	uint8_t buf[40]; //read buf (min. size = sizeof(BMP_DIPHeader))
	BMP_Header *bmp_hd;
	BMP_DIPHeader *bmp_dip;
	int16_t width, height, w, h;
	uint8_t pad, result = 0;

	//open file
	myFile = SD.open(file);
	if (myFile)
	{
		result = 1;
		//BMP Header
		myFile.read(&buf, sizeof(BMP_Header));
		bmp_hd = (BMP_Header*)&buf[0];
		if ((bmp_hd->magic[0] == 'B') && (bmp_hd->magic[1] == 'M') && (bmp_hd->offset == 54))
		{
			result = 2;
			//BMP DIP-Header
			myFile.read(&buf, sizeof(BMP_DIPHeader));
			bmp_dip = (BMP_DIPHeader*)&buf[0];
			if ((bmp_dip->size == sizeof(BMP_DIPHeader)) && (bmp_dip->bitspp == 24) && (bmp_dip->compress == 0))
			{
				result = 3;
				//BMP Data (1. pixel = bottom left)
				width = bmp_dip->width;
				height = bmp_dip->height;
				pad = width % 4; //padding (line is multiply of 4)
				if ((x + width) <= lcd.getWidth() && (y + height) <= lcd.getHeight())
				{
					result = 4;
					lcd.setArea(x, y, x + width - 1, y + height - 1);
					for (h = (y + height - 1); h >= y; h--) //for every line
					{
						for (w = x; w < (x + width); w++) //for every pixel in line
						{
							myFile.read(&buf, 3);
							lcd.drawPixel(w, h, RGB(buf[2], buf[1], buf[0]));
						}
						if (pad)
						{
							myFile.read(&buf, pad);
						}
					}
				}
				else
				{
					lcd.drawText(x, y, "Pic out of screen!", RGB(0, 0, 0), RGB(255, 255, 255), 1);
				}
			}
		}

		myFile.close();
	}

	return result;
}

void drawTexture(int texture, int x, int y) {
	int picker, bomb, crate1, static1, player1, player2, player3, player4, explosion1, explosion2, explosion3, ep_powerup, er_powerup, mb_powerup, wf_powerup;
	picker = texture;
	switch (picker) {
	case 1:
		bomb = OpenBMPFile("Bomb.bmp", x, y);
		break;
	case 2:
		crate1 = OpenBMPFile("Crate1.bmp", x, y);
		break;
	case 3:
		static1 = OpenBMPFile("static1.bmp", x, y);
		break;

	case 5:
		player1 = OpenBMPFile("Player1.bmp", x, y);
		break;
	case 6:
		player2 = OpenBMPFile("Player2.bmp", x, y);
		break;
	case 7:
		player3 = OpenBMPFile("Player3.bmp", x, y);
		break;
	case 8:
		player4 = OpenBMPFile("Player4.bmp", x, y);
		break;

	case 10:
		explosion1 = OpenBMPFile("Ex1.bmp", x, y);
		break;
	case 11:
		explosion2 = OpenBMPFile("Ex2.bmp", x, y);
		break;
	case 12:
		explosion3 = OpenBMPFile("Ex3.bmp", x, y);
		break;

	case 14:
		ep_powerup = OpenBMPFile("EPPU.bmp", x, y);
		break;
	case 15:
		er_powerup = OpenBMPFile("ERPU.bmp", x, y);
		break;
	case 16:
		mb_powerup = OpenBMPFile("MBPU.bmp", x, y);
		break;
	case 17:
		wf_powerup = OpenBMPFile("WFPU.bmp", x, y);
		break;
	}
}

void loadTextures() {
	init();
	int x, i, y, j;
	//init Display
	lcd.begin();
	lcd.fillScreen(RGB(255, 255, 255));

	//init SD-Card
	x = lcd.drawText(5, 5, "Init SD-Card...", RGB(0, 0, 0), RGB(255, 255, 255), 1);
	if (!SD.begin(4)) //cs-pin=4
	{
		lcd.drawText(x, 5, "failed", RGB(0, 0, 0), RGB(255, 255, 255), 1);
		while (1);
	}

	//open windows bmp file (24bit RGB)
	x = lcd.drawText(5, 5, "Open File...", RGB(0, 0, 0), RGB(255, 255, 255), 1);
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