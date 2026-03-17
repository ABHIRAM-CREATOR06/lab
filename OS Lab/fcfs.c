#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    int completion[n], waiting[n], turnaround[n];
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < arrival[i]) {
            current_time = arrival[i];
        }
        completion[i] = current_time + burst[i];
        current_time = completion[i];
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    }

    float avg_turnaround = 0, avg_waiting = 0;
    for (int i = 0; i < n; i++) {
        avg_turnaround += turnaround[i];
        avg_waiting += waiting[i];
    }
    avg_turnaround /= n;
    avg_waiting /= n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround);
    printf("Average Waiting Time: %.2f\n", avg_waiting);

    return 0;
}
