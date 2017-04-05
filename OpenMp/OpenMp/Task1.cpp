#include <omp.h>
#include <iostream>
using namespace std;
void main1() {
	int size, rank;

	//task1
#pragma omp parallel num_threads(8)  //получает количество нитей
	{
		size = omp_get_num_threads();
		rank = omp_get_thread_num();


		printf("Hello world threadnum %d number of threads %d \n", rank, size);


	}

	system("pause");
}