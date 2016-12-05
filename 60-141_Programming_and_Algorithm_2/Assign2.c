#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Constant Declarations
#define ROW 20
#define COL 20

// Function Prototypes
void PopulateArray2DUnique(int A[][COL], unsigned int rowsize, unsigned int colsize, int min, int max);
void DisplayArray2D(int A[][COL], unsigned int rowsize, unsigned int colsize);
int FindLargest(int A[][COL], unsigned int rowsize, unsigned int colsize);
int FindColSum(int A[][COL], unsigned int rowsize, unsigned int colsize, unsigned int col_to_sum);
int Sort2DArray(int A[][COL], unsigned int rowsize, unsigned int colsize);
int CopyArray2D(int A[][COL], int B[][COL], unsigned int rowsize, unsigned int colsize);
int CopyArray2DSpiral(int A[][COL], int B[][COL], unsigned int rowsize, unsigned int colsize);


// Control Function
int main()
{
	int A[ROW][COL];
	int B[ROW][COL];
	//Setting row and column size to random number in range for ROW and COL
	srand(time(NULL));
//	unsigned int rowsize = (rand() % (ROW-1)) + 1;
//	unsigned int colsize = (rand() % (COL-1)) + 1;

	//FOR TESTING - DELETE AFTER AND REPLACE WITH ABOVE
	unsigned int rowsize = 5;
	unsigned int colsize = 5;

	printf("Testing an array of size: %d x %d\n", rowsize, colsize);
	
	// Populating array A with random numbers
	int min = 1;
	int max = 99;
	printf("Populate Array with Unique random integers between %d and %d...\n", min, max);
	PopulateArray2DUnique(A, rowsize, colsize, min, max);
	
	// Display array A
	puts("Display Array 2D:");
	DisplayArray2D(A, rowsize, colsize);
	
	// Find Largest
	printf("FindLargest: %d\n", FindLargest(A, rowsize, colsize));
	
	// Sort array A and display it
	puts("Sort2DArray followed by DisplayArray2D:");
	Sort2DArray(A, rowsize, colsize);
	DisplayArray2D(A, rowsize, colsize);

	// Copy array A into array B, then display B
	puts("CopyArray2D from A to B, then Display B:");
	CopyArray2D(A, B, rowsize, colsize);
	DisplayArray2D(B, rowsize, colsize);

	// Copy array A into array B in spiral form, then display B
	puts("CopyArray2D from A to B, then Display B:");
	CopyArray2DSpiral(A, B, rowsize, colsize);
	DisplayArray2D(B, rowsize, colsize);
	
	return 0;
}

// Populates 2D Array of rowsize x colsize with random integers between min and max
// Input: 
// Output: 
void PopulateArray2DUnique(int A[][COL], unsigned int rowsize, unsigned int colsize, int min, int max)
{
	int r,c;
	srand(time(NULL));
	for (r = 0; r < rowsize; r ++) //Filling Row
		for (c = 0; c < colsize; c ++) //Column
			A[r][c] = (rand() % (max-min)) + min;
}

// Displays contents of 2D array of rowsize x colsize in a neat table
// Input: 
// Output: 
void DisplayArray2D(int A[][COL], unsigned int rowsize, unsigned int colsize)
{
	int r, c;
	for (r = 0; r < rowsize; r ++)
	{
		for (c = 0; c < colsize; c ++)
		{
		printf("%02d ", A[r][c]);
		}	// End of c loop - last column in row
		puts(""); // Return to next line
	}	//End of r loop - last row
}
// Finds largest int value in a 2D array of rowsize x colsize
//
//
int FindLargest(int A[][COL], unsigned int rowsize, unsigned int colsize)
{
	int r, c;
	int max = 0;	// placeholder for largest value
	for (r = 0; r < rowsize; r ++)
	{
		for (c = 0; c < colsize; c ++)
		{
			if (max < A[r][c])
			{
				max = A[r][c];
			}
		}	// End of c loop - last column in row
	}	//End of r loop - last row
	return max;
}

// Sums a given column of ints in a 2D array
// Input: 2d array with row and column size, column to process starting at 0
// Output: The sum of the column
int FindColSum(int A[][COL], unsigned int rowsize, unsigned int colsize, unsigned int col_to_sum)
{
	int r;
	int sum = 0;	// counter for summing up column
	for (r = 0; r < rowsize; r ++)
	{
			sum += A[r][col_to_sum];
	}	//End of r loop - last row
	return sum;
}

// 
// 
// 
int Sort2DArray(int A[][COL], unsigned int rowsize, unsigned int colsize)
{
	// Putting 2D array in 1D form for easier sorting.
	int array1D[rowsize*colsize]; 
	int x = 0;
	int r, c;
	for (r = 0; r < rowsize; r ++)
	{
		for (c = 0; c < colsize; c ++)
		{
			array1D[x] = A[r][c];	// Each entry transfered to 1D array
			x++;
		}	// End of c loop - last column in row
	}	// End of r loop - last row

	// bubble sort
	// loop to control number of passes
	for (r = 0; r < (rowsize*colsize) - 1; r ++)
	{
		// loop to control number of comparisons per pass
		for (x = 0; x < (rowsize*colsize) - 1; x ++)
		{
			// compare adjacent cells, swap if 1st cell is greater than 2nd
			if (array1D[x] > array1D[x+1])
			{
				int swap = array1D[x];
				array1D[x] = array1D[x+1];
				array1D[x+1] = swap;
			}
		}
	}

	// Putting sorted 1D array back into 2D array
	x = 0;
	for (r = 0; r < rowsize; r ++)
	{
		for (c = 0; c < colsize; c ++)
		{
			A[r][c] = array1D[x];	// Each entry transfered to 2D array
			x++;
		}	// End of c loop - last column in row
	}	// End of r loop - last row
	return 0;
}

// 
// 
// 
int CopyArray2D(int A[][COL], int B[][COL], unsigned int rowsize, unsigned int colsize)
{
	int r,c;
	for (r = 0; r < rowsize; r ++) //Filling Row
		for (c = 0; c < colsize; c ++) //Column
			B[r][c] = A[r][c];
	return 0;
}

// 
// 
// 
int CopyArray2DSpiral(int A[][COL], int B[][COL], unsigned int rowsize, unsigned int colsize)
{
	// Putting 2D array in 1D form for easier sorting.
	int array1D[rowsize*colsize]; 
	int x = 0;
	int r, c;
	for (r = 0; r < rowsize; r ++)
	{
		for (c = 0; c < colsize; c ++)
		{
			array1D[x] = A[r][c];	// Each entry transfered to 1D array
			x++;
		}	// End of c loop - last column in row
	}	// End of r loop - last row

	// Storing row and column sizes for use in spiral loop
	int rs = rowsize;
	int cs = colsize;
	// Directional flags
	int right = 1;
	int left = 0;
	int down = 1;
	int up = 0;
	// Spiral loop
	x = 0;
	//	visiting every cell of array A
	while (x != (rowsize * colsize)-1)
	{
		if (right = 1)
		{
			for (c = colsize-cs; c < cs; c++, x++)
			{
				B[rowsize-rs][c] = array1D[x];
			}
			right = 0;
			left = 1;
			cs--;
		}
		if (down = 1)
		{
			for (r = rowsize-rs; r < rs; r++, x++)
			{
				B[r][colsize-(colsize-cs)] = array1D[x];
			}
			up = 1;
			down = 0;
			rs--;
		}
		if (left = 1)
		{
			for (c = cs; c > 0; c--, x++)
			{
				B[rs][c] = array1D[x];
			}
			right = 1;
			left = 0;
			cs--;
		}
		if (up = 1)
		{
			for (r = rs; r > 0; r--, x++)
			{
				B[r][colsize-cs] = array1D[x];
			}
			up = 0;
			down = 1;
			rs--;
		}
		x ++;
	}
	return 0;
}
