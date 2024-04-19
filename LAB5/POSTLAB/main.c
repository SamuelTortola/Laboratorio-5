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
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

void setup(void);
void initADC(void);


uint8_t valorADC2;


int main(void)
{
	setup();
	ADCSRA |= (1<<ADSC);
	
	while (1){
		OCR2A = valorADC2;
	}
}

void setup(void){
	cli();
	
	DDRB |= (1<<DDB3);
	
	
	TCCR2A = 0;
	TCCR2B = 0;
	
	TCCR2A |= (1<<COM2A1);	//no invertido 
	TCCR2A |= (1<<WGM21)|(1<<WGM20);	//fast pwm
	
	TCCR2B &= ~(1<<WGM22);	//
	TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20);	//PRESCALER DE 1024

	initADC();
	
	sei();
}

void initADC(void){
	
	ADMUX = 1;  //ADC en A1
	
	
	ADMUX |= (1<<REFS0);//  AVCC = 5V 
	ADMUX &= ~(1<<REFS1);
	
	
	ADMUX |= (1<<ADLAR);// Justificacion a la Izquierda
	
	ADCSRA = 0;
	
	
	ADCSRA |= (1<<ADEN);// Habilitando el ADC
	
	
	ADCSRA |= (1<<ADIE);//Habilitamos las interrupciones de ADC
	
	
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);  //Prescaler de 128
	
	DIDR0 |= (1<<ADC0D);
	DIDR0 |= (1 << ADC1D);	//desabilitar el A1 como digital
}

ISR(ADC_vect){
	valorADC2 = ADCH;

	ADCSRA |= (1<<ADIF);
	ADCSRA |= (1<<ADSC);
}
