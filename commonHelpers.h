// ===================================================================================
//
//  Assignment:  2 
//  Milestone:   4
//  Description: Common Helpers Header
// 
// ===================================================================================
// 
//  Name   : Semen Khlavich
//  ID: 107305203
//  Email : skhlavich@myseneca.ca
//  Section : NGG
//
// ===================================================================================

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

// FUNCTIONS PROTOTYPES
int currentYear(void);
void clearStanadardInputBuffer(void);
//INTEGER
int getInteger(void);
//POSITIVE INTEGER
int getPositiveInteger(void);
// INTEGER FROM RANGE -3 AND 11, -40 AND 14
int getIntFromRange(int lo, int hi);
// DOUBLE
double getDouble(void);
// POSITIVE DOUBLE
double getPositiveDouble(void);
// CHARACTER
int length(const char* s);
char getCharOption(const char* allowedCharacters);
// STRING
void getCString(char* s, int lo, int hi);


#endif// !COMMON_HELPERS_H_
