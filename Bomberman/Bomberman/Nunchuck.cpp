#include "Nunchuck.h"

/* array used to sdtore data from the nunchuck */
uint8_t nunchuck_buf[6];

/* function used to setup the nunchuck */
void Nunchuck_setpowerpins() {
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
}

/* function used to initialize the I2C protocol, join the I2C bus and
tell the nunchuck that we are talking to it */
void Nunchuck_init() {
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

/* function to send a request to the nunchuck */
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

/* function to receive data from the nunchuck */
uint8_t Nunchuck_get_data()
{

/* the minimal value is defined as 80 */
#define MIN 80

/* the maximum value is defined as 180 */
#define MAX 180

	/*  */
	int cnt = 0;
	Wire.requestFrom(0x52, 6);	// request data from nunchuck
	while (Wire.available()) {
		// receive byte as an integer
		nunchuck_buf[cnt] = Nunchuk_decode_byte(Wire.read());
		cnt++;
	}
	Nunchuck_send_request();  // send request for next data payload
	// If we recieved the 6 bytes, then go print them
	if (cnt >= 5) {
		uint8_t nunchuckdata = 0xC0; // default 0b1100 0000

		// byte nunchuck_buf[5] contains bits for z and c buttons
		// it also contains the least significant bits for the accelerometer data
		// so we have to check each bit of byte outbuf[5]
		if (nunchuck_buf[1] > MAX) {
			nunchuckdata = 1;
		}
		else if (nunchuck_buf[1] < MIN) {
			nunchuckdata = 3;
		}
		else if (nunchuck_buf[0] > MAX) {
			nunchuckdata = 2;
		}
		else if (nunchuck_buf[0] < MIN) {
			nunchuckdata = 4;
		}


		if ((nunchuck_buf[5] >> 0) & 1)
			nunchuckdata &= ~(1 << 6);
		if ((nunchuck_buf[5] >> 1) & 1)
			nunchuckdata &= ~(1 << 7);
		return nunchuckdata;
	}
	return 0; //failure
}

// Print the input data we have recieved
// accel data is 10 bits long
// so we read 8 bits, then we have to add
// on the last 2 bits.  That is why I
// multiply them by 2 * 2
void Nunchuck_print_data(uint8_t data)
{
	Serial.print(data, BIN);
	Serial.print("\r\n");  // newline
}

// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char Nunchuk_decode_byte(char x)
{
	x = (x ^ 0x17) + 0x17;
	return x;
}