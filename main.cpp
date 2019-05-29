#include <math.h>
#include <time.h>
#include "stdio.h"
#include <stdlib.h>
#include <sys/time.h>

#define DATA_COUNT 32768
int MLUhw2Op(float* input1,float* input2, float*output, int dims_a);

int main() {
  float* input_x = (float*)malloc(DATA_COUNT * sizeof(float));
  float* input_y = (float*)malloc(DATA_COUNT * sizeof(float));
  float* output_data = (float*)malloc(DATA_COUNT * sizeof(float));
  float* output_data_cpu = (float*)malloc(DATA_COUNT * sizeof(float));
  FILE* f_input_x = fopen("../data/in_x.txt", "r");
  FILE* f_input_y = fopen("../data/in_y.txt", "r");
//   FILE* f_output_data = fopen("../data/out.txt", "r");
  struct timeval tpend, tpstart;
  float err = 0.0;
  float cpu_sum = 0.0;
  float time_use = 0.0;

  if (f_input_x == NULL|| f_input_y == NULL) {
    printf("Open file fail!\n");
    return 0;
  }

  gettimeofday(&tpstart, NULL);
  srand((unsigned)time(NULL));
  for (int i = 0; i < DATA_COUNT; i++) {
    fscanf(f_input_x, "%f\n", &input_x[i]);
    fscanf(f_input_y, "%f\n", &input_y[i]);
    // fscanf(f_output_data, "%f\n", &output_data_cpu[i]);
  }
  gettimeofday(&tpend, NULL);
  time_use = 1000000 * (tpend.tv_sec - tpstart.tv_sec)+ tpend.tv_usec - tpstart.tv_usec;
  printf("get data cost time %f ms\n", time_use/1000.0);

  gettimeofday(&tpstart, NULL);
  MLUhw2Op(input_x,input_y,output_data,DATA_COUNT);
  gettimeofday(&tpend, NULL);
  time_use = 1000000 * (tpend.tv_sec - tpstart.tv_sec)+ tpend.tv_usec - tpstart.tv_usec;
  printf("compute data cost time %f ms\n", time_use/1000.0);
  for(int i = 0; i < DATA_COUNT;++i)
  {
     if(input_x[i] < 0.01 || fabs(input_x[i]-input_y[i]) < 0.01) continue;
     output_data_cpu[i] = log(input_x[i]) / pow(input_x[i]-input_y[i], 2);
     err +=fabs(output_data_cpu[i] - output_data[i]) ;
     cpu_sum +=fabs(output_data_cpu[i]);
  }
     printf("err rate = %0.4f%%\n", err*100.0/cpu_sum);
  return 0;
}
