/*
 * GameplayHandler.cpp
 *
 * Created: 2025-04-02 4:45:43 PM
 *  Author: mattm
 */ 
#include "GamePlayHandler.h"
#include "SwitchesHandler.h"
#include "AI.h"

//occupied states for the board for both colors
static uint16_t blueBoardState = 0;
static uint16_t yellowBoardState = 0;

//the current bits in the shift register
static uint8_t currentShiftRegisterValue = 0;

//struct containing info on port and pin controlling that spot on the board
struct boardSpotInfo {
	volatile uint8_t* inputOutputPort;
	volatile uint8_t* port;
	uint8_t pin;
	uint8_t onShift;
	};
	
//arrays for both colors and info on port and pin for board position
static boardSpotInfo blueBoardInfo[9];
static boardSpotInfo yellowBoardInfo[9];

//initialize the game
void InitGameplay(){
	CreateBoardStateArrays();
	ResetShiftRegister();
	ResetBoards();
	SetRegisters();
}	

//reset game components to be played again
void ResetGameStuff(void){
	ResetShiftRegister();
	ResetBoards();
}

//set input output registers for ones being used
void SetRegisters(void){
	//set as input for blue and yellow winning pins and turn on internal pullups
	*BLUEWINDDPORT &= ~(1 << BLUEWINPIN);
	*YELLOWWINDDPORT &= ~(1 << YELLOWWINPIN);
	
	*BLUEWINPORT |= (1 << BLUEWINPIN);
	*YELLOWWINPORT |= (1 << YELLOWWINPIN);
	
	//set shift register controlling pins to output
	*SHIFTREGISTERCLKDDPORT |= (1 << SHIFTREGISTERCLKPIN);
	*SHIFTREGISTERDATADDPORT |= (1 << SHIFTREGISTERDATAPIN);
	*SHIFTREGISTERLATCHDDPORT |= (1 << SHIFTREGISTERLATCHPIN);
	
	
	//set as output all of the pins for board spots - check to make sure not on the shift register
	for (int i = 0; i < 9; i++){
		if (blueBoardInfo[i].onShift == 0){
			*blueBoardInfo[i].inputOutputPort |= (1 << blueBoardInfo[i].pin);
		}
	}
		
		
		for (int i = 0; i < 9; i++){
			if (yellowBoardInfo[i].onShift ==0){
				*yellowBoardInfo[i].inputOutputPort |= (1 << yellowBoardInfo[i].pin);
			}
		}
	}

//reset the shift register with 8 0s
void ResetShiftRegister(void){
	for (int i = 7; i >= 0; i--){
			
				*SHIFTREGISTERDATAPORT &= ~(1 << SHIFTREGISTERDATAPIN);
			
			*SHIFTREGISTERCLKPORT |= (1 << SHIFTREGISTERCLKPIN);
			*SHIFTREGISTERCLKPORT &= ~(1 << SHIFTREGISTERCLKPIN);
		}
		*SHIFTREGISTERLATCHPORT |= (1 << SHIFTREGISTERLATCHPIN);
		*SHIFTREGISTERLATCHPORT &= ~(1 << SHIFTREGISTERLATCHPIN);
		currentShiftRegisterValue = 0;
}

//reset the board to be empty
void ResetBoards(){
	blueBoardState = 0;
	yellowBoardState = 0;
	for (int i = 0; i < 9; i++){
		if (blueBoardInfo[i].onShift == 0){
			*blueBoardInfo[i].port &= ~(1 << blueBoardInfo[i].pin);
		}
	}
	for (int i = 0; i < 9; i++){
		if (yellowBoardInfo[i].onShift == 0){
			*yellowBoardInfo[i].port &= ~(1 << yellowBoardInfo[i].pin);
		}
	}
}



//set up the arrays which contain the structs of port and pin for each board position
void CreateBoardStateArrays(void){
	
	blueBoardInfo[0].port = TOPLEFTBLUEPORT;
	blueBoardInfo[0].pin = TOPLEFTBLUEPIN;
	blueBoardInfo[0].onShift = TOPLEFTBLUEONSHIFT;
	blueBoardInfo[0].inputOutputPort = TOPLEFTBLUEDDPORT;
	
	blueBoardInfo[1].port = TOPMIDDLEBLUEPORT;
	blueBoardInfo[1].pin = TOPMIDDLEBLUEPIN;
	blueBoardInfo[1].onShift = TOPMIDDLEBLUEONSHIFT;
	blueBoardInfo[1].inputOutputPort = TOPMIDDLEBLUEDDPORT;
	
	blueBoardInfo[2].port = TOPRIGHTBLUEPORT;
	blueBoardInfo[2].pin = TOPRIGHTBLUEPIN;
	blueBoardInfo[2].onShift = TOPRIGHTBLUEONSHIFT;
	blueBoardInfo[2].inputOutputPort = TOPRIGHTBLUEDDPORT;
	
	blueBoardInfo[3].port = MIDDLELEFTBLUEPORT;
	blueBoardInfo[3].pin = MIDDLELEFTBLUEPIN;
	blueBoardInfo[3].onShift = MIDDLELEFTBLUEONSHIFT;
	blueBoardInfo[3].inputOutputPort = MIDDLELEFTBLUEDDPORT;
	
	blueBoardInfo[4].port = MIDDLEMIDDLEBLUEPORT;
	blueBoardInfo[4].pin = MIDDLEMIDDLEBLUEPIN;
	blueBoardInfo[4].onShift = MIDDLEMIDDLEBLUEONSHIFT;
	blueBoardInfo[4].inputOutputPort = MIDDLEMIDDLEBLUEDDPORT;
	
	blueBoardInfo[5].port = MIDDLERIGHTBLUEPORT;
	blueBoardInfo[5].pin = MIDDLERIGHTBLUEPIN;
	blueBoardInfo[5].onShift = MIDDLERIGHTBLUEONSHIFT;
	blueBoardInfo[5].inputOutputPort = MIDDLERIGHTBLUEDDPORT;
	
	blueBoardInfo[6].port = BOTTOMLEFTBLUEPORT;
	blueBoardInfo[6].pin = BOTTOMLEFTBLUEPIN;
	blueBoardInfo[6].onShift = BOTTOMLEFTBLUEONSHIFT;
	blueBoardInfo[6].inputOutputPort = BOTTOMLEFTBLUEDDPORT;
	
	blueBoardInfo[7].port = BOTTOMMIDDLEBLUEPORT;
	blueBoardInfo[7].pin = BOTTOMMIDDLEBLUEPIN;
	blueBoardInfo[7].onShift = BOTTOMMIDDLEBLUEONSHIFT;
	blueBoardInfo[7].inputOutputPort = BOTTOMMIDDLEBLUEDDPORT;
	
	blueBoardInfo[8].port = BOTTOMRIGHTBLUEPORT;
	blueBoardInfo[8].pin = BOTTOMRIGHTBLUEPIN;
	blueBoardInfo[8].onShift = BOTTOMRIGHTBLUEONSHIFT;
	blueBoardInfo[8].inputOutputPort = BOTTOMRIGHTBLUEDDPORT;
	
	
	yellowBoardInfo[0].port = TOPLEFTYELLOWPORT;
	yellowBoardInfo[0].pin = TOPLEFTYELLOWPIN;
	yellowBoardInfo[0].onShift = TOPLEFTYELLOWONSHIFT;
	yellowBoardInfo[0].inputOutputPort = TOPLEFTYELLOWDDPORT;
	
	yellowBoardInfo[1].port = TOPMIDDLEYELLOWPORT;
	yellowBoardInfo[1].pin = TOPMIDDLEYELLOWPIN;
	yellowBoardInfo[1].onShift = TOPMIDDLEYELLOWONSHIFT;
	yellowBoardInfo[1].inputOutputPort = TOPMIDDLEYELLOWDDPORT;
	
	yellowBoardInfo[2].port = TOPRIGHTYELLOWPORT;
	yellowBoardInfo[2].pin = TOPRIGHTYELLOWPIN;
	yellowBoardInfo[2].onShift = TOPRIGHTYELLOWONSHIFT;
	yellowBoardInfo[2].inputOutputPort = TOPRIGHTYELLOWDDPORT;
	
	yellowBoardInfo[3].port = MIDDLELEFTYELLOWPORT;
	yellowBoardInfo[3].pin = MIDDLELEFTYELLOWPIN;
	yellowBoardInfo[3].onShift = MIDDLELEFTYELLOWONSHIFT;
	yellowBoardInfo[3].inputOutputPort = MIDDLELEFTYELLOWDDPORT;
	
	yellowBoardInfo[4].port = MIDDLEMIDDLEYELLOWPORT;
	yellowBoardInfo[4].pin = MIDDLEMIDDLEYELLOWPIN;
	yellowBoardInfo[4].onShift = MIDDLEMIDDLEYELLOWONSHIFT;
	yellowBoardInfo[4].inputOutputPort = MIDDLEMIDDLEYELLOWDDPORT;
	
	yellowBoardInfo[5].port = MIDDLERIGHTYELLOWPORT;
	yellowBoardInfo[5].pin = MIDDLERIGHTYELLOWPIN;
	yellowBoardInfo[5].onShift = MIDDLERIGHTYELLOWONSHIFT;
	yellowBoardInfo[5].inputOutputPort = MIDDLERIGHTYELLOWDDPORT;
	
	yellowBoardInfo[6].port = BOTTOMLEFTYELLOWPORT;
	yellowBoardInfo[6].pin = BOTTOMLEFTYELLOWPIN;
	yellowBoardInfo[6].onShift = BOTTOMLEFTYELLOWONSHIFT;
	yellowBoardInfo[6].inputOutputPort = BOTTOMLEFTYELLOWDDPORT;
	
	yellowBoardInfo[7].port = BOTTOMMIDDLEYELLOWPORT;
	yellowBoardInfo[7].pin = BOTTOMMIDDLEYELLOWPIN;
	yellowBoardInfo[7].onShift = BOTTOMMIDDLEYELLOWONSHIFT;
	yellowBoardInfo[7].inputOutputPort = BOTTOMMIDDLEYELLOWDDPORT;
	
	yellowBoardInfo[8].port = BOTTOMRIGHTYELLOWPORT;
	yellowBoardInfo[8].pin = BOTTOMRIGHTYELLOWPIN;
	yellowBoardInfo[8].onShift = BOTTOMRIGHTYELLOWONSHIFT;
	yellowBoardInfo[8].inputOutputPort = BOTTOMRIGHTYELLOWDDPORT;
	
	
	
}

//run a tic tac toe game with selected settings
void PlayGame(uint8_t onePlayer, uint8_t goingFirst){
	uint8_t currentTeam = 0;
	//will add some more logic and stuff if ai is playing - for now just pretend they wont
	while (1){
		
		if (onePlayer){
			//_delay_ms(5000);
			if (goingFirst && currentTeam == 1){
				//_delay_ms(5000);
				DoTurn(currentTeam, 0);
			}
			else if(!goingFirst && currentTeam ==0){
				//_delay_ms(5000);
				DoTurn(currentTeam, 0);
			}
			else{
				DoTurn(currentTeam, 1);
			}
		}
		else{
			DoTurn(currentTeam, 1);
		}
		uint8_t isWon = CheckForWin(currentTeam);
		if (isWon){
			_delay_ms(5000);
			return;
		}
		else if (CheckForDraw()){
			_delay_ms(5000);
			return;
		}
		if (currentTeam == 0){
			currentTeam = 1;
			//dont switch team right now while only blue is available
		}
		else{
			currentTeam = 0;
		}
	}
}



//do a turn for given team and whether human or not
void DoTurn(uint8_t team, uint8_t humanPlayer){
	uint16_t currentBoardSpot = 0;
	//info on currently selected spot
	/*
	volatile uint8_t* portOfCurrentSelection = 0;
	uint8_t pinOfCurrentSelection = 0;
	uint8_t currentSelectionIsOnShiftRegister = 0;
	*/
	if (humanPlayer){
		if (team == 0){
			uint8_t finished = 0;
			while(finished == 0){				
				if (currentBoardSpot > 8){
					currentBoardSpot = 0;
				}			
				//check if current location on board is already occupied and skip it until landing on suitable location
				
				while (((blueBoardState & (1 << currentBoardSpot)) != 0) || ((yellowBoardState & (1 << currentBoardSpot)) != 0)){
						//go to next board spot and reset to zero if past the last spot
						currentBoardSpot ++;
						if (currentBoardSpot > 8){
							currentBoardSpot = 0;
						}
				}
				//wait to select this current board location for move or go to next location
				//blink currently selected led while waiting to show which is selection
				uint8_t choice = 2;
				uint8_t isCurrentlyOn = 0;
				while (choice == 2){
					if (isCurrentlyOn == 0){
						isCurrentlyOn = 1;
					}
					else{
						isCurrentlyOn = 0;
					}
					SetPinOnPort(blueBoardInfo[currentBoardSpot].port, blueBoardInfo[currentBoardSpot].pin, isCurrentlyOn, blueBoardInfo[currentBoardSpot].onShift);
					choice = WaitForEitherSwitchPress(1000);
					
				}
				_delay_ms(1);
				SetPinOnPort(blueBoardInfo[currentBoardSpot].port, blueBoardInfo[currentBoardSpot].pin, 0, blueBoardInfo[currentBoardSpot].onShift);
				//go to next spot if click left button
				if (choice == 0){
					currentBoardSpot += 1;
				}
				//choose this spot if clicked right button
				else if (choice == 1){
					finished = 1;
				}
				//an error somehow
				else{
					
				}
				_delay_ms(1);

			}
			//set the pin and add to the board state
			SetPinOnPort(blueBoardInfo[currentBoardSpot].port, blueBoardInfo[currentBoardSpot].pin, 1, blueBoardInfo[currentBoardSpot].onShift);
			SetBoardLocation(1, currentBoardSpot, 1);
			_delay_ms(1);
			
		}
		else{
			uint8_t finished = 0;
			while(finished == 0){
				if (currentBoardSpot > 8){
					currentBoardSpot = 0;
				}
				//check if current location on board is already occupied and skip it until landing on suitable location
				
				while (((blueBoardState & (1 << currentBoardSpot)) != 0) || ((yellowBoardState & (1 << currentBoardSpot)) != 0)){
					//go to next board spot and reset to zero if past the last spot
					currentBoardSpot ++;
					if (currentBoardSpot > 8){
						currentBoardSpot = 0;
					}
				}
				//wait to select this current board location for move or go to next location
				//blink currently selected led while waiting to show which is selection
				uint8_t choice = 2;
				uint8_t isCurrentlyOn = 0;
				while (choice == 2){
					if (isCurrentlyOn == 0){
						isCurrentlyOn = 1;
					}
					else{
						isCurrentlyOn = 0;
					}
					SetPinOnPort(yellowBoardInfo[currentBoardSpot].port, yellowBoardInfo[currentBoardSpot].pin, isCurrentlyOn, yellowBoardInfo[currentBoardSpot].onShift);
					choice = WaitForEitherSwitchPress(1000);
					
				}
				_delay_ms(1);
				SetPinOnPort(yellowBoardInfo[currentBoardSpot].port, yellowBoardInfo[currentBoardSpot].pin, 0, yellowBoardInfo[currentBoardSpot].onShift);
				//go to next spot if click left button
				if (choice == 0){
					currentBoardSpot += 1;
				}
				//choose this spot if clicked right button
				else if (choice == 1){
					finished = 1;
				}
				//an error somehow
				else{
					
				}
				_delay_ms(1);

			}
			//set the pin and add to the board state
			SetPinOnPort(yellowBoardInfo[currentBoardSpot].port, yellowBoardInfo[currentBoardSpot].pin, 1, yellowBoardInfo[currentBoardSpot].onShift);
			SetBoardLocation(0, currentBoardSpot, 1);
			_delay_ms(1);
		}
	}
	else{
		//run the algorithim to find top move for ai and then make the found move
		uint8_t move = GetTopMove(blueBoardState, yellowBoardState, team);
		if (team == 0){
			SetPinOnPort(blueBoardInfo[move].port, blueBoardInfo[move].pin, 1, blueBoardInfo[move].onShift);
			SetBoardLocation(1, move, 1);
		}
		else{
				SetPinOnPort(yellowBoardInfo[move].port, yellowBoardInfo[move].pin, 1, yellowBoardInfo[move].onShift);
				SetBoardLocation(0, move, 1);
		}
		
	}
}

//set board location to occupied
void SetBoardLocation(uint8_t isBlue, uint8_t square, uint8_t occupied){
	if (isBlue != 0){
		if (occupied != 0){
				blueBoardState |= (1 << square);
		}
		else{
			blueBoardState &= ~(1 << square);
		}
	}
	else{
		if (occupied != 0){
			yellowBoardState |= (1 << square);
		}
		else{
			yellowBoardState &= ~(1 << square);
		}
	}
}

//set the given port and pin to on/off
void SetPinOnPort(volatile uint8_t* port, uint8_t pin, uint8_t turnOn, uint8_t onShift){
	if (onShift == 0){
		if (turnOn != 0){
			*port |= (1 << pin);
		}
		else{
			*port &= ~(1 << pin);
		}
	}
	//use the pin which is pin on shift register to update the register
	else{
		
		if (turnOn != 0){
			currentShiftRegisterValue |= (1 << pin);
		}
		else{
			currentShiftRegisterValue &= ~(1 << pin);
		}
		for (int i = 7; i >= 0; i--){
			if (((currentShiftRegisterValue) & (1 << i)) != 0){
				*SHIFTREGISTERDATAPORT |= (1 << SHIFTREGISTERDATAPIN);
			}
			else{
				*SHIFTREGISTERDATAPORT &= ~(1 << SHIFTREGISTERDATAPIN);
				//*SHIFTREGISTERDATAPORT = 0b00000000;
			}
			*SHIFTREGISTERCLKPORT |= (1 << SHIFTREGISTERCLKPIN);
			*SHIFTREGISTERCLKPORT &= ~(1 << SHIFTREGISTERCLKPIN);
		}
		*SHIFTREGISTERLATCHPORT |= (1 << SHIFTREGISTERLATCHPIN);
		*SHIFTREGISTERLATCHPORT &= ~(1 << SHIFTREGISTERLATCHPIN);
	}
	
}

//check if the board is full and therefore it is a draw
uint8_t CheckForDraw(){
	if ((legalSpaces & ~(blueBoardState | yellowBoardState)) == 0){
		return 1;
	}
	return 0;
}

//check if the given team has won
uint8_t CheckForWin(uint8_t team){
	if (team == 0){
		uint8_t hasWon = ((*BLUEWINREADREGISTER) & (1 << BLUEWINREADPIN));
		//gryffindor wins!
		
		if (hasWon == 0){
			return 1;
		}
	}
	else{
		uint8_t hasWon = ((*YELLOWWINREADREGISTER) & (1 << YELLOWWINREADPIN));
		//gryffindor wins!
		
		if (hasWon == 0){
			return 1;
		}
	}
	return 0;
}