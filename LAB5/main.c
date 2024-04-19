//******************************************************************************
// Universidad Del Valle De Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Samuel Tortola - 22094
// Proyecto: Laboratorio 5
// Hardware: Atmega238P
// Creado: 11/04/2024
//Última modificación: 18/04/2024
//******************************************************************************

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "PWM1/PWM1.h"

void initADC(void);



int main(void)
{
	cli();  //Apagar interrupciones
	DDRB |= (1 << PORTB2);		//PB2 como salida de servo
	DDRC = 0;  //Puerto C como entrada
	
	
	initFastPWM1(settedUp, 8);  //Iniciar funcion de FASTPWM en timer1
	channel(channelB, nop);   
	topValue(39999);   //Valor alto de desbordamiento para 1 a 2 ms que se necesita de servo
	
	initADC();   //Iniciar la funcion de ADC
	sei();   //Activar interrupciones
	
	while (1)
	{
		ADCSRA |= (1 << ADSC);   //Leer puerto de ADC 
		_delay_ms(10);   //Velocidad de servo
		//suma ++;
		
		convertServo(ADCH, channelB);
	
	}
}

void initADC(void){
	ADMUX = 0;  //Elegir el pin A0 como lectura
	
	ADMUX |= (1 << REFS0); //Vref = AVcc = 5Vs
	ADMUX &= ~(1 << REFS1);  //Justificación a la izquierda
	ADMUX |= (1 << ADLAR);
	
	ADCSRA = 0;
	ADCSRA |= (1 << ADEN);	//Encender ADC
	ADCSRA |= (1 << ADIE);
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);   //prescaler 128 > 125kHz
	DIDR0 |= (1 << ADC0D);	//desabilitar el A0 como digital
}


ISR (ADC_vect){
	ADCSRA |= (1 << ADIF);	//Apagar bandera de interrupcion
}
