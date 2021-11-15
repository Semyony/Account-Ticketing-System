#ifndef ACCOUNTTICKETING_H_
#define ACCOUNTTICKETING_H_
#include "account.h"
#include "ticket.h"

struct AccountTicketingData{
  struct Account* accounts;   // array of accounts
  const int ACCOUNT_MAX_SIZE; // maximum elements for account array
  struct Ticket* tickets;     // array of tickets
  const int TICKET_MAX_SIZE;  // maximum elements for ticket array
};

//READ ACCOUNTS

int loadAccounts(struct Account accounts[], int size);

//READ TICKETS

int loadTickets(struct Ticket tickets[], int size);


void pauseExecution(void);
int findAccountIndexByAcctNum(const struct Account accounts[], int size, int f);
int zeroAccNum(const struct Account accounts[], int size);

void displayAccountSummaryHeader(void);
void displayAccountDetailHeader(void);

void displayAccountSummaryRecord(const struct Account *account);
void displayAccountDetailRecord(const struct Account* account);

void applicationStartup(struct AccountTicketingData *data);
int menuLogin(const struct Account accounts[], int arrSize);
void menuClient(const struct Account *acc, int arrSize, struct Ticket tickets[], int ticktSize);
void menuAgent(struct AccountTicketingData *data, const struct Account* acc);
void updateAccount(struct Account *acc);
void updateUserLogin(UserLogin *changelog);
void updateDemographic(Demographic *changedemo);
void displayAllAccountSummaryRecords(const struct Account accounts[], int arrSize);
void displayAllAccountDetailRecords(const struct Account accounts[], int arrSize);
int findTicketIndexByAcctNum(const struct Ticket tickets[], int size, const struct Account* account, int option);

#endif // !ACCOUNTTICKETING_H_
