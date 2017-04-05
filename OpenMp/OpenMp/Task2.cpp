#include <omp.h>
#include <stdio.h>
using namespace std;

void main2() {
	omp_set_dynamic(0);
	omp_set_num_threads(3);
	int size, rank;
#pragma omp parallel if(omp_get_max_threads() > 2)
	{
		size = omp_get_num_threads();
		rank = omp_get_thread_num();
		printf("Hello world threadnum %d number of threads %d \n", rank, size);
	}

	omp_set_num_threads(1);

#pragma omp parallel if(omp_get_max_threads() > 2)
	{
		size = omp_get_num_threads();
		rank = omp_get_thread_num();
		printf("Hello world threadnum %d number of threads %d \n", rank, size);
	}
}