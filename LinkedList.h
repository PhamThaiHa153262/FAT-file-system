
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct 
{
    uint8_t data;
    struct Node* next;
} Node;


Node* LinkedList_CreateNode(uint8_t inputdata);
void LinkedList_AddNode(uint8_t inputdata);
void LinkedList_DeleteNode(uint8_t inputdata);
void LinkedList_Display();
uint32_t LinkedList_GetLength();
void LinkedList_PrintNodes();


#endif /* _LINKEDLIST_H */
