#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

    pthread_mutex_t x = PTHREAD_MUTEX_INITIALIZER;  //Initialize the thread
    int j; //Our index
    double sum = 0.0; //Total sum - shared global variable

    void *calc (void *arg) {
        long tid = (long) arg; //Casting
        double lsum = 0.0; //Partial sums
        for (int i = (tid * j) + 1; i <= (tid + 1) * j; i++) { //We set a range from 1 to n/m and n/m + 1 to 2n/m
            lsum += sqrt(i); //Adding the square roots in the range
        }
        printf("thr %ld: %lf\n", tid, lsum); //Print each thread and its partial sum

        pthread_mutex_lock(&x); //Lock the thread
        sum += lsum; //Partial sums to the total sum
        pthread_mutex_unlock(&x); //Unlock the thread

    }

    int main (int argc, char *argv[]){
        int m = atoi(argv[1]);
        int n = atoi(argv[2]);
        j = n/m;
        pthread_t thr[m];

        for(long i = 0 ; i <= m-1 ; i++){ //Loops throguh and creates the thread
            pthread_create(&thr[i], NULL, calc, (void*)i);
        }

        for(long i=0; i < m; i++) {
            pthread_join(thr[i], NULL); //Lets the main thread know that all of the m computational threads have done the atomic additions
        }

        printf("sum of square roots: %f\n", sum); //Print the total sum
}
