#include "Display.h"
#include "RootDirectory.h"
#include "LinkedList.h"
#include <math.h>
#define ROOT_DIRECTORY_SIZE 11
#define SECTOR_SIZE 512
//#pragma pack(1)
// //Function to print the list of files
//void FAT_Print_List_Files()
//{
//	uint8_t i;
//	// Print header
//    printf("File Name           Type                 Size              Date                   Time\n");
//    printf("-----------------------------------------------------------------------------------------\n");
//
//    // Iterate through root directory entries and print information
//    for ( i = 0; i < ROOT_DIRECTORY_SIZE; i++) 
//    {
//        if (entriesArr[i].FileAttribute != 0x10)
//        {
//        	i++;
//        }
//        printf("%s         %s                 %d               %d/%d/%d              %d:%d:%d \n",
//               entriesArr[i].FileName,
//               entriesArr[i].FileExtension,
//               //(root_directory[i].attributes & 0x10) ? 'D' : 'F',
//               entriesArr[i].FileSize,
//               ((entriesArr[i].Date >> 9) & 0x7F) + 1980,
//               (entriesArr[i].Date >> 5) & 0x0F,
//               entriesArr[i].Date & 0x1F,
//               (entriesArr[i].Time >> 11) & 0x1F,
//               (entriesArr[i].Time >> 5) & 0x3F,
//               (entriesArr[i].Time ) & 0x1F);
//    }
//}
//
//void displayFATEntries(FILE* pFile, uint32_t startAddr, uint8_t entriesNum, Node** head)
//{
//    Entries* entriesArr = (Entries*)malloc(entriesNum * sizeof(Entries));
//    FAT_ReadEntries(pFile, startAddr, entriesNum, entriesArr);
//
//    uint8_t i;
//    printf("File Name           Type                 Size              Date                   Time\n");
//    printf("-----------------------------------------------------------------------------------------\n");
//    for (i = 0; i < entriesNum; i++)
//    {
//        if (entriesArr[i].FileAttribute[1] == 0x10)
//        {
//            // ignore sub-folders
//            continue;
//        }
//
//        uint32_t fileSize = ArrFlipToNum(entriesArr[i].FileSize, 4);
//        uint32_t clusterAddr = FAT_ClusterAddr(startAddr, ArrFlipToNum(entriesArr[i].ClusterNum, 2));
//
//        LinkedList_AddNode(head, clusterAddr, fileSize);
//        printf("%s         %s                 %d               %d/%d/%d              %d:%d:%d \n",
//    }
//	
//    free(entriesArr);
//    
//}
Entries entriesArr[ROOT_DIRECTORY_SIZE];
void displayFAT(FILE* pFile, uint32_t rootStart, uint32_t dataStart)
{
    uint8_t entriesNum = FAT_EntriesCount(pFile, rootStart);
    Entries* entriesArr = (Entries*)malloc(ROOT_DIRECTORY_SIZE * sizeof(Entries));
    FAT_ReadEntries(pFile, rootStart, entriesNum, entriesArr);

    Node* head = NULL;

    uint8_t i;
    printf("File Name           Type                 Size              Date                   Time\n");
    printf("-----------------------------------------------------------------------------------------\n");

    for (i = 0; i < entriesNum; i++)
    {
        if (entriesArr[i].FileAttribute[1] == 0x10)
        {
            uint32_t clusterAddr = FAT_ClusterAddr(dataStart, ArrFlipToNum(entriesArr[i].ClusterNum, 2));
            //displayFATEntries(pFile, clusterAddr, ROOT_DIRECTORY_SIZE, &head);
        }
        else
        {
            uint32_t fileSize = ArrFlipToNum(entriesArr[i].FileSize, 4);
            uint32_t clusterAddr = FAT_ClusterAddr(rootStart, ArrFlipToNum(entriesArr[i].ClusterNum, 2));

          
        }
    }

    LinkedList_Display(head);

    freeLinkedList(&head);
    free(entriesArr);
}

