//All functions are declared in the showLives.h headerfile
#include "showLives.h"									

//Initializes and declares lives to 0
extern uint8_t player1Lives;
extern uint8_t player2Lives;
//>=1 = true so that means the end of the game, 0 is false so not the end of the game
uint8_t ifEndGame = 0;
//Initializes and declares endOfGameTick to 0, endOfGameTcik will store the tick number
uint16_t endOfGameTick = 0;

//These are all the patterns for the leds, the first 3 bits are not used because the leds aren't connected to those digital ports
//A 1 stands for no output, a 0 stands for output.
const uint8_t patterns[] PROGMEM = {
	//These 6 patterns are for showing the lives
	0b11111111, 
	0b11111110,
	0b11111100,
	0b11111000,
	0b11110000,
	0b11100000,

	//These patterns are used to show to the endGame animation
	0b11111011,
	0b11110001,
	0b11100100,
	0b11101110,
};

//Setting up the expander for use
void setupExpander() {
	Wire.begin();
}

//Turns all leds on which is equal to having 5 lives
void startLives() {	
	//Begins transmission to adress 56
	Wire.beginTransmission(56);
	//Writes the pattern that corresponds to 0 to the adres
	Wire.write(pgm_read_byte(&patterns[5]));
	//Ends all transmissions
	Wire.endTransmission();
	//Sets lives to 5		
	player1Lives = 5;
}

//Activates the blinking and after that the amount of leds equal to the amount of lives is set.
void loseLife(uint16_t count) {				
	//Checks how many lives the player has and which leds have to be displayed
	if (player1Lives && player2Lives){
		//Begins transmission to adress 56, etc.												
		Wire.beginTransmission(56);
		//Writes the pattern that corresponds to lives to the adress, etc.
		Wire.write(pgm_read_byte(&patterns[player1Lives])); 
		//Ends all transmissions
		Wire.endTransmission();
		//When a player has 0 lives this part of the switch statement will be executed
	}else {
		//The endOfGameTick integer gets the current gametick value
		endOfGameTick = count;
		//Starts the gameOver animation and gives the current gametick value with it
		startGameOver(count);
		//ifEndGame gets the value 3, it is set to 3 so the animation will be executed 3 times
		ifEndGame = 3;									
	}
}

//This is the animation the game will execute when a player is dead
void endOfGame(uint16_t count) {
	//If ifEnGame is >=1 this part of the code will be executed, every time this code is executed 
	//ifEndGame gets - 1 so at some point it will reach 0 and this part of the code won't be executed anymore
	if (ifEndGame) {
		if (count == endOfGameTick) {
			//Begins transmission to adress 56, etc.		
			Wire.beginTransmission(56);
			//Writes the pattern that corresponds to 6 to the adres, etc
			Wire.write(pgm_read_byte(&patterns[6])); //xxoxx
			//Ends all transmissions
			Wire.endTransmission();
		}
		else if (count == endOfGameTick + 2) {
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[7])); //xooox
			Wire.endTransmission();
		}
		else if (count == endOfGameTick + 4) {
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[8])); //ooxoo
			Wire.endTransmission();
		}
		else if (count == endOfGameTick + 6) {
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[9])); //oxxxo
			Wire.endTransmission();
		}
		else if (count == endOfGameTick + 8) {
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[0])); //xxxxx
			Wire.endTransmission();
			//ifEndGame - 1
			ifEndGame--;
			//endOfGameTick gets the current tick value of the game
			endOfGameTick = count;
		}

		if(ifEndGame == 0){
		
			//This will start the GameOverMenu
			setGameover(1);
			uint8_t selectie = gameOverMenu();
			if (selectie == 1) {
			/*Rebooting the arduino to go to the main menu and clear the memory*/
				__asm volatile ("  jmp 0");
			}
			else if (selectie == 2) {
				DisplayKeyboard();
			}
			
		}
	}
}

//This part is a comment because it is not neccesary for the end product, when we have extra time we will probably implement it
/*
void blink(int check2) {								//Makes the leds blink when a live is lost
	for (int i = 0; i < 3; i++) {
		switch (check2) {								//Checks how many lives the player has and which leds have to be animated
		case 4:											//What the leds should look like: (o = on and x = off)
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[0]));
			Wire.endTransmission();						//ooooo
			_delay_ms(200);
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[5]));
			Wire.endTransmission();						//xxxxx
			_delay_ms(200);
			break;
		case 3:
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[1]));
			Wire.endTransmission();						//oooox
			_delay_ms(200);
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[5]));
			Wire.endTransmission();						//xxxxx
			_delay_ms(200);
			break;
		case 2:
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[2]));
			Wire.endTransmission();						//oooxx
			_delay_ms(200);
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[5]));
			Wire.endTransmission();						//xxxxx
			_delay_ms(200);
			break;
		case 1:
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[3]));
			Wire.endTransmission();						//ooxxx
			_delay_ms(200);
			Wire.beginTransmission(56);
			Wire.write(pgm_read_byte(&patterns[5]));
			Wire.endTransmission();						//xxxxx
			_delay_ms(200);
			break;
		}
	}
}
*/