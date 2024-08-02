#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stdtypes.h"
#include "LINKEDLIST.h"

node* head = NULL;
node* tail = NULL;

node* CreateNode(u32 id, u32 age, char gender, const char* name) {
    node* NewNode = (node*)malloc(sizeof(node));
    NewNode->data.id = id;
    NewNode->data.age = age;
    NewNode->data.gender = gender;
    strcpy(NewNode->data.name, name);
    NewNode->next = NULL;
    return NewNode;
}

void insertFirst(u32 id, u32 age, char gender, const char* name) {
    node* NewNode = CreateNode(id, age, gender, name);
    if (head == NULL) {
        head = NewNode;
        tail = NewNode;
    } else {
        NewNode->next = head;
        head = NewNode;
    }
}

void printPatientByID(u32 id) {
    node* current = head;
    bool found = false;

    while (current != NULL) {
        if (current->data.id == id) {
            printf("Patient Record for ID: %u\n", current->data.id);
            printf("Age: %u\n", current->data.age);
            printf("Gender: %c\n", current->data.gender);
            printf("Name: %s\n", current->data.name);
            found = true;
            break; 
        }
        current = current->next;
    }

    if (!found) {
        printf("Patient with ID %u not found.\n", id);
    }
}
void printListAsTable()
{
    if (head == NULL)
	{
        printf("---------------------------->There is no patient data available<------------------.\n");
    }
	else
	{
        printf("--------------------------------------------------------------------------------------------\n");
        printf("| %-10s | %-30s | %-4s | %-3s |\n", "ID", "Name", "Age", "Gender");
        printf("|------------|--------------------------------|------|--------|\n");

        node* current = head;
        while (current != NULL)
		{
            printf("| %-10u | %-30s | %-4u | %-3c   |\n",
                   current->data.id, current->data.name, current->data.age, current->data.gender);
            current = current->next;
        }
        printf("--------------------------------------------------------------------------------------------\n");
    }
}


int searchByID(u32 id) {
    node* current = head;

    while (current != NULL) {
        if (current->data.id == id)
		{
            return 1; // ID found
        }
        current = current->next;
    }

    return 0; // ID not found
}

node* searchNodeByID(u32 id) {
    node* current = head;

    while (current != NULL) {
        if (current->data.id == id) {
            return current; // Return the pointer to the node with the matching ID
        }
        current = current->next;
    }

    return NULL; // ID not found
}

