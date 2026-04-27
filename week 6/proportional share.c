#include <stdio.h>
#define MAX 10
typedef struct {
    int id;
    int bt;
    int remaining;
    int share;
    int ct, wt, tat;
} Process;
void print_gantt(int timeline[], int time) {
    printf("\nGantt Chart:\n");

    for (int i = 0; i < time; i++)
        printf("| P%d ", timeline[i]);
    printf("|\n");

    for (int i = 0; i <= time; i++)
        printf("%3d ", i);
    printf("\n");
}
void proportional(Process p[], int n) {
    printf("\n===== Proportional Share Scheduling =====\n");
    int timeline[100], t = 0;
    int total_share = 0;
    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].bt;
        total_share += p[i].share;
    }
    int completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            int times = p[i].share; // weight-based execution
            while (times-- && p[i].remaining > 0) {
                timeline[t++] = p[i].id;
                p[i].remaining--;
                if (p[i].remaining == 0) {
                    p[i].ct = t;
                    completed++;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
    }
    print_gantt(timeline, t);
    printf("\nID\tBT\tShare\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].share,
               p[i].ct, p[i].wt, p[i].tat);
    }
}
int main() {
    int n;
    Process p[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Share (Weight): ");
        scanf("%d", &p[i].share);
    }
    proportional(p, n);
    return 0;
}
