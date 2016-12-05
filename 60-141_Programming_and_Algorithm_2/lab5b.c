#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define SEED 50

// Function Prototypes
void FillArray(int *array, unsigned int size);
void PrintArray(int *array, unsigned int size);
void Swap (int *ptr_a, int *ptr_b);
void BubbleSort(int *array, unsigned int size);
void SelectionSort(int *array, unsigned int size);

int main ()
{
	unsigned int size = SIZE;
	int numList[SIZE] = {0};
	int *ptr_numList = numList;
	
	puts("Bubble Sort");

	FillArray(ptr_numList, size);
	PrintArray(ptr_numList, size);

	BubbleSort(ptr_numList, size);
	PrintArray(ptr_numList, size);

	puts("");
	puts("Selection Sort");

	FillArray(ptr_numList, size);
	PrintArray(ptr_numList, size);

	SelectionSort(ptr_numList, size);
	PrintArray(ptr_numList, size);

	return 0;
}

// Populates Array of inputted size with random integers between 0 and 100
// Input: Array pointer and its size.
// Output: Nothing returned, array is updated.
void FillArray(int *array, unsigned int size)
{
	// Random numbers will be generated by taking current time plus the seed
	static int seed = SEED;
	long int random_time = time(NULL) + seed;
	srand(random_time);
	while (size != 0)
	{
		*array = (rand() % 100);
		size--;
		array++;
	}
	seed = seed+10;	// on leaving function, change seed	
}

// Displays Array of inputted size horizontally
// Input: Array pointer and its size.
// Output: Nothing returned, array is printed and goes to next line
void PrintArray(int *array, unsigned int size)
{
	while (size != 0)
	{
		printf("%d ", *array);
		size--;
		array++;
	}
	puts("");		
}

// Swap trads values of two integers digits
// Input: 2 pointers to 2 different ints
// Output: null
void Swap (int *ptr_a, int *ptr_b)
{
	int temp = *ptr_a;	// temporarily store first digit
	*ptr_a = *ptr_b;	// place value of dereferenced ptr_b in location of ptr_a
	*ptr_b = temp;		// place temp in location of ptr b
}

// Bubble sorts array using pointers, largest to smallest
// Input: Array pointer and its size.
// Output: Nothing returned, array is sorted
void BubbleSort(int *array, unsigned int size)
{
	int *ptr_reset = array; // holds original array pointer position
	int hold_size = size;	// holds original array size
	while (size-1 != 0)
	{
		for (int x = 1; x < hold_size; x++)
		{ 
			if (*array < *(array+1))
			{
				Swap(array, (array+1));
			}
			array++;
		}
		array = ptr_reset;	// Reset pointer to beginning of array for next pass
		size--;
	}		
}

// Selection sorts array using pointers, largest to smallest
// Input: Array pointer and its size.
// Output: Nothing returned, array is sorted
void SelectionSort(int *array, unsigned int size)
{
	for(int x = 0; x < size; x++)
	{
		for (int y = x; y < size; y++)
		{ 
			if (*(array+x) < *(array+y))
			{
				Swap((array+x), (array+y));
			}
		}
	}		
}