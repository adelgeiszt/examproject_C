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
void menu(void);
void freeAccountLinkedList(struct AccountLinkedListNode *head);
void printAccountLinkedList(const struct AccountLinkedListNode *head);
void findClientbyAccNr(struct AccountLinkedListNode *head);

int main() {
    int choice;
    printf("MAIN MENU");
    printf("\n\n\t 1.Display all accounts\n\t 2.Find account by ID \n\n\t Select a module:");
    scanf("%d",&choice);
    //system("clear");
    
    const char *accountsFilePath ="/Users/geisztadel/account2.csv";
    struct AccountLinkedListNode *head = readAccountsFile(accountsFilePath);
    //printAccountLinkedList(head);
    //freeAccountLinkedList(head);
    
    switch(choice)
        {
            case 1:
                readAccountsFile(accountsFilePath);
                printAccountLinkedList(head);
                freeAccountLinkedList(head);
                break;
            case 2:
                readAccountsFile(accountsFilePath);
                findClientbyAccNr(head);
                freeAccountLinkedList(head);
                break;
        }
    return 0;
}


struct AccountLinkedListNode *readAccountsFile(const char *accountsFilePath) {

    FILE *filePtr = fopen(accountsFilePath, "r");
    if (filePtr == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    struct AccountLinkedListNode *firstNode = NULL;
    struct AccountLinkedListNode *lastNode = NULL;

    char name[64], accNr[64], address[64], citizenship[64], phone[64], accType[64];
    double accBalance;

    while (fscanf(
            filePtr,
            "\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",\"%lf\"\n",
            name,
            accNr,
            address,
            citizenship,
            phone,
            accType,
            &accBalance
    ) != EOF) {
        struct AccountLinkedListNode *nextNode = malloc(sizeof(struct AccountLinkedListNode));
        nextNode->account = malloc(sizeof(struct Account));

        unsigned long nameLength = strlen(name);
        nextNode->account->name = malloc(sizeof(char) * nameLength);
        strncpy(nextNode->account->name, name, nameLength);

        unsigned long accNrLength = strlen(accNr);
        nextNode->account->accNr = malloc(sizeof(char) * accNrLength);
        strncpy(nextNode->account->accNr, accNr, accNrLength);

        unsigned long addressLength = strlen(address);
        nextNode->account->address = malloc(sizeof(char) * addressLength);
        strncpy(nextNode->account->address, address, addressLength);

        unsigned long citizenshipLength = strlen(citizenship);
        nextNode->account->citizenship = malloc(sizeof(char) * citizenshipLength);
        strncpy(nextNode->account->citizenship, citizenship, citizenshipLength);

        unsigned long phoneLength = strlen(phone);
        nextNode->account->phone = malloc(sizeof(char) * phoneLength);
        strncpy(nextNode->account->phone, phone, phoneLength);

        unsigned long accTypeLength = strlen(accType);
        nextNode->account->accType = malloc(sizeof(char) * accTypeLength);
        strncpy(nextNode->account->accType, accType, accTypeLength);

        nextNode->account->accBalance = accBalance;

        nextNode->next = NULL;
        if (lastNode != NULL) {
            lastNode->next = nextNode;
            nextNode->prev = lastNode;
        } else {
            nextNode->prev = NULL;
            firstNode = nextNode;
        }
        lastNode = nextNode;
    }

    fclose(filePtr);

    return firstNode;
}

void freeAccountLinkedList(struct AccountLinkedListNode *head) {
    free(head->account->accNr);
    free(head->account->accType);
    free(head->account->address);
    free(head->account->citizenship);
    free(head->account->name);
    free(head->account->phone);
    free(head->account);

    if (head->next != NULL) {
        freeAccountLinkedList(head->next);
    }

    free(head);
}

void printAccountLinkedList(const struct AccountLinkedListNode *head) {
    const struct AccountLinkedListNode *temp = head;
    while (temp != NULL) {
        if (temp != head) {
            printf("\n----------------------------\n\n");
        }

        printf("%-16s %s\n", "Full name:", temp->account->name);
        printf("%-16s %s\n", "Account number:", temp->account->accNr);
        printf("%-16s %s\n", "Address:", temp->account->address);
        printf("%-16s %s\n", "Citizenship:", temp->account->citizenship);
        printf("%-16s %s\n", "Phone number:", temp->account->phone);
        printf("%-16s %s\n", "Account type:", temp->account->accType);
        printf("%-16s %lf\n", "Account balance:", temp->account->accBalance);

        temp = temp->next;
    }
}

void findClientbyAccNr(struct AccountLinkedListNode *head) {
    char userinput[MAX];
   
    const struct AccountLinkedListNode *current = head; // Initialize current
    printf("Enter the Account number: ");
    scanf("%s", userinput);
    
    int index;
    index = 0;

    // Iterate till last element until key is not found
    while (current != NULL)
    {
        if(strcmp(current->account->accNr,userinput)==0) {
            //printf("%s %d", userinput, index);
            printf("%-16s %s\n", "Account number:", current->account->accNr);

        }
        index++;
        current = current->next;
    }
}


