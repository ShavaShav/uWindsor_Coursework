#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0 // 1 for printouts, 0 for clean version
#define MAXNUM 100 // max absolute integer value used in array
#define SIZE 30  // num of elements in heap/array

void Heapify(int array[], int i, int size);
void BuildHeap(int array[], int size);
void Heapsort(int heap[], int size);
void Swap(int array[], int index1, int index2);
void DisplayArray(int array[], int size, char* title);
void PopulateUniqueArray(int array[], int size);

int main()
{
	int size = SIZE;
	int array[size];

	PopulateUniqueArray(array, size);
	DisplayArray(array, size, "Array:");
	BuildHeap(array, size);
	DisplayArray(array, size, "Heap:");
	Heapsort(array, size);
	DisplayArray(array, size, "Heapsorted:");


	return 0;
}

// BuildHeap subroutine, top-down, heapifies part of array
// I/P: int array with start (i) and end (size) indices
void Heapify(int array[], int i, int size)
{
	// "i" is the temporary parent we are looking at
	int leftChild = 2*i; // 2
	int rightChild = leftChild+1; // 3
	int temp;

	if (leftChild > size && rightChild > size)
		return;	// array[i] is a leaf, no children

	// store larger child, or only child (must be left to satisfy heap)
	if (array[leftChild] > array[rightChild] || rightChild > size)
		temp = leftChild;
	else
		temp = rightChild;

	// if parent is less than stored child, swap and
	// run heapify on this new child, to push it down where it belongs
	if (array[i] < array[temp])
	{
		Swap(array, i, temp);
		Heapify(array, temp, size);
	}
}


// Turns an array in to a "heap" (each child less than parent)
// I/P: int array (starting at 1), and it's size
// O/P: null
void BuildHeap(int array[], int size)
{
	int i = size;
	while (i > 0)
	{
		Heapify(array, i, size);
		i--;
	}
}


// sorts a heap in ascending order
// I/P: a heap of int values and number of nodes
// O/P: null
void Heapsort(int heap[], int size)
{
	int i = size; // index of last element
	// keep reheaping, placing top element at back of array
	while (i > 1)
	{
		Swap(heap, 1, i);       // swap top element for last in heap
		Heapify(heap, 1, i-1);  // re-heap elements before last to make smaller heap
		if (DEBUG){DisplayArray(heap, i-1, "ReHeaped");}
		i--;    // do again on on smaller heap until 1 element.
	}
}

// standard swap of array elements
void Swap(int array[], int index1, int index2)
{
	int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

// populate a given array with unique random integers
void PopulateUniqueArray(int array[], int size)
{
	srand(time(NULL));	//set random seed
	size_t i = 1;
	// populate array with random intergers,
	for (; i <= size; i++)
	{
		int temp = (rand() % MAXNUM);
		size_t j = 1;
		for (; j < i; j++)	// check previous elements
		{
			// if not unique, generate new random number and recheck
			if (array[j] == temp)
			{
				temp = (rand() % MAXNUM);
				j = 0; // since j will be incremented to 1 at end iteration
            }
		}
		array[i] = temp; // place unique element in array
	}
}

// display an array's contents on terminal
void DisplayArray(int array[], int size, char* title)
{
    printf("\n%s\n", title);
	size_t i = 1;	// print array
	for (; i <= size; i++) printf("%d ", array[i]);
	puts("\n");
}
