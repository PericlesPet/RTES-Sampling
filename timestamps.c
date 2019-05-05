// #include <chrono>
// #include <thread>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void sleep_ms(int milliseconds);

void main(int argc, char const *argv[]) {
  /* code */
  // INTRO
  if (argc != 3){
    printf("incorrect args --- total_time, dt \n");
    return;
  }
  float total_time = atoi(argv[1]);
  float time_dt = atof(argv[2]);
  float time_dt_ms = time_dt * 1000;

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
    // std::this_thread::sleep_for(std::chrono::milliseconds());
    gettimeofday(&endwtime,NULL);

    // printf("%ld -- %ld -- %f -- %f \n",tv2.tv_usec,tv1.tv_usec,(float)((tv2.tv_usec)/1000000.0f),(tv1.tv_sec+tv1.tv_usec/1000000.0f));
    real_dt = (float)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
  + endwtime.tv_sec - startwtime.tv_sec);

    time_shift = (real_dt-time_dt);
    time_shift_accum += time_shift;
    // printf("time_dt = %f ---- real_dt = %f ||--|| time-shift = %f  ---- time-shift accumulation = %f ||--|| virtual_time = %f ---- real_time = %f \n",time_dt,real_dt,time_shift,time_shift_accum, i, real_total_time);
    printf(" real_dt = %f ||--|| time-shift = %f  ---- time-shift accumulation = %f ||--|| virtual_time = %f ---- real_time = %f \n",real_dt,time_shift,time_shift_accum, i, real_total_time);
    real_total_time += real_dt;
  }

  return;
}



//HELPERS
void sleep_ms(int milliseconds){
struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
