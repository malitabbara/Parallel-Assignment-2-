#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>

#define M 1000

#define NUM_THREADS 20

int mat1[M][M];
int mat2[M][M];
int result[M][M];
int step = 0;


void *multiply(void *arg){

    int threads_id = *(int *)(arg);
    int block_size = M/NUM_THREADS; 

    int start = threads_id * block_size;
    int end = start + block_size;

    for(int i = start; i<end; i++){
        for(int j = 0; j < M; j++){
            int sum = 0;
            for(int k = 0; k < M; k++){
                sum += mat1[i][k] * mat2[k][j];
            }
            result[i][j] = sum;
        }
    }
}
int main(){
    
    struct timeval start_time, end_time;

    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < M ; j++){
            mat1[i][j] = rand() % 10;
            mat2[i][j] = rand() % 10;
        }
    }
    
    gettimeofday(&start_time, NULL);  
    pthread_t threads[NUM_THREADS];
    
    for(int i = 0 ; i < NUM_THREADS; i++){
        int* threads_id;
        threads_id = (int *) malloc(sizeof(int));
        *threads_id = i;
        pthread_create(&threads[i], NULL, multiply, (void *)(threads_id));
    }

    for(int i = 0 ; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    
    gettimeofday(&end_time, NULL);
    
    double execution_time = (double) (end_time.tv_sec - start_time.tv_sec) + (double) (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    
    printf("Execution time: %f seconds \nNUM THREADS = %d", execution_time, NUM_THREADS);
    
    return 0;
}
