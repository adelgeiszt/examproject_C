//
//  main.c
//  bankingProgram
//
//  Created by Geiszt Adél on 2020. 03. 13..
//  Copyright © 2020. Geiszt Adél. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "account.h"
#include "transaction.h"

int main() {
    int choice;
    printf("MAIN MENU");
    printf("\n\n\t 1. Display all accounts\n\t 2. Find account by ID\n\t 3. Find account(s) by name\n\t 4. Cash deposit\n\t 5. Cash withdrawal\n\t 6. Transaction history\n\t 7. Add new client\n\n\t Select a module: ");
    scanf("%d",&choice);
    printf("\n");
    
    const char *transactLogFilePath = "/Users/geisztadel/transactlog.csv";
    const char *accountsFilePath ="/Users/geisztadel/account2.csv";
    struct AccountLinkedListNode *head = readAccountsFile(accountsFilePath);
    struct TransactionLinkedListNode *head2 = readTransactHistory(transactLogFilePath);

    switch(choice)
        {
            case 1:
                readAccountsFile(accountsFilePath);
                printAccountLinkedList(head);
                freeAccountLinkedList(head);
                break;
            case 2:
                readAccountsFile(accountsFilePath);
                findAccByID(head);
                freeAccountLinkedList(head);
                break;
            case 3:
                readAccountsFile(accountsFilePath);
                findAccByName(head);
                freeAccountLinkedList(head);
                break;
            case 4:
                readAccountsFile(accountsFilePath);
                deposit(head, transactLogFilePath, accountsFilePath);
                freeAccountLinkedList(head);
                break;
            case 5:
                readAccountsFile(accountsFilePath);
                withdraw(head, transactLogFilePath, accountsFilePath);
                freeAccountLinkedList(head);
                break;
            case 6:
                readTransactHistory(transactLogFilePath);
                printTransactionLinkedList(head2);
                freeTransactionLinkedList(head2);
                break;
            case 7:
                newClient(accountsFilePath);
                break;
        }
    return 0;
}






