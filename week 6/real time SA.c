#include <stdio.h>
#include <math.h>
#define MAX 10
typedef struct {
    int id;
    int bt;
    int deadline;
    int period;
    int ct, wt, tat;
    int done;
} Process;
float calculate_utilization(Process p[], int n) {
    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (float)p[i].bt / p[i].period;
    }
    return U;
}
void check_schedulability(Process p[], int n) {
    float U = calculate_utilization(p, n);
    float bound = n * (pow(2, 1.0/n) - 1);
    printf("\n===== SCHEDULABILITY TEST =====\n");
    printf("Total Utilization (U) = %.3f\n", U);

    printf("\n[RMS]\n");
    printf("Bound = %.3f\n", bound);
    if (U <= bound)
        printf(" Schedulable under RMS\n");
    else
        printf(" Not guaranteed schedulable under RMS\n");
    printf("\n[EDF]\n");
    if (U <= 1.0)
        printf(" Schedulable under EDF\n");
    else
        printf(" Not schedulable under EDF\n");
}
void print_gantt(int order[], int time_marks[], int size) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < size; i++)
        printf("|  P%d  ", order[i]);
    printf("|\n");
    printf("0");
    for (int i = 0; i < size; i++)
        printf("     %d", time_marks[i]);
    printf("\n");
}
void edf(Process p[], int n) {
    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    int time = 0, completed = 0;
    int order[MAX], time_marks[MAX], k = 0;
    for (int i = 0; i < n; i++) p[i].done = 0;
    while (completed < n) {
        int idx = -1, min_deadline = 9999;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].deadline < min_deadline) {
                min_deadline = p[i].deadline;
                idx = i;
            }
        }
        time += p[idx].bt;
        order[k] = p[idx].id;
        time_marks[k] = time;
        k++;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;
        completed++;
    }
    print_gantt(order, time_marks, k);
    printf("\nID\tDeadline\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].deadline, p[i].ct, p[i].wt, p[i].tat);
    }
}
void rms(Process p[], int n) {
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    int time = 0, completed = 0;
    int order[MAX], time_marks[MAX], k = 0;
    for (int i = 0; i < n; i++) p[i].done = 0;
    while (completed < n) {
        int idx = -1, min_period = 9999;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].period < min_period) {
                min_period = p[i].period;
                idx = i;
            }
        }
        time += p[idx].bt;
        order[k] = p[idx].id;
        time_marks[k] = time;
        k++;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;
        completed++;
    }
    print_gantt(order, time_marks, k);
    printf("\nID\tBT\tPeriod\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
    }
}
int main() {
    int n;
    Process p[MAX], temp[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);
        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
    }
    check_schedulability(p, n);
    for (int i = 0; i < n; i++) temp[i] = p[i];
    edf(temp, n);
    for (int i = 0; i < n; i++) temp[i] = p[i];
    rms(temp, n);
    return 0;
}

