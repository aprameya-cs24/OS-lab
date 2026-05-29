#include <stdio.h>
#define MAX 50
void displayFrames(int frames[], int f)
{
    int i;
    for(i = 0; i < f; i++)
    {
        if(frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}
void FIFO(int pages[], int n, int f)
{
    int frames[MAX], i, j, k = 0, flag, faults = 0;
    for(i = 0; i < f; i++)
        frames[i] = -1;
    printf("\n--- FIFO Page Replacement ---\n");
    for(i = 0; i < n; i++)
    {
        flag = 0;
        for(j = 0; j < f; j++)
            if(frames[j] == pages[i]) { flag = 1; break; }
        if(flag == 0)
        {
            frames[k] = pages[i];
            k = (k + 1) % f;
            faults++;
            printf("Page %d -> ", pages[i]);
            displayFrames(frames, f);
        }
        else
        {
            printf("Page %d -> Hit\n", pages[i]);
        }
    }
    printf("Total Page Faults (FIFO) = %d\n", faults);
}
void LRU(int pages[], int n, int f)
{
    int frames[MAX], time[MAX];
    int i, j, pos, faults = 0, counter = 0, flag;
    for(i = 0; i < f; i++) { frames[i] = -1; time[i] = 0; }
    printf("\n--- LRU Page Replacement ---\n");
    for(i = 0; i < n; i++)
    {
        flag = 0;
        for(j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            pos = 0;
            for(j = 1; j < f; j++)
                if(time[j] < time[pos]) pos = j;
            frames[pos] = pages[i];
            counter++;
            time[pos] = counter;
            faults++;
            printf("Page %d -> ", pages[i]);
            displayFrames(frames, f);
        }
        else
        {
            printf("Page %d -> Hit\n", pages[i]);
        }
    }
    printf("Total Page Faults (LRU) = %d\n", faults);
}
void Optimal(int pages[], int n, int f)
{
    int frames[MAX];
    int i, j, k, pos, faults = 0, flag;
    int farthest, index;
    for(i = 0; i < f; i++)
        frames[i] = -1;
    printf("\n--- Optimal Page Replacement ---\n");
    for(i = 0; i < n; i++)
    {
        flag = 0;
        for(j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            pos = -1;
            farthest = -1;
            for(j = 0; j < f; j++)
            {
                index = -1;
                for(k = i + 1; k < n; k++)
                {
                    if(frames[j] == pages[k])
                    {
                        index = k;
                        break;
                    }
                }
                if(index == -1)
                {
                    pos = j;
                    break;
                }
                if(index > farthest)
                {
                    farthest = index;
                    pos = j;
                }
            }
            if(pos == -1)
                pos = 0;
            frames[pos] = pages[i];
            faults++;
            printf("Page %d -> ", pages[i]);
            displayFrames(frames, f);
        }
        else
        {
            printf("Page %d -> Hit\n", pages[i]);
        }
    }
    printf("Total Page Faults (Optimal) = %d\n", faults);
}
int main()
{
    int pages[MAX], n, f, i;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    FIFO(pages, n, f);
    LRU(pages, n, f);
    Optimal(pages, n, f);
    return 0;
}
