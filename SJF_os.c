#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];
    for(int i=0; i<n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].pid = i+1;
        p[i].remaining_time = p[i].burst_time;
    }
    
    // Sort the processes in ascending order based on arrival time
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(p[i].arrival_time > p[j].arrival_time) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    
    // Calculate completion time, waiting time, and turnaround time for each process
    int current_time = p[0].arrival_time;
    int completed = 0;
    while(completed < n) {
        int shortest = -1;
        for(int i=0; i<n; i++) {
            if(p[i].arrival_time <= current_time && p[i].remaining_time > 0 && (shortest == -1 || p[i].remaining_time < p[shortest].remaining_time)) {
                shortest = i;
            }
        }
        if(shortest == -1) {
            current_time++;
        } else {
            p[shortest].remaining_time--;
            if(p[shortest].remaining_time == 0) {
                p[shortest].completion_time = current_time + 1;
                p[shortest].turnaround_time = p[shortest].completion_time - p[shortest].arrival_time;
                p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;
                completed++;
            }
            current_time++;
        }
    }
    
    // Calculate average waiting time and average turnaround time
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;
    for(int i=0; i<n; i++) {
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    
    // Print the results
    printf("\nSJF Scheduling:\n");
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].waiting_time, p[i].turnaround_time);
    }
    printf("Average waiting time: %.2f\n", avg_waiting_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);
    
    return 0;
}
