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

void menu(void);
void display(void);


struct Date{
    int month,day,year;

    };
struct Account{

    char *name;
    char *accNr;
    char *address;
    char *citizenship;
    char *phone;
    char *accType;
    double accBalance;

};

struct LinkedListNode{
    struct Account *data;
    struct LinkedListNode *prev;
    struct LinkedListNode *next;
    
};

struct LinkedListNode* readFile(void);
struct LinkedListNode *head;

int main() {
    head = readFile();
    menu();
        return 0;
}

void menu(void)
{   int choose;

    printf("Main menu \n\n");
    printf("Press 1 to display account\n");
    printf("Press 2 to deposit money to account\n");
    printf("Press 3 to withdraw money from account\n");
    printf("Press 4 to display transaction history\n");
    printf("Press 5 to exit\n\n");
    printf("Select a menu item:\n");
    scanf("%d",&choose);

    //system("clear");
    
    switch (choose) {
      case 1: {
          printf("Account display\n");
      
          break;
      }
      case 2: {
          printf("Deposit menu\n");
      
          break;
      }
      case 3: {
          printf("Withdraw menu\n");
     
          break;
      }
      case 4: {
          printf("Transaction history\n");
        
          break;
      }
      case 5: {
          printf("Exit sucessful.\n");
          
          break;
      }
      default:
          printf("Error! There is no such option.\n");
      }
}

struct LinkedListNode* readFile() {
    
    FILE *ptr;
    
    ptr=fopen("account.csv","r");
    if (ptr == NULL) {
           printf("Cannot open file \n");
           exit(0);
    }
    
    struct LinkedListNode *firstNode = NULL;
    struct LinkedListNode *lastNode = NULL;
    char name[60], accNr[60], address[60], citizenship[60], phone[60], accType[60];
    double accBalance;

    while (fscanf(ptr, "%s,%s,%s,%s,%s,%s,%lf",
                  name,
                  accNr,
                  address,
                  citizenship,
                  phone,
                  accType,
                  &accBalance) != EOF) {
        struct LinkedListNode *nextNode = malloc(sizeof(struct LinkedListNode));
        lastNode->data = malloc(sizeof(struct Account));
        
        unsigned long nameLength = strlen(name);
        lastNode->data->name = malloc(sizeof(char) * nameLength);
        strncpy(name, lastNode->data->name, nameLength);
        
        unsigned long accNrLength = strlen(accNr);
        lastNode->data->accNr = malloc(sizeof(char) * accNrLength);
        strncpy(accNr, lastNode->data->accNr, accNrLength);
        
        unsigned long addressLength = strlen(address);
        lastNode->data->address = malloc(sizeof(char) * addressLength);
        strncpy(address, lastNode->data->address, addressLength);
        
        unsigned long citizenshipLength = strlen(citizenship);
        lastNode->data->citizenship = malloc(sizeof(char) * citizenshipLength);
        strncpy(citizenship, lastNode->data->citizenship, citizenshipLength);
        
        unsigned long phoneLength = strlen(phone);
        lastNode->data->phone = malloc(sizeof(char) * phoneLength);
        strncpy(phone, lastNode->data->phone, phoneLength);
        
        unsigned long accTypeLength = strlen(accType);
        lastNode->data->accType = malloc(sizeof(char) * accTypeLength);
        strncpy(accType, lastNode->data->accType, accTypeLength);
        
        lastNode->data->accBalance = accBalance;
        
        nextNode->next = NULL;
        if (lastNode != NULL) {
            lastNode->next = nextNode;
            nextNode->prev = lastNode;
        } else {
            nextNode->prev = NULL;
            firstNode = nextNode;
            lastNode = firstNode;
        }
    }
    
    if (ptr != NULL) {
        fclose(ptr);
    }
    
    return firstNode;
}

void freeLinkedList(struct LinkedListNode *firstNode) {
    free(firstNode->data->accNr);
    free(firstNode->data->accType);
    free(firstNode->data->address);
    free(firstNode->data->citizenship);
    free(firstNode->data->name);
    free(firstNode->data->phone);
    free(firstNode->data);
    
    if(firstNode->next!=NULL) {
        freeLinkedList(firstNode->next);
    }
    free(firstNode);
}

void printFileContents() {
    struct LinkedListNode* temp = head;
    while(temp != NULL) {
        printf("%s",temp->data);
        temp = temp->next;
    }
    printf("\n");
}
