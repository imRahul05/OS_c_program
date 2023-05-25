#include <stdio.h>

struct Process
{
    int pid;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(struct Process processes[], int n)
{
    processes[0].waitingTime = 0;

    for (int i = 1; i < n; i++)
    {
        processes[i].waitingTime = processes[i - 1].burstTime + processes[i - 1].waitingTime;
    }
}

void calculateTurnaroundTime(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
    }
}

void calculateAvgTimes(struct Process processes[], int n, double *avgWaitingTime, double *avgTurnaroundTime)
{
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    *avgWaitingTime = (double)totalWaitingTime / n;
    *avgTurnaroundTime = (double)totalTurnaroundTime / n;
}

void sortProcessesByPriority(struct Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority > processes[j + 1].priority)
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void displayProcesses(struct Process processes[], int n)
{
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burstTime,
               processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);
        processes[i].pid = i + 1;
        printf("Enter burst time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority: ");
        scanf("%d", &processes[i].priority);
    }

    sortProcessesByPriority(processes, n);

    double avgWaitingTime, avgTurnaroundTime;
    calculateAvgTimes(processes, n, &avgWaitingTime, &avgTurnaroundTime);

    printf("\nProcess Scheduling:\n");
    displayProcesses(processes, n);

    printf("\nAverage Waiting Time: %.2lf", avgWaitingTime);
    printf("\nAverage Turnaround Time: %.2lf\n", avgTurnaroundTime);

    return 0;
}
