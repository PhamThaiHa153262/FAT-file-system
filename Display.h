#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdio.h>
#include <stdint.h>
#include "LinkedList.h"
#include "FatLib.h"

void FAT_Print_header();
void FAT_Print_List_Files(Entries entriesArr);

#endif		/* _DISPLAY_H_ */
