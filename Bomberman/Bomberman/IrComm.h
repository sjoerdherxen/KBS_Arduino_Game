#include <Arduino.h>
#include "Game.h"

#ifndef IrComm_h
#define IrComm_h


void setupIR();
void IrSendByte(uint8_t byte);
uint8_t* dataRecieve();
#if IrCommUseTimer == 1
void sendTrippleStart(uint8_t b1, uint8_t b2, uint8_t b3);
uint8_t sendTrippleDone(uint8_t b1, uint8_t b2, uint8_t b3);
#else
void sendTripple(uint8_t b1, uint8_t b2, uint8_t b3);
#endif
uint8_t dataAvailable();


#endif