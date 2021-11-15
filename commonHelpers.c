#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

#include "commonHelpers.h"


// Uses the time.hlibrary to obtain current year information
// Get the current 4-digit yearfrom the system
int currentYear(void) {
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}
// Empty the standard input buffer
void clearStanadardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

//INTEGER

int getInteger() {
	char nl = 'x';
	int value;

	while (nl != '\n') {
		scanf("%d%c", &value, &nl);
		if (nl != '\n') {
			clearStanadardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	}
	return value;
}

//POSITIVE INTEGER

int getPositiveInteger()
{
	char nl = 'x';
	int value = -1;

	while (nl != '\n' || value < 0) {
		scanf("%d%c", &value, &nl);
		if (nl != '\n') {
			clearStanadardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		
    else if (value < 0 ) {
      printf("ERROR: Value must be positive or zero: ");
      nl = 'x';
		  value = -1;
    }
		
	}

	return value;
}

// INTEGER FROM RANGE -3 AND 11, -40 AND 14

int getIntFromRange(int lo, int hi) {

	char nl = 'x';
	int value = -41;

	while (nl != '\n' || value < lo || value > hi) {
		scanf("%d%c", &value, &nl);
		if (nl != '\n') {
			clearStanadardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		else if (value < lo || value > hi) {
			//clearStanadardInputBuffer();
			printf("ERROR: Value must be between %d and %d inclusive: ", lo, hi);
			nl = 'x';
			value = -41;
		}
		//clearStanadardInputBuffer();
	}

	return value;
}

// DOUBLE

double getDouble() {
	char nl = 'x';
	double value;

	while (nl != '\n') {
		scanf("%lf%c", &value, &nl);
		if (nl != '\n') {
			clearStanadardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	}
	return value;
}

// POSITIVE DOUBLE

double getPositiveDouble() {
	char nl = 'x';
	double value = -1;

	while (nl != '\n' || value <= 0.0) {
		scanf("%lf%c", &value, &nl);
		if (nl != '\n') {
			clearStanadardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
		else if (value <= 0.0) {
			printf("ERROR: Value must be a positive double floating-point number: ");
			nl = 'x';
			value = -1;
		}
	}

	return value;
}

// CHARACTER 
int length(const char* s) {
	int i;
	for (i = 0; s[i] != 0; i++);
	return i;
}

int position(const char* allowedCharacters, char c) {
	int p = -1;
	int i = 0;
	while (allowedCharacters[i] != '\0') {
		if (allowedCharacters[i] == c) {
			p = i;
			break;
		}
		i++;
	}

	return p;
}
//---------------------------------------------
char getCharOption(const char* allowedCharacters) {
	int p = -1;
	char opt, nl;
	while (p == -1) {
		scanf("%c%c", &opt, &nl);
		if (nl != '\n') {
			clearStanadardInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", allowedCharacters);
		}
		else {
			p = position(allowedCharacters, opt);
			if (p == -1)
				printf("ERROR: Character must be one of [%s]: ", allowedCharacters);
			else
				break;
		}
	}

	return allowedCharacters[p];
}

// STRING

void copy(char* to, char* from) {
	int i;
	for (i = 0; from[i] != 0; i++) {
		to[i] = from[i];
	}
	to[i] = 0;
	return;
}


void getCString(char* s, int lo, int hi) {
	char cstring[100];
	int lengthOfStr;

	scanf("%[^\n]", cstring);

	lengthOfStr = length(cstring);
	while (lengthOfStr < lo || lengthOfStr > hi) {
		if (lo == hi) {
			printf("ERROR: String length must be exactly %d chars: ", hi);
		}
		else {
			if (lengthOfStr > hi) {
				printf("ERROR: String length must be no more than %d chars: ", hi);
			}
			else {
				printf("ERROR: String length must be between %d and %d chars: ", lo, hi);
			}
		}
		clearStanadardInputBuffer();
		scanf("%[^\n]", cstring);
		lengthOfStr = length(cstring);
	}
	copy(s, cstring);
	clearStanadardInputBuffer();
	return;
}

