#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes and time quantum: ");
    scanf("%d %d", &n, &tq);

    int pid[n], bt[n], rt[n], ct[n];
    float total_tat = 0, total_wt = 0;

    printf("Enter process details (PID, Burst Time):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &pid[i], &bt[i]);
        rt[i] = bt[i];
        ct[i] = 0;
    }

    int time = 0, completed = 0, i = 0;

    while (completed < n) {
        if (rt[i] > 0) {
            int exec_time = (rt[i] < tq) ? rt[i] : tq;
            time += exec_time;
            rt[i] -= exec_time;

            if (rt[i] == 0) {
                completed++;
                ct[i] = time;
            }
        }
        i = (i + 1) % n;
    }


    printf("Process Scheduling Results:\n");
    printf("PID\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        int tat = ct[i];
        int wt = tat - bt[i];
        printf("%d\t%d\t%d\t%d\t%d\n", pid[i], bt[i], ct[i], tat, wt);
        total_tat += tat;
        total_wt += wt;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    

    return 0;
}
