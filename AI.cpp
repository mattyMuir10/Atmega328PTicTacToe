/*
 * AI.cpp
 *
 * Created: 2025-04-07 4:28:35 PM
 *  Author: mattm
 */

#include "AI.h"


static uint8_t topMove = 0;

//get the top move which was found by the minimax algorithm
uint8_t GetTopMove(uint16_t blueBoard, uint16_t yellowBoard, uint8_t currentTeam) {
	BoardState currentBoard{};
	currentBoard.teamOneOccupation = blueBoard;
	currentBoard.teamTwoOccupation = yellowBoard;
	MiniMaxFindMove(1, currentTeam, &currentBoard, 10, 10);
	return topMove;
}

//minimax algorithm which takes the current team to make the move, the current board situation, the previous move if there was one
uint8_t MiniMaxFindMove(uint8_t firstMove, uint8_t currentTeam, BoardState* currentBoard, uint8_t prevMove, uint8_t currentDepth) {
	//see which team is playing
	if (currentTeam == 0) {
		//if a move is made from previous iteration, make the move and check for victory for that team- return if win
		if (prevMove <= 8) {
			MakeMove(currentBoard, 1, prevMove);

			if (CheckForVictory(currentBoard, 1, prevMove)) {
				//second team has won
				if (prevMove <= 8) {
					UnMakeMove(currentBoard, 1, prevMove);
				}
				return 127 - currentDepth;
			}
			else if (CheckForAllSpacesFilled(currentBoard)) {
				//game is drawn with all spaces filled
				if (prevMove <= 8) {
					UnMakeMove(currentBoard, 1, prevMove);
				}
				return 128;
			}
		}

		//find the spaces left on the board which are the potential moves
		uint16_t spacesLeft = (legalSpaces) & ~(currentBoard->teamOneOccupation | currentBoard->teamTwoOccupation);

		//go through potential moves and find which is best
		//team one wants high values for move (> 128 is one victory, 128 is draw, < 128 is two victory)
		uint8_t currentBest = 0;
		uint8_t currentTopMove = 10;
		for (uint8_t i = 0; i < 9; i++) {
			if (((spacesLeft) & (1 << i)) != 0) {
				uint8_t thisMoveValue = MiniMaxFindMove(0, 1, currentBoard, i, currentDepth -1);
				if (thisMoveValue > currentBest) {
					currentBest = thisMoveValue;
					currentTopMove = i;
				}
			}
		}
		//return the value which is best for team making it
		if (firstMove) {
			topMove = currentTopMove;
		}
		if (prevMove <= 8) {
			UnMakeMove(currentBoard, 1, prevMove);
		}
		return currentBest;


	}
	else {
		//if a move is made from previous iteration, make the move and check for victory for that team- return if win
		if (prevMove <= 8) {
			MakeMove(currentBoard, 0, prevMove);
			if (CheckForVictory(currentBoard, 0, prevMove)) {
				//first team has won
				if (prevMove <= 8) {
					UnMakeMove(currentBoard, 0, prevMove);
				}
				return 129 + currentDepth;
			}
			else if (CheckForAllSpacesFilled(currentBoard)) {
				//game is drawn with all spaces filled
				if (prevMove <= 8) {
					UnMakeMove(currentBoard, 0, prevMove);
				}
				return 128;
			}
		}

		//find the spaces left on the board which are the potential moves
		uint16_t spacesLeft = (legalSpaces) & ~(currentBoard->teamOneOccupation | currentBoard->teamTwoOccupation);

		//go through potential moves and find which is best
		//team two wants low values for move (> 128 is one victory, 128 is draw, < 128 is two victory)
		uint8_t currentBest = 255;
		uint8_t currentTopMove = 10;
		for (uint8_t i = 0; i < 9; i++) {
			if (((spacesLeft) & (1 << i)) != 0) {
				
				uint8_t thisMoveValue = MiniMaxFindMove(0, 0, currentBoard, i, currentDepth - 1);
				if (thisMoveValue < currentBest) {
					currentBest = thisMoveValue;
					currentTopMove = i;
				}
			}
		}
		//return the value which is best for team making it
		if (firstMove) {
			topMove = currentTopMove;
		}
		if (prevMove <= 8) {
			UnMakeMove(currentBoard, 0, prevMove);
		}
		return currentBest;
	}



}


//unmake a given move on the board
void UnMakeMove(BoardState* currentBoard, uint8_t team, uint8_t space){
	if (team == 0) {
		currentBoard->teamOneOccupation &= ~(1 << space);
	}
	else {
		currentBoard->teamTwoOccupation &= ~(1 << space);
	}
}
//make a given move on a given board
void MakeMove(BoardState* currentBoard, uint8_t team, uint8_t space) {
	if (team == 0) {
		currentBoard->teamOneOccupation |= (1 << space);
	}
	else {
		currentBoard->teamTwoOccupation |= (1 << space);
	}
}
//check to see if all spaces are filled and it is a draw
uint8_t CheckForAllSpacesFilled(BoardState* currentBoard) {
	if ((legalSpaces & ~(currentBoard->teamOneOccupation | currentBoard->teamTwoOccupation)) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

//check to see if given team has won the game
uint8_t CheckForVictory(BoardState* currentBoard, uint8_t team, uint8_t recentMove) {
	//only look for victories for given team
	if (team == 0) {
		//only look for victories with latest move spaces involved
		//dont bother checking most recent move position is filled as we know its filled
		/*
		these are the spaces layout
		0 1 2
		3 4 5
		6 7 8
		*/
		switch (recentMove) {
		case TOPLEFTBOARDSPACE:
			if ((currentBoard->teamOneOccupation & TOPMIDDLEUINT16) && (currentBoard->teamOneOccupation & TOPRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLELEFTUINT16) && (currentBoard->teamOneOccupation & BOTTOMLEFTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamOneOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			break;
		case TOPMIDDLEBOARDSPACE:
			if ((currentBoard->teamOneOccupation & TOPLEFTUINT16) && (currentBoard->teamOneOccupation & TOPRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamOneOccupation & BOTTOMMIDDLEUINT16)) {
				return 1;
			}
			break;
		case TOPRIGHTBOARDSPACE:
			if ((currentBoard->teamOneOccupation & TOPMIDDLEUINT16) && (currentBoard->teamOneOccupation & TOPLEFTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLERIGHTUINT16) && (currentBoard->teamOneOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamOneOccupation & BOTTOMLEFTUINT16)) {
				return 1;
			}
			break;
		case MIDDLELEFTBOARDSPACE:
			if ((currentBoard->teamOneOccupation & TOPLEFTUINT16) && (currentBoard->teamOneOccupation & BOTTOMLEFTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamOneOccupation & MIDDLERIGHTUINT16)) {
				return 1;
			}
			break;
		case MIDDLEMIDDLEBOARDSPACE:
			if ((currentBoard->teamOneOccupation & MIDDLELEFTUINT16) && (currentBoard->teamOneOccupation & MIDDLERIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & TOPMIDDLEUINT16) && (currentBoard->teamOneOccupation & BOTTOMMIDDLEUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & TOPLEFTUINT16) && (currentBoard->teamOneOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & TOPRIGHTUINT16) && (currentBoard->teamOneOccupation & BOTTOMLEFTUINT16)) {
				return 1;
			}
			break;
		case MIDDLERIGHTBOARDSPACE:
			if ((currentBoard->teamOneOccupation & TOPRIGHTUINT16) && (currentBoard->teamOneOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamOneOccupation & MIDDLELEFTUINT16)) {
				return 1;
			}
			break;
		case BOTTOMLEFTBOARDSPACE:
			if ((currentBoard->teamOneOccupation & MIDDLELEFTUINT16) && (currentBoard->teamOneOccupation & TOPLEFTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & BOTTOMMIDDLEUINT16) && (currentBoard->teamOneOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamOneOccupation & TOPRIGHTUINT16)) {
				return 1;
			}
			break;
		case BOTTOMMIDDLEBOARDSPACE:
			if ((currentBoard->teamOneOccupation & BOTTOMLEFTUINT16) && (currentBoard->teamOneOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamOneOccupation & TOPMIDDLEUINT16)) {
				return 1;
			}
			break;
		case BOTTOMRIGHTBOARDSPACE:
			if ((currentBoard->teamOneOccupation & BOTTOMLEFTUINT16) && (currentBoard->teamOneOccupation & BOTTOMMIDDLEUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLERIGHTUINT16) && (currentBoard->teamOneOccupation & TOPRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamOneOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamOneOccupation & TOPLEFTUINT16)) {
				return 1;
			}
			break;


		}
		return 0;
	}
	else {
		//only look for victories with latest move spaces involved
		//dont bother checking most recent move position is filled as we know its filled
		/*
		these are the spaces layout
		0 1 2
		3 4 5
		6 7 8
		*/
		switch (recentMove) {
		case TOPLEFTBOARDSPACE:
			if ((currentBoard->teamTwoOccupation & TOPMIDDLEUINT16) && (currentBoard->teamTwoOccupation & TOPRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLELEFTUINT16) && (currentBoard->teamTwoOccupation & BOTTOMLEFTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamTwoOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			break;
		case TOPMIDDLEBOARDSPACE:
			if ((currentBoard->teamTwoOccupation & TOPLEFTUINT16) && (currentBoard->teamTwoOccupation & TOPRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamTwoOccupation & BOTTOMMIDDLEUINT16)) {
				return 1;
			}
			break;
		case TOPRIGHTBOARDSPACE:
			if ((currentBoard->teamTwoOccupation & TOPMIDDLEUINT16) && (currentBoard->teamTwoOccupation & TOPLEFTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLERIGHTUINT16) && (currentBoard->teamTwoOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamTwoOccupation & BOTTOMLEFTUINT16)) {
				return 1;
			}
			break;
		case MIDDLELEFTBOARDSPACE:
			if ((currentBoard->teamTwoOccupation & TOPLEFTUINT16) && (currentBoard->teamTwoOccupation & BOTTOMLEFTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamTwoOccupation & MIDDLERIGHTUINT16)) {
				return 1;
			}
			break;
		case MIDDLEMIDDLEBOARDSPACE:
			if ((currentBoard->teamTwoOccupation & MIDDLELEFTUINT16) && (currentBoard->teamTwoOccupation & MIDDLERIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & TOPMIDDLEUINT16) && (currentBoard->teamTwoOccupation & BOTTOMMIDDLEUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & TOPLEFTUINT16) && (currentBoard->teamTwoOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & TOPRIGHTUINT16) && (currentBoard->teamTwoOccupation & BOTTOMLEFTUINT16)) {
				return 1;
			}
			break;
		case MIDDLERIGHTBOARDSPACE:
			if ((currentBoard->teamTwoOccupation & TOPRIGHTUINT16) && (currentBoard->teamTwoOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamTwoOccupation & MIDDLELEFTUINT16)) {
				return 1;
			}
			break;
		case BOTTOMLEFTBOARDSPACE:
			if ((currentBoard->teamTwoOccupation & MIDDLELEFTUINT16) && (currentBoard->teamTwoOccupation & TOPLEFTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & BOTTOMMIDDLEUINT16) && (currentBoard->teamTwoOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamTwoOccupation & TOPRIGHTUINT16)) {
				return 1;
			}
			break;
		case BOTTOMMIDDLEBOARDSPACE:
			if ((currentBoard->teamTwoOccupation & BOTTOMLEFTUINT16) && (currentBoard->teamTwoOccupation & BOTTOMRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamTwoOccupation & TOPMIDDLEUINT16)) {
				return 1;
			}
			break;
		case BOTTOMRIGHTBOARDSPACE:
			if ((currentBoard->teamTwoOccupation & BOTTOMLEFTUINT16) && (currentBoard->teamTwoOccupation & BOTTOMMIDDLEUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLERIGHTUINT16) && (currentBoard->teamTwoOccupation & TOPRIGHTUINT16)) {
				return 1;
			}
			else if ((currentBoard->teamTwoOccupation & MIDDLEMIDDLEUINT16) && (currentBoard->teamTwoOccupation & TOPLEFTUINT16)) {
				return 1;
			}
			break;
		}
		return 0;
	}
	
	
}