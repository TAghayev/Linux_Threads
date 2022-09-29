all : thr_atomic.c thr_reduce.o thr_atomic thr_reduce

thr_atomic.o : thr_atomic.c
	gcc -c thr_atomic.c

thr_reduce.o : thr_reduce.c
	gcc -c thr_reduce.c

thr_atomic : thr_atomic.o
	gcc -o thr_atomic -pthread thr_atomic.o -lm

thr_reduce : thr_reduce.o
	gcc -o thr_reduce -pthread thr_reduce.o -lm
