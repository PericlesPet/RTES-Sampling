// #include <chrono>
// #include <thread>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "timestamps.h"


void sleep_ms(int milliseconds);

void main(int argc, char const *argv[]) {
  /* code */
  // INTRO
  if (argc != 4){
    printf("incorrect args --- total_time, dt, target-filename \n");
    return;
  }

  float total_time = atof(argv[1]);
  float time_dt = atof(argv[2]);
  float time_dt_ms = time_dt * 1000;

// initialize files

  int targetLength=strlen(argv[3]);
  char *targetFileNameComplete = (char *)malloc(sizeof(char)*(targetLength+14)); //targetFileName_complete.txt\NULL = targetFileName + (_complete.txt\NULL)
  char *targetFileNameLean = (char *)malloc(sizeof(char)*(targetLength+10)); //targetFileName_lean.txt\NULL = targetFileName + (_lean.txt\NULL)

// targetFileNameComplete = targetFileName_complete.txt
  strncpy(targetFileNameComplete,argv[3],targetLength);
  strcat(targetFileNameComplete,"-complete.txt");

// targetFileNameLean = targetFileName_lean.txt
  strncpy(targetFileNameLean,argv[3],targetLength);
  strcat(targetFileNameLean,"-lean.csv");

  printf("Target Length: %d, Copied string: %s\n Copied String2: %s\n",targetLength, targetFileNameComplete,targetFileNameLean);

  FILE *timestampsComplete = fopen(targetFileNameComplete,"w");
  FILE *timestampsLean = fopen(targetFileNameLean,"w");


  // strncpy()
  // char *targetFileNameLean = argv[3];
  //
  // printf("string: %s \n",targetFileName);
  // strcat()

  printf("Total Time = %f \nTime_dt = %f \nTime_dt_ms=%f\n\n",total_time,time_dt,time_dt_ms);
  // BEGIN
  struct timeval startwtime;
  struct timeval endwtime;
  float real_dt;
  float real_total_time=0;
  float time_shift;
  float time_shift_accum=0;

  // TIME LOOP
  for(float i=0;i<total_time;i+=time_dt){


    gettimeofday(&startwtime,NULL);
    sleep_ms(time_dt_ms);
    gettimeofday(&endwtime,NULL);

    real_dt = (float)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
  + endwtime.tv_sec - startwtime.tv_sec);

    time_shift = (real_dt-time_dt);
    time_shift_accum += time_shift;
    fprintf(timestampsComplete,"%5d. real_dt = %f ||--|| time-shift accumulation = %f ||--|| virtual_time = %f ---- real_time = %f \n",(int)(i/time_dt+1),real_dt,time_shift_accum, i, real_total_time);
    fprintf(timestampsLean, "%f\n",time_shift);
    // printf("time_dt = %f ---- real_dt = %f ||--|| time-shift = %f  ---- time-shift accumulation = %f ||--|| virtual_time = %f ---- real_time = %f \n",time_dt,real_dt,time_shift,time_shift_accum, i, real_total_time);
    // printf("%5d. real_dt = %f ||--|| time-shift = %f  ---- time-shift accumulation = %f ||--|| virtual_time = %f ---- real_time = %f \n",(int)(i/time_dt+1),real_dt,time_shift,time_shift_accum, i, real_total_time);
    real_total_time += real_dt;
  }//END OF TIME LOOP

  fclose(timestampsComplete);
  fclose(timestampsLean);

  // timestampStats(targetFileNameLean,time_dt,total_time);

  return;
}



//HELPERS
void sleep_ms(int milliseconds){
struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
