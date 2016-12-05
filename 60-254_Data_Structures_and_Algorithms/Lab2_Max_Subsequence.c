#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMSIZE 100 // maximum absolute value of random number in sequence
#define SEQLEN 15   // length of sequence
#define CASES 10    // number of cases to test algorithm
#define DEBUG 1     // 1 to display debug messages, 0 for production version

// Structure for subsequence data
struct subSequence
{
    int begin;  // beginning index of subsequence
    int end;    // ending index of subsequence
    int max;    // maximum value of subsequence
};

// Function prototype
struct subSequence* findmaxsubsequence(int sequence[SEQLEN]);

int main()
{
	size_t i, j;        // incremental variables for loops
	srand(time(NULL));  // set random seed

	for (i = 0; i < CASES; i++)    // Loop through test cases
	{
		// Populate sequence of SEQLEN with random integers
		int sequence[SEQLEN];
		for (j = 0; j < SEQLEN; j++)
			sequence[j] = (rand() % NUMSIZE*2)-(NUMSIZE); // random number between -NUMSIZE and NUMSIZE

        // Display input
        printf("*** CASE %ld ***", i+1);  // Print test case #
        if (DEBUG) {printf("\nIndex\t\t"); for (j = 0; j < SEQLEN; j++) printf("%5ld", j);}
        printf("\nSequence\t"); for (j = 0; j < SEQLEN; j++) printf("%5d", sequence[j]);

        // Find maximum subsequence
        struct subSequence *max_subsequence = findmaxsubsequence(sequence);

        // Display results
        if (max_subsequence->begin == -1)
            puts("\n\nNo subsequence found.\n");
        else
        {
            printf("\n\nMax subsequence ([%d] to [%d]):\t\t\tMax subsequence sum: %d\n{ ", 
            	max_subsequence->begin, max_subsequence->end, max_subsequence->max); 
            for (j = max_subsequence->begin; j <= max_subsequence->end; j++) printf("%d ", sequence[j]);
            puts("}\n\n");
        }

        // Deallocate memory created during findmaxsubsequence()
        free(max_subsequence);
	}
	return 0;
}

// Calculate maximum contiguous subsequence of a given sequence (and display computations) in O(n) time
// I/P: a sequence of numbers (int array)
// O/P: maximum contiguous subsequence (pointer to subSequence struct)
struct subSequence* findmaxsubsequence(int sequence[])
{
    // initialize and preset subsequence struct
    struct subSequence *max_subsequence = malloc(sizeof(struct subSequence));
    max_subsequence->max = 0;
    max_subsequence->begin = -1;
    max_subsequence->end = -1;

    unsigned int segment_sum[SEQLEN] = {0};		// sum of subsequence up to index
    int start_index[SEQLEN] = {-1};				// starting position of subsequence up to index

    int sum = 0;			// the accumulated sum of the sequence
    int start_flag = -1;	// flag to be changed when a subsequence starts

    // FIND SIZES OF SUBSEQUENCES AND MAX SUBSEQUENCE
    size_t j;
    for (j = 0; j < SEQLEN; j++)    // loop through sequence elements (0 - SEQLEN)
    {
        sum += sequence[j];	// add number to sum

        if (sum >= 0)		// continue contiguous subsequence if sum is 0 or greater
        {
            segment_sum[j] = sum;	// track sum at current subsequence position
            if (start_flag == -1)	// if start of new subsequence, change flag to current index
                start_flag = (int) j;
        }
        else				// reset subsequence
        {
            sum = 0;        // reset sum
            start_flag = -1;            // change flag back to -1
        }
        start_index[j] = start_flag;	// set starting index to flag

        // check if current subsequence sum is the maximum subsequence sum (2nd pass unnecessary)
        if (segment_sum[j] >= max_subsequence->max) // assumes subsequence can have multiple same peaks
        {
            max_subsequence->begin = start_index[j];
            max_subsequence->end = j;
            max_subsequence->max = segment_sum[j];
        }
    }

    // DISPLAY COMPUTATIONS
    if (DEBUG)
    {
        printf("\nStart Index\t"); for (j = 0; j < SEQLEN; j++) printf("%5d", start_index[j]);
        printf("\nSegment Sum\t"); for (j = 0; j < SEQLEN; j++) printf("%5d", segment_sum[j]);
    }

    return max_subsequence;
}
