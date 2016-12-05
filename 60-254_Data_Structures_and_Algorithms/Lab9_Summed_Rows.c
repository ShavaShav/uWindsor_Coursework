#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 15
#define COLS 25

int main()
{
    // set random seed
    srand(time(NULL));

    // populate a 2d array with 1s and 0s
	int array[ROWS][COLS];
    int row, col;
    for (row = 0; row < ROWS; row++) // go over rows
    {
        // get a random number less than column size
        int numOnes = rand() % COLS;
        // fill with 1's up to this number
		for (col = 0; col < numOnes; col++)
        {
			array[row][col] = 1;
        }
        // fill rest of row with 0's
        for (; col < COLS; col++)
            array[row][col] = 0;
    }

	// print 2d array with row indicators
	for (row = 0; row < ROWS; row++)
    {
        printf("Row %-2d\t", row);
		for (col = 0; col < COLS; col++)
        {
			printf("%d ", array[row][col]);
        }
        puts("");
    }

    // find max row O(n)
    int maxLen = 0, maxRow = -1;    // set intial maximums
    row = 0, col = 0;   // start at first row, first column
    while (row < ROWS && col < COLS)    // while in bounds
    {
        if (array[row][col] == 1) // sequence of 1 detected
        {
            col++; // increment col to check next
            maxLen = col;   // store length
            maxRow = row;   // store row
        }
        else
        {
            row++;  // go to next row
        }
    }   // end while, max and maxRow now set

    printf("Maximum row is %d with a length of %d.\n", maxRow, maxLen);

	return 0;
}
