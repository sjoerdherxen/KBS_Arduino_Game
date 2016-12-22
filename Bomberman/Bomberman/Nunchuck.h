#include <Wire.h>
#include <Arduino.h>

#ifndef Nunchuck
#define Nunchuck

/* function used to setup the nunchuck */
void setupNunchuck();

/* function used to send a request to the nunchuck */
void Nunchuck_send_request();

/* function used to receive data from the nunchuck,
returns an 8-bit integer */
uint8_t Nunchuck_get_data();

/* function used to print the data received from the nunchuck,
needs an 8-bit integer to function */
void Nunchuck_print_data(uint8_t data);

/* function used to decode data received from the nunchuck,
returns a character and needs a character to function */
char Nunchuk_decode_byte(char x);

#endif
