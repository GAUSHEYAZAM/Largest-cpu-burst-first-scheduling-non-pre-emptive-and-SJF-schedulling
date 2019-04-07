#include<stdio.h>
struct process
{
char name_of_process[20];
int TAT;
int arrival_time;
int cpu_burst;
int start_time;
int end_time;
int avg_wait;
int check; /*to check that whether certain process has been scheduled or not if check=0(not scheduled yet)
                                                                            if check=1(already scheduled)*/
};
int main()
{
    printf("\t\t*** READ INSTRUCTIONS CAREFULLY***\n");
    printf("\t1. Name of the processes must be in \"string\" type only.\n");
    printf("\t2. No two processes must have same arrival time.\n");
    printf("\t3. No process must have 0 or -ve arrival time.\n\n\n");
int n,i,j=1,k=1;
float avgTAT,avgWait;
printf("Enter the number of process: ");
scanf("%d",&n);
struct process obj[n],temp;
for(i=0;i<n;i++)
{
printf("Enter the name of process: ");
scanf("%s",obj[i].name_of_process);
printf("Enter the arrival time of the process: ");
scanf("%d",&obj[i].arrival_time);
obj[i].cpu_burst=2 * obj[i].arrival_time;
obj[i].check=0;
}

for(i=0;i<n;i++)   //sorting of process on the basis of arrival time
{
	for(j=0;j<n-i-1;j++)
	{
	if(obj[j].arrival_time>obj[j+1].arrival_time)
	{
		temp=obj[j];
		obj[j]=obj[j+1];
		obj[j+1]=temp;
	}
	}
}
int endtime=obj[0].arrival_time; //to store the end_time of process so that we can trace the end time
//for executing the first process which has less arrival time
obj[0].start_time=obj[0].arrival_time;
obj[0].end_time=endtime+ obj[0].cpu_burst;
endtime=obj[0].end_time;
obj[0].TAT=obj[0].end_time - obj[0].arrival_time;
obj[0].avg_wait=obj[0].TAT - obj[0].cpu_burst;
avgTAT=obj[0].TAT;
avgWait=avgWait + obj[0].avg_wait;
obj[0].check=1;
for(j=1;j<n;j++)  //for highest cpu burst first scheduling
{
int count=0;
while(endtime>=(obj[j].arrival_time) && j<n)
{
j++;
count=1;
}
if(count==1) //if at least one process has been arrived in the system in the end_time of last executed process
{
    j--;
obj[j].start_time=endtime;
obj[j].end_time=endtime + obj[j].cpu_burst;
endtime=obj[j].end_time;
obj[j].TAT=obj[j].end_time - obj[j].arrival_time;
obj[j].avg_wait=obj[j].TAT - obj[j].cpu_burst;
avgTAT=avgTAT+obj[j].TAT;
avgWait=avgWait + obj[j].avg_wait;
obj[j].check=1;
}
else if(count==0)//if no process has arrived in between the execution of the last executed process
{
    k=j-1;
	while(obj[k].check!=0 && k>0)  //backtracking the processes
	{
		k--;
	}
	if(obj[k].check==0)
    {
        count=1;
    }
	if(count==1) //if there is any process in backtracking which has not been scheduled
	{
		obj[k].start_time=endtime;
		obj[k].end_time=obj[k].start_time + obj[k].cpu_burst;
		endtime=obj[k].end_time;
		obj[k].TAT=obj[k].end_time - obj[k].arrival_time;
		obj[k].avg_wait=obj[k].TAT - obj[k].cpu_burst;
		avgTAT=avgTAT+obj[k].TAT;
		avgWait=avgWait + obj[k].avg_wait;
		obj[k].check=1;
		j--;
	}
	if(count==0)  // if every previous process has been scheduled
	{
		obj[j].start_time=obj[j].arrival_time;
		obj[j].end_time=obj[j].start_time + obj[j].cpu_burst;
		endtime=obj[j].end_time;
		obj[j].TAT=obj[j].end_time-obj[j].arrival_time;
		obj[j].avg_wait=obj[j].TAT - obj[j].cpu_burst;
		avgTAT = avgTAT + obj[j].TAT;
		avgWait=avgWait + obj[j].avg_wait;
		obj[j].check=1;
	}
}
}
for(i=n-1;i>0;i--) //to schedule the process which has not been scheduled yet and all the process has come into the system
{
if(obj[i].check==0)
{
	obj[i].start_time=endtime;
	obj[i].end_time=obj[i].start_time + obj[i].cpu_burst;
	endtime=obj[i].end_time;
	obj[i].TAT=obj[i].end_time - obj[i].arrival_time;
	obj[i].avg_wait=obj[i].TAT - obj[i].cpu_burst;
	avgTAT=avgTAT+obj[i].TAT;
	avgWait=avgWait + obj[i].avg_wait;
	obj[i].check=1;
}
}
for(i=0;i<n;i++)   //sorting of process on the basis of start time of process
{
	for(j=0;j<n-i-1;j++)
	{
	if(obj[j].start_time>obj[j+1].start_time)
	{
		temp=obj[j];
		obj[j]=obj[j+1];
		obj[j+1]=temp;
	}
	}
}
printf("\n\n\t\t***LARGEST CPU BURST FIRST***\n\n");
printf("Process\t\t");
printf("Start\t\t");
printf("END\t\t");
printf("TAT\t\t");
printf("WAIT TIME\n");
for(i=0;i<n;i++)
{
printf("%s\t\t",obj[i].name_of_process);
printf("%d\t\t",obj[i].start_time);
printf("%d\t\t",obj[i].end_time);
printf("%d\t\t",obj[i].TAT);
printf("%d\n",obj[i].avg_wait);
}
printf("\nAVERAGE TAT : %f\n",avgTAT/n);
printf("AVERAGE WAIT TIME :%f\n",avgWait/n);
for(i=0;i<n;i++)   //sorting of process on the basis of arrival time
{
	for(j=0;j<n-i-1;j++)
	{
	if(obj[j].arrival_time>obj[j+1].arrival_time)
	{
		temp=obj[j];
		obj[j]=obj[j+1];
		obj[j+1]=temp;
	}
	}
}
avgWait=0;
endtime=obj[0].arrival_time; //to store the end_time of process so that we can trace the end time
//for executing the first process which has less arrival time
obj[0].start_time=obj[0].arrival_time;
obj[0].end_time=obj[0].arrival_time + obj[0].cpu_burst;
endtime=obj[0].end_time;
obj[0].TAT=obj[0].end_time - obj[0].arrival_time;
obj[0].avg_wait=obj[0].TAT - obj[0].cpu_burst;
avgTAT=obj[0].TAT;
avgWait=avgWait + obj[0].avg_wait;
obj[0].check=1;
for(j=1;j<n;j++) //for shortest job time first
{
    if(obj[j].arrival_time>endtime)
    {
        obj[j].start_time=obj[j].arrival_time;
		obj[j].end_time=obj[j].start_time + obj[j].cpu_burst;
		endtime=obj[j].end_time;
		obj[j].TAT=obj[j].end_time-obj[j].arrival_time;
		obj[j].avg_wait=obj[j].TAT - obj[j].cpu_burst;
		avgTAT = avgTAT + obj[j].TAT;
		avgWait=avgWait + obj[j].avg_wait;
		obj[j].check=1;
    }
    else if(obj[j].arrival_time<=endtime)
    {
        obj[j].start_time=endtime;
		obj[j].end_time=obj[j].start_time + obj[j].cpu_burst;
		endtime=obj[j].end_time;
		obj[j].TAT=obj[j].end_time-obj[j].arrival_time;
		obj[j].avg_wait=obj[j].TAT - obj[j].cpu_burst;
		avgTAT = avgTAT + obj[j].TAT;
		avgWait=avgWait + obj[j].avg_wait;
		obj[j].check=1;
    }
}
printf("\n\n\t\t***SHORTEST JOB FIRST***\n\n");
printf("Process\t\t");
printf("Start\t\t");
printf("END\t\t");
printf("TAT\t\t");
printf("WAIT TIME\n");
for(i=0;i<n;i++)
{
printf("%s\t\t",obj[i].name_of_process);
printf("%d\t\t",obj[i].start_time);
printf("%d\t\t",obj[i].end_time);
printf("%d\t\t",obj[i].TAT);
printf("%d\n",obj[i].avg_wait);
}
printf("\nAVERAGE TAT : %f\n",avgTAT/n);
printf("AVERAGE WAIT TIME : %f\n",avgWait/n);
}












