#include <stdio.h>
#include <stdlib.h>

// Define the maximum number of processes and the time slice
#define MAX_PROCESSES 10
#define TIME_SLICE 2

// Define the process structure
typedef struct {
    int pid;            // process ID
    int arrival_time;   // arrival time
    int burst_time;     // burst time
    int remaining_time; // remaining time
    int turnaround_time;// turnaround time
    int waiting_time;   // waiting time
} Process;

// Function to sort the processes by arrival time
void sort_processes_by_arrival_time(Process *processes, int n) {
    Process temp;
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

int main() {
    // Initialize the processes
    Process processes[MAX_PROCESSES];
    int n, i, time, total_burst_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the arrival time and burst time of each process:\n");
    for (i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        total_burst_time += processes[i].burst_time;
    }

    // Sort the processes by arrival time
    sort_processes_by_arrival_time(processes, n);

    // Simulate the Round Robin algorithm
    int remaining_processes = n;
    time = 0;
    while (remaining_processes > 0) {
        for (i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > TIME_SLICE) {
                    time += TIME_SLICE;
                    processes[i].remaining_time -= TIME_SLICE;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    remaining_processes--;
                }
            }
        }
    }

    // Calculate the average turnaround time and waiting time
    float avg_turnaround_time = 0, avg_waiting_time = 0;
    for (i = 0; i < n; i++) {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    // Output the results
    printf("\nRound Robin (preemptive) scheduling algorithm\n");
    printf("Process ID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d",processes[i].pid,processes[i].pid,processes[i].arrival_time,processes[i].burst_time,processes[i].turnaround_time,processes[i].waiting_time);
    }
    return 0;
}

