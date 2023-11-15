#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>

#define M 1000

#define NUM_THREADS 20

int mat1[M][M];
int mat2[M][M];
int result[M][M];

int main(){
    
    struct timeval start_time, end_time;

    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < M ; j++){
            mat1[i][j] = rand() % 10;
            mat2[i][j] = rand() % 10;
        }
    }
  
    omp_set_num_threads(NUM_THREADS);
    gettimeofday(&start_time, NULL); 
     
    #pragma omp parallel for
    for(int i = 0; i < M; i++){
        for(int j = 0; j < M; j++){
            int sum = 0;
            for(int k = 0 ; k < M; k++){
                sum+= mat1[i][k] * mat2[k][j];
        }
        result[i][j] = sum;
        }
    }
    
    gettimeofday(&end_time, NULL);
    
    double execution_time = (double) (end_time.tv_sec - start_time.tv_sec) + (double) (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    
    printf("Execution time: %f seconds \nNUM THREADS = %d", execution_time, NUM_THREADS);
    
    return 0;
}
