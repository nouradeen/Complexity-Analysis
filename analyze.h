#include <stdio.h>
#include <stdbool.h>
#ifndef ANALYZE_H
#define ANALYZE_H

#define SIZE_START 512
#define ITERATIONS 4
#define SORT_TEST_ITERATIONS 15
#define SEARCH_TEST_ITERATIONS 100000
#define BILLION 1000000000

//extern int array_length;

// algorithm_t defines different algorithms
typedef enum {
	bubble_sort_t,
	insertion_sort_t,
	quick_sort_t,
	linear_search_t,
	binary_search_t
} algorithm_t;

// case_t defines different cases
typedef enum {
	best_t,
	worst_t,
	average_t,
} case_t;


typedef enum{
	T_1_t = 1,//0
	T_logN_t = 1,
	T_N_t = 2,
	T_NlogN_t = 3,
	T_N2_t = 4,
	T_N3_t = 4//5
}notation_t;

typedef struct Big_notation{
	notation_t best;
	notation_t worst;
	notation_t average;
}Big_notation_t;

// result_t defines a timed measurement for a given array size
typedef struct {
	int size;
	double time;
} result_t;

typedef struct {
	int *array;
	size_t used;
	size_t size;
} Array_t;

// benchmark benchmarks an algorithm a for a specific case c, writing n results
// to the result buffer buf
typedef void (*t_generate_array_funcp)(int*, int);
typedef void (*t_sort_funcp)(int*, int);
typedef bool (*t_search_funcp)(const int*, int, int);


void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n, Big_notation_t *o, t_generate_array_funcp g_array, int search_value);
double T_1(double time, int length);
double T_logN(double time, int length);
double T_N(double time, int length);
double T_NlogN(double time, int length);
double T_N2(double time, int length);
double T_N3(double time, int length);


void randomArray(int *a, int length);
void sortedArray(int *a, int length);
void reversedArray(int *a, int length);
void quicksortArray(int *a, int length);
#endif
