#include <Wire.h>
#include <Arduino.h>
#include <SPI.h>
#include <Arduino.h>
#include <digitalWriteFast.h>
#include <GraphicsLib.h>
#include <MI0283QT2.h>
#include <MI0283QT9.h>
#include <DisplaySPI.h>
#include <DisplayI2C.h>
#include <SD.h>
#include <BMPheader.h>

#ifndef Textures_h
#define Textures_h

/* function used to open a bitmapping file */
void OpenBMPFile(char *texture, int16_t x, int16_t y, MI0283QT9 *lcd);

/* function used to draw a texture on the lcd-screen */
void drawTexture(int texture, int16_t x, int16_t y, MI0283QT9 *lcd);

/* UNUSED */
void OpenBMPFile(char *name);

/* function used to load textures from the SD-card */
uint8_t loadTextures();

#endif