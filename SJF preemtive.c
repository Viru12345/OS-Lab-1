#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

int findShortestJob(struct Process processes[], int n, int current_time) {
    int shortest_job = -1;
    int shortest_time = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
            if (processes[i].remaining_time < shortest_time) {
                shortest_time = processes[i].remaining_time;
                shortest_job = i;
            }
        }
    }
    
    return shortest_job;
}

void preemptiveSJF(struct Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;
    
    while (completed_processes < n) {
        int shortest_job = findShortestJob(processes, n, current_time);
        
        if (shortest_job == -1) {
            current_time++;
        } else {
            processes[shortest_job].remaining_time--;
            current_time++;
            
            if (processes[shortest_job].start_time == -1) {
                processes[shortest_job].start_time = current_time - 1;
            }
            
            printf("Time %d: Process %d is running\n", current_time, processes[shortest_job].id);
            
            if (processes[shortest_job].remaining_time == 0) {
                completed_processes++;
                processes[shortest_job].completion_time = current_time;
                printf("Time %d: Process %d completed\n", current_time, processes[shortest_job].id);
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].id = i + 1;
        processes[i].start_time = -1;
        processes[i].completion_time = -1;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
    
    printf("\nPreemptive SJF Scheduling:\n");
    preemptiveSJF(processes, n);
    
    printf("\nProcess\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = processes[i].completion_time - processes[i].burst_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        printf("%d\t%d\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time);
    }
    
    return 0;
}
