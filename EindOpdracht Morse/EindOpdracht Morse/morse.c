/*
 * morse.c
 *
 * Created: 17/03/2021 14:50:46
 *  Author: Kasper & Erwin
 */ 

#include "morse.h"

MorseCode MorseCodes[] = {
	{' ', {empty, empty, empty, empty, empty, empty}},
	{'A', {dot, dash, empty, empty, empty, empty}},
	{'B', {dash, dot, dot, dot, empty, empty}},
	{'C', {dash, dot, dash, dot, empty, empty}},
	{'D', {dash, dot, dot, empty, empty, empty}},
	{'E', {dot, empty, empty, empty, empty, empty}},
	{'F', {dot, dot, dash, dot, empty, empty}},
	{'G', {dash, dash, dot, empty, empty, empty}},
	{'H', {dot, dot, dot, dot, empty, empty}},
	{'I', {dot, dot, empty, empty, empty, empty}},
	{'J', {dot, dash, dash, dash, empty, empty}},
	{'K', {dash, dot, dash, empty, empty, empty}},
	{'L', {dot, dash, dot, dot, empty, empty}},
	{'M', {dash, dash, empty, empty, empty, empty}},
	{'N', {dash, dot, empty, empty, empty, empty}},
	{'O', {dash, dash, dash, empty, empty, empty}},
	{'P', {dot, dash, dash, dot, empty, empty}},
	{'Q', {dash, dash, dot, dash, empty, empty}},
	{'R', {dot, dash, dot, empty, empty, empty}},
	{'S', {dot, dot, dot, empty, empty, empty}},
	{'T', {dash, empty, empty, empty, empty, empty}},
	{'U', {dot, dot, dash, empty, empty, empty}},
	{'V', {dot, dot, dot, dash, empty, empty}},
	{'W', {dot, dash, dash, empty, empty, empty}},
	{'X', {dash, dot, dot, dash, empty, empty}},
	{'Y', {dash, dot, dash, dash, empty, empty}},
	{'Z', {dash, dash, dot, dot, empty, empty}},
	{'1', {dot, dash, dash, dash, dash, empty}},
	{'2', {dot, dot, dash, dash, dash, empty}},
	{'3', {dot, dot, dot, dash, dash, empty}},
	{'4', {dot, dot, dot, dot, dash, empty}},
	{'5', {dot, dot, dot, dot, dot, empty}},
	{'6', {dash, dot, dot, dot, dot, empty}},
	{'7', {dash, dash, dot, dot, dot, empty}},
	{'8', {dash, dash, dash, dot, dot, empty}},
	{'9', {dash, dash, dash, dash, dot, empty}},
	{'0', {dash, dash, dash, dash, dash, empty}}
};

char getCharFromMorse(int morse[]) {
	
	for (int i = 0; i < 37; i++) {
		if (compareArray(MorseCodes[i].morse, morse, 6)) {
			return MorseCodes[i].character;
		}
	}
	return '$';
}

int * getMorseFromChar(char character) {
	static int morse[6] = {empty, empty, empty, empty, empty, empty};
	for (int i = 0; i < 37; i++) {
		if (character == MorseCodes[i].character) {
			
			for (int j = 0; j < 6; j++)
			{
				morse[j] = MorseCodes[i].morse[j];
			}
			return morse;
		}
	}
	return morse;
}

char compareArray(int a[],int b[],int size) {
	for(int i = 0;	i < size; i++) {
		if(a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}