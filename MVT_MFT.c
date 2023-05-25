#include <stdio.h>

#define MAX_BLOCKS 100

// Structure to represent a memory block
struct Block
{
    int id;
    int size;
    int processId;
};

// Function to allocate memory using MVT technique
void allocateMVT(struct Block blocks[], int n, int processId, int reqSize)
{
    int allocated = 0;

    for (int i = 0; i < n; i++)
    {
        if (blocks[i].processId == -1 && blocks[i].size >= reqSize)
        {
            blocks[i].processId = processId;
            allocated = 1;
            printf("Process %d allocated to Block %d\n", processId, blocks[i].id);
            break;
        }
    }

    if (!allocated)
    {
        printf("Insufficient memory to allocate Process %d\n", processId);
    }
}

// Function to allocate memory using MFT technique
void allocateMFT(struct Block blocks[], int n, int processId, int reqSize)
{
    int allocated = 0;

    for (int i = 0; i < n; i++)
    {
        if (blocks[i].processId == -1 && blocks[i].size >= reqSize)
        {
            int j = i;
            int count = 0;

            while (j < n && blocks[j].processId == -1 && blocks[j].size >= reqSize && count < reqSize)
            {
                blocks[j].processId = processId;
                count++;
                j++;
            }

            if (count == reqSize)
            {
                allocated = 1;
                printf("Process %d allocated to Blocks %d to %d\n", processId, i, j - 1);
                break;
            }
            else
            {
                for (int k = i; k < j; k++)
                {
                    blocks[k].processId = -1;
                }
            }
        }
    }

    if (!allocated)
    {
        printf("Insufficient memory to allocate Process %d\n", processId);
    }
}

// Function to deallocate memory
void deallocate(struct Block blocks[], int n, int processId)
{
    for (int i = 0; i < n; i++)
    {
        if (blocks[i].processId == processId)
        {
            blocks[i].processId = -1;
            printf("Process %d deallocated from Block %d\n", processId, blocks[i].id);
        }
    }
}

// Function to display the memory blocks
void displayBlocks(struct Block blocks[], int n)
{
    printf("Block\tSize\tProcess ID\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t", blocks[i].id, blocks[i].size);
        if (blocks[i].processId == -1)
        {
            printf("None\n");
        }
        else
        {
            printf("%d\n", blocks[i].processId);
        }
    }
}

int main()
{
    int choice, n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    struct Block blocks[MAX_BLOCKS];

    for (int i = 0; i < n; i++)
    {
        blocks[i].id = i + 1;
        printf("\nEnter the size of Block %d: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].processId = -1;
    }

    while (1)
    {
        printf("\nMemory Management Techniques\n");
        printf("1. MVT (Memory Variable Technique)\n");
        printf("2. MFT (Memory Fixed Technique)\n");
        printf("3. Deallocate Memory\n");
        printf("4. Display Memory Blocks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int processId, reqSize;

        switch (choice)
        {
        case 1:
            printf("\nMVT (Memory Variable Technique)\n");
            printf("Enter the Process ID: ");
            scanf("%d", &processId);
            printf("Enter the required memory size: ");
            scanf("%d", &reqSize);
            allocateMVT(blocks, n, processId, reqSize);
            break;
        case 2:
            printf("\nMFT (Memory Fixed Technique)\n");
            printf("Enter the Process ID: ");
            scanf("%d", &processId);
            printf("Enter the required memory size: ");
            scanf("%d", &reqSize);
            allocateMFT(blocks, n, processId, reqSize);
            break;
        case 3:
            printf("\nDeallocate Memory\n");
            printf("Enter the Process ID to deallocate: ");
            scanf("%d", &processId);
            deallocate(blocks, n, processId);
            break;
        case 4:
            printf("\nMemory Blocks\n");
            displayBlocks(blocks, n);
            break;
        case 5:
            printf("\nExiting...\n");
            return 0;
        default:
            printf("\nInvalid choice. Please try again.\n");
            break;
        }
    }

    return 0;
}
