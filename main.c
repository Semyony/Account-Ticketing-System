#include <stdio.h>

#include "accountTicketingUI.h"

// System Data Array sizes
#define ACCOUNT_SIZE 15
#define TICKET_SIZE 17

int main(void)
{
    int recsLoaded;
    struct Account accounts[ACCOUNT_SIZE] = { {0} };
    struct Ticket tickets[TICKET_SIZE] = { {0} };
    struct AccountTicketingData data = { accounts, ACCOUNT_SIZE, tickets, TICKET_SIZE };

    // Call student function to load records from a file :)
    puts("\n\n##########################################################################");
    puts("Starting Account Ticketing System....");
    printf("   Loading account data... ");
    recsLoaded = loadAccounts(accounts, ACCOUNT_SIZE);
    printf("(%d accounts loaded)\n", recsLoaded);
    printf("   Loading ticket data...  ");
    recsLoaded = loadTickets(tickets, TICKET_SIZE);
    printf("(%d tickets loaded)\n", recsLoaded);
    puts("##########################################################################\n\n");

    // launch application logic
    applicationStartup(&data);

    return 0;
}
