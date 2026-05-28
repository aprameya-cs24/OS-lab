#include <stdio.h>
#define MAX 20
void priority_np(int n,int at[],int bt[],int pr[]){
    int wt[MAX]={0},tat[MAX],rt[MAX],done[MAX]={0};
    int time=0,count=0;
    float sw=0,st=0,sr=0;
    int gantt[100], g_index=0;
    while(count<n){
        int idx=-1,min=9999;
        for(int i=0;i<n;i++)
            if(at[i]<=time && !done[i] && pr[i]<min){
                min=pr[i];
                idx=i;
            }
        if(idx!=-1){
            rt[idx]=time-at[idx];
            wt[idx]=time-at[idx];
            for(int k=0;k<bt[idx];k++) gantt[g_index++]=idx+1;
            time+=bt[idx];
            tat[idx]=wt[idx]+bt[idx];
            done[idx]=1;
            count++;
        }
        else time++;
    }
    printf("\nPID WT TAT RT\n");
    for(int i=0;i<n;i++){
        printf("%d \t%d \t%d \t%d\n",i+1,wt[i],tat[i],rt[i]);
        sw+=wt[i]; st+=tat[i]; sr+=rt[i];
    }
    printf("\nAvg WT=%.2f\nAvg TAT=%.2f\nAvg RT=%.2f\n",sw/n,st/n,sr/n);
    printf("\nGantt Chart:\n");
    for(int i=0;i<g_index;i++) printf("P%d | ",gantt[i]);
    printf("\n");
}
void priority_p(int n,int at[],int bt[],int pr[]){
    int rt_bt[MAX],wt[MAX]={0},tat[MAX],rt[MAX];
    int gantt[1000], g_index=0;
    for(int i=0;i<n;i++){ rt_bt[i]=bt[i]; rt[i]=-1; }
    int time=0,complete=0;
    float sw=0,st=0,sr=0;
    while(complete<n){
        int idx=-1,min=9999;
        for(int i=0;i<n;i++)
            if(at[i]<=time && rt_bt[i]>0 && pr[i]<min){
                min=pr[i]; idx=i;
            }
        if(idx!=-1){
            if(rt[idx]==-1) rt[idx]=time-at[idx];
            rt_bt[idx]--;
            gantt[g_index++]=idx+1;
            time++;
            if(rt_bt[idx]==0){
                complete++;
                tat[idx]=time-at[idx];
                wt[idx]=tat[idx]-bt[idx];
            }
        }
        else time++;
    }
    printf("\nPID WT TAT RT\n");
    for(int i=0;i<n;i++){
        printf("%d\t %d\t %d\t %d\n",i+1,wt[i],tat[i],rt[i]);
        sw+=wt[i]; st+=tat[i]; sr+=rt[i];
    }
    printf("\nAvg WT=%.2f\nAvg TAT=%.2f\nAvg RT=%.2f\n",sw/n,st/n,sr/n);
    printf("\nGantt Chart:\n");
    for(int i=0;i<g_index;i++) printf("P%d | ",gantt[i]);
    printf("\n");
}

int main(){
    int n,choice,q;
    int at[MAX],bt[MAX],pr[MAX];
    printf("Enter the number of Processes: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("Arrival Time Burst Time Priority for P%d: ",i+1);
        scanf("%d %d %d",&at[i],&bt[i],&pr[i]);
    }
    printf("\n1.Priority Non-Preemptive");
    printf("\n2.Priority Preemptive");
    printf("\nChoice: ");
    scanf("%d",&choice);
    switch(choice){
        case 1: priority_np(n,at,bt,pr); break;
        case 2: priority_p(n,at,bt,pr); break;

    }
    return 0;
}
