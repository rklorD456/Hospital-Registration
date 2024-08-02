#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct {
    u32 id;
    u32 age;
    char gender;
    char name[50];
} Data;

typedef struct Node {
    Data data;
    struct Node* next;
} node;

node* CreateNode(u32 id, u32 age, char gender, const char* name);

void insertFirst(u32 id, u32 age, char gender, const char* name);
void printListAsTable();
void printPatientByID(u32 id);

node* searchNodeByID(u32 id);

int searchByID(u32 id);

#endif
