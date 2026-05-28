#include <stdio.h>
#define MAX 10
int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    int alloc[MAX][MAX], request[MAX][MAX];
    int avail[MAX], finish[MAX], safeSeq[MAX];
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    printf("\nEnter Request Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);
    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);
    for (int i = 0; i < n; i++)
        finish[i] = 0;
    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > avail[j])
                        break;
                }
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("\nSystem is NOT in a safe state\n");
            return 0;
        }
    }
    printf("\nSystem is in SAFE state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 0;
}
