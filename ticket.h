// ===================================================================================
//
//  Assignment:  2 
//  Milestone:   4
//  Description: Tickets Header
// 
// ===================================================================================
// 
//  Name   : Semen Khlavich
//  ID: 107305203
//  Email : skhlavich@myseneca.ca
//  Section : NGG
//
// ===================================================================================

#ifndef TICKET_H_ 
#define TICKET_H_ 

typedef struct {
  char accountType;
  char customerName[31];
  char messageDet[151];
} Message;

struct Ticket {
  int uniqueNumber;
  int accountNumber;
  int TicketStatus;
  char subject[31];
  int numofMessages;
  Message messages[21]; 
};

//CREATE TICKET

void getTicket(struct Ticket tickets[], const struct Account* acc, int size);

//DISPLAY TICKETS

void displayTicketClientTicketInfo(const struct Ticket tickets[], const struct Account* account, int ticketSize);
void displayTicket(const struct Ticket tickets[], const struct Account* account, int ticketSize, int option);
void displayAgentTicketInfoAll(const struct Ticket tickets[], const struct Account* account, int ticketSize);
void displayAgentTicketInfoNew(const struct Ticket tickets[], const struct Account* account, int ticketSize);
void displayAgentTicketInfoAllClosed(const struct Ticket tickets[], const struct Account* account, int ticketSize);
//UPDATE TICKET

void updateTicket(struct Ticket tickets[], const struct Account* acc, int size);
void updateTicketAgent(struct Ticket tickets[], const struct Account* acc, int size);

//HELPERS

int highestTicket(const struct Ticket tickets[], int size);
int zeroTicketAccNum(const struct Ticket tickets[], int size);
void addMessage(struct Ticket* ticket, const struct Account* acc);
int findTicketIndex(const struct Ticket tickets[], const struct Account* acc, int ticketnumber, int size);
int findTicketIndexAgent(const struct Ticket tickets[], int ticketnumber, int size);

//ARCHIVE TICKETS

void archiveCloseTickets(struct Ticket* tickets, int size);
void archivedTicketsStatistics();
void archiveCloseTicketsAccount(struct Ticket* tickets, struct Account* account, int size);
int saveTickets(struct Ticket* tickets, int ticktSize);

#endif // !TICKET_H_