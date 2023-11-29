#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef _LISTLIB_H
#define _LISTLIB_H

typedef struct Node
{
	uint8_t *DataPtr;
	struct Node *pNext;
} NodeType;

typedef enum
{
	LIST_OK					= 0U,
	LIST_OUT_OF_RANGE		= 1U,
	LIST_OUT_OF_MEMORIES 	= 2U,
	LIST_NOT_CREATE			= 3U
} ListStatusType;

ListStatusType List_Create(uint16_t dataSize);
ListStatusType List_AddFirst(uint8_t *Data);
ListStatusType List_Delete(uint32_t index);
//ListStatusType List_Print();
ListStatusType List_GetData(uint8_t *dataRecv ,uint32_t index);
uint32_t List_GetLen();

#endif
