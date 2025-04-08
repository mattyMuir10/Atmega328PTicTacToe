/*
 * AI.h
 *
 * Created: 2025-04-07 4:28:23 PM
 *  Author: mattm
 */


#ifndef AI_H_
#define AI_H_

#include <stdint.h>

#define TOPLEFTBOARDSPACE 0
#define TOPMIDDLEBOARDSPACE 1
#define TOPRIGHTBOARDSPACE 2
#define MIDDLELEFTBOARDSPACE 3
#define MIDDLEMIDDLEBOARDSPACE 4
#define MIDDLERIGHTBOARDSPACE 5
#define BOTTOMLEFTBOARDSPACE 6
#define BOTTOMMIDDLEBOARDSPACE 7
#define BOTTOMRIGHTBOARDSPACE 8

#define TOPLEFTUINT16 1
#define TOPMIDDLEUINT16 2
#define TOPRIGHTUINT16 4
#define MIDDLELEFTUINT16 8
#define MIDDLEMIDDLEUINT16 16
#define MIDDLERIGHTUINT16 32
#define BOTTOMLEFTUINT16 64
#define BOTTOMMIDDLEUINT16 128
#define BOTTOMRIGHTUINT16 256

#define legalSpaces 0b0000000111111111

struct BoardState {
	uint16_t teamOneOccupation;
	uint16_t teamTwoOccupation;
};

uint8_t MiniMaxFindMove(uint8_t firstMove, uint8_t currentTeam, BoardState* currentBoard, uint8_t prevMove, uint8_t currentDepth);
uint8_t CheckForVictory(BoardState* currentBoard, uint8_t team, uint8_t recentMove);
uint8_t CheckForAllSpacesFilled(BoardState* currentBoard);
void MakeMove(BoardState* currentBoard, uint8_t team, uint8_t space);
void UnMakeMove(BoardState* currentBoard, uint8_t team, uint8_t space);
uint8_t GetTopMove(uint16_t blueBoard, uint16_t yellowBoard, uint8_t currentTeam);





#endif /* AI_H_ */