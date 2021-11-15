#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include "ticket.h"

//CREATE TICKET 

void getTicket(struct Ticket tickets[], const struct Account* acc, int size) {
    int i;
    int number_of_tickets = 0;
    for (i = 0; i < size; ++i) {
        if (tickets[i].accountNumber == acc->accountNumber && tickets[i].uniqueNumber != 0) {
            number_of_tickets++;
        }
    }
    if (number_of_tickets >= 5) {
        printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
        pauseExecution();
        putchar('\n');
    }
    else {
        int indexOfTicket;
        indexOfTicket = zeroTicketAccNum(tickets, size);
        tickets[indexOfTicket].uniqueNumber = highestTicket(tickets, size) + 1;
        tickets[indexOfTicket].accountNumber = acc->accountNumber;
        tickets[indexOfTicket].TicketStatus = 1;

        printf("New Ticket (Ticket#:%06d)\n", tickets[indexOfTicket].uniqueNumber);
        printf("----------------------------------------\n");
        printf("Enter the ticket SUBJECT (30 chars. maximum): ");
        getCString(tickets[indexOfTicket].subject, 0, 30);
        putchar('\n');
        printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
        addMessage(&tickets[indexOfTicket], acc);
        printf("\n*** New ticket created! ***\n\n");
        pauseExecution();
        putchar('\n');
    }
}

//DISPLAY TICKETS

void displayAgentTicketInfoNew(const struct Ticket tickets[], const struct Account* account, int ticketSize) {
    int i;
    for (i = 0; i < ticketSize; ++i) {
        if (tickets[i].numofMessages == 1 && tickets[i].TicketStatus == 1 && tickets[i].uniqueNumber != 0) {

            printf("%06d %5d %-15s %-6s %-30s %5d\n", tickets[i].uniqueNumber, tickets[i].accountNumber, tickets[i].messages->customerName, tickets[i].TicketStatus == 1 ? "ACTIVE" : "CLOSED", tickets[i].subject, tickets[i].numofMessages);

        }
    }
}

void displayAgentTicketInfoAll(const struct Ticket tickets[], const struct Account* account, int ticketSize) {
    int i;
    for (i = 0; i < ticketSize; ++i) {
        if (tickets[i].TicketStatus == 1 && tickets[i].uniqueNumber != 0) {

            printf("%06d %5d %-15s %-6s %-30s %5d\n", tickets[i].uniqueNumber, tickets[i].accountNumber, tickets[i].messages->customerName, tickets[i].TicketStatus == 1 ? "ACTIVE" : "CLOSED", tickets[i].subject, tickets[i].numofMessages);

        }
    }
}

void displayAgentTicketInfoAllClosed(const struct Ticket tickets[], const struct Account* account, int ticketSize) {
    int i;
    for (i = 0; i < ticketSize; ++i) {
        if (tickets[i].TicketStatus == 0 && tickets[i].uniqueNumber != 0) {

            printf("%06d %5d %-15s %-6s %-30s %5d\n", tickets[i].uniqueNumber, tickets[i].accountNumber, tickets[i].messages->customerName, tickets[i].TicketStatus == 1 ? "ACTIVE" : "CLOSED", tickets[i].subject, tickets[i].numofMessages);

        }
    }
}

void displayTicketClientTicketInfo(const struct Ticket tickets[], const struct Account* account, int ticketSize) {
    int i;
    for (i = 0; i < ticketSize; ++i) {
        if (tickets[i].accountNumber == account->accountNumber) {
            printf("%06d %-6s %-30s %5d\n", tickets[i].uniqueNumber, tickets[i].TicketStatus == 1 ? "ACTIVE" : "CLOSED", tickets[i].subject, tickets[i].numofMessages);
        }
    }
}

void displayTicket(const struct Ticket tickets[], const struct Account* account, int ticketSize, int option) {
    int arrNum;
    int x = 0;
    while (x != -1) {

        if (option == 6 || option == 7 || option == 8) {
            printf("------ ----- --------------- ------ ------------------------------ --------\n");
            printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
            printf("------ ----- --------------- ------ ------------------------------ --------\n");
            if (option == 7) {
                displayAgentTicketInfoAll(tickets, account, ticketSize);
            }
            else if (option == 6) {
                displayAgentTicketInfoNew(tickets, account, ticketSize);
            }
            else if (option == 8) {
                displayAgentTicketInfoAllClosed(tickets, account, ticketSize);
            }
            printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
        }
        else if (option == 4) {
            printf("------ ------ ------------------------------ --------\n");
            printf("Ticket Status Subject                        Messages\n");
            printf("------ ------ ------------------------------ --------\n");

            displayTicketClientTicketInfo(tickets, account, ticketSize);

            printf("------ ------ ------------------------------ --------\n\n");
        }

        printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");

        arrNum = findTicketIndexByAcctNum(tickets, ticketSize, account, option);
        if (arrNum == -3) {
            putchar('\n');
            printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
            pauseExecution();
            putchar('\n');
        }
        else if (arrNum == -2) {
            putchar('\n');
            printf("ERROR: Invalid ticket number.\n\n");
            pauseExecution();
            putchar('\n');
        }
        else if (arrNum == -1) {
            putchar('\n');
            x = arrNum;

        }
        else {
            putchar('\n');
            printf("================================================================================\n");
            printf("%06d (%s) Re: %s\n", tickets[arrNum].uniqueNumber, tickets[arrNum].TicketStatus == 1 ? "ACTIVE" : "CLOSED", tickets[arrNum].subject);
            printf("================================================================================\n");
            int i;

            for (i = 0; i < tickets[arrNum].numofMessages; ++i) {
                if (tickets[arrNum].messages[i].accountType != '\0') {
                    printf("%s (%s):\n", tickets[arrNum].messages[i].accountType == 'A' ? "AGENT" : "CUSTOMER", tickets[arrNum].messages[i].customerName);
                    printf("   %s\n", tickets[arrNum].messages[i].messageDet);
                    putchar('\n');
                }
                if (((i + 1) % 5) == 0) {
                    pauseExecution();
                    putchar('\n');
                }
            }
            if ((i % 5) != 0) {
                pauseExecution();
                putchar('\n');
            }
        }
    }
}

//MODIFY TICKETS

void updateTicket(struct Ticket tickets[], const struct Account* acc, int size) {
    int ticketnumber;
    
    int error = 0; 
    int index = -1;
    
    printf("Enter ticket number: ");
    ticketnumber = getPositiveInteger();
    index = findTicketIndex(tickets, acc, ticketnumber, size);
    
    
        if (index == -1) {
            printf("\nERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
            pauseExecution();
            putchar('\n');
        }
        else if (tickets[index].TicketStatus == 0)
        {
            printf("\nERROR: Ticket is closed - changes are not permitted.\n\n");
            pauseExecution();
            putchar('\n');
        }
        else {
            int option;
            do {
                printf("\n----------------------------------------\n");
                printf("Ticket %06d - Update Options\n", tickets[index].uniqueNumber);
                printf("----------------------------------------\n");
                printf("Status  : %s\n", tickets[index].TicketStatus == 1 ? "ACTIVE" : "CLOSED");
                printf("Subject : %s\n", tickets[index].subject);
                printf("----------------------------------------\n");
                printf("1) Modify the subject\n");
                printf("2) Add a message\n");
                printf("3) Close ticket\n");
                printf("0) Done\n");
                printf("Selection: ");
                option = getIntFromRange(0, 3);
                putchar('\n');
                if (option == 1) {
                    printf("Enter the revised ticket SUBJECT (30 chars. maximum): ");
                    getCString(tickets[index].subject, 0, 30);
                }

                else if (option == 2) {
                    if (tickets[index].TicketStatus == 0) {
                        printf("ERROR: Ticket is closed - new messages are not permitted.\n");
                    }
                    else {
                        if (tickets[index].numofMessages < 20) {
                            printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                            addMessage(&tickets[index], acc);
                        }
                        else {
                            printf("ERROR: Message limit has been reached, call ITS Support!\n");
                        }
                    }
                }

                else if (option == 3) {
                    if (tickets[index].TicketStatus == 0) {
                        printf("ERROR: Ticket is already closed!\n");
                    }
                    else {
                        char charoption;
                        //int messInd = 0;
                        printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                        charoption = getCharOption("YN");
                        putchar('\n');

                        if (charoption == 'Y') { // If yes do following:
                            tickets[index].TicketStatus = 0;
                            if (tickets[index].numofMessages < 20) {
                                printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
                                charoption = getCharOption("YN");
                                putchar('\n');
                                if (charoption == 'Y') {
                                    printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                                    addMessage(&tickets[index], acc);
                                    putchar('\n');
                                }
                            }

                            printf("*** Ticket closed! ***\n\n");
                            pauseExecution();
                            putchar('\n');
                            break;

                        }
                    }
                }
                else if (option == 0) {
                    pauseExecution();
                    putchar('\n');
                }

            } while (option != 0 && error != 1);
        }
   

}

void updateTicketAgent(struct Ticket tickets[], const struct Account* acc, int size) {
    int ticketnumber;
    int error = 0;
    int index = -1;

    printf("Enter ticket number: ");
    ticketnumber = getPositiveInteger();
    index = findTicketIndexAgent(tickets, ticketnumber, size);
    if (index == -1) {
        printf("\nERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
        pauseExecution();
        putchar('\n');
    }
    else {
        int option;
        do {
            
            printf("\n----------------------------------------\n");
            printf("Ticket %06d - Update Options\n", tickets[index].uniqueNumber);
            printf("----------------------------------------\n");
            printf("Status  : %s\n", tickets[index].TicketStatus == 1 ? "ACTIVE" : "CLOSED");
            printf("Subject : %s\n", tickets[index].subject);
            printf("Acct#   : %d\n", tickets[index].accountNumber);
            printf("Customer: %s\n", tickets[index].messages[0].customerName);
            printf("----------------------------------------\n");
            printf("1) Add a message\n");
            printf("2) Close ticket\n");
            printf("3) Re-open ticket\n");
            printf("0) Done\n");
            printf("Selection: ");
            option = getIntFromRange(0, 3);
            
            putchar('\n');
            if (option == 1) {
                if (tickets[index].TicketStatus == 0) {
                    printf("ERROR: Ticket is closed - new messages are not permitted.\n");
                }
                else {
                    if (tickets[index].numofMessages < 20) {
                        printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                        addMessage(&tickets[index], acc);
                    }
                    else {
                        printf("ERROR: Message limit has been reached, call ITS Support!\n");
                    }
                }
            }

            else if (option == 2) {
                if (tickets[index].TicketStatus == 0) {
                    printf("ERROR: Ticket is already closed!\n");
                }
                else {
                    char charoption;
                    
                    printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                    charoption = getCharOption("YN");
                    putchar('\n');

                    if (charoption == 'Y') { // If yes do following:
                        tickets[index].TicketStatus = 0; //Close the ticket assigning zero to ticket status
                        
                        if (charoption == 'Y') { // If yes do following:
                            tickets[index].TicketStatus = 0;
                            if (tickets[index].numofMessages < 20) {
                                printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
                                charoption = getCharOption("YN");
                                putchar('\n');
                                if (charoption == 'Y') {
                                    printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                                    addMessage(&tickets[index], acc);
                                    putchar('\n');
                                }
                            }
                            printf("*** Ticket closed! ***\n");
                        }
                        
                    }
                }
            }

            else if (option == 3) {
                char charoption;
                if (tickets[index].TicketStatus == 1) {
                    printf("ERROR: Ticket is already active!\n");
                }
                else {
                    printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
                    charoption = getCharOption("YN");
                    
                    if (charoption == 'Y') {
                        tickets[index].TicketStatus = 1;
                        printf("\n*** Ticket re-opened! ***\n");
                    }
                }
            }
        } while (option != 0 && error != 1);
    }

}
//HELPERS

int highestTicket(const struct Ticket tickets[], int size) {
    int x = 0;
    int i;
    for (i = 0; i < size; ++i) {
        if (x < tickets[i].uniqueNumber) {
            x = tickets[i].uniqueNumber;
        }
    }
    return x;
}

int zeroTicketAccNum(const struct Ticket tickets[], int size) {
    int b = -1;
    int i;
    for (i = 0; i < size; i++) {
        if (tickets[i].uniqueNumber == 0) {
            b = i;
            break;
        }
    }
    return b;
}

void addMessage(struct Ticket* ticket, const struct Account* acc) {
    int i;
    int messInd = 0;
    for (i = 0; i <= ticket->numofMessages; ++i) {
        if (ticket->messages[i].accountType == '\0') {
            messInd = i;
        }
    }
    getCString(ticket->messages[messInd].messageDet, 0, 150);
    ticket->numofMessages += 1;
    ticket->messages[messInd].accountType = acc->accountType;
    strcpy(ticket->messages[messInd].customerName, acc->userlogin.customerName);
}

int findTicketIndex(const struct Ticket tickets[], const struct Account* acc, int ticketnumber, int size) {
    int index = -1;
    int i;
    for (i = 0; i < size; ++i) {

        if (tickets[i].uniqueNumber == ticketnumber && tickets[i].accountNumber == acc->accountNumber) {
            index = i;
        }
    }
    return index;
}

int findTicketIndexAgent(const struct Ticket tickets[], int ticketnumber, int size) {
    int index = -1;
    int i;
    for (i = 0; i < size; ++i) {
        if (tickets[i].uniqueNumber == ticketnumber) {
            index = i;
        }
    }
    return index;
}

//ARCHIVE TICKETS

void archiveCloseTickets(struct Ticket* tickets, int size) {
    int i = 0, j, arc_tickets = 0;
    int option;
    printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
    option = getCharOption("YN");
    putchar('\n');

    if (option == 'Y') {
        for (j = 0; j < size; ++j) {
            if (tickets[j].TicketStatus == 0) {
                ++arc_tickets;
            }
        }
        FILE* fp = fopen("tickets_arc.txt", "a");
        if (fp != NULL) {
            while (i < size) {
                if (tickets[i].TicketStatus == 0 && tickets[i].uniqueNumber != 0) {
                    fprintf(fp, "%d|%d|%d|%s|%d|",
                        tickets[i].uniqueNumber,
                        tickets[i].accountNumber,
                        tickets[i].TicketStatus,
                        tickets[i].subject,
                        tickets[i].numofMessages);
                    for (j = 0; j < tickets[i].numofMessages; ++j) {
                        fprintf(fp, "%c|%s|%s|",
                            tickets[i].messages[j].accountType,
                            tickets[i].messages[j].customerName,
                            tickets[i].messages[j].messageDet);
                    }
                    fprintf(fp, "\n");
                    tickets[i].uniqueNumber = 0;
                }
                i++;
            }
        }
        fclose(fp);
        printf("*** %d tickets archived ***\n\n", --arc_tickets);
    }

}

void archivedTicketsStatistics() {
    int ticketNumber;
    int i, numoftickets = 0;
    int accountNumber = 0, ticketStatus = 0, numofMessages = 0;
    int n = 0;
    char subject[31];

    FILE* fp = fopen("tickets_arc.txt", "r");
    if (fp != NULL) {
        for (i = 1; fscanf(fp, "%d|%d|%d|%[^|]|%d|%*[^\n]",
            &ticketNumber,
            &accountNumber,
            &ticketStatus,
            subject,
            &numofMessages) != EOF; ++i) {
            if (ticketNumber > 0) {
                numoftickets = i;
                n = n + numofMessages;
            }
        }

    }
    fclose(fp);
    printf("There are %d ticket(s) and a total of %d message(s) archived.\n", numoftickets, n);
}

void archiveCloseTicketsAccount(struct Ticket* tickets, struct Account* acc, int size) {
    int i, j;

    FILE* fp = fopen("tickets_arc.txt", "a");
    if (fp == NULL) {
        printf("1\n");
    }
    else if (fp != NULL) {
        for (i = 0; i < size; ++i) {

            if (tickets[i].TicketStatus == 0 && tickets[i].uniqueNumber != 0 && tickets[i].accountNumber == acc->accountNumber) {
                
                fprintf(fp, "%d|%d|%d|%s|%d|",
                    tickets[i].uniqueNumber,
                    tickets[i].accountNumber,
                    tickets[i].TicketStatus,
                    tickets[i].subject,
                    tickets[i].numofMessages);
                for (j = 0; j < tickets[i].numofMessages; ++j) {
                    fprintf(fp, "%c|%s|%s|",
                        tickets[i].messages[j].accountType,
                        tickets[i].messages[j].customerName,
                        tickets[i].messages[j].messageDet);
                }
                fprintf(fp, "\n");
                tickets[i].uniqueNumber = 0;
            }
        }
        fclose(fp);
    }
}

int saveTickets(struct Ticket *tickets, int ticktSize) {
    int i = 0, j, numoftickets = 0;
        FILE* fp = fopen("tickets.txt", "w");
        if (fp != NULL) {
            for (i = 0; i < ticktSize; ++i) {
                if (tickets[i].uniqueNumber != 0) {
                    fprintf(fp, "%d|%d|%d|%s|%d|",
                        tickets[i].uniqueNumber,
                        tickets[i].accountNumber,
                        tickets[i].TicketStatus,
                        tickets[i].subject,
                        tickets[i].numofMessages);
                    for (j = 0; j < tickets[i].numofMessages; ++j) {
                        fprintf(fp, "%c|%s|%s|",
                            tickets[i].messages[j].accountType,
                            tickets[i].messages[j].customerName,
                            tickets[i].messages[j].messageDet);
                    }
                    fprintf(fp, "\n");
                    numoftickets++;
                }
               
            }
        }
        fclose(fp);
        return numoftickets;
}
