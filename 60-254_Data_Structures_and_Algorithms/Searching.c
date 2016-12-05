#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 25

int LinearSearch(int A[SIZE], int key);
void selectionSort(int A[SIZE]);
int BinarySearch(int A[SIZE], int key);

int main()
{
	puts("Unsorted:");
	// populate list of random numbers and display
	srand(time(NULL));
	int A[SIZE] = {0};
	for (size_t i = 0; i < SIZE; i++) 
	{
		A[i] = rand()%SIZE;
		printf("%d, ", A[i]);
	}

	int searchkey = rand()%24;
	printf("\nLinear Search for %d -> Index at: %d", searchkey, LinearSearch(A, searchkey));

	selectionSort(A);
	puts("\nSorted:");
	for (size_t i = 0; i < SIZE; i++)
		printf("%d, ", A[i]);

	printf("\nBinary Search for %d -> Index at: %d", searchkey, BinarySearch(A, searchkey));
	return 0;
}

// unsorted array search algo
int LinearSearch(int A[SIZE], int key)
{
	for (size_t i = 0; i < SIZE; i ++)
	{
		if (A[i] == key)
			return i;
	}
	return -1;	// no find 
}

// sorted array search algo
int BinarySearch(int A[SIZE], int key)
{
	int lowerBound = 0, upperBound = SIZE-1;
	
	while (lowerBound <= upperBound)
	{
		int middle = (lowerBound+upperBound)/2;	// go to middle
		if (A[middle] < key)	// key is in upper half
			lowerBound = middle + 1;	// set new lower bound
		else if (A[middle] > key)	// key is lower half
			upperBound = middle - 1;	// set new upper bound
		else if (A[middle] == key)	// key found
			return middle;	// return array index
	}

	return -1; // un successful, list either empty or key nonexistent.
}

//Ascending order
void selectionSort(int A[SIZE])
{
	for (size_t i = 0; i < SIZE-1; i++)	// go over all elements
	{
		int min = i;	// store min index as first element
		for (size_t j = i; j < SIZE; j++)	// for each element, go over rest and find min, replace.
		{
			if (A[j] < A[min])	
			{
				min = j;
			} 
		}
		if (min != i)	// if min is not previous min
		{
			int temp = A[i];
			A[i] = A[min];
			A[min] = temp;
		}
	}
}