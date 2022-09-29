#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

    pthread_mutex_t x = PTHREAD_MUTEX_INITIALIZER;
    pthread_t *thr;
    int m;
    int n;
    int j;
    double *sum;

    void *calc (void *arg) {
        long tid = (long) arg; //Casting arg to long type and assigning it as our thread index
        double lsum = 0.0; //"local" sum variable initialized
        for (int i = (tid * j) + 1; i <= (tid + 1) * j; i++) {   //for loop to summarize the square roots into lsum
            lsum += sqrt(i);
        }

        sum[tid] = lsum; //assign sum at the tid index to the lsum variable
        int i = 1;


        while (tid < m/(int)pow(2,i)){
          int p = ((int)(pow(2.0,log(m)/log(2) - i))) ^ (int)tid; //assign p to be the index of the partner
          pthread_join(thr[p], NULL);  //wait on the partner of value index p to terminate
          sum[tid] += sum[p];
          i++;
        }

       if (tid == 0) { //once our thread index is equal to zero, it is done, and we print the final summation
          printf("sum of squares: %lf\n", sum[tid]);

      }

    }

    int main (int argc, char *argv[]){
         j = atoi(argv[2])/atoi(argv[1]);
         m = atoi(argv[1]);
        //n = atoi(argv[2]);

        sum = malloc(sizeof(double) * m); //important: use malloc to allocate space for the global array sum
        thr = malloc(sizeof(pthread_t) * m);

        for(long i = m-1 ; i >= 0 ; i--){
            pthread_create(&thr[i], NULL, calc, (void*)i);
        }

        pthread_exit(NULL);
    }
