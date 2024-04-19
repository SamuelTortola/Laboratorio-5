/*
 * PWM1.c
 *
 * Created: 12/04/2024 17:48:37
 *  Author: samuel
 */ 

#include "PWM1.h"

uint16_t topVal = 0;
uint16_t i, j;		


void channel(uint8_t setChannel, uint8_t inverted){
	switch(setChannel){
		case 1:
		if(inverted == 1){
			TCCR1A |= (1 << COM1A0) | (1 << COM1A1);	//A invertido 
			}else{
			TCCR1A |= (1 << COM1A1);					//A no invertido 
		}
		break;
		
		case 2:
		if(inverted == 1){
			TCCR1A |= (1 << COM1B0) | (1 << COM1B1);	//B invertido 
			}else{
			TCCR1A |= (1 << COM1B1);					//B no invertido 
		}
		break;
	}
}


void initFastPWM1(uint8_t modePWM, uint16_t prescaler){
	//initialize register timer1
	TCCR1A = 0;
	TCCR1B = 0;
	
	switch (prescaler)
	{
		case 8:
		TCCR1B |= (1 << CS11);					//prescaler 8
		break;
		
		case 1024:
		TCCR1B |= (1 << CS10) | (1 << CS12);	//prescaler 1024
		break;
	}
	
	
	switch (modePWM)
	{
		case normal:
	
		TCCR1A |= (1 << WGM11) | (1 << WGM10);   //Fast PWM
		TCCR1B |= (1 << WGM12);
		break;
		
		case settedUp:
	
		TCCR1A |= (1 << WGM11);
		TCCR1B |= (1 << WGM12) | (1 << WGM13);
		topVal = 1;		
		break;
	}
	
}


void topValue(uint16_t top){
	if (topVal == 1)	{
		ICR1 = top;		//set top value
		}else{
		topVal = 0;
	}
}


void convertServo(uint16_t analogIn, uint8_t selChannel){   //Conversion para servos
	
	switch(selChannel){
		case 1:
		i = ADCH;
		j = (200/12)*i+1000;
		OCR1A = j;
		break;
		
		case 2:
		i = ADCH;
		j = (200/12)*i+1000;
		OCR1B = j;
		break;
	}
}