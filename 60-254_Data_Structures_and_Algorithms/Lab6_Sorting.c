#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 100  // max random int generated in array to keep manageable

void PopulateArray(int array[], int size);
void InsertionSort(int array[], int size);
void QuickSort(int array[], int low, int high);
int Partition(int array[], int low, int high);
void DisplayArray(int array[], int size, char* title);
void Swap(int array[], int index1, int index2);
void SortAndClock(int array[], int size, int algorithm);
void ClearBuffer();


int main()
{
	while (1)   // loop forever
    {
        int size;   // get size of array

        printf("Enter size of array (int): ");
        scanf("%d", &size);
		ClearBuffer();
		
        int array[size];    // create array

        PopulateArray(array, size);
        //DisplayArray(array, size, "Populated Array");

        unsigned int input;

        printf("Enter 1 for Insertion Sort, 2 for QuickSort: ");

        scanf("%d", &input);
		ClearBuffer();

        SortAndClock(array, size, input);

        char choice;    // prompt for next case
        printf("\nPress Enter for another, or N to exit.");
        choice = getchar();
		ClearBuffer();
		
        if (choice == 'n' || choice == 'N') break;
    }

	return 0;
}

// sort, clock run time, display results of given array and sorting algo
// 1 = Insertion Sort, 2 = Quicksort
void SortAndClock(int array[], int size, int algorithm)
{
    clock_t start_time, end_time;
    double time_ms;	// time in miliseconds

    start_time = clock();	// log start time
    // uncomment the DisplayArray() lines to see sorted arrays
    switch (algorithm)
    {
        case 1: InsertionSort(array, size);
        		end_time = clock();	// log end
                //DisplayArray(array, size, "Insertion Sorted");
                break;
        case 2: QuickSort(array, 0, size-1);
        		end_time = clock();
                //DisplayArray(array, size, "QuickSorted");
                break;
        default: "Invalid Input";
        		return;
    }
    time_ms = (double) (end_time-start_time)/CLOCKS_PER_SEC*1000.00;  // calculate run time in mili secs
    printf("Took %0.2f miliseconds to complete sort.\n", time_ms);
}

// insertion sort algorithm
void InsertionSort(int array[], int size)
{
	int i = 1;
	for (; i < size; i++)   // go through array from 1 to size - 1
	{
		int temp = array[i];    // store current array element
		int j = i - 1;          // store previous element's index

		 // shift elements before current up, terminating at element < current or lower bound
		while (j >= 0 && array[j] > temp)
		{
			array[j+1] = array[j];  // swap neighbour elements
			j--;                    // go to previous element
		}
		array[j+1] = temp;  //place temp is correct position
	}
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

// populate a given array with random integers
void PopulateArray(int array[], int size)
{
	srand(time(NULL));	//set random seed

	size_t i = 0;	// populate array with random intergers
	for (; i < size; i++) array[i] = rand() % MAXNUM;

}

// display an array's contents on terminal
void DisplayArray(int array[], int size, char* title)
{
    printf("\n%s\n", title);
	size_t i = 0;	// print array
	for (; i < size; i++) printf("%d ", array[i]);
	puts("\n");
}

// consumes stray input characters left behind in input stream
void ClearBuffer()
{
	while ( getchar() != '\n' );	// get chracters to newline
}