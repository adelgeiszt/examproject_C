//
//  account.c
//  
//
//  Created by Geiszt Adél on 2020. 05. 15..
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "account.h"
#include "transaction.h"

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

        unsigned long nameLength = strlen(name) + 1;
        nextNode->account->name = malloc(sizeof(char) * nameLength);
        strncpy(nextNode->account->name, name, nameLength);

        unsigned long accNrLength = strlen(accNr) + 1;
        nextNode->account->accNr = malloc(sizeof(char) * accNrLength);
        strncpy(nextNode->account->accNr, accNr, accNrLength);

        unsigned long addressLength = strlen(address) + 1;
        nextNode->account->address = malloc(sizeof(char) * addressLength);
        strncpy(nextNode->account->address, address, addressLength);

        unsigned long citizenshipLength = strlen(citizenship) + 1;
        nextNode->account->citizenship = malloc(sizeof(char) * citizenshipLength);
        strncpy(nextNode->account->citizenship, citizenship, citizenshipLength);

        unsigned long phoneLength = strlen(phone) + 1;
        nextNode->account->phone = malloc(sizeof(char) * phoneLength);
        strncpy(nextNode->account->phone, phone, phoneLength);

        unsigned long accTypeLength = strlen(accType) + 1;
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
void findAccByID(struct AccountLinkedListNode *head) {
    char userinputAccNr[MAX];
   
    const struct AccountLinkedListNode *current = head; // Initialize current
    printf("Enter the Account number: ");
    scanf("%s", userinputAccNr);
    
    int index;
    index = 0;

    while (current != NULL)
    {
        if(strcmp(current->account->accNr,userinputAccNr)==0) {
            printf("\n");
            printf("%-16s %s\n", "Full name:", current->account->name);
            printf("%-16s %s\n", "Account number:", current->account->accNr);
            printf("%-16s %s\n", "Address:", current->account->address);
            printf("%-16s %s\n", "Citizenship:", current->account->citizenship);
            printf("%-16s %s\n", "Phone number:", current->account->phone);
            printf("%-16s %s\n", "Account type:", current->account->accType);
            printf("%-16s %lf\n", "Account balance:", current->account->accBalance);
        }
        index++;
        current = current->next;
    }
}
void findAccByName(struct AccountLinkedListNode *head) {
    char userinputName[MAX];
   
    const struct AccountLinkedListNode *current = head;
    
    fflush(stdin);
    printf("Enter the full name: ");
    input(userinputName, sizeof(userinputName));
        
    int index;
    index = 0;

    while (current != NULL)
    {
        if(strcmp(current->account->name,userinputName)==0) {
            printf("\n");
            printf("%-16s %s\n", "Full name:", current->account->name);
            printf("%-16s %s\n", "Account number:", current->account->accNr);
            printf("%-16s %s\n", "Address:", current->account->address);
            printf("%-16s %s\n", "Citizenship:", current->account->citizenship);
            printf("%-16s %s\n", "Phone number:", current->account->phone);
            printf("%-16s %s\n", "Account type:", current->account->accType);
            printf("%-16s %lf\n", "Account balance:", current->account->accBalance);
        }
        index++;
        current = current->next;
    }
}
void newClient(const char *accountsFilePath) {
    FILE *filePtr = fopen(accountsFilePath, "a");
       if (filePtr == NULL) {
           printf("Cannot open file \n");
           exit(0);
       }
    
    char name[64], accNr[64], address[64], citizenship[64], phone[64], accType[64];
    double accBalance;
  
    // Read data
    fflush(stdin); //a menu valasztasnal kert be inputot, ami ures sort generalt tehat azt torli
    printf("\tFull name: ");
    input(name, sizeof(name));
    
    printf("\tAccount number: ");
    input(accNr, sizeof(accNr));
    
    printf("\tAddress: ");
    input(address, sizeof(address));
    
    printf("\tCitizenship: ");
    input(citizenship, sizeof(citizenship));
    
    printf("\tPhone: ");
    input(phone, sizeof(phone));
    
    printf("\tAccount type: ");
    input(accType, sizeof(accType));
    
    printf("\tAccount balance: ");
    scanf("%lf", &accBalance);
    
    // Save data
    fprintf(filePtr, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%lf\"", name, accNr, address, citizenship, phone, accType, accBalance);
    
    printf("\n\tAccount added.");
    fclose(filePtr);
}
void input(char *string,int length)
{
    fgets(string,length,stdin); //space kezelese
    while(*string != '\n')
        string++;
    *string = '\0';
}
