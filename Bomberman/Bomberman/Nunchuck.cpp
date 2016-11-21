#include "Nunchuck.h"

uint8_t nunchuck_buf[6];   // array to store nunchuck data,
uint8_t nunchuckdata = 0x00;
// Uses port C (analog in) pins as power & ground for Nunchuck
void Nunchuck_setpowerpins()
{
#define pwrpin PORTC3
#define gndpin PORTC2
	DDRC |= _BV(pwrpin) | _BV(gndpin);
	PORTC &= ~_BV(gndpin);
	PORTC |= _BV(pwrpin);
	delay(100);  // wait for things to stabilize        
}

// initialize the I2C system, join the I2C bus,
// and tell the nunchuck we're talking to it
void Nunchuck_init()
{
	Wire.begin();	                // join i2c bus as master
	Wire.beginTransmission(0x52);	// transmit to device 0x52
	Wire.write(0x40);		// sends memory address
	Wire.write(0x00);		// sends sent a zero.  
	Wire.endTransmission();	// stop transmitting
}

// Send a request for data to the nunchuck
// was "send_zero()"
void Nunchuck_send_request()
{
	Wire.beginTransmission(0x52);	// transmit to device 0x52
	Wire.write(0x00);		// sends one byte
	Wire.endTransmission();	// stop transmitting
}

// Receive data back from the nunchuck, 
int Nunchuck_get_data()
{
#define MIN 80
#define MAX 180
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
		uint8_t nunchuckdata = 0xC0;
		int joy_x_axis = nunchuck_buf[0];
		int joy_y_axis = nunchuck_buf[1];


		// byte nunchuck_buf[5] contains bits for z and c buttons
		// it also contains the least significant bits for the accelerometer data
		// so we have to check each bit of byte outbuf[5]
		if (joy_y_axis > MAX) {
			nunchuckdata = 1;
		}
		else if (joy_y_axis < MIN) {
			nunchuckdata = 3;
		}
		else if (joy_x_axis > MAX) {
			nunchuckdata = 2;
		}
		else if (joy_x_axis < MIN) {
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