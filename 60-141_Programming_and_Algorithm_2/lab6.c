#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function Prototypes
void printString(char *string);
void Reverse(char *string);
void RecursiveReverse(char *string);
void ParseSentence(char *string);

int main(void)
{
// PART A - CHARACTER ARRAY AND STRING
	char buffer1[] = {'t','h','i','s',' ','i','s',' ','t','h','e',' ','f','i','r','s','t',' ','b','u','f','f','e','r','\0'};	
	char buffer2[] = {"this is the second buffer"};
	char buffer3[80];
	char *pBuffer = buffer3;

	puts("Please enter string to store in buffer3:");
	scanf("%80[^\n]", buffer3); // reads 80 characters until newline (delimiter), regardless of whitespace
/* 
	PROBLEM: scanf %s reads the string up to the white space.
	To conform to scanf requirement, "negated subset" is used to read white space.
	Other option: use fgets as follows: 

	fgets (buffer3, 80, stdin);
*/
	printf("\n%s\n", buffer1);
	printf("%s\n", buffer2);
	printf("%s\n\n", buffer3);

	// Display buffer3 using pBuffer
	while(*pBuffer != '\0')
	{
		printf("%c", *pBuffer);
		pBuffer++;
	}
	puts(""); puts("");

// PART B - STRING MANIPULATION: REVERSE
	Reverse(buffer3);
	printString(buffer3);

// PART C - STRING TOKENIZATION
	ParseSentence(buffer1);
	return 0;
}

// Reverses a char array
// Input: Pointer to char array (string)
// Output: void
void Reverse(char *string)
{
	// set second pointer to end of string, just before '\0'
	char *ptr_endstring = (string + strlen(string)-1);
	// Once the start pointer overlaps the end, string has been reversed.
	while (string < ptr_endstring)
	{
		char temp = *ptr_endstring;
		*ptr_endstring = *string;
		*string = temp;
		string++;
		ptr_endstring--;	
	}
}

// Reverses a char array
// Input: Pointer to char array (string)
// Output: void
void RecursiveReverse(char *string)
{
	if (*string == '\0')
		return;
	else
	{
		RecursiveReverse(string+1);
		putchar(*string);
	}
}

// Reverses a char array
// Input: Pointer to char array (string)
// Output: void
void ParseSentence(char *string)
{
	char *ptr_token = strtok(string, " ");

	while (ptr_token != NULL)
	{
		printf("%s\n", ptr_token);
		ptr_token = strtok(NULL, " ");
	}
}

// Reverses a char array
// Input: Pointer to char array (string)
// Output: void
void printString(char *string)
{
	while(*string != '\0')
	{
		printf("%c", *string);
		string++;
	}
	puts("");
}