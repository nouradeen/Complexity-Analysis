#include "analyze.h"
#include "algorithm.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>



int warmup(){ // Warmup function for the CPU
    int temp = 0;
    for(int i = 0; i<1000000; i++){
        temp += i;
    }
    return temp;
}

double measureSort(t_sort_funcp fun, int *array, int array_length){ // Function to measure the sorting algorithm for "TEST_ITERATIONS" times and return the mean value
    struct timespec start, stop;
    long int medium = 0, sta, sto;
    warmup();
    for(int i = 0; i<SORT_TEST_ITERATIONS; i++){
        clock_gettime(CLOCK_MONOTONIC, &start);
        fun(array, array_length);
        clock_gettime(CLOCK_MONOTONIC, &stop);
        sta = start.tv_sec*BILLION + start.tv_nsec;
        sto = stop.tv_sec*BILLION + stop.tv_nsec;
        medium += sto - sta;// Sum all the values
    }
    return ((double)medium/SORT_TEST_ITERATIONS)/BILLION; // return the mean value
}

double measureSearch(t_search_funcp fun, int*array, int array_length, int value){// Function to measure the searching algorithm for "TEST_ITERATIONS" times and return the mean value
    struct timespec start, stop;
    long int medium = 0, sta, sto;
    warmup();
    for(int i = 0; i<SEARCH_TEST_ITERATIONS; i++){
        clock_gettime(CLOCK_MONOTONIC, &start);
        fun(array, array_length, value);
        clock_gettime(CLOCK_MONOTONIC, &stop);
        sta = start.tv_sec*BILLION + start.tv_nsec;
        sto = stop.tv_sec*BILLION + stop.tv_nsec;
        medium += sto - sta;// Sum all the values
    }
    return ((double)medium/SEARCH_TEST_ITERATIONS)/BILLION;// return the mean value
}

double SearchCaseTest(t_search_funcp fun, const case_t c, int array_length, result_t *buf, t_generate_array_funcp g_array, int search_value){ // Function to check for which test case should be running for the search algorithms
    int array[array_length];
    
    switch (c)
    {
    case best_t: // Best case for the searching algorithms is a Sorted Array and searching for the value 0. The first value of the array
        g_array(array, array_length);
        return measureSearch(fun, array, array_length, search_value);

        break;
    case worst_t:// The worst case is a Random Array and searching for a value that does not exist in the array
        g_array(array, array_length);
        return measureSearch(fun, array, array_length, search_value);

        break;
    case average_t: // Average case is a Random Array and searching for a random value
        g_array(array, array_length);
        return measureSearch(fun, array, array_length, search_value);
        break;
    }
    return 0;
}


double SortCaseTest(t_sort_funcp fun, const case_t c, int array_length, result_t *buf, t_generate_array_funcp g_array){// Function to check for which test case should be running for the sort algorithms
    int array[array_length];
    switch (c)
    {
    case best_t: // Best case is an already sorted array
        g_array(array, array_length);
        return measureSort(fun, array, array_length);
        break;
    case worst_t:// Worst case is an inverted sorted array.
        g_array(array, array_length);
        return measureSort(fun, array, array_length);
        break;
    case average_t:
        g_array(array, array_length);
        return measureSort(fun, array, array_length);
        break;
    }
    return 0;
}



void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n, Big_notation_t *o, t_generate_array_funcp g_array, int search_value){
    int array_length = SIZE_START; //Start with a 512 array, then double it 6 times up to 16384
    int search_quick = search_value;
    for(int i = 0; i<n; i++){
        switch(a){
            case bubble_sort_t:
                buf[i].size = array_length;//Save the current size of the array 
                buf[i].time = SortCaseTest(bubble_sort, c, array_length, buf, g_array); // Save the current time of the test
                o->best = T_N_t;
                o->worst = T_N2_t;
                o->average = T_N2_t;
                break;
            case insertion_sort_t:
                buf[i].size = array_length;
                buf[i].time = SortCaseTest(insertion_sort, c, array_length, buf, g_array);
                o->best = T_N_t;
                o->worst = T_N2_t;
                o->average = T_N2_t;
                break;
            case quick_sort_t:
                buf[i].size = array_length;
                buf[i].time = SortCaseTest(quick_sort, c, array_length, buf, g_array);
                o->best = T_NlogN_t;
                o->worst = T_N2_t;
                o->average = T_NlogN_t;
                
                break;
            case linear_search_t:
                buf[i].size = array_length;
                buf[i].time = SearchCaseTest(linear_search, c, array_length, buf, g_array, search_value);
                o->best = T_1_t;
                o->worst = T_N_t;
                o->average = T_N_t;
                break;
            case binary_search_t:
                buf[i].size = array_length;
                buf[i].time = SearchCaseTest(binary_search, c, array_length, buf, g_array, search_quick);
                o->best = T_1_t;
                o->worst = T_logN_t;
                o->average = T_logN_t;
                break;
        }
        array_length *= 2;
        search_quick *= 2;
        printf("Pass %d/%d done\n", i+1, n);
    }
    
}


void randomArray(int *a, int length){ // Create a random array of length "length"
    srand(clock());
    for(int i = 0; i<length; i++){
        a[i] = rand();
    }
}

void sortedArray(int *a, int length){ // Create a sorted array
    for(int i = 0; i<length;i++){
        a[i] = i;
    }
}

void reversedArray(int *a, int length){ // Create an inverted sorted array
    for(int i = 0; i<length; i++){
        a[i] = length - i;
    }
}

void quicksortArray(int *a, int length){
    for(int i = 0; i<length; i++){
        a[i] = 1;
    }
}


// The calculation of the time complexity
double T_1(double time, int length){
    return time / 1;
}

double T_logN(double time, int length){
    return time/log10(length);
}

double T_N(double time, int length){
    return time / length;
}

double T_NlogN(double time, int length){
    return time/(length * log10(length));
}

double T_N2(double time, int length){
    return time/(length * length);
}

double T_N3(double time, int length){
    return time/(length*length*length);
}