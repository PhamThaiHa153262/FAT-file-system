#include "LinkedList.h"

static NodeType *HEAD = NULL;
static uint32_t Len = 0;
static uint16_t DataSize = 0;

// Create list
ListStatusType List_Create(uint16_t dataSize)
{
	if(DataSize == 0)
	{
		DataSize = dataSize;
	}
	
	return LIST_OK;
}

// Add node
ListStatusType List_AddFirst(uint8_t *Data)
{
	ListStatusType status = LIST_OK;
	
	if(DataSize > 0)
	{
		// create none type data block
		uint8_t *dataPtr = (uint8_t *)malloc(DataSize), i;
		if(dataPtr != NULL)
		{
			for(i=0; i<DataSize; i++)
			{
				*(dataPtr+i) = *(Data+i);
			}
		}
		else
		{
			status = LIST_OUT_OF_MEMORIES;
		}
		
		// create node
		NodeType *nodePtr = (NodeType*)malloc(sizeof(NodeType));
		if(nodePtr != NULL)
		{
			nodePtr->DataPtr = dataPtr;
			nodePtr->pNext = HEAD;
			HEAD = nodePtr;
			
			Len++;
		}
		else
		{
			status = LIST_OUT_OF_MEMORIES;
		}
	}
	else
	{
		status = LIST_NOT_CREATE;
	}
	
	return  status;
}

// Delete node by index
ListStatusType List_Delete(uint32_t index)
{
	ListStatusType status = LIST_OK;
	NodeType *current = HEAD, *tempPtr;
	uint32_t i=0;
	
	do
	{
		// Out of range
		if(index >= Len)
		{
			status = LIST_OUT_OF_RANGE;
			break;
		}
		
		// Delete first index
		if(index == 0)
		{
			HEAD = HEAD->pNext;
			free(current->DataPtr);
			free(current);
			Len--;
			break;
		}
		
		// Delete other index
		if(i == index-1)
		{
			tempPtr = current->pNext;
			current->pNext = current->pNext->pNext;
			free(tempPtr->DataPtr);
			free(tempPtr);
			Len--;
			break;
		}
		
		current = current->pNext;
		i++;
	}
	while(current != NULL);
	
	return status;
}

// Print All
/*
ListStatusType List_Print()
{
	NodeType *current = HEAD;
	
	while(current != NULL)
	{
		printf("%d ", current->DataPtr);
		current = current->pNext;
	}
	
	return LIST_OK;
}
*/

// Get value by index
ListStatusType List_GetData(uint8_t *dataRecv ,uint32_t index)
{
	NodeType *current = HEAD;
	uint32_t i = 0;
	
	if(index >= Len)
	{
		return LIST_OUT_OF_RANGE;
	}
	
	while(current != NULL)
	{
		if(i == index)
		{
			int i;
			//sent byte to data receiver
			for(i=0; i<DataSize; i++)
			{
				*(dataRecv+i) = *((current->DataPtr)+i);
			}
		}
		current = current->pNext;
		i++;
	}
	
	return LIST_OK;
}

// Get length
uint32_t List_GetLen()
{
	return Len;
}
