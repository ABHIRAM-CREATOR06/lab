#include <stdio.h>
#include <string.h>

struct process {
    char name[20];
    int at, bt, wt, tt, status, ct, pr;
    int remaining_bt; // Added for preemption
};

struct done {
    char name[20];
    int st, ct;
};

int main() {
    int n, i, j, current_time = 0, completed = 0, num = 0;
    float twt = 0.0, ttt = 0.0;

    printf("ENTER THE NUMBER OF PROCESSES : ");
    scanf("%d", &n);

    struct process p[20];
    struct done d[20];

    for (i = 0; i < n; i++) {
        printf("\nENTER DETAILS OF PROCESS %d", i + 1);
        printf("\nPROCESS NAME : ");
        scanf(" %s", p[i].name);
        printf("ARRIVAL TIME : ");
        scanf("%d", &p[i].at);
        printf("BURST TIME : ");
        scanf("%d", &p[i].bt);
        printf("PRIORITY : ");
        scanf("%d", &p[i].pr);
        p[i].status = 0;
        p[i].remaining_bt = p[i].bt;
    }

    while (completed < n) {
        int highest_priority = -1;
        for (i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].status == 0) {
                if (highest_priority == -1 || p[i].pr < p[highest_priority].pr) {
                    highest_priority = i;
                }
            }
        }

        if (highest_priority != -1) {
            if (p[highest_priority].remaining_bt == p[highest_priority].bt) {
                d[num].st = current_time;
                strcpy(d[num].name, p[highest_priority].name);
            }
            p[highest_priority].remaining_bt--;
            current_time++;

            if (p[highest_priority].remaining_bt == 0) {
                p[highest_priority].status = 1;
                p[highest_priority].ct = current_time;
                p[highest_priority].tt = p[highest_priority].ct - p[highest_priority].at;
                p[highest_priority].wt = p[highest_priority].tt - p[highest_priority].bt;
                d[num].ct = current_time;
                num++;
                completed++;
            }
        } else {
            current_time++; // Idle time
            if (num > 0 && strcmp(d[num-1].name, "Idle") == 0) {
                d[num-1].ct = current_time;
            } else {
                strcpy(d[num].name, "Idle");
                d[num].st = current_time -1;
                d[num].ct = current_time;
                num++;
            }
        }
    }
    printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
  for(i=0;i<n;i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].name,p[i].ct,p[i].wt,p[i].tt);
    twt+=p[i].wt;
    ttt+=p[i].tt;
  }
  printf("\n\nGANTT CHART ");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
    printf("|");
    printf("%s\t",d[i].name);
  }
  printf(" |");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
      printf("%d\t",d[i].st);
  }
  printf("%d\t\n",d[num-1].ct);
  printf("\nAVERAGE WAITING TIME : %f",(twt/n));
  printf("\nAVERAGE TURNAROUND TIME : %f\n",(ttt/n));
}
