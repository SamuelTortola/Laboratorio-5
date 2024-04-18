/*
 * PWM1.h
 *
 * Created: 12/04/2024 17:41:48
 *  Author: samuel
 */ 


#ifndef PWM1_H_
#define PWM1_H_

#include <avr/io.h>
#include <stdint.h>

#define yes 1    //Enviar configuraciones inciales
#define nop 0 
#define normal 1
#define settedUp 2
#define channelA 1
#define channelB 2


void initFastPWM1(uint8_t modePWM, uint16_t prescaler);


void channel(uint8_t setChannel, uint8_t inverted);


void topValue(uint16_t top);


void convertServo(uint16_t analogIn, uint8_t selChannel);


#endif /* PWM1_H_ */