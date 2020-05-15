//
//  transaction.c
//  bankingProgram
//
//  Created by Geiszt Adél on 2020. 05. 15..
//  Copyright © 2020. Geiszt Adél. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "account.h"
#include "transaction.h"
#define MAX 64

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
    //Amount valtozoba, majd fajlba irom
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
    }

void saveTransactRecord(const char *transactLogFilePath, char *accNr, double amount) {
    FILE *filePtr = fopen(transactLogFilePath, "a");
        if (filePtr == NULL) {
            printf("Cannot open file \n");
            exit(0);
        }
    
    char timeBuffer[MAX];
    time_t current = time(NULL);
    struct tm* locTime = localtime(&current);
    strftime(timeBuffer, sizeof(timeBuffer),  "%a %m/%d/%Y %I:%M:%S %p", locTime);
         
     // Adat mentes
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
    
    char accNr[MAX], valueDate[MAX];
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
    
    const struct AccountLinkedListNode *current = head; // current inicializalas
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
