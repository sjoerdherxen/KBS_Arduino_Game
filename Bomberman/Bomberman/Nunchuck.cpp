#include "Nunchuck.h"

/* array used to sdtore data from the nunchuck */
uint8_t nunchuck_buf[6];

/* function used to setup the nunchuck */
void setupNunchuck() {

/* PORTC3 (Analog 3) is used as the power-pin (pwrpin) */
#define pwrpin PORTC3

/* PORTC2 (Analog 2) is used as the ground-pin (gndpin) */
#define gndpin PORTC2

	/* DDR-register of the power-pin and ground-pin are set to INPUT */
	DDRC |= _BV(pwrpin) | _BV(gndpin);

	/* the ground-pin is set to LOW */
	PORTC &= ~_BV(gndpin);

	/* the power-pin is set to HIGH */
	PORTC |= _BV(pwrpin);

	/* this delay waits for the program to stabilize */
	delay(100);

	/* from here the code is used to initialize the I2C protocol, join the I2C bus and
	tell the nunchuck that we are talking to it */

	/* this sets begins the transmision by I2C, using the Wire library,
	the I2C bus is joined as a master */
	Wire.begin();

	/* the address of the nunchuck is 52 (this is the same for every white
	nunchuck), this address is send to all the divices connected by I2C,
	the nunchuck now knows that we are talking to it */
	Wire.beginTransmission(0x52);

	/* send the memory address to the nunchuck */
	Wire.write(0x40);

	/* send a zero to the nunchuck */
	Wire.write(0x00);

	/* stop the transmission */
	Wire.endTransmission();
}

/* function used to send a request to the nunchuck */
void Nunchuck_send_request()
{
	/* the address of the nunchuck is 52 (this is the same for every white
	nunchuck), this address is send to all the divices connected by I2C, 
	the nunchuck now knows that we are talking to it */
	Wire.beginTransmission(0x52);

	/* send a zero to the nunchuck */
	Wire.write(0x00);

	/* stop the transmission */
	Wire.endTransmission();
}

/* function used to receive data from the nunchuck */
uint8_t Nunchuck_get_data()
{

/* the minimal value is defined as 80, used for the nunchuck buffer */
#define MIN 80

/* the maximum value is defined as 180, used for the nunchuck buffer */
#define MAX 180

	/* an integer is made as a count variable */
	int cnt = 0;

	/* a data request is send to the nunchuck on address 52 */
	Wire.requestFrom(0x52, 6);

	/* while the nunchuck is sending data this loop keeps going */
	while (Wire.available()) {
		/* the data send by the nunchuck is decoded */
		nunchuck_buf[cnt] = Nunchuk_decode_byte(Wire.read());
		cnt++;
	}

	/* a new data request is send to the nunchuck for a new data payload */
	Nunchuck_send_request();

	/* when the counter hits 5, we received 6 bytes,
	then we can print the full data payload */
	if (cnt >= 5) {
		/* default data is set to binary 1100 0000 (0xC0) */
		uint8_t nunchuckdata = 0xC0;

		/* byte 6 of the nunchuck contains the bits for the Z- and C-buttons
		it also contains the least significant bits for the accelerometer,
		the next lines check if the received data contains this infromation */
		if (nunchuck_buf[1] > MAX) {
			nunchuckdata |= 1;
		}
		else if (nunchuck_buf[1] < MIN) {
			nunchuckdata |= 3;
		}
		else if (nunchuck_buf[0] > MAX) {
			nunchuckdata |= 2;
		}
		else if (nunchuck_buf[0] < MIN) {
			nunchuckdata |= 4;
		}

		/* Z-button */
		if ((nunchuck_buf[5] >> 0) & 1)
			nunchuckdata &= ~(1 << 6);

		/* C-button */
		if ((nunchuck_buf[5] >> 1) & 1)
			nunchuckdata &= ~(1 << 7);

		/* the function will return the nunchuck data */
		return nunchuckdata;
	}

	/* if the data request fails, the function returns a 0 */
	return 0;
}

/* the nunchuck uses a specific data format, this has to
be decoded to use in our functions, this function does that
(only needed if the regular wiimote driver is used) */
char Nunchuk_decode_byte(char x)
{
	x = (x ^ 0x17) + 0x17;
	return x;
}