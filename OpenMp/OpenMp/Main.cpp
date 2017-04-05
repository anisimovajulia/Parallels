#include <omp.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


//task1
void main1() {
	int size, rank;

	
#pragma omp parallel num_threads(8)  
	{
		size = omp_get_num_threads();
		rank = omp_get_thread_num();


		printf("Hello world threadnum %d number of threads %d \n", rank, size);


	}

	system("pause");
}
//task2
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
//task3
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
//task4
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
						sumElements++;
					}
				}
			}
			printf("sum of elements::3 is %d from %d thread\n", sumElements, omp_get_thread_num());
		}
	}

}
//task6
void main6() {

	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int b[10] = { 11, 12, 16, 17, 45, 77, -4, -14, 0, 2 };

	int a_sum = 0;
	int b_sum = 0;
#pragma omp parallel for reduction(+: a_sum) reduction(+: b_sum)
	for (int i = 0; i < 10; i++) {
		a_sum += a[i];
		b_sum += b[i];
	}

	printf("mid from a is %d ; mid from b is %d\n", a_sum / 10, b_sum / 10);

}
//task10
void main10() {


	int d[6][8];

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			d[i][j] = rand();
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	int min = d[0][0];
	int max = d[0][0];

	int counter = 0;
#pragma omp parallel num_threads(6) 
#pragma omp for
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			if (min > d[i][j]) {
#pragma omp critical
				min = d[i][j];
			}
			if (max < d[i][j]) {
#pragma omp critical
				max = d[i][j];
			}
		}
	}
	printf("max: %d, min: %d\n", max, min);
}
//task11
void main11() {

	int a[30];

	int c = 0;
#pragma omp parallel for num_threads(8) shared(c)
	for (int i = 0; i < 30; i++) {
		a[i] = rand();
		printf("%d ", a[i]);
		if (a[i] % 9 == 0) {
#pragma omp atomic
			c++;
		}
	}

	printf("the number of digits::9 is %d\n", c);

}

//task12
void main12() {

	int a[30];

	for (int i = 0; i < 30; i++) {
		a[i] = rand();
	}
	int max = a[0];
#pragma omp parallel for num_threads(8) shared(max)
	for (int i = 0; i < 30; i++) {
		if (a[i] % 7 == 0 && a[i] > max) {
#pragma omp critical
			{
				max = a[i];
			}
		}
	}

	printf("max of digit::7  is %d\n", max);

}
void main() {
	//main1();
	//main2();
	//main3();
	//main4();
	//main5();
	//main6();
	//main10();
	//main11();
	//main12();
}