#ifndef Textures_h
#define Textures_h

#include "Game.h"

#if UseTextures == 1
#include <Arduino.h>
#include <MI0283QT9.h>
#include <SD.h>
#include <BMPheader.h>
#endif

/* function used to open a bitmapping file */
void OpenBMPFile(char *texture, int16_t x, int16_t y, MI0283QT9 *lcd);

/* function used to draw a texture on the lcd-screen */
void drawTexture(int texture, int16_t x, int16_t y, MI0283QT9 *lcd);

/* function used to load textures from the SD-card */
uint8_t loadTextures();

#endif