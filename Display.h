#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdio.h>
#include <stdint.h>
#include "linkedlist.h"
#include "RootDirectory.h"

//void displayFATEntries(FILE* pFile, uint32_t startAddr, uint8_t entriesNum, Node** head);
void displayFAT(FILE* pFile, uint32_t rootStart, uint32_t dataStart);

#endif		/* _DISPLAY_H_ */
