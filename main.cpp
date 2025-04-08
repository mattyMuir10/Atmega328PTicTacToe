/*
 * Setup.cpp
 *
 * Created: 2025-03-22 11:56:35 PM
 * Author : mattm
 */ 
#include <stdint.h>
#include <stdio.h>

#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "TIMER_0.h"
#include "TicTacToeGame.h"





int main(void)
{
	
	
	
	
	
	timer0_init();
	sei();
	
	StartTicTacToe();
	
	
		
	
	
  
}

