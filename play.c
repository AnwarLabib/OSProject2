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
  remove("./file.txt");
  FILE *f = fopen("./file.txt", "a"); //open in append mode
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }
  const char *text = "Write this to the file";
  fprintf(f, "Some tex2t: %s\n", text);

sleepReal(1000);


}
