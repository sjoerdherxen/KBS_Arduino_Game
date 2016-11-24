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

#ifndef Game_h
#define Game_h

uint8_t OpenBMPFile(char *file, int16_t x, int16_t y);
void drawTexture(int texture, int x, int y);
void loadTextures();

#endif