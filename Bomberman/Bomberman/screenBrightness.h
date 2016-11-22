#include <Arduino.h>
#include <wiring_private.h>

#ifndef screenBrightness_h
#define screenBrightness_h

/* used to setup the potentiometer, sets the input port A0 open */
void setupPot();

/*  needs a pin to function, pin A0 (pin 14) is used in our case it returns a 16 bit value */
uint16_t analogReadPot(uint8_t pin);

/* used in the main program as value of the brightness of the lcd screen */
int setBrightness();

#endif