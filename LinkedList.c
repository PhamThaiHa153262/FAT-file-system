#include "LinkedList.h"
#include "Display.h"
#include "RootDirectory.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


static Node* head = NULL;
static uint8_t Len = 0;

Node* LinkedList_CreateNode(uint8_t inputdata) 
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = inputdata;
    new_node->next = NULL;
    return new_node;
}
void LinkedList_AddNode(uint8_t inputdata) 
{
    Node* new_node = LinkedList_CreateNode(inputdata);

    if (head == NULL) {
        head = new_node;
    } else {
        Node* curr = head;

        while (curr->next != NULL) {
            curr = curr->next;
        }

        curr->next = new_node;
    }

    Len++;
}

void LinkedList_DeleteNode(uint8_t inputdata) 
{
    if (head == NULL) 
	{
        return;
    }

    Node* curr = head;
    Node* prev = NULL;

    if (curr->data == inputdata) 
	{
        head = curr->next;
        free(curr);
        Len--;
        return;
    }

    while (curr != NULL && curr->data != inputdata) 
	{
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return;
    }

    prev->next = curr->next;
    free(curr);
    Len--;
}

void LinkedList_Display() 
{
    Node* curr = head;

    while (curr != NULL) {
        printf("%d\n ", curr->data);
        curr = curr->next;
    }

    printf("\n");
}
//Operators(Create/add node/delete node)
uint32_t LinkedList_GetLength() 
{
    return Len;
}

void LinkedList_PrintNodes() 
{
    Node* curr = head;
    uint8_t count = 1;
    
    printf("Nodes: \n");
    
    while (curr != NULL) 
	{
        printf("Node %d: %d \n", count, curr->data);
        curr = curr->next;
        count++;
    }
    
    printf("\n");
}
void freeLinkedList() 
{
    Node* temp = head;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
