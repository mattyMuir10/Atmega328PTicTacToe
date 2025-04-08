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
#include "UART_HAL.h"
#include "ADC_Hal.h"
#include "TIMER_0.h"
#include "TicTacToeGame.h"





int main(void)
{
	
	
	
	
	
	timer0_init();
	sei();
	
	
	//DDRD |= 0b11111111;
	//DDRB |= 0b11111111;
	//DDRC |= 0b11111111;
	
	//DDRC &= ~(1 << BLUEWINPIN);
	
	//PORTD = 0b10000010;
	//PORTC = 0b00100000;

	//*BLUEWINDDPORT &= ~(1 << BLUEWINPIN);
	
	//Initialize();
	//SetPinOnPort(BOTTOMLEFTYELLOWPORT, BOTTOMLEFTYELLOWPIN, 1,BOTTOMLEFTYELLOWONSHIFT);
	//SetPinOnPort(BOTTOMMIDDLEYELLOWPORT, BOTTOMMIDDLEYELLOWPIN, 1,BOTTOMMIDDLEYELLOWONSHIFT);
	//SetPinOnPort(BOTTOMRIGHTYELLOWPORT, BOTTOMRIGHTYELLOWPIN, 1,BOTTOMRIGHTYELLOWONSHIFT);
	
	//PORTD = 0b00010001;
	
	StartTicTacToe();
	/*
	for (int i = 0; i < 8; i++){
		if (i == 1){
			SetPinOnPort(SHIFTREGISTERDATAPORT, i, 1, 1);
		}
		else{
			SetPinOnPort(SHIFTREGISTERDATAPORT, i, 0, 1);
		}
	}
	*/
	
			//*BLUEWINPORT |= (1 << BLUEWINPIN);

	/*
	PORTB |= 0b00000010;
	for (int i = 0; i < 16; i++){
		_delay_ms(5);
		PORTC |= 0b00000001;
		_delay_ms(5);
		PORTC &= 0b11111110;
	}
	
	PORTB &= 0b11111101;
	
	PORTB |= 0b00000100;	
	_delay_ms(5);

	PORTB &= 0b11111011;
	*/
	
		
	
	
    while (1) 
    {
		
		
		
		/*
		
		curInt--;
		if (curInt < 1){
			curInt = 3;
		}
		*/
		
		//volts = ADC_VOLTS(converted_value);
		//printf("volts: %.2f\n", volts);
		/*
		if (lightOn)
		{
			PORTD &= 0b11110111;
			lightOn = false;
		}
		else
		{
			PORTD |= 0b00001000;
			lightOn = true;
		}
		delay_ms_custom(1000);
		*/
		//adc conversion
		/*
		converted_value = adc_convert();
		if(converted_value > 1022){
			PORTD |= 0b00001000;
		}
		else{
			PORTD &= 0b11110111;
		}
		
		*/
		
		/*
		if (uart_read_count() > 0)
		{
			data = uart_read();
			uart_send_byte(data);
			if (lightOn)
			{
				PORTD &= 0b11110111;
				lightOn = false;
			}
			else
			{
				PORTD |= 0b00001000;
				lightOn = true;
			}
		}
		*/
		
		
		
		
		
    }
}

