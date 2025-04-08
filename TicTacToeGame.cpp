/*
 * TicTacToeGame.cpp
 *
 * Created: 2025-04-02 3:33:14 PM
 *  Author: mattm
 */ 

#include "TicTacToeGame.h"
#include "GamePlayHandler.h"


static uint8_t onePlayer;
static uint8_t goingFirst;

//initialize different systems for tic tac toe
void Initialize(void){
	SwitchesInit();
	InitGameplay();
}

//the tic tac toe loop
void StartTicTacToe(void){
	Initialize();
	while (1)
	{
		ResetGame();
		ChooseGame(&onePlayer, &goingFirst);
		StartGame(onePlayer, goingFirst);
		//return;
	}
	
}

//use the switches to select what kind of game will be played
void ChooseGame(uint8_t* onePlayer, uint8_t* goingFirst){
	uint8_t chosen = 0;
	uint8_t current = 1;
	//go until button is chosen to select number of players
	//one player is the first selection(a zero)
	while(chosen == 0){
		//set the current selection to be lit up (top left blue led for second selection and top middle blue for first)
		if (current == 1){
			SetPinOnPort(TOPLEFTBLUEPORT, TOPLEFTBLUEPIN, 1, TOPLEFTBLUEONSHIFT);
			SetPinOnPort(TOPMIDDLEBLUEPORT, TOPMIDDLEBLUEPIN, 0, TOPMIDDLEBLUEONSHIFT);
		}
		else{
			
			SetPinOnPort(TOPLEFTBLUEPORT, TOPLEFTBLUEPIN, 0, TOPLEFTBLUEONSHIFT);
			SetPinOnPort(TOPMIDDLEBLUEPORT, TOPMIDDLEBLUEPIN, 1, TOPMIDDLEBLUEONSHIFT);
			
		}
		if (WaitForEitherSwitchPress(0) == 0){
			if (current == 0){
				current = 1;
			}
			else{
				current = 0;
			}
		}
		else{
			chosen = 1;
		}
	}
	*onePlayer = current;
	SetPinOnPort(TOPLEFTBLUEPORT, TOPLEFTBLUEPIN, 0, TOPLEFTBLUEONSHIFT);
	SetPinOnPort(TOPMIDDLEBLUEPORT, TOPMIDDLEBLUEPIN, 0, TOPMIDDLEBLUEONSHIFT);
	_delay_ms(1000);
	chosen = 0;
	current = 1;
	//go until button is chosen to select if blue is going first
	//blue going first is the first selection(a 1)
	while(chosen == 0){
		//set the current selection to be lit up (top left blue led for second selection and top middle blue for first)
		if (current == 1){
			SetPinOnPort(TOPLEFTBLUEPORT, TOPLEFTBLUEPIN, 1, TOPLEFTBLUEONSHIFT);
			SetPinOnPort(TOPMIDDLEBLUEPORT, TOPMIDDLEBLUEPIN, 0, TOPMIDDLEBLUEONSHIFT);
		}
		else{
			
			SetPinOnPort(TOPLEFTBLUEPORT, TOPLEFTBLUEPIN, 0, TOPLEFTBLUEONSHIFT);
			SetPinOnPort(TOPMIDDLEBLUEPORT, TOPMIDDLEBLUEPIN, 1, TOPMIDDLEBLUEONSHIFT);
			
		}
		if (WaitForEitherSwitchPress(0) == 0){
			if (current == 0){
				current = 1;
			}
			else{
				current = 0;
			}
		}
		else{
			chosen = 1;
		}
	}
	*goingFirst = current;
	SetPinOnPort(TOPLEFTBLUEPORT, TOPLEFTBLUEPIN, 0, TOPLEFTBLUEONSHIFT);
	SetPinOnPort(TOPMIDDLEBLUEPORT, TOPMIDDLEBLUEPIN, 0, TOPMIDDLEBLUEONSHIFT);
	_delay_ms(2000);
}

//start the game with specific settings
void StartGame(uint8_t onePlayer, uint8_t goingFirst){
	PlayGame(onePlayer, goingFirst);
}

//reset the game to original starting conditions
void ResetGame(void){
	ResetShiftRegister();
	ResetGameStuff();
}
