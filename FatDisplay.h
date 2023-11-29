#include "FatLib.h"
#include "LinkedList.h"

#ifndef _DISPLAY_H
#define _DISPLAY_H

void FAT_Display(char *file);
void FAT_Print_header();
void read_file_content(Entries entry);
void FAT_Print_List_Files(Entries entriesArr);
void PrintArray(uint8_t input[], uint16_t Len, char *type);
Fat_Status InputCheck(char *input, uint8_t maxNum, uint8_t *returnNum);

#endif
