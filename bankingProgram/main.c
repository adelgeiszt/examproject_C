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

struct Transaction {
    char *accNr;
    char *valueDate;
    double transactAmt;

};

struct AccountLinkedListNode {
    struct Account *account;
    struct AccountLinkedListNode *prev;
    struct AccountLinkedListNode *next;
};

struct TransactionLinkedListNode {
    struct Transaction *transact;
    struct TransactionLinkedListNode *prev;
    struct TransactionLinkedListNode *next;
};


struct AccountLinkedListNode *readAccountsFile(const char*);
struct TransactionLinkedListNode *readTransactHistory(const char*);
void freeAccountLinkedList(struct AccountLinkedListNode *head);
void freeTransactionLinkedList(struct TransactionLinkedListNode *head2);
void printAccountLinkedList(const struct AccountLinkedListNode *head);
void printTransactionLinkedList(const struct TransactionLinkedListNode *head);
void findAccByID(struct AccountLinkedListNode *head);
void findAccByName(struct AccountLinkedListNode *head);
void deposit(struct AccountLinkedListNode *head, const char *, const char *);
void withdraw(struct AccountLinkedListNode *head, const char *, const char *);
void saveTransactRecord(const char *, char *, double amount);
void input(char *string,int length);
void newClient(const char*);
void fileWriteUpdatedLinkedList(const char*, struct AccountLinkedListNode *head);


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

void printTransactionLinkedList(const struct TransactionLinkedListNode *head2) {
    const struct TransactionLinkedListNode *current = head2;
    
    char userinput[MAX];
    printf("\n\nEnter the Account number: ");
    scanf("%s", userinput);
    
    int index;
    index = 0;
    
    while (current != NULL) {
        if (current != head2) {
            printf("\n");
        }
        if(strcmp(current->transact->accNr,userinput)==0) {
            printf("%-16s %s\n", "Account number:", current->transact->accNr);
            printf("%-16s %s\n", "Value date:", current->transact->valueDate);
            printf("%-16s %lf\n", "Transaction amount:", current->transact->transactAmt);
        }
        index++;
        current = current->next;
    }
}

void freeTransactionLinkedList(struct TransactionLinkedListNode *head2) {
    free(head2->transact->accNr);
    free(head2->transact->valueDate);
    free(head2->transact);

    if (head2->next != NULL) {
        freeTransactionLinkedList(head2->next);
    }

    free(head2);
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

void deposit(struct AccountLinkedListNode *head, const char *transactLogFilePath, const char *accountsFilePath) {
    char useraccnr[MAX];
    double userdeposit = 0;
      
    const struct AccountLinkedListNode *current = head; // Initialize current
    printf("\n\nEnter the Account number: ");
    scanf("%s", useraccnr);
       
    int index;
    index = 0;
    double depositAmount;

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
    //Store amount in a variable, write it to log file
    depositAmount = userdeposit;
    fileWriteUpdatedLinkedList(accountsFilePath, head);
    saveTransactRecord(transactLogFilePath, useraccnr, depositAmount);
    
}

void withdraw(struct AccountLinkedListNode *head, const char *transactLogFilePath, const char  *accountsFilePath) {
        char useraccnr[MAX];
        double userwithdraw = 0;
          
        const struct AccountLinkedListNode *current = head; // Initialize current
        printf("\nEnter the Account number: ");
        scanf("%s", useraccnr);
           
        int index;
        double withdrawalAmount;
        index = 0;

        while (current != NULL)
        {
               if(strcmp(current->account->accNr,useraccnr)==0) {
                   printf("\n");
                   printf("%-16s %lf\n", "Available balance:", current->account->accBalance);
                   printf("\n");
                   printf("Enter the amount of the withdrawal: ");
                   scanf("%lf", &userwithdraw);
                   if(current->account->accBalance >= userwithdraw) {
                       current->account->accBalance = current->account->accBalance - userwithdraw;
                       withdrawalAmount = -userwithdraw;
                       printf("\nWithdrawal successful.\n");
                       printf("%-16s %lf\n", "Available balance:", current->account->accBalance);
                       fileWriteUpdatedLinkedList(accountsFilePath, head);
                       saveTransactRecord(transactLogFilePath, useraccnr, withdrawalAmount);
                   } else {
                       printf("\nInvalid amount: not enough balance for withdrawal!\n");
                   }
               }
               index++;
               current = current->next;
           }
        //withdrawalAmount = -userwithdraw;
        //fileWriteUpdatedLinkedList(accountsFilePath, head);
        //saveTransactRecord(transactLogFilePath, useraccnr, withdrawalAmount);
    }

void saveTransactRecord(const char *transactLogFilePath, char *accNr, double amount) {
    FILE *filePtr = fopen(transactLogFilePath, "a");
        if (filePtr == NULL) {
            printf("Cannot open file \n");
            exit(0);
        }
    
    char timeBuffer[50];
    time_t current = time(NULL);
    struct tm* locTime = localtime(&current);
    strftime(timeBuffer, sizeof(timeBuffer),  "%a %m/%d/%Y %I:%M:%S %p", locTime);
         
     // Save data
    fprintf(filePtr, "\"%s\",\"%s\",\"%lf\"\n", accNr, timeBuffer, amount);
     
    fclose(filePtr);
     
}

struct TransactionLinkedListNode *readTransactHistory(const char *transactLogFilePath) {
    
    FILE *filePtr = fopen(transactLogFilePath, "r");
        if (filePtr == NULL) {
            printf("Cannot open file \n");
            exit(0);
        }
    
    struct TransactionLinkedListNode *firstNode = NULL;
    struct TransactionLinkedListNode *lastNode = NULL;
    
    char accNr[64], valueDate[64];
    double transactAmt;

       while (fscanf(
               filePtr,
               "\"%[^\"]\",\"%[^\"]\",\"%lf\"\n",
               accNr,
               valueDate,
               &transactAmt)!= EOF) {
           
             struct TransactionLinkedListNode *nextNode = malloc(sizeof(struct TransactionLinkedListNode));
               nextNode->transact = malloc(sizeof(struct Transaction));

               unsigned long accNrLength = strlen(accNr) + 1;
               nextNode->transact->accNr = malloc(sizeof(char) * accNrLength);
               strncpy(nextNode->transact->accNr, accNr, accNrLength);

               unsigned long valueDateLength = strlen(valueDate) + 1;
               nextNode->transact->valueDate = malloc(sizeof(char) * valueDateLength);
               strncpy(nextNode->transact->valueDate, valueDate, valueDateLength);
           
               nextNode->transact->transactAmt = transactAmt;

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


void fileWriteUpdatedLinkedList(const char *accountsFilePath, struct AccountLinkedListNode *head) {
    FILE *filePtr = fopen(accountsFilePath, "w");
         if (filePtr == NULL) {
             printf("Cannot open file \n");
             exit(0);
         }
    
    const struct AccountLinkedListNode *current = head; // Initialize current
    while (current != NULL)
    {
        fprintf(filePtr, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%lf\"\n",
                current->account->name,
                current->account->accNr,
                current->account->address,
                current->account->citizenship,
                current->account->phone,
                current->account->accType,
                current->account->accBalance);
        
        current= current->next;
    }
    
    fclose(filePtr);
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
  
    // Read data
    fflush(stdin);
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



