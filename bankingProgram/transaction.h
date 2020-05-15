//
//  transaction.h
//  bankingProgram
//
//  Created by Geiszt Adél on 2020. 05. 15..
//  Copyright © 2020. Geiszt Adél. All rights reserved.
//

#ifndef transaction_h
#define transaction_h

struct Transaction {
    char *accNr;
    char *valueDate;
    double transactAmt;

};
struct TransactionLinkedListNode {
    struct Transaction *transact;
    struct TransactionLinkedListNode *prev;
    struct TransactionLinkedListNode *next;
};

struct TransactionLinkedListNode *readTransactHistory(const char*);
void freeTransactionLinkedList(struct TransactionLinkedListNode *head2);
void printTransactionLinkedList(const struct TransactionLinkedListNode *head);
void deposit(struct AccountLinkedListNode *head, const char *, const char *);
void withdraw(struct AccountLinkedListNode *head, const char *, const char *);
void saveTransactRecord(const char *, char *, double amount);
void fileWriteUpdatedLinkedList(const char*, struct AccountLinkedListNode *head);

#endif /* transaction_h */
