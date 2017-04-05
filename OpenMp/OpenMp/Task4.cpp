#include <omp.h>
#include <stdio.h>

void main4() {

	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int b[10] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 10 };

	int min = a[0];
	int max = b[0];

#pragma omp parallel  num_threads(2)
	{
#pragma omp parallel if(omp_get_thread_num == 0)
		{
#pragma omp for
			for (int i = 0; i < 10; i++) {
				if (a[i] < min) { min = a[i]; }
			}
		}

#pragma omp for
		for (int i = 0; i < 10; i++) {
			if (b[i] > max) { max = b[i]; }
		}


	}

	printf("min element in a[] is %d, max element in b[] is %d\n", min, max);

}