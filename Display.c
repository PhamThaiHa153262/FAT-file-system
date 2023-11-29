#include"Display.h"

void FAT_Print_header()
{
		// Print header
    printf("File Name               Type                    Size(bytes)             Date                    Time\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
}
void FAT_Print_List_Files(Entries entriesArr)
{

    // Iterate through root directory entries and print information
        PrintArray(entriesArr.FileName, 8, "%c");  
		printf("\t\t");
		printf("File ");     
		if (entriesArr.FileAttribute[0] == 0x10) 
        printf("Folder");
        else
        PrintArray(entriesArr.FileExtension, 3, "%c"); 
        printf("\t\t");
        if (entriesArr.FileAttribute[0] == 0x10) 
        printf(" ");
        else
        printf("%d",ArrFlipToNum(entriesArr.FileSize, 4));  
        printf("\t\t\t");
        printf("%02u/",(ArrFlipToNum(entriesArr.Date, 2)) & 0x1F); 
        printf("%02u/",(ArrFlipToNum(entriesArr.Date, 2) >> 5) & 0x0F);  
        printf("%d", ((ArrFlipToNum(entriesArr.Date, 2) >> 9) & 0x7F)+1980  );  
        printf("\t\t");
        printf("%02u:",(ArrFlipToNum(entriesArr.Time, 2) >> 11) & 0x1F); 
        printf("%02u:",(ArrFlipToNum(entriesArr.Time, 2) >> 5) & 0x3F); 
		printf("%02u\n", ArrFlipToNum(entriesArr.Time, 2)  & 0x1F); 
}
