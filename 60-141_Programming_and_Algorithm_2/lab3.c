#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Constant Declarations
#define M 20
#define N 20

// Function Prototypes
void PopulateRandom(int A2D[][N], unsigned int rowsize, unsigned int colsize, int min, int max);
void PrintArray2D(int A2D[][N], unsigned int rowsize, unsigned int colsize);
int LinearSearch2D(int A2D[][N], unsigned int rowsize, unsigned int colsize, unsigned int key);
int LeftShift(int A2D[][N], unsigned int rowsize, unsigned int colsize);


// Control Function
int main()
{
	int A2D[M][N];

	unsigned int rowsize;
	unsigned int colsize;

	printf("Please enter row size followed by a column size (max of 20 each): ");
	scanf("%d %d", &rowsize, &colsize);

	printf("Testing an array of size: %d x %d\n", rowsize, colsize);
	
	// Populating array A with random numbers between 1 and rows*columns
	int min = 1;
	int max = rowsize * colsize;
	printf("Populate Array with Unique random integers between %d and %d...\n", min, max);
	PopulateRandom(A2D, rowsize, colsize, min, max);
	
	// Display array
	puts("PrintArray2D:");
	PrintArray2D(A2D, rowsize, colsize);
	
	// Linear Search
	unsigned int key;
	puts("Enter number to search for in array:");
	scanf("%d", &key);
	if (LinearSearch2D(A2D, rowsize, colsize, key) == 0)
	{
		printf("%d was not found.", key);
	}
	else
	{
		printf("%d was found!", key);
	}

	// Left shift array A and display it
	puts("LeftShift followed by PrintArray2D:");
	LeftShift(A2D, rowsize, colsize);
	PrintArray2D(A2D, rowsize, colsize);
	
	return 0;
}

// Populates 2D Array of rowsize x colsize with random integers between min and max
// Input: Array A and its row and column size. A min and max number to calculate possible range
// Output: Nothing return, array A is updated.
void PopulateRandom(int A2D[][N], unsigned int rowsize, unsigned int colsize, int min, int max)
{
	int r,c;
	srand(time(NULL));
	for (r = 0; r < rowsize; r ++) //Filling Row
		for (c = 0; c < colsize; c ++) //Column
			A2D[r][c] = (rand() % (max-min)) + min;
}

// Displays contents of 2D array of rowsize x colsize in a neat table
// Input: Array A and its row and column size
// Output: Nothing return, array A displayed.
void PrintArray2D(int A2D[][N], unsigned int rowsize, unsigned int colsize)
{
	int r, c;
	for (r = 0; r < rowsize; r ++)
	{
		for (c = 0; c < colsize; c ++)
		{
		printf("%03d ", A2D[r][c]);
		}	// End of c loop - last column in row
		puts(""); // Return to next line
	}	//End of r loop - last row
}

// Searchs for "key" in a 2D array, passes it's array position
// Input : Array A and its row and column size, along with a "key", a positive int value.
// Output: Returns 0 if nothing found, > 0 if succesful 
int LinearSearch2D(int A2D[][N], unsigned int rowsize, unsigned int colsize, unsigned int key)
{
	int r, c;
	int x = 0;
	for (r = 0; r < rowsize; r ++)
	{
		for (c = 0; c < colsize; c ++)
		{
			if (A2D[r][c] == key)
			{
				return 1;
			}
		}	// End of c loop - last column in row
	}	//End of r loop - last row
	return 0;
}

// Sorts 2D array from smallest to largest integer, row-wize
// Input : Array A and its row and column size
// Output: returns 0 if sucessful, array A is updated.
int LeftShift(int A2D[][N], unsigned int rowsize, unsigned int colsize)
{
	int r, c;
	int B2D[M][N];
	// Copying array for temporary use
	for (r = 0; r < rowsize; r++)
	{
		for (c = 0; c < colsize; c++)
		{
			B2D[r][c] = A2D[r][c];
		}
	}
	// Shifting columns to left, last column filled with garbage.
	for (r = 0; r < rowsize; r++)
	{
		for (c = 0; c < colsize; c++)
		{
			A2D[r][c] = B2D[r][c+1];
		}
	}
	// Filling last column digits from first column, shifted up.
	for (r = 0; r < rowsize; r++)
	{
		A2D[r][colsize-1] = B2D[r+1][0];
	}
	A2D[rowsize-1][colsize-1] = B2D[0][0];
}