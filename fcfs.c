#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
};

void input(struct process p[], int n) {
    printf("Enter the arrival time and burst (CPU) time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].pid = i + 1;
    }
}

void calculateTimeFCFS(struct process p[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        if (sum < p[i + 1].at) {
            int t = p[i + 1].at - sum;
            sum += t;
        }
    }
}

void calculateTimeSJF(struct process p[], int n) {
    int completed = 0;
    int currentTime = 0;

    while (completed != n) {
        int shortest = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].completed == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    shortest = i;
                }
                if (p[i].bt == min_bt) {
                    if (p[i].at < p[shortest].at) {
                        shortest = i;
                    }
                }
            }
        }

        if (shortest == -1) {
            currentTime++;
        } else {
            p[shortest].ct = currentTime + p[shortest].bt;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            p[shortest].completed = 1;
            completed++;
            currentTime = p[shortest].ct;
        }
    }
}



void calculateTimeSRTF(struct process p[], int n) {
    int completed = 0;
    int currentTime = 0;
    int min_bt, shortest, temp;
    int remaining[n];

    for (int i = 0; i < n; i++) {
        remaining[i] = p[i].bt;
    }

    while (completed != n) {
        min_bt = 9999;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && remaining[i] < min_bt && remaining[i] > 0) {
                min_bt = remaining[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
        } else {
            remaining[shortest]--;
            currentTime++;

            if (remaining[shortest] == 0) {
                completed++;
                p[shortest].ct = currentTime;
                p[shortest].tat = p[shortest].ct - p[shortest].at;
                p[shortest].wt = p[shortest].tat - p[shortest].bt;
            }
        }
    }
}

void displayProcessDetails(struct process p[], int n) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at,
            p[i].bt, p[i].wt, p[i].tat);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process* p = (struct process*)malloc(n * sizeof(struct process));

    input(p, n);

    // FCFS Algorithm
    calculateTimeFCFS(p, n);
    printf("\nFCFS Algorithm:\n");
    displayProcessDetails(p, n);



    // SRTF Algorithm
    calculateTimeSRTF(p, n);
    printf("\nSRTF Algorithm:\n");
    displayProcessDetails(p, n);

     // SJF Algorithm
    calculateTimeSJF(p, n);
    printf("\nSJF Algorithm:\n");
    displayProcessDetails(p, n);

    free(p);

    return 0;
}
