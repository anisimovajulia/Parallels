#include <omp.h>
#include <stdio.h>
void main3() {

	int a = 0, b = 0;

	printf("first a:%d b:%d\n", a, b);

#pragma omp parallel num_threads(2) private(a) firstprivate(b)
	{
		a = 0;
		a += omp_get_thread_num();
		b += omp_get_thread_num();
		printf("in thread num %d a:%d b:%d\n", omp_get_thread_num(), a, b);
	}
	printf("after a:%d b:%d\n\n\n", a, b);
	int b2 = b;
#pragma omp parallel num_threads(4) shared(a) private(b)
	{
		b = b2;
		a -= omp_get_thread_num();
		b -= omp_get_thread_num();
		printf("in thread num %d a:%d b:%d\n", omp_get_thread_num(), a, b);
	}
	printf("after a:%d b:%d\n\n\n", a, b);
}