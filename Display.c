#include "FatLib.h"
#include "Display.h"
#include "LinkedList.h"
#define FileNameLen 8
#define FileExtensionLen 3
#define FileSizeLen 4
#define DateLen 2
#define TimeLen 2

void FAT_Print_header() {
    printf("File Name  Type       Size(Bytes)    Date       Time\n");
    printf("----------------------------------------------------------------------------------------------\n");
}

void FAT_Print_List_Files(Entries entriesArr) 
{
    PrintArray(entriesArr.FileName, FileNameLen, "%c");
    printf("\t\t\t");
    
    if (entriesArr.FileAttribute[0] == 0x10) 
	{
        printf("Folder\t\t\t");
    } else 
	{
        PrintArray(entriesArr.FileExtension, FileExtensionLen, "%c");
        printf("\t\t\t");
        uint32_t fileSize = ArrFlipToNum(entriesArr.FileSize, FileSizeLen);
	    printf("%d\t\t\t", fileSize);
	    
	    
	    uint8_t day = (ArrFlipToNum(entriesArr.Date, DateLen)) & 0x1F;
	    uint8_t month = (ArrFlipToNum(entriesArr.Date, DateLen) >> 5) & 0x0F;
	    uint16_t year = ((ArrFlipToNum(entriesArr.Date, DateLen) >> 9) & 0x7F) + 1980;
	    printf("%02u/ %02u/ %d\t\t", day, month, year);
	
	    uint8_t hour = (ArrFlipToNum(entriesArr.Time, TimeLen) >> 11) & 0x1F;
	    uint8_t minute = (ArrFlipToNum(entriesArr.Time, TimeLen) >> 5) & 0x3F;
	    uint8_t second = ArrFlipToNum(entriesArr.Time, TimeLen) & 0x1F;
	    printf("%02u: %02u: %02u\n", hour, minute, second);
    }
   
	    
}
