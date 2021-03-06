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
   int ticketMinRange;
   int ticketMaxRange; //di el max range lma ha generate random number
   //then haykoon fih if random number between el two ranges beta3 el process di, w kman quantum time beta3ha ma5lsh
};


void sleepReal(int timeM);

struct Process procs[0];

int totalCPUburtTime = 0;  //to know when to stop at the end

int n;
float size;
char path[] = "Input1.in";

int main(){

  remove("./Output-LOT.txt");  //remove file to start a new one
  FILE *f = fopen("./Output-LOT.txt", "a"); //open in append mode
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }


  //reading from file, and putting data into the array procs
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
  int currentTicketRange = 0;
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
                      totalCPUburtTime = totalCPUburtTime + procs[a].cpuBurst;
                  } else if(j==3){
                      procs[a].numberOfTickets = atoi(pch);
                      procs[a].ticketMinRange = currentTicketRange + 1;
                      currentTicketRange = currentTicketRange +   procs[a].numberOfTickets;
                      procs[a].ticketMaxRange = currentTicketRange;
                      // printf("Min range: %d\n", procs[a].ticketMinRange);
                      // printf("Max range: %d\n", procs[a].ticketMaxRange);
                      // printf("---------\n");
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

  //testing
  //printf("Total CPU burst time: %d \n", totalCPUburtTime); //correct!

  //generting random number
  /* Intializes random number generator */
  time_t t;
  srand((unsigned) time(&t)); //only called once

  /** for testing ***/
  //printf("%d\n", rand() % 50); //between 0 and 49, needs + 1
  //printf("%d\n", rand() % (numberOfTickets+1)); //to generate from 0 to total number of tickets
  //printf("%d\n", sizeof procs / sizeof procs[0]); //to get array length (struct)
  /** end testing ***/

  int time = 0;
  int procsLength = sizeof procs / sizeof procs[0];
  int averageTurnAround=0;
  int averageWaiting=0;

//  int randomTicket = rand() % (numberOfTickets+1);
//  printf("%d\n", randomTicket);


  // for (int x = 0; x < procsLength; x ++){ //loop on each process, 3shan tshoof hwa el random ticket da beta3ha wala la2
  //   if(randomTicket >= procs[x].ticketMinRange && randomTicket <= procs[x].ticketMaxRange){
  //         printf("%d\n", x + 1); //correct el7, just to test hya fein bezbt
  //         printf("Process CPU burst: %d\n", procs[x].cpuBurst);
  //         //awel matla2iha, na2as el cpu burst beta3ha (bel quantum)
  //         //then na2as el total cpu burst beta3 kolo (bel quantum)
  //         //break the loop
  //         procs[x].cpuBurst =   procs[x].cpuBurst - quantamLength;
  //         totalCPUburtTime = totalCPUburtTime - quantamLength;
  //
  //         sleep(quantamLength/1000);
  //
  //         printf("Process CPU burst: %d\n", procs[x].cpuBurst);
  //         printf("Total CPU burst time: %d\n", totalCPUburtTime);
  //
  //   }
  // }



   while(totalCPUburtTime > 0){   //total CPU burst time = 0, kda kolo 5eles

     int randomTicket = rand() % (numberOfTickets+1);

     for (int x = 0; x < procsLength; x ++){ //loop on each process, 3shan tshoof hwa el random ticket da beta3ha wala la2
       if(procs[x].cpuBurst > 0 && randomTicket >= procs[x].ticketMinRange && randomTicket <= procs[x].ticketMaxRange){
             //printf("%d\n", x + 1); //correct el7, just to test hya fein bezbt
             //printf("Process CPU burst: %d\n", procs[x].cpuBurst);
             //awel matla2iha, na2as el cpu burst beta3ha (bel quantum)
             //then na2as el total cpu burst beta3 kolo (bel quantum)
             //break the loop



             //check if it is end time
             if(procs[x].cpuBurst - quantamLength <= 0){ //ma3naha hate5las dlwa2ty!, a5r marra liha ya3ini


               //3akst order kol 7aga 3shan ashtghl abl ma el cpu burst tob2a zero
               printf("Time %i: P%i Entering quantum\n",time,procs[x].processId);

               fprintf(f, "Time %i: P%i Entering quantum\n",time,procs[x].processId); //APPEND TO FILE

               fflush(stdout);
               time = time+ procs[x].cpuBurst; //lazm tkoon hena 3shan tet3ml abl maykoon zero
               totalCPUburtTime = totalCPUburtTime - procs[x].cpuBurst;
               //sleep(procs[x].cpuBurst/1000);
               sleepReal(procs[x].cpuBurst);
               procs[x].cpuBurst =   procs[x].cpuBurst - procs[x].cpuBurst;  //aw = 0, lol


               //printf("P%i ended at %i\n", procs[x].processId, time);
               procs[x].endTime = time;

             }else  //ma3naha lssa hya hata5od 3adi el quantam kolaha
             {
               procs[x].cpuBurst =   procs[x].cpuBurst - quantamLength;
               totalCPUburtTime = totalCPUburtTime - quantamLength;
               //procs[x].ticketMaxRange =  procs[x].ticketMaxRange - 1;   //uncomment law 3ayz, taree2a msh efficient 5ales bas shaghala

               printf("Time %i: P%i Entering quantum\n",time,procs[x].processId);
              fprintf(f, "Time %i: P%i Entering quantum\n",time,procs[x].processId); //APPEND TO FILE
               fflush(stdout);
               //sleep(quantamLength/1000);
               sleepReal(quantamLength);
               time = time+ quantamLength;
             }

             //printf("Process CPU burst: %d\n", procs[x].cpuBurst);
             //printf("Total CPU burst time: %d\n", totalCPUburtTime);
             break;
       }
     }
   }
   for (int x = 0; x < procsLength; x ++){
       int turnAround = procs[x].endTime-procs[x].arrivalTime;
       int waitingTime = turnAround-procs[x].staticCpuBurst;
       averageTurnAround+=turnAround;
       averageWaiting+=waitingTime;
    }



   printf("\n");
    fprintf(f, "\n");
   printf("Average Waiting Time= %.2f\n",averageWaiting/size);
                 fprintf(f, "Average Waiting Time= %.2f\n",averageWaiting/size); //APPEND TO FILE
   printf("Average Turnaround Time= %.2f\n",averageTurnAround/size);
              fprintf(f, "Average Turnaround Time= %.2f\n",averageTurnAround/size); //APPEND TO FILE

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
