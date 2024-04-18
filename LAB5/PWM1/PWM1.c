/*
 * PWM1.c
 *
 * Created: 12/04/2024 17:48:37
 *  Author: samuel
 */ 

#include "PWM1.h"

uint16_t tope = 0;
uint16_t i, j;		

void channel(uint8_t setChannel, uint8_t inverted){
	switch(setChannel){
		case 1:
			if(inverted == 1){     //Si se desea inverir la se�al o no, del canal A
				TCCR1A |= (1 << COM1A0) | (1 << COM1A1);	//invertido 
			}else{
				TCCR1A |= (1 << COM1A1);     //No invertido 
			}
		break;
		
		case 2:
			if(inverted == 1){   //Si se desea el canal B invertido o no 
				TCCR1A |= (1 << COM1B0) | (1 << COM1B1);	 //Invertido 
			}else{
				TCCR1A |= (1 << COM1B1);					//No invertido
			}
		break;
	}
}


void initFastPWM1(uint8_t modePWM, uint16_t prescaler){
	
	TCCR1A = 0;   //Iniciar timer1 
	TCCR1B = 0;
	
	switch (prescaler)  //Elecci�n del prescaler
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
			//fast PWM 10-bit 
			TCCR1A |= (1 << WGM11) | (1 << WGM10);
			TCCR1B |= (1 << WGM12);
		break;
		
		case settedUp:
			TCCR1A |= (1 << WGM11);    //Poner el valor final
			TCCR1B |= (1 << WGM12) | (1 << WGM13);
			tope = 1;		
		break;
	}
	
}

void topValue(uint16_t tope){
	if (tope == 1)	{
		ICR1 = tope;		//Poner valor final
	}else{
		tope = 0;
	}
}


void convertServo(uint16_t analogIn, uint8_t selChannel){    //Conversiones para servo
	
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