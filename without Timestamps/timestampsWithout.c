// #include <chrono>
// #include <thread>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
// #include "timestamps.h"


void sleep_ms(int milliseconds);

void main(int argc, char const *argv[]) {
  /* code */
  // INTRO & Argument Conversion
  if (argc != 4){
    printf("incorrect args --- total_time, dt, target-filename \n");
    return;
  }

  float total_time = atof(argv[1]);
  float time_dt = atof(argv[2]);
  float time_dt_ms = time_dt * 1000;

  // Initialize & Open FILES

  int targetLength=strlen(argv[3]);
  char *targetFileNameComplete = (char *)malloc(sizeof(char)*(targetLength+29)); // ./../Results/targetFileName_completeWo.txt\NULL = "./../Results/" + targetFileName + "-completeWo.txt\NULL"
  char *targetFileNameLean = (char *)malloc(sizeof(char)*(targetLength+25)); // ./Results/targetFileName_leanWo.txt\NULL = "./../Results/" + targetFileName + "-leanWo.txt\NULL"

  // targetFileNameComplete = ./Results/targetFileName-complete.txt
  strcpy(targetFileNameComplete,"./../Results/");
  strncat(targetFileNameComplete,argv[3],targetLength);
  strcat(targetFileNameComplete,"-completeWo.txt");

  // targetFileNameLean = ./Results/targetFileName-lean.csv
  strcpy(targetFileNameLean,"./../Results/");
  strncat(targetFileNameLean,argv[3],targetLength);
  strcat(targetFileNameLean,"-leanWo.csv");

  // printf("Target Length: %d, Copied string: %s\n Copied String2: %s\n",targetLength, targetFileNameComplete,targetFileNameLean);

  FILE *timestampsComplete = fopen(targetFileNameComplete,"w");
  FILE *timestampsLean = fopen(targetFileNameLean,"w");


  // BEGIN
  printf("Total Time = %f \nTime_dt = %f \nTime_dt_ms=%f\n\n",total_time,time_dt,time_dt_ms);
  struct timeval startwtime;
  struct timeval endwtime;
  float real_dt;
  float real_total_time=0;
  float time_shift;
  float time_shift_accum=0;
  int minutes=0;

  float i=0;
  // TIME LOOP
  for(i=0;i<total_time;i+=time_dt){


    gettimeofday(&startwtime,NULL);
    sleep_ms(time_dt_ms);
    gettimeofday(&endwtime,NULL);

    real_dt = (float)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
  + endwtime.tv_sec - startwtime.tv_sec);

    time_shift = (real_dt-time_dt);
    time_shift_accum += time_shift;

    //WRITE TO FILES
    fprintf(timestampsComplete,"%5d. real_dt = %f ||--|| time-shift accumulation = %f ||--|| virtual_time = %f ---- real_time = %f \n",(int)(i/time_dt+1),real_dt,time_shift_accum, i, real_total_time);
    fprintf(timestampsLean, "%f\n",time_shift);

    // printf("%d. real_dt = %f ||--|| time-shift = %f  ---- time-shift accumulation = %f ||--|| virtual_time = %f ---- real_time = %f \n",(int)(i/time_dt+1),real_dt,time_shift,time_shift_accum, i, real_total_time);

    if(0==((int)(i/time_dt+1)%600)){ //600 means 600 iterations, or 1 minute when dt = 0.1
      minutes++;
      printf("%d. iteration %d - time-shift accumulation = %f ||--|| virtual_time = %f ---- real_time = %f \n",minutes,(int)(i/time_dt+1),time_shift_accum, i, real_total_time);
    }

    real_total_time += real_dt;
  }//END OF TIME LOOP

  printf("%d. iteration %d - time-shift accumulation = %f ||--|| virtual_time = %f ---- real_time = %f \n**Finished**\n",minutes,(int)(i/time_dt+1),time_shift_accum, i, real_total_time);

  fclose(timestampsComplete);
  fclose(timestampsLean);

  return;
}



//HELPERS
void sleep_ms(int milliseconds){
struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
