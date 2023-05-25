#include <stdio.h>
#include <stdbool.h>

#define PAGE_SIZE 256
#define PAGE_TABLE_SIZE 256
#define FRAME_SIZE 256
#define FRAME_TABLE_SIZE 256
#define MEMORY_SIZE (FRAME_SIZE * FRAME_TABLE_SIZE)

int main()
{
    int pageTable[PAGE_TABLE_SIZE];
    int frameTable[FRAME_TABLE_SIZE];
    char memory[MEMORY_SIZE];

    int i;
    for (i = 0; i < PAGE_TABLE_SIZE; i++)
    {
        pageTable[i] = -1; // Initialize page table entries as invalid (-1)
    }

    for (i = 0; i < FRAME_TABLE_SIZE; i++)
    {
        frameTable[i] = -1; // Initialize frame table entries as empty (-1)
    }

    printf("Paging Simulation\n");

    while (true)
    {
        int logicalAddress;
        printf("\nEnter a logical address (0 to quit): ");
        scanf("%d", &logicalAddress);

        if (logicalAddress == 0)
        {
            break;
        }

        // Extract page number and offset from the logical address
        int pageNumber = (logicalAddress & 0xFF00) >> 8;
        int offset = logicalAddress & 0x00FF;

        // Check if the page is in memory (page table entry is valid)
        if (pageTable[pageNumber] != -1)
        {
            int frameNumber = pageTable[pageNumber];
            int physicalAddress = (frameNumber * FRAME_SIZE) + offset;
            char data = memory[physicalAddress];
            printf("Physical address: %d\n", physicalAddress);
            printf("Data at physical address %d: %c\n", physicalAddress, data);
        }
        else
        {
            // Page fault: Page is not in memory, allocate a free frame
            int freeFrame = -1;
            for (i = 0; i < FRAME_TABLE_SIZE; i++)
            {
                if (frameTable[i] == -1)
                {
                    freeFrame = i;
                    break;
                }
            }

            if (freeFrame == -1)
            {
                printf("Memory is full. Unable to allocate a free frame.\n");
                continue;
            }

            // Load the page from disk into memory
            pageTable[pageNumber] = freeFrame;
            frameTable[freeFrame] = pageNumber;

            // Simulate loading the page from disk (setting memory content)
            printf("Page fault occurred. Page loaded from disk into memory.\n");
            printf("Page number: %d\n", pageNumber);
            printf("Frame number: %d\n", freeFrame);

            // Set the memory content for the allocated frame
            int startAddress = freeFrame * FRAME_SIZE;
            int endAddress = startAddress + FRAME_SIZE;
            for (i = startAddress; i < endAddress; i++)
            {
                memory[i] = 'A' + (i % 26); // Setting some sample data for the frame
            }

            // Calculate the physical address and retrieve the data
            int physicalAddress = (freeFrame * FRAME_SIZE) + offset;
            char data = memory[physicalAddress];
            printf("Physical address: %d\n", physicalAddress);
            printf("Data at physical address %d: %c\n", physicalAddress, data);
        }
    }

    return 0;
}
