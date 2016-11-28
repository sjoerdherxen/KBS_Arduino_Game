#include <Arduino.h>

#ifndef IrSend_h
#define IrSend_h

void initSendPin();
void IrSendByte(uint8_t byte);

#endif