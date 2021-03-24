/*
 * morse.h
 *
 * Created: 17/03/2021 14:50:55
 *  Author: Kasper & Erwin
 */ 


#ifndef MORSE_H_
#define MORSE_H_

#define empty 0
#define dot 1
#define dash 2

typedef struct {
	char character;
	int morse[6];
}MorseCode;

char getCharFromMorse(int morse[]);
int * getMorseFromChar(char character);
char compareArray(int a[],int b[],int size);

#endif /* MORSE_H_ */