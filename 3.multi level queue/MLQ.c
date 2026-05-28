#include <stdio.h>
#include <string.h>
#define MAX 100
typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
    int response;
    int started;
    char type[10];
} Process;
typedef struct {
    Process queue[MAX];
    int front, rear;
} Queue;
void initQueue(Queue *q) {
    q->front = q->rear = -1;
}
int isEmpty(Queue *q) {
    return (q->front == -1);
}
void enqueue(Queue *q, Process p) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->queue[++q->rear] = p;
}
Process dequeue(Queue *q) {
    Process p = q->queue[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return p;
}
void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[MAX];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1; // Sequential IDs
        printf("\nEnter Arrival Time, Burst Time, Type(system/user): ");
        scanf("%d %d %s", &p[i].arrival, &p[i].burst, p[i].type);
        p[i].remaining = p[i].burst;
        p[i].started = 0;
    }
    sortByArrival(p, n);
    Queue systemQueue, userQueue;
    initQueue(&systemQueue);
    initQueue(&userQueue);
    int time = 0, completed = 0, i = 0;
    Process current;
    int hasProcess = 0;
    int gantt[MAX], gIndex = 0;
    while (completed < n) {
        while (i < n && p[i].arrival <= time) {
            if (strcmp(p[i].type, "system") == 0)
                enqueue(&systemQueue, p[i]);
            else
                enqueue(&userQueue, p[i]);
            i++;
        }
        if (hasProcess) {
            if (strcmp(current.type, "user") == 0 && !isEmpty(&systemQueue)) {
                enqueue(&userQueue, current);
                hasProcess = 0;
            }
        }
        if (!hasProcess) {
            if (!isEmpty(&systemQueue)) {
                current = dequeue(&systemQueue);
                hasProcess = 1;
            } else if (!isEmpty(&userQueue)) {
                current = dequeue(&userQueue);
                hasProcess = 1;
            } else {
                gantt[gIndex++] = -1; // idle
                time++;
                continue;
            }
        }
        if (current.started == 0) {
            for (int k = 0; k < n; k++) {
                if (p[k].pid == current.pid) {
                    p[k].response = time - p[k].arrival;
                    p[k].started = 1;
                }
            }
            current.started = 1;
        }
        gantt[gIndex++] = current.pid;
        current.remaining--;
        time++;
        if (current.remaining == 0) {
            for (int k = 0; k < n; k++) {
                if (p[k].pid == current.pid) {
                    p[k].completion = time;
                    p[k].turnaround = time - p[k].arrival;
                    p[k].waiting = p[k].turnaround - p[k].burst;
                }
            }
            completed++;
            hasProcess = 0;
        }
    }
    printf("\n\nGantt Chart:\n|");
    for (int j = 0; j < gIndex; j++) {
        if (gantt[j] == -1)
            printf(" Idle |");
        else
            printf(" P%d |", gantt[j]);
    }
    printf("\n0");
    for (int j = 1; j <= gIndex; j++)
        printf("    %d", j);
    printf("\n\nProcess\ttype\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    float avgTAT = 0, avgWT = 0, avgRT = 0;
    for (int j = 0; j < n; j++) {
        printf("P%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[j].pid,p[j].type, p[j].arrival, p[j].burst,
               p[j].completion, p[j].turnaround,
               p[j].waiting, p[j].response);
        avgTAT += p[j].turnaround;
        avgWT += p[j].waiting;
        avgRT += p[j].response;
    }
    printf("\nAverage TAT = %.2f", avgTAT / n);
    printf("\nAverage WT  = %.2f", avgWT / n);
    printf("\nAverage RT  = %.2f\n", avgRT / n);
}
