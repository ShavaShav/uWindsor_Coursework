#include <stdio.h>

#define LENGTH 10	// size of array.

int *Largest (int *ptr_array, int size);
void Swap (int *ptr_a, int *ptr_b);

int main()
{
	//Testing Largest Address function
	int size = LENGTH;
	int array[LENGTH] = {0,1,2,3,12,5,6,7,8,9};
	int *ptr_array = array;
	printf("Starting address of ptr_array: %p\n", ptr_array); // Prints address of where ptr_array is pointing
	printf("Address of largest element in array: %p\n\n", Largest(ptr_array, size));
	
	//Testing Swap function
	int a = 4444;
	int b = 8888;
	printf("Before Swap\na = %d, b = %d.\n\n", a, b);
	Swap(&a, &b);
	printf("After Swap\na = %d, b = %d.\n\n", a, b);

	return 0; //on successful completion
}

// Largest uses a linear search to point to the address of the largest number in an array
// Input: a pointer to a 1D array of integers, and the size of the array
// Output: returns hex address (void)
int *Largest (int *ptr_array, int size)
{
	int *max = ptr_array;	// will point to first array position by default
	while (size > 0)
	{
		if (*ptr_array > *max)	// if deferenced ptr_array bigger then deferenced max
		{
			max = ptr_array;	// max will point to ptr_array's current address
		}
		// counters
		ptr_array++;
		size--;
	}
	return max;		// return the pointer to the largest array cell
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