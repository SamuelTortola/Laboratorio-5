//******************************************************************************
// Universidad Del Valle De Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Samuel Tortola - 22094
// Proyecto: Laboratorio 5
// Hardware: Atmega238p
// Creado: 11/04/2024
//Última modificación: 12/04/2024
//******************************************************************************



#define F_CPU 12000000
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

void setup(void);
void initADC(void);

int dato = 0;


#define set_bit(sfr, bit)	(_SFR_BYTE(sfr) |= _BV(bit))
#define clear_bit(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))



void setup(void){
	DDRD = 0b01100000;  //PD5 y PD6 como salida a los servos
	
	
	
	initADC();
	sei(); //Activar interrupciones
}


void initADC(){
	ADMUX = 0;   //Usar el ADC0 del atmega328P
	ADMUX |= (1<<REFS0);  //Referencia AVCC = 5V
	ADMUX &= ~(1<<REFS1); //Justificación a la izquierda
	ADMUX |= (1<<ADLAR);
	ADCSRA = 0;
	ADCSRA |= (1<<ADIE);  //Habilitando interrupcion de ADC
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  //Habilitando prescaler de 16M/128 frecuencia = 125Khz
	ADCSRA |= (1<<ADEN);   //Habilitando el ADC
}



int main(void)
{
  setup();
    while (1) 
    {
    }
}

ISR(ADC_vect){
	dato = ADCH;   //Contador general
	
	ADCSRA |= (1<<ADIF); //Se borra la bandera de interrupción

}
