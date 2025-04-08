/*
 * TicTacToeGame.h
 *
 * Created: 2025-04-02 3:32:59 PM
 *  Author: mattm
 */ 


#ifndef TICTACTOEGAME_H_
#define TICTACTOEGAME_H_

#include <stdint.h>

#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SwitchesHandler.h"
#include "GamePlayHandler.h"


void StartTicTacToe(void);
void ChooseGame(uint8_t* onePlayer, uint8_t* goingFirst);
void StartGame(uint8_t onePlayer, uint8_t goingFirst);
void ResetGame(void);
void Initialize(void);




/*
1. start tictactoe
2. select one or two player and going first or second
3. make moves
4. check for win after each move
5. if win, restart game to 2. 






*/






#endif /* TICTACTOEGAME_H_ */