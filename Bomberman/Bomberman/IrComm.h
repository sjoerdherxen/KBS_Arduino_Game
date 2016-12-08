#include <Arduino.h>

#ifndef IrComm_h
#define IrComm_h

void initIrSend();
void IrSendByte(uint8_t byte);
uint8_t* dataRecieve();
void SendUpdateData(uint8_t playerlocation, uint16_t bomb);
void SendInitData(uint8_t seed);
void sendTripple(uint8_t b1, uint8_t b2, uint8_t b3);
uint8_t dataAvailable();


#endif