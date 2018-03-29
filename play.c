#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


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

int main(){
//   struct timespec start, end;
// clock_gettime(CLOCK_MONOTONIC_RAW, &start);
// //do stuff
//
// //loop
// //Le7ad ma el expression eli ta7t da yews lel raam eli ana 3ayzo, example 1000ms
//
// int x = 0;
// while (x != 10000) {  //2000, wait 2 seconds
// clock_gettime(CLOCK_MONOTONIC_RAW, &end);
//   uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
//   x = delta_us;
//   //printf("%d\n", x);
//   //end loop
// }

sleepReal(6000);


}
