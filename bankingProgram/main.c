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
void freeAccountLinkedList(struct AccountLinkedListNode *head);
void printAccountLinkedList(const struct AccountLinkedListNode *head);
void findClientbyAccNr(struct AccountLinkedListNode *head);
void deposit(struct AccountLinkedListNode *head);
void withdraw(struct AccountLinkedListNode *head);
void saveTransactRecord(void);
void input(char *string,int length);
void newClient(const char*);



int main() {
    int choice;
    printf("MAIN MENU");
    printf("\n\n\t 1. Display all accounts\n\t 2. Find account by ID \n\t 3. Deposit money\n\t 4. Withdraw money\n\t 5. Transaction history \n\t 6. Add client \n\n\t Select a module: ");
    scanf("%d",&choice);
    //system("clear");
    
    const char *accountsFilePath ="/Users/geisztadel/account2.csv";
    struct AccountLinkedListNode *head = readAccountsFile(accountsFilePath);

    
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
            case 3:
                readAccountsFile(accountsFilePath);
                deposit(head);
                freeAccountLinkedList(head);
                break;
            case 4:
                readAccountsFile(accountsFilePath);
                withdraw(head);
                freeAccountLinkedList(head);
                break;
            case 5:
                printf("Transaction history");
                break;
            case 6:
                newClient(accountsFilePath);
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

void findClientbyAccNr(struct AccountLinkedListNode *head) {
    char userinput[MAX];
   
    const struct AccountLinkedListNode *current = head; // Initialize current
    printf("\n\nEnter the Account number: ");
    scanf("%s", userinput);
    
    int index;
    index = 0;

    // Iterate till last element until key is not found
    while (current != NULL)
    {
        if(strcmp(current->account->accNr,userinput)==0) {
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

void deposit(struct AccountLinkedListNode *head) {
    char useraccnr[MAX];
    double userdeposit;
      
    const struct AccountLinkedListNode *current = head; // Initialize current
    printf("\n\nEnter the Account number: ");
    scanf("%s", useraccnr);
       
    int index;
    index = 0;

    while (current != NULL)
    {
           if(strcmp(current->account->accNr,useraccnr)==0) {
               printf("\n");
               printf("%-16s %lf\n", "Available balance:", current->account->accBalance);
               printf("\n");
               printf("Enter the amount of the deposit: ");
               scanf("%lf", &userdeposit);
               current->account->accBalance = current->account->accBalance + userdeposit;
               printf("\nDeposit successful.\n");
               printf("%-16s %lf\n", "Available balance:", current->account->accBalance);
           }
           index++;
           current = current->next;
       }
    
}

void withdraw(struct AccountLinkedListNode *head) {
        char useraccnr[MAX];
        double userwithdraw;
          
        const struct AccountLinkedListNode *current = head; // Initialize current
        printf("\n\nEnter the Account number: ");
        scanf("%s", useraccnr);
           
        int index;
        index = 0;

        while (current != NULL)
        {
               if(strcmp(current->account->accNr,useraccnr)==0) {
                   printf("\n");
                   printf("%-16s %lf\n", "Available balance:", current->account->accBalance);
                   printf("\n");
                   printf("Enter the amount of the withdrawal: ");
                   scanf("%lf", &userwithdraw);
                   current->account->accBalance = current->account->accBalance - userwithdraw;
                   printf("\nWithdrawal successful.\n");
                   printf("%-16s %lf\n", "Available balance:", current->account->accBalance);
               }
               index++;
               current = current->next;
           }
        
    }
void saveTransactRecord(void) {
    //TODO
}

void input(char *string,int length)
{
    fgets(string,length,stdin);
    while(*string != '\n')
        string++;
    *string = '\0';
}

void newClient(const char *accountsFilePath) {
    FILE *filePtr = fopen(accountsFilePath, "a");
       if (filePtr == NULL) {
           printf("Cannot open file \n");
           exit(0);
       }
    
    char name[64], accNr[64], address[64], citizenship[64], phone[64], accType[64];
    double accBalance;
    //int i;
    
  
    // Read data
    fflush(stdin);
    printf("\tFull name: ");
    //fgets(name,sizeof(name),stdin);
    input(name, sizeof(name));

    
    printf("\tAccount number: ");
    //fgets(accNr,sizeof(accNr),stdin);
    input(accNr, sizeof(accNr));
    
    printf("\tAddress: ");
    //fgets(address,sizeof(address),stdin);
    input(address, sizeof(address));
    
    printf("\tCitizenship: ");
    //fgets(citizenship,sizeof(citizenship),stdin);
    input(citizenship, sizeof(citizenship));
    
    printf("\tPhone: ");
    //fgets(phone,sizeof(phone),stdin);
    input(phone, sizeof(phone));
    
    printf("\tAccount type: ");
    //fgets(accType,sizeof(accType),stdin);
    input(accType, sizeof(accType));
    
    printf("\tAccount balance: ");
    scanf("%lf", &accBalance);
    
    // Save data
    fprintf(filePtr, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%lf\"", name, accNr, address, citizenship, phone, accType, accBalance);
    
    fclose(filePtr);
}



