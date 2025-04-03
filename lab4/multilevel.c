3
#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void calculateTimes(Process queue[], int n) {
    queue[0].waiting_time = 0;
    queue[0].turnaround_time = queue[0].burst_time;

    for (int i = 1; i < n; i++) {
        queue[i].waiting_time = queue[i - 1].waiting_time + queue[i - 1].burst_time;
        queue[i].turnaround_time = queue[i].waiting_time + queue[i].burst_time;
    }
}

void printQueue(Process queue[], int n, char *queueName) {
    printf("\n%s Queue:\n", queueName);
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    int total_wt = 0, total_tat = 0;
    
    for (int i = 0; i < n; i++) {
        total_wt += queue[i].waiting_time;
        total_tat += queue[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\n", queue[i].id, queue[i].burst_time, queue[i].waiting_time, queue[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n, sys_count = 0, user_count = 0;
    Process systemQueue[MAX], userQueue[MAX];

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int type, bt;
        printf("\nEnter process %d type (1 = System, 2 = User): ", i + 1);
        scanf("%d", &type);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt);

        if (type == 1) {
            systemQueue[sys_count].id = i + 1;
            systemQueue[sys_count].burst_time = bt;
            sys_count++;
        } else {
            userQueue[user_count].id = i + 1;
            userQueue[user_count].burst_time = bt;
            user_count++;
        }
    }

    // Process System Queue (Higher Priority)
    if (sys_count > 0) {
        calculateTimes(systemQueue, sys_count);
        printQueue(systemQueue, sys_count, "System");
    }

    // Process User Queue (Lower Priority)
    if (user_count > 0) {
        calculateTimes(userQueue, user_count);
        printQueue(userQueue, user_count, "User");
    }

    return 0;
}
