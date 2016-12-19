#include <Arduino.h>

#ifndef IrComm_h
#define IrComm_h

void setupIR();
void IrSendByte(uint8_t byte);
uint8_t* dataRecieve();
void sendTripple(uint8_t b1, uint8_t b2, uint8_t b3);
uint8_t dataAvailable();


#endif