#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void main5() {
	const int a = 6;
	const int b = 8;
	int d[a][b];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			d[i][j] = rand();
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}

#pragma omp parallel sections
	{
#pragma omp section
		{
			int sum = 0;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					sum += d[i][j];
				}
			}

			printf("mid is %.2f from %d thread\n", sum * 1.0 / (a*b), omp_get_thread_num());

			
			
			
		}
#pragma omp  section
		{
			int min = d[0][0];
			int max = d[0][0];
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					if (d[i][j]< min) {
						min = d[i][j];
					}
					if (d[i][j]> max) {
						max = d[i][j];
					}
				}
			}
			printf("max is %d and max is %d from %d thread\n", min, max, omp_get_thread_num());
		}
#pragma omp  section
		{
			int sumElements = 0;

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					if (d[i][j] % 3 == 0) {
						sumElements ++;
					}
				}
			}
			printf("sum of elements::3 is %d from %d thread\n", sumElements, omp_get_thread_num());
		}
	}

}