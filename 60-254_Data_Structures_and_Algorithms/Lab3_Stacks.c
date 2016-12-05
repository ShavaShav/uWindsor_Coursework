#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10     // size of max sequence
#define CASES 10    // # of cases

int stackMethod(char *sequence);
void push(int stack[]);
void pop(int stack[]);
int prefixMethod(char *sequence);

int main ()
{
    size_t i;
    char sequence[CASES][SIZE+1]; // array for storing sequences (SIZE+1 for '\0' char)

    // Scan (CASES) number of sequences of size (SIZE)
    printf("Enter %d Sequences of Parenthesis':\n", CASES);
    for (i = 0; i < CASES; i++) scanf("%s", sequence[i]);

    // Compute if each sequence has balanced parenthesis, display results
    printf("%-15s%-15s%-15s\n", "Sequence", "Stack Method", "Prefix Method");
    for (i = 0; i < CASES; i++)
    {
        printf("%-15s", sequence[i]);

        // Method 1 - Stack Implementation
        if (stackMethod(sequence[i]) == 1) printf("%-15s", "Balanced");
        else printf("%-15s", "Unbalanced");

        // Method 2 - Checking Prefix Sum
        if (prefixMethod(sequence[i]) == 1) printf("%-15s\n", "Balanced");
        else printf("%-15s\n", "Unbalanced");
    }
	return 0;
}

// Checks if a sequences of parenthesis is balanced, by implementing a pseudo-stack with an array
// I/P: a string made up of parenthesis e.g. "(()())"
// O/P: 1 if sequence is balanced, -1 if unbalanced
int stackMethod(char *sequence)
{
    char *ptr_sequence = sequence;  // point to beginning of sequence
    int stack[SIZE] = {0};          // initialize stack to zero's

	while (*ptr_sequence != '\0')   // loop through sequence
    {
    	if (stack[(SIZE/2)+1] == 1) return -1;	// exit early if more than half of seq is opening brackets

        if (*ptr_sequence == '(')   // push opening brackets to stack
            push(stack);
        else if (*ptr_sequence == ')')      // for closing brackets:
        {
            if (stack[0] == 0) return -1;   // if trying to pop empty stack, sequence is unbalanced!

            pop(stack);                     // otherwise, pop opening bracket off stack
        }
        ptr_sequence++; // go to next character in sequence
    }

    if (stack[0] == 0) return 1;    // exhausted stack = balanced sequence
    else return -1;     // opening brackets left on stack = unbalanced
}

// Add to stack.
// Assumes stack is <= SIZE
void push(int stack[SIZE])
{
    size_t i = 0;
    while (stack[i] != 0)   // go to top of stack (first 0)
        i++;

    stack[i] = 1;           // set top element (push to stack)
}

// Remove from stack.
// Assumes that stack is non-empty
void pop(int stack[SIZE])
{
    size_t i = 0;
    while (stack[i] != 0)   // go to top of stack (first 0)
        i++;

    stack[i-1] = 0;           // reset element sitting below top (pop from stack)
}

// Checks if a sequences of parenthesis is balanced, by converting to -1's & 1's and checking pre-fix sums
// I/P: a string made up of parenthesis e.g. "(()())"
// O/P: 1 if sequence is balanced, -1 if unbalanced
int prefixMethod(char *sequence)
{
    size_t seq_len = strlen(sequence);    // length of sequence
    int prefix_sequence[seq_len];         // initialize array for -1's and 1's
    int prefix_sum[seq_len];              // initialize prefix sum array

    size_t i;
    int sum = 0;    // cumulative sum
    for (i = 0; i < seq_len; i++)
    {
        if (sequence[i] == '(')     // assign prefix value to array according to sequence
            prefix_sequence[i] = 1;
        else
            prefix_sequence[i] = -1;

        sum += prefix_sequence[i];  // add previx value to cumulative sum
        prefix_sum[i] = sum;        // prefix sum (a.k.a sum at current index)

        if (prefix_sum[i] < 0)  // balanced subsequence will have a prefix sum >= 0 (must be opening
            return -1;          // bracket before closing) so can exit early if it dips below 0
    }

    if (sum == 0)   // balanced sequences must end with a cumulative sum of 0 (every bracket matched)
        return 1;
    else
        return -1;
}
