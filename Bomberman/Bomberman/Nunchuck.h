#include <Wire.h>
#include <Arduino.h>

#ifndef Nunchuck
#define Nunchuck

void Nunchuck_setpowerpins();
void Nunchuck_init();
void Nunchuck_send_request();
int Nunchuck_get_data();
void Nunchuck_print_data();
char Nunchuk_decode_byte(char x);

#endif
