#include <Arduino.h>

#ifndef IrComm_h
#define IrComm_h

void initIrSend();
void IrSendByte(uint8_t byte);
void dataRecieve();

#endif