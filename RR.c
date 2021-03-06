#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

static const struct Process EmptyStruct;

struct Process {
   int  processId;
   int  arrivalTime;
   int  cpuBurst;
   int staticCpuBurst;
   int  startTime;
   int  endTime;
   int   numberOfTickets;
};

void sleepReal(int timeM);
void printProcsArray(struct Process procs[],int size);
struct Process removeFirst(struct Process procs[],int size);
struct Process procs[0];

int n;
float size;
char path[] = "Input1.in";

int main(){

  remove("./Output-RR.txt");  //remove file to start a new one
  FILE *f = fopen("./Output-RR.txt", "a"); //open in append mode
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }



FILE * fp;
char * line = NULL;
size_t len = 0;
ssize_t read;

int i=1; //counter

fp = fopen(path, "r");
if (fp)
{
    while ((read = getline(&line, &len, fp)) != -1) {
        i++;
    }
}
n = i-3; //no of processes
size = n;
struct Process procs[n];

int quantamLength = 0;
int numberOfTickets = 0;
i=0;
int a=0;
fp = fopen(path, "r");
if (fp)
{
    while ((read = getline(&line, &len, fp)) != -1) {
        if(i==0){
            quantamLength = atoi(line);
        } else if(i==1){
            numberOfTickets = atoi(line);
        } else{

            char * pch;
            pch = strtok (line,",");
            int j=0;
            struct Process proc;
            while (pch != NULL)
            {
                if(j==0){
                    procs[a].processId = atoi(pch);
                } else if(j==1){
                    procs[a].arrivalTime = atoi(pch);
                } else if(j==2){
                    procs[a].cpuBurst = atoi(pch);
                    procs[a].staticCpuBurst = atoi(pch);
                } else if(j==3){
                    procs[a].numberOfTickets = atoi(pch);
                }
                procs[a].startTime = -1;
                procs[a].endTime =-1;
                j++;
                pch = strtok (NULL, ",");
            }
            a++;
        }
        i++;
    }
}
fclose(fp);

i=0;
int time =0;

int averageTurnAround=0;
int averageWaiting=0;

while(n>0){

    struct Process p = removeFirst(procs,n);
    int newCPU = p.cpuBurst - quantamLength;
    if(p.startTime==-1){
        p.startTime = time;
    }
    if(newCPU>0){
        printf("Time %i: P%i Entering quantum\n",time,p.processId);
                  fprintf(f,"Time %i: P%i Entering quantum\n",time,p.processId);
        fflush(stdout);
        //sleep(quantamLength/1000);
        sleepReal(quantamLength);
        time = time+ quantamLength;
        p.cpuBurst = newCPU;
        procs[n] = p;
        n++;
    }else{
        printf("Time %i: P%i Entering quantum\n",time,p.processId);
          fprintf(f,"Time %i: P%i Entering quantum\n",time,p.processId);
        fflush(stdout);
        //sleep(p.cpuBurst/1000)
        sleepReal(p.cpuBurst);
        time = time+p.cpuBurst;
        p.endTime = time;
        int turnAround = p.endTime-p.arrivalTime;
        int waitingTime = turnAround-p.staticCpuBurst;
        averageTurnAround+=turnAround;
        averageWaiting+=waitingTime;
        printf("Time %i: P%i Done Turn around:%i Waiting time: %i\n",time,p.processId,turnAround,waitingTime);

         fprintf(f, "Time %i: P%i Done Turn around:%i Waiting time: %i\n",time,p.processId,turnAround,waitingTime);
        p.cpuBurst = 0;
    }
    i++;
}

printf("\n");
 fprintf(f, "\n");
printf("Average Waiting Time= %.2f\n",averageWaiting/size);
              fprintf(f, "Average Waiting Time= %.2f\n",averageWaiting/size); //APPEND TO FILE
printf("Average Turnaround Time= %.2f\n",averageTurnAround/size);
           fprintf(f, "Average Turnaround Time= %.2f\n",averageTurnAround/size); //APPEND TO FILE

}

struct Process removeFirst(struct Process procs[],int size){

    int i;
    struct Process proc;
    proc = procs[0];
    for (i = 0; i < size-1; i += 1)
    {
        procs[i] = procs[i+1];
    }
    procs[i] = EmptyStruct;

    n=n-1;

    return proc;
}

void printProcsArray(struct Process procs[],int size){
    struct Process proc;
    proc = procs[0];
    int i;
    for (i = 0; i < size; i += 1)
    {
        printf("Array number %i:\n",i);
        printf("Process ID: %i ",procs[i].processId);
        printf("Arrival Time: %i ",procs[i].arrivalTime);
        printf("CPU Burst Time: %i ",procs[i].cpuBurst);
        printf("Number of tickets: %i\n",procs[i].numberOfTickets);
    }

}
void sleepReal(int timeM){ //time is in milliseconds
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  int x = 0;
  while (x != timeM) {  //2000, wait 2 seconds
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    x = delta_us;
  }
}
