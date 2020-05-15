//
//  account.h
//  bankingProgram
//
//  Created by Geiszt Adél on 2020. 05. 15..
//  Copyright © 2020. Geiszt Adél. All rights reserved.
//

#ifndef account_h
#define account_h
#define MAX 30

struct Account {
    char *name;
    char *accNr;
    char *address;
    char *citizenship;
    char *phone;
    char *accType;
    double accBalance;
};
struct AccountLinkedListNode {
    struct Account *account;
    struct AccountLinkedListNode *prev;
    struct AccountLinkedListNode *next;
};

struct AccountLinkedListNode *readAccountsFile(const char*);
void freeAccountLinkedList(struct AccountLinkedListNode *head);
void printAccountLinkedList(const struct AccountLinkedListNode *head);
void findAccByID(struct AccountLinkedListNode *head);
void findAccByName(struct AccountLinkedListNode *head);
void input(char *string,int length);
void newClient(const char*);

#endif /* account_h */
