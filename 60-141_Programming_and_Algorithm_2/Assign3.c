#include <stdio.h>
#include <string.h>

#define DEBUG 0		// 1 to display display debug printouts, 0 to hide

// Function Prototypes
int ReadWords(char wordList[][21], char sorted_wordList[][21], int *word_count);
int SortWord(char *word, int word_size);
int SortWordLists(char sorted_wordList[][21], char wordList[][21], int *word_count);
int AssignAnagramGroup(char sorted_wordList[][21], int *word_count, int *anagramGroup, int *anagramgroup_count, int *anagramGroup_sizes);
int SortAnagramGroups(char wordList[][21], int *word_count, int *anagramGroup, int *anagramGroup_count, int *anagramGroup_sizes);
void PrintResults(char wordList[][21], int *word_count, int *anagramGroup, int *anagramgroup_count, int *anagramGroup_sizes);

int main(void)
{
	char wordList[101][21];	// stores list of up 100 words (max 21 char)
	char sorted_wordList[101][21];	// stores sorted wordList
	int word_count = 0; // the number of words in wordList
	int anagramGroup[101];	// assigns each word it's group ID
	int anagramGroup_count = 0;		// number of groups, starting at 0 for first group
	int anagramGroup_sizes[101];	// for each group, size is stored

	for (int i = 0; i < 100; i++)
	{
		anagramGroup_sizes[i] = 1;	//populate Group sizes, starting at 1
	}

// READ WORDS INTO FIRST WORD LIST, WHILE SORTING CHARACTERS AND PUTTING RESULTS IN SECOND LIST
	if(ReadWords(wordList, sorted_wordList, &word_count) != 0)
		puts("ReadWords Failed!");

	if (DEBUG)
	{	
		puts("");	
		puts("***DEBUG after ReadWords()***");
		printf("wordcount=%d, ptr_word_count=%d\n", word_count, word_count);
		for (int i = 0; i < word_count; i++)
		{
			printf("wordList[%d]= %s\tsorted_wordList[%d]= %s\n", i, wordList[i], i, sorted_wordList[i]);
		}
	}


// SORT WORD LISTS APHBETICALLY, USING SECOND (CHARACTER-SORTED) LIST - EFFECTIVELY GROUPING ANAGRAMS TOGETHER IN LIST
	if(SortWordLists(sorted_wordList, wordList, &word_count) != 0)
		puts("SortWordList Failed!");

	if (DEBUG)
	{		
		puts("");
		puts("***DEBUG after SortWordList())***");
		for (int i = 0; i < word_count; i++)
		{
			printf("wordList[%d]= %s\tsorted_wordList[%d]= %s\n", i, wordList[i], i, sorted_wordList[i]);
		}
	}	

// DETERMINE GROUP IDS AND GROUP SIZES OF EACH WORD IN LIST
	if(AssignAnagramGroup(sorted_wordList, &word_count, anagramGroup, &anagramGroup_count, anagramGroup_sizes) != 0)
		puts("AssignAnagramGroup() Failed!");

	if (DEBUG)
	{		
		puts("");
		puts("***DEBUG after AssignAnagramGroup()***");
		for (int i = 0; i < word_count; i++)
			printf("sorted_wordList[%d]= %s\t\tanagramGroup[%d]= %d\n", i, sorted_wordList[i], i, anagramGroup[i]);
		for (int i = 0; i <= anagramGroup_count; i++)
			printf("Group %d size = %d\n", i, anagramGroup_sizes[i]);
		printf("No. of Groups = %d\n", anagramGroup_count+1);
	}
// SORT THE ANAGRAM GROUPS BY LARGEST SIZE TO SMALLEST
	if(SortAnagramGroups(wordList, &word_count, anagramGroup, &anagramGroup_count, anagramGroup_sizes) != 0)
		puts("SortAnagramGroups() Failed!");

	if (DEBUG)
	{
		puts("");
		puts("***DEBUG after SortAnagramGoups()***");
			for (int j = 0; j < word_count; j++)
				printf("wordList[%d] = %s\n", j, wordList[j]);
			for (int i = 0; i <= anagramGroup_count; i++)
				printf("Group %d size = %d\n", i, anagramGroup_sizes[i]);
	}

// PRINT REULTS OF FIRST FIVE GROUPS
	PrintResults(wordList, &word_count, anagramGroup, &anagramGroup_count, anagramGroup_sizes);

	return 0;
}

// Reads a list of up to 100 words (seperated by whitespace or newline) until sentinel value "STOP" into list (array).
// Also populates second list, which is a duplicate of first list but with words sorted by character
// Input: 2 Char arrays and their size, passed by reference 		
// Output: 0 if success
int ReadWords(char wordList[][21], char sorted_wordList[][21], int *word_count)
{
	int done = 1;
	char word[21];
	while (done != 0)
	{
		scanf("%s", word);
		if (strcmp(word, "STOP") == 0 || *word_count > 99)	// exits at STOP or 100 words
			done = 0;
		else	// otherwise, scans word into wordList and sorts characters for sorted_wordList
		{
			strcpy(wordList[*word_count], word);	// store original word in first list			
			SortWord(word, strlen(word));				// sort word by characters - ascending
			strcpy(sorted_wordList[*word_count], word);	// store sorted word in second list
			(*word_count)++;			// increments the value of word count by 1
		}
	}
	return 0; // returns 0 if successful
}

// Sorts Word by characters- ascending
// Input: Word and it's size
// Output: 0 if success
int SortWord(char *word, int word_size)
{
	for (int i = 0; i < word_size-1; i++)
	{
		for (int j = 0; j < word_size-1; j++)
		{
			if (word[j] > word[j+1])
			{				
				char temp = word[j];
				word[j] = word[j+1];
				word[j+1] = temp;
			}
		}		
	}
	return 0;	// returns 0 if successful
}

// Sorts 1st list of words alphabetically, ascending (eg. aa -> zz). Performs idential swaps on 2nd wordlist 
// Input: 2 same sized list of words (char arrays) and their size
// Output: 0 if success
int SortWordLists(char sorted_wordList[][21], char wordList[][21], int *word_count)
{
	// Bubble Sort
	for (int i = 0; i < *word_count-1; i++)
	{
		for (int j = 0; j < *word_count-1; j++)
		{
			// If word different (different ints from str cmp), place smaller word (int value) first, effectively grouping anagrams
			if (strcmp(sorted_wordList[j], sorted_wordList[j+1]) > 0)
			{
				// Swap words 
				char temp[21];
				strcpy(temp, sorted_wordList[j]);
				strcpy(sorted_wordList[j], sorted_wordList[j+1]);
				strcpy(sorted_wordList[j+1], temp);
				// in both lists (IDEA TO BE BUILT ON)
				strcpy(temp, wordList[j]);
				strcpy(wordList[j], wordList[j+1]);
				strcpy(wordList[j+1], temp);
			}
		}
	}
	return 0; // returns 0 if successful
}

// Assigns group IDs and group sizes to prepared list of anagrams grouped together 
// Input: Prepared list of anagrams (char array), size of list, groupID, and group size
// Output; 0 if success
int AssignAnagramGroup(char sorted_wordList[][21], int *word_count, int *anagramGroup, int *anagramGroup_count, int *anagramGroup_sizes)
{
	anagramGroup[0] = 0;	// Start IDs at 1
	for (int i = 0; i < *word_count; i++)
	{
		if (strcmp(sorted_wordList[i], sorted_wordList[i+1]) != 0) // If words are different
		{
			(*anagramGroup_count)++;	// new group ID
			anagramGroup[i+1] = *anagramGroup_count;	// give anagramGroup new group ID
		}
		else	// If words are same
		{
			anagramGroup[i+1] = *anagramGroup_count;  		// give original group ID to anagramGroup
			(anagramGroup_sizes[*anagramGroup_count])++;	// increment group size at group ID
		}
	}
	(*anagramGroup_count)--;	//to compensate for extra count
	return 0;
}

// Sort Anagram Groups in original list by size, largest to smallest
// Input: Prepared word List (char array), size of list, group ID and group size
// Output: return 0 if success
int SortAnagramGroups(char wordList[][21], int *word_count, int *anagramGroup, int *anagramGroup_count, int *anagramGroup_sizes)
{
	char grouped_sorted_wordList[100][21];	// for storing groups in order of size
	int sorted_ids[100];					// for storing index positions once sorted
	for (int i = 0; i < 100; i++)
	{
		strcpy(grouped_sorted_wordList[i],wordList[i]);	// populated sorted grouped word list
		sorted_ids[i] = i;	// populate index 0 - 100
	}
	// Sort group sizes array, largest to smallest
	for (int i = 0; i <= (*anagramGroup_count)-1; i++)
	{
		for (int j = 0; j <= (*anagramGroup_count)-1; j++)
		{
			if (anagramGroup_sizes[j] < anagramGroup_sizes[j+1])
			{
				int temp = anagramGroup_sizes[j];
				anagramGroup_sizes[j] = anagramGroup_sizes[j+1];
				anagramGroup_sizes[j+1] = temp;

				temp = sorted_ids[j+1];
				sorted_ids[j+1] = sorted_ids[j];
				sorted_ids[j] = temp;
			}
		}
	}

	// Match words and group IDs to sorted sizes
	int knt = 0;
	for (int i = 0; i <= *anagramGroup_count; i++)
	{
		for (int j = 0; j < *word_count; j++)
		{	
			if (sorted_ids[i] == anagramGroup[j]) // Match sorts ID to original ID
			{	
				strcpy(grouped_sorted_wordList[knt++], wordList[j]); // copy word to a new list
			}
		}
	}

	// Copy new lists back to original lists
	for (int i = 0; i < *word_count; i++)
	{
		strcpy(wordList[i], grouped_sorted_wordList[i]);
	}
	for (int i = 0; i <= *anagramGroup_count; i++)
	{
		anagramGroup[i] = sorted_ids[i];
	}
	return 0;
}

// Prints the 5 largest anagram groups, largest to smallest
// Input: Original word List (char array), sorted index for comparing, size of list, group ID and group size
// Output: void
void PrintResults(char wordList[][21], int *word_count, int *anagramGroup, int *anagramGroup_count, int *anagramGroup_sizes)
{
	puts("***Anagrams***");
	int knt = 0;
	for (int i = 0; i < 5, i < *anagramGroup_count+1; i++) // First five groups
	{
		printf("Group of size %d: ", anagramGroup_sizes[i]);
		for (int j = 0; j < anagramGroup_sizes[i]; j++) // display group [i]
		{
			printf("%s ", wordList[knt++]);
		}
		puts("");
	}
}