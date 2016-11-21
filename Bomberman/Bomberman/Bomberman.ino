#include <Arduino.h>
#include <MI0283QT9.h>
#include <Wire.h>

#include "BasicDisplay.h"
#include "Nunchuck.h"


uint8_t crates[127];

int main(void){
	init();
	Serial.begin(19200);
	Nunchuck_setpowerpins(); // use analog pins 2&3 as fake gnd & pwr
	Nunchuck_init(); // send the initilization handshake
	Serial.print("Finished setup\n");

	while (1) {
		Nunchuck_get_data();
		Nunchuck_print_data();
		delay(100);
	}
	return 0;

	//init();



	//for (int i = 0; i < 127; i++){
	//	crates[i] = 0xFF;
	//}
	//for (uint8_t i = 0; i < 127; i++){
	//	crates[i] = 0x02;
	//}

	//DisplayOn();
	//DisplayGame(crates, 0x00, 0xCC);

	//while (1){
	//	UpdateGame(crates, 0x01, 0xCC);
	//}

	//return 0;
	//// feature
}