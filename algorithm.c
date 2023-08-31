#include "algorithm.h"
#include <stdlib.h>
#include <stdio.h>

void bubble_sort(int *a, int n)
{
	for(int i = 0; i < n-1; i++){
		int swapped = 0; // Check if there is swap
		for(int j = 0; j < n-1-i; j++){
			if(a[j]>a[j+1]){
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				swapped = 1;
			}
		}
		if(swapped == 0){ // If no swap, means the array is sorted
			break;
		}
	}
}

void insertion_sort(int *a, int n)
{
	int el, j;
	for(int i = 0; i < n; i++){
		el = a[i];
		for(j = i - 1; j >= 0; j--){
			if(a[j] <= el){
				break;
			}
			a[j+1] = a[j];
		}

		a[j + 1] = el;
	}
}

int partition(int *array, int a, int b){
	int pivot, temp;
	pivot = array[(a+b)/2]; // Pivot is in the middle
	
	int i = (a - 1);
	for(int j = a; j<=b;j++){
		if(j == (a+b)/2){ // If j == pivot index {skip}
			continue;
		}
		if(array[j]<pivot){ // If the number is smaller than the pivot
			if(i+1 == (a+b)/2){ // If the next i == pivot index ---> index + 2, beacuse the pivot should not be swapped
				i++;
			}
			i++;
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	if(((a + b)/2) < i + 1){ //Check if the number is a higher or lower than pivot
		i--; // i-- if the pivot is larger than array[i + 1]
	}
	
	temp = array[i+1];
	array[i+1] = array[(a+b)/2];
	array[(a+b)/2] = temp;

	return (i + 1);
}
void mine_quick_sort(int *array, int a, int b){
	if(a < b){
		int k = partition(array, a, b);
		mine_quick_sort(array, a, k-1);
		mine_quick_sort(array, k+1, b);
	}
}
void quick_sort(int *a, int n)
{
	mine_quick_sort(a, 0, n-1);
}


bool linear_search(const int *a, int n, int v)
{
	for(int i = 0; i < n; i++){
		if(a[i] == v)
			return true;
	}
	return false;
}

bool binary_search(const int *a, int n, int v)
{
	int low = 0, high = n-1;
	int mitt;

	while(high - low > 1){
		mitt = (high + low)/2;
		if(a[mitt] < v){
			low = mitt + 1;
		}else{
			high = mitt;
		}
	}

	if(a[low] == v)
		return true;
	else if(a[high] == v)
		return true;

	return false;
}
