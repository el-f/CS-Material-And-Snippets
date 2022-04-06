
#include <math.h>

#define HEAVY 10000000

void heavy() {
    int i;
    for (i = 0; i < HEAVY; i++)
        exp(sin(exp(sin(exp(-2.)))));
}

#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    double start_time, end_time, tick;
    start_time = omp_get_wtime();
    heavy();
    end_time = omp_get_wtime();
    tick = omp_get_wtick();
    printf("Time %e\n", end_time - start_time);
    printf("Timer Precision %e\n", tick);
}

//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	double start_time, end_time;
//	int i;
//
//	start_time = omp_get_wtime();
////#pragma omp parallel for
//	for (i = 0;   i < 6;   i++)
//		heavy();
//	end_time = omp_get_wtime();
//	
//	printf("Time %e\n", end_time - start_time);
//}	


//#include <stdio.h>
//int main(int argc, char *argv[]) {
//	int count = 0;
//	#pragma omp parallel reduction (+: count) 
//	{
//		count++;
//		printf("count: %d\n", count);
//	}
//	printf("After the pragma :  count = %d\n", count);
//}



//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//omp_set_num_threads(4);
//#pragma omp parallel num_threads(3)
//{
//	printf("First\n");
//}
//#pragma omp parallel
//{
//	printf("Second\n");
//}
//}


//#include <stdio.h>
//int main(int argc, char *argv[]) {
//#pragma omp parallel
//{
//	printf("First\n");
//	#pragma omp single nowait
//	{
//		printf("Single\n");
//	}
//	printf("Second\n");
//}
//
//}


//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//int n, tid;
//#pragma omp parallel private(n, tid)
//{
//	tid = n = omp_get_thread_num();
//	printf("Start: tid = %d n = %d\n", tid, n);
//	#pragma omp single copyprivate(n)
//		{
//		printf("Middle: tid = %d n = %d\n", tid, n);
//		n=100;
//		}
//	printf("End: tid = %d n = %d\n", tid, n);
//}
//}


//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//int n, tid;
//#pragma omp parallel private(n, tid)
//{
//	tid = n = omp_get_thread_num();
//	n=1;
//	#pragma omp master
//	{
//	n=2;
//	}
//	printf("First n: %d tid = %d\n", n, tid);
//	#pragma omp barrier
//	#pragma omp master
//	{
//	n=3;
//	}
//	printf("Second n: %d tid = %d\n", n, tid);
//}
//}




//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	int i, m[10];
//	printf("Before:\n");
//	for (i=0; i<10; i++) {
//		m[i]=0;
//		printf("%d\n", m[i]);
//	}
//
//#pragma omp parallel shared(m)
//	{
//		int tid = omp_get_thread_num();
//		m[tid] = 1;
//	}
//	
//	printf("After:\n");
//	for (i=0; i<10; i++) 
//		printf("%d\n", m[i]);
//}


//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	int n=1;
//	printf("Before n = %d\n", n);
//#pragma omp parallel firstprivate(n)
//{
//	int tid = omp_get_thread_num();
//	printf("Enter n =  %d tid = %d\n", n, tid);
//	n = omp_get_thread_num();
//	printf("Exit n = %d tid = %d\n", n, tid);
//}
//	printf("After n = %d\n", n);
//}

//#include <stdio.h>
//#include <omp.h>
//
//int n;
//#pragma omp threadprivate(n)
//
//int main(int argc, char *argv[]) {
//	int num;
//	n=1;
//#pragma omp parallel private (num)
//	{
//		num = omp_get_thread_num();
//		printf("Enter tid = %d n = %d\n", num, n);
//		n = omp_get_thread_num();
//		printf("Exit tid = %d n = %d\n", num, n);
//	}
//	printf("Middle n = %d\n", n);
//#pragma omp parallel private (num)
//	{
//		num = omp_get_thread_num();
//		printf("Tid =  %d n = %d\n", num, n);
//	}
//}



//#include <stdio.h>
//#include <omp.h>
//int n = 7;
//#pragma omp threadprivate(n)
//
//int main(int argc, char *argv[]) {
//	n=1;
//#pragma omp parallel //copyin(n)
//{
//	int num = omp_get_thread_num();
//	printf("tid = %d  n = %d\n", num, n);
//}
//}



//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	int count, num;
//#pragma omp parallel
//{
//	count = omp_get_num_threads();
//	num = omp_get_thread_num();
//	if (num == 0) 
//		printf("count = %d\n", count);
//	else 
//		printf("num = %d\n", num);
//}
//}



//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	int A[10], B[10], C[10], i, tid;
//	
//	for (i = 0;   i < 10;   i++) { 
//		A[i]=i; B[i]=2*i; C[i]=0; 
//	}
//
//#pragma omp parallel shared(A, B, C) private(i, tid)
//	{
//	tid = omp_get_thread_num();
//#pragma omp for
//	for (i = 0;   i < 10;   i++) {
//		C[i] = A[i] + B[i];
//		printf("tid = %d i = %d\n", tid, i);
//	}
//	}
//}

//#include <stdio.h>
//#include <windows.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	int i;
//#pragma omp parallel private(i)
//	{
////#pragma omp for schedule (static)
////#pragma omp for schedule (static, 1)
////#pragma omp for schedule (static, 2)
////#pragma omp for schedule (dynamic)
////#pragma omp for schedule (dynamic, 2)
////#pragma omp for schedule (guided)
////#pragma omp for schedule (guided, 2)
//	for (i = 0;    i < 20;   i++) {
//		printf("tid = %d i = %d\n", omp_get_thread_num(), i);
//	}
//	}
//}

// omp.cpp : Defines the entry point for the console application.
//



//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	int tid;
//#pragma omp parallel private(tid)
//{
//	tid = omp_get_thread_num();
//	printf("Before  tid = %d\n", tid);
//#pragma omp sections
//	{
//	#pragma omp section
//		{
//			printf("First tid = %d\n", tid);
//		}
//	#pragma omp section
//		{
//			printf("Second tid = %d\n", tid);
//		}
//	#pragma omp section
//		{
//			printf("Third tid = %d\n", tid);
//		}
//
//	}
//	printf("After  tid = %d\n", tid);
//}
//}



//


//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//#pragma omp parallel
//{
//	printf("First\n");
//	printf("Second\n");
//#pragma omp barrier
//	printf("Third\n");
//}
//}



//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	int i, tid;
//#pragma omp parallel private (i, tid)
//{
//	tid = omp_get_thread_num();
//#pragma omp for ordered
//	for (i=0; i<5; i++) {
//			printf("Before tid = %d, i = %d\n", tid, i);
//			#pragma omp ordered
//			{
//			printf("\tordered: tid %d, i = %d\n", tid, i);
//			}
//			printf("After tid = %d, i = %d\n", tid, i);
//	}
//}
//}


//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	int tid;
//#pragma omp parallel
//	{
//	#pragma omp critical
//	{
//		tid = omp_get_thread_num();
//		heavy();
//		printf("tid = %d\n", tid);
//	}
//	}
//}

//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[]) {
//	int count = 0;
//#pragma omp parallel
//{
//	#pragma omp atomic
//	count++;
//}
//	printf("count: %d\n", count);
//}

//#include <stdio.h>
//#include <omp.h>
//omp_lock_t lock;
//int main(int argc, char *argv[]) {
//	int tid;
//	omp_init_lock(&lock);
//#pragma omp parallel private (tid)
//{
//	tid = omp_get_thread_num();
//	omp_set_lock(&lock);
//	printf("Start, tid =  %d\n", tid);
//	heavy();
//	printf("End, tid =  %d\n", tid);
//	omp_unset_lock(&lock);
//}
//	omp_destroy_lock(&lock);
//}


//#include <stdio.h>
//#include <omp.h>
//int main(int argc, char *argv[])
//{
//	omp_lock_t lock;
//	int tid;
//	omp_init_lock(&lock);
//#pragma omp parallel private (tid)
//{
//	tid = omp_get_thread_num();
//	while (!omp_test_lock (&lock)) {
//		printf("Closed tid =  %d\n", tid);
//		heavy();
//	}
//	printf("Start tid = %d\n", tid);
//	heavy();
//	printf("End tid = %d\n", tid);
//	omp_unset_lock(&lock);
//}
//	omp_destroy_lock(&lock);
//}



//#pragma omp parallel for shared(a, b, c) private(i, j, k)

//#include <stdio.h>
//#include <omp.h>
//#define N 600
//double a[N][N], b[N][N], c[N][N];
//int main()
//{
//	int i, j, k;
//	double t1, t2;
//	
//	// Initialization
//	for(i = 0;   i < N;   i++)
//		for(j = 0;    j<N;   j++)
//			a[i][j] = b[i][j] = i*j;
//
//	t1 = omp_get_wtime();
//
//	// Multiply matrices
//
//	for(i = 0;   i < N;   i++){
//		for(j = 0;    j<N;   j++){
//			c[i][j] = 0.0;
//			for(k = 0;   k < N;   k++)
//				c[i][j] += a[i][k]*b[k][j];
//		}
//	}
//
//	t2 = omp_get_wtime();
//	printf("Time = %f\n", t2-t1);
//}









