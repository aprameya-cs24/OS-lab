#include <stdio.h>
#define MAX 10
int main() {
    int n, m;
    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int avail[MAX], finish[MAX] = {0}, safeSeq[MAX];
    int i, j, k = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    printf("\nNEED Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
    int completed = 0;
    while (completed < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canExecute = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canExecute = 0;
                        break;
                    }
                }
                if (canExecute) {
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    safeSeq[k++] = i;
                    finish[i] = 1;
                    found = 1;
                    completed++;
                }
            }
        }
        if (!found) {
            printf("\nSystem is NOT in safe state (Deadlock possible)\n");
            return 0;
        }
    }
    printf("\nSystem is in SAFE state\nSafe Sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 0;
}
