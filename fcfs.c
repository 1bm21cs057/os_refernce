#include<stdio.h>
#include<conio.h>

struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void input(struct process p[], int n)
{
    printf("Enter the arrival time and burst(cpu) time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].pid = i + 1;
    }
}

void calculateTimeFCFS(struct process p[], int n)
{
    int j=0;
    while(p[j].at==0&&p[j].at==p[j+1].at)
    {
         if(p[j+1].bt<p[j].bt)
         {
             int temp=p[j].pid;
             p[j].pid=p[j+1].pid;
             p[j+1].pid=temp;
             temp=p[j].bt;
             p[j].bt=p[j+1].bt;
             p[j+1].bt=temp;
             j++;
         }
    }
    int sum=0;
    sum+=p[0].at;
    for(int i=0;i<n;i++)
    {
        sum+=p[i].bt;
        p[i].ct=sum;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        if(sum<p[i+1].at)
        {
            int t=p[i+1].at-sum;
            sum+=t;
        }
    }
}

void displayProcessDetails(struct process p[], int n) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at,
            p[i].bt, p[i].wt, p[i].tat);
    }
}

void main()
{
    int n;
    struct process* p = (struct process*)malloc(n * sizeof(struct process));
    printf("\nEnter the number of processes: ");
    scanf("%d",&n);
    input(p,n);
    calculateTimeFCFS(p,n);
    displayProcessDetails(p,n);
    free(p);
}
