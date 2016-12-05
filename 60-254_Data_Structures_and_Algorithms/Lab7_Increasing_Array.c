#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 30 // max absolute integer value used in array
#define MAXDIF 10 // numbers will be bounded by random # between {0..MAXNUM} + or - MAXNUM/MAXDIF
#define SIZE 20	// size of array, should be ~20% smaller than maxnum to work algos
#define DEBUG 0	// 1 for debug printouts, 0 for prod version
#define LABMETHOD 1 // 1 for copied array method: O(n), 0 for other method O(log n)

// Function Prototypes:
// Lab Method - second array of index differences
void CopyArray(int array1[], int array2[], int size);
void PrepareArray_IndexDifference(int array[], int size);
int BinarySearch(int sorted_array[], int size, int key);

// Other Method looks at index diff within func, saving time and space
int BinarySearchForDiff(int sorted_array[], int size);	

// Need the following functions to create a strictly increasing array
void PopulateUniqueArray(int array[], int size);
void QuickSort(int array[], int low, int high);
int Partition(int array[], int low, int high);
void Swap(int array[], int index1, int index2);
void DisplayArray(int array[], int size, char* title);

int main()
{
	int size = SIZE;
	int array[size];

	// creating stricly increasing array O(n^2)
	PopulateUniqueArray(array, size);
	QuickSort(array, 0, size-1);
	DisplayArray(array, size, "Strictly Increasing Array");

	int match;

	if (LABMETHOD)	// method described in instructions creates second array, making algo O(n)
	{
		// create second array consisting of first array's values minus respective index
	    int array2[size];
	    CopyArray(array, array2, size);
	    PrepareArray_IndexDifference(array2, size);
	    DisplayArray(array2, size, "Differences between value and index");

		// binary search for value that is same as index, O(log n)
		// "Key" in the binary search is when array[i]-i = 0
		match = BinarySearch(array2, size, 0);
	}
	else match = BinarySearchForDiff(array, size);	// this is the proper O(log n) method    


	if (match == -1)
		puts("No values in array equal their index.");
	else
		printf("Value at Array[%d] is %d!\n", match, match);

	return 0;
}

// converts array's values to the difference between value and index
void PrepareArray_IndexDifference(int array[], int size)
{
    size_t i = 0;
    for (; i < size; i++)
        array[i] = array[i] - i;
}

// Binary search for key
// I/P: Sorted array of integers, it's size, and search key.
// O/P: index of found key, or -1 if unsuccessful
int BinarySearch(int sorted_array[], int size, int key)
{
	int low = 0;	// track lower bound of search area
	int high = size - 1;	// track upper bound of search area

	while (low <= high)	// while search area contains at least 1 element
	{
		int middle = low + ((high - low) / 2);	// choose middle element (floor)

		if (DEBUG) printf("Low: %d (%d)\tMiddle: %d (%d)\tHigh: %d (%d)\tKey: %d\n",
			sorted_array[low], low,
			sorted_array[middle], middle,
			sorted_array[high], high, key);

		if (sorted_array[middle] == key)
			return middle;	// success
		else if (sorted_array[middle] < key)	// middle value < key so key will be on right side
			low = middle + 1;	// move lower bound up, shrinking search area
		else
			high = middle - 1;	// move upper bound down
	}
	return -1;	// key not found
}

// Binary search for integer with the value of it's index
// I/P: Sorted array of integers, stricly increasing and it's size.
// O/P: Index of A[i] = i, or -1 if unsuccessful
int BinarySearchForDiff(int sorted_array[], int size)
{
	int low = 0;	// track lower bound of search area
	int high = size - 1;	// track upper bound of search area
	
	while (low <= high)	// while search area contains at least 1 element
	{
		int middle = low + ((high - low) / 2);	// choose middle element (floor)
		// "Key" in the binary search is when array[i]-i = 0
		int key = sorted_array[middle] - middle;

		if (DEBUG) printf("Low: %d (%d)\tMiddle: %d (%d)\tHigh: %d (%d)\tKey: %d\n", 
			sorted_array[low], low, 
			sorted_array[middle], middle,
			sorted_array[high], high, key);

		if (key == 0)
			return middle;	// success
		else if (key < 0)	// index > value so key will be on right side
			low = middle + 1;	// move lower bound up, shrinking search area
		else
			high = middle - 1;	// move upper bound down
	} 
	return -1;	// key not found
}

// sort a sub array with quicksort
// input: subarray of main A, defined by left and right indices l & r.
// output: sorted subarray
void QuickSort(int array[], int low, int high)
{

    int pivot;

	if (low < high) // for array of 1, sorted, low == high
	{
	    // partition array around returned pivot (smaller on left, larger on right)
		pivot = Partition(array, low, high);

        // recursively run on left side
		QuickSort(array, low, pivot);

		// recursively run on right side
		QuickSort(array, pivot+1, high);
	}
}

// hoare's partition scheme, returns pivot where values to left are smaller and values to right are larger
int Partition(int array[], int low, int high)
{
	int pivot = array[low];      // make pivot first element
	int ptr_left = low - 1;      // set pseudo-pointer to outside left bound
	int ptr_right = high + 1;    // set pseduo-pointer to outside right bound

	while (1)    // loop forever
	{
	    // move left pointer to first spot where val is >= pivot
		do {ptr_left++;} while (array[ptr_left] < pivot);

        // move right pointer to first spot where val is <= pivot
		do {ptr_right--;} while (array[ptr_right] > pivot);

        // if pointers have crossed, return right pointer
        if (ptr_left >= ptr_right) return ptr_right;

        // swap the elements at these pointers if pointers not crossed yet
        Swap(array, ptr_left, ptr_right);
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
    char string[15];
	size_t i = 0;
	// populate array with random intergers, - & +
	for (; i < size; i++)
	{
		int temp = (rand() % MAXNUM) - MAXNUM/MAXDIF;
		size_t j = 0;
		for (; j < i; j++)	// check previous elements
		{
			// if not unique, generate new random number and recheck
			if (array[j] == temp)
			{
				temp = (rand() % MAXNUM) - MAXNUM/MAXDIF;
				j = -1; // since j will be incremented to 0 at end iteration
            }
		}
		array[i] = temp; // place unique element in array
	}
}

// copies an int array1 to array2
void CopyArray(int array1[], int array2[], int size)
{
    size_t i = 0;
    for (; i < size; i++)
        array2[i] = array1[i];
}

// display an array's contents on terminal
void DisplayArray(int array[], int size, char* title)
{
    printf("\n%s\n", title);
	// print array
    if (DEBUG) // displays values next to array index
    {
    	puts("Value (Index): ");
		size_t i = 0;
		for (; i < size; i++) printf("%d (%d) - ", array[i], (int) i);
		puts("\n");
    }
    else
    {
		size_t i = 0;
		for (; i < size; i++) printf("%3d ", array[i]);
		puts("\n");
    }
}
