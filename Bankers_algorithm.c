#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main()
{
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    bool finished[MAX_PROCESSES];

    int numProcesses, numResources;
    int i, j;

    printf("Banker's Algorithm - Deadlock Avoidance\n");

    printf("\nEnter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    // Input allocation matrix
    printf("\nEnter the allocation matrix:\n");
    for (i = 0; i < numProcesses; i++)
    {
        printf("Process %d: ", i);
        for (j = 0; j < numResources; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input maximum matrix
    printf("\nEnter the maximum matrix:\n");
    for (i = 0; i < numProcesses; i++)
    {
        printf("Process %d: ", i);
        for (j = 0; j < numResources; j++)
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
        finished[i] = false;
    }

    // Input available resources
    printf("\nEnter the available resources:\n");
    for (i = 0; i < numResources; i++)
    {
        printf("Resource %d: ", i);
        scanf("%d", &available[i]);
    }

    // Perform the Banker's algorithm
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    int numSafeProcesses = 0;

    for (i = 0; i < numResources; i++)
    {
        work[i] = available[i];
    }

    bool canAllocate;
    do
    {
        canAllocate = false;

        for (i = 0; i < numProcesses; i++)
        {
            if (!finished[i])
            {
                bool canProcess = true;

                for (j = 0; j < numResources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canProcess = false;
                        break;
                    }
                }

                if (canProcess)
                {
                    for (j = 0; j < numResources; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[numSafeProcesses++] = i;
                    finished[i] = true;
                    canAllocate = true;
                }
            }
        }
    } while (canAllocate);

    // Check if the system is in a safe state
    bool isSafe = (numSafeProcesses == numProcesses);

    printf("\nSafe Sequence: ");
    if (isSafe)
    {
        for (i = 0; i < numProcesses; i++)
        {
            printf("%d ", safeSequence[i]);
        }
    }
    else
    {
        printf("No safe sequence found. Deadlock may occur.");
    }
    printf("\n");

    return 0;
}
