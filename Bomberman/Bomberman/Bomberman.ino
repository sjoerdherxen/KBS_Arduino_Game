#include <Arduino.h>
#include <MI0283QT9.h>

#include "BasicDisplay.h"



int main(void){
	init();

	DisplayOn();
	DisplayGame();

	while (1);

	return 0;
	// feature
}