#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include <string.h>
#include <ctype.h>

//GET DATA FOR ACCOUNTS
void getAccount(struct Account *account, struct Account accounts[], int size) {
	account->accountNumber = highestNumber(accounts, size) + 1;
  printf("New Account Data (Account#:%d)\n----------------------------------------\n", account->accountNumber);
	printf("Enter the account type (A=Agent | C=Customer): ");
	account->accountType = getCharOption("AC");
	printf("\n");
  getUserLogin(&account->userlogin);
  getDemographic(&account->demographic);
}

void getUserLogin(UserLogin *login) {
  char space = ' ';
  int x = 0;
  
  printf("User Login Data Input\n----------------------------------------\n");
  
  while(x == 0){
    printf("Enter user login (10 chars max): ");
    getCString(login->loginName, 0, 10);
    x = findChar(login->loginName, space);
    if (x == 0){
      printf("ERROR:  The user login must NOT contain whitespace characters.\n");
    }
  }

	printf("Enter the display name (30 chars max): ");
	getCString(login->customerName, 0, 30);
  while (x == 1){
    printf("Enter the password (must be 8 chars in length): ");
    getCString(login->password, 8, 8);
    x = passwordCheck(login->password);
    if (x == 1){
      printf("SECURITY: Password must contain 2 of each:\n");
      printf("          Digit: 0-9\n");
      printf("          UPPERCASE character\n");
      printf("          lowercase character\n");
      printf("          symbol character: !@#$%%^&*\n");
    }
  }
  printf("\n");
}

void getDemographic(Demographic* demo) {
  int i;
	printf("Demographic Data Input\n----------------------------------------\n");
	printf("Enter birth year (current age must be between 18 and 110): ");
	demo->birthYear = getIntFromRange(currentYear() - 110, currentYear() - 18);
	printf("Enter the household Income: $");
	demo->income = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(demo->orgCountry, 0, 30);
  for (i = 0; i < strlen(demo->orgCountry); ++i){
    demo->orgCountry[i] = toupper(demo->orgCountry[i]);
  }
	printf("\n");
}

//HIGHEST ACCOUNT NUMBER
int highestNumber(struct Account accounts[], int size){
  int x = 0;
  int i;
  for (i = 0; i < size; ++i){
    if (x < accounts[i].accountNumber){
      x = accounts[i].accountNumber;
    }
  }
  return x;
}

int findChar(char *login_name, char charerr){
  char *i;
  int x;
  i = strchr(login_name, charerr);
  
  if (i == NULL){
    x = 1;
  }
  else{
    x = 0;
  }
  return x;  
}

int passwordCheck(char *password){
  int i;
  int digits = 0;
  int lower_case = 0;
  int upper_case = 0;
  int symbol = 0;
  int status = 0; 
  for (i = 0; i < strlen(password); ++i){
    if (password[i] <= '9' && password[i] >= '0')
      digits++;
    else if (password[i] <= 'Z' && password[i] >= 'A')
      upper_case++;
    else if (password[i] <= 'z' && password[i] >= 'a')
      lower_case++;
    else if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '%' || password[i] == '^' || password[i] == '&' || password[i] == '*')
      symbol++;
    
  }
  
  if (digits > 2 || upper_case > 2 || lower_case > 2 || symbol > 2 || digits < 2 || upper_case < 2 || lower_case < 2 || symbol < 2)
    status = 1;
  return status;
}

//ARCHIVE ACCOUNTS

void archivedAccountStatistics() {
    int accountNumber;
    int i, numofaccounts = 0;
    FILE* fp = fopen("accounts_arc.txt", "r");
    if (fp!=NULL) {
        for (i = 1; fscanf(fp, "%d%*[^\n]", &accountNumber) != EOF; ++i) {
            if (accountNumber > 0) {
                numofaccounts = i;
            }
        }
    }
    fclose(fp);
    printf("There are %d account(s) currently archived.\n\n", numofaccounts);

}

void archiveAccount(struct Account* accounts, struct Account *acc, int size) {
    int i = 0;
    FILE* fp = fopen("accounts_arc.txt", "a");
    if (fp != NULL) {
        for (i = 0; i < size; ++i) {
            if (accounts[i].accountNumber == acc->accountNumber) {
                fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s",
                    accounts[i].accountNumber,
                    accounts[i].accountType,
                    accounts[i].userlogin.customerName,
                    accounts[i].userlogin.loginName,
                    accounts[i].userlogin.password,
                    accounts[i].demographic.birthYear,
                    accounts[i].demographic.income,
                    accounts[i].demographic.orgCountry);
                fprintf(fp, "\n");
                accounts[i].accountNumber = 0;
            }

        }
    }
    fclose(fp);
}

int saveAccount(struct Account* accounts, int size) {
    int i = 0, numofaccounts = 0;
    FILE* fp = fopen("accounts.txt", "w");
    if (fp != NULL) {
        for (i = 0; i < size; ++i) {
            if (accounts[i].accountNumber != 0){
                fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s",
                    accounts[i].accountNumber,
                    accounts[i].accountType,
                    accounts[i].userlogin.customerName,
                    accounts[i].userlogin.loginName,
                    accounts[i].userlogin.password,
                    accounts[i].demographic.birthYear,
                    accounts[i].demographic.income,
                    accounts[i].demographic.orgCountry);
                fprintf(fp, "\n");
                numofaccounts++;
            }
            
        }
    }
    fclose(fp);
    return numofaccounts;
}
