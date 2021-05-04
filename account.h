// ===================================================================================
//
//  Assignment:  2 
//  Milestone:   4
//  Description: Account Header
// 
// ===================================================================================
// 
//  Name   : Semen Khlavich
//  ID: 107305203
//  Email : skhlavich@myseneca.ca
//  Section : NGG
//
// ===================================================================================

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

typedef struct  {
	int birthYear;
	double income;
	char orgCountry[31];
} Demographic;

typedef struct  {
	char customerName[31];
	char loginName[31];
	char password[9];
} UserLogin ;

struct Account {
	int accountNumber;
	char accountType;
	UserLogin userlogin;
	Demographic demographic;
};

void getAccount(struct Account *account, struct Account accounts[], int size);
void getUserLogin(UserLogin *login);
void getDemographic(Demographic *demo);
int highestNumber(struct Account accounts[], int size);
int findChar(char *login_name, char charerr);
int passwordCheck(char *password);
void archivedAccountStatistics();
void archiveAccount(struct Account* accounts, struct Account* acc, int size);
int saveAccount(struct Account* accounts, int size);

#endif // !ACCOUNT_H_




