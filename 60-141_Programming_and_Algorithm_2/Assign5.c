#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
typedef struct event
{
	int hour;				// 0 - 23
	int minute;				// 0 - 59
	char description[41];	// short description of event [max 41 chars]
	struct event *next;		// self-referential pointer for linked-list
} Event;

// Function Prototypes
void Read();
void SetLast();
void InsertionSort(Event *node);
void RemoveRedundant(); // bonus mark
void Print();
void ClearList();

// Global Variables
Event *ptrFirst = NULL;	// pointer to first node
Event *ptrLast = NULL;	// pointer to last node

// Control Function
int main()
{
	Read();

	RemoveRedundant();

	Print();

	ClearList();

	puts("\"mylist.txt\" has been sorted and saved.");

	return 0;
}

/*
  Scans from file sequentially into a linked-list
  I/P: None 
  O/P: None
  Assumptions: There exists a *ptrFirst pointing to self-referential struct event,
  				and a file called "mylist.txt"
*/  
void Read()
{
	// Open file for reading
	FILE *ptrFile;
	ptrFile = fopen("mylist.txt", "r");

	while(!feof(ptrFile)) // scan sequentially to end of file
	{
		// Allocate memory for node
		Event *node = malloc(sizeof(Event));
		
		// Check if allocation successful
		if (node == NULL)
		{
			puts("No memory left.");
			break;
		}
		node->next = NULL;

		fscanf(ptrFile, "%d %d %s", &node->hour, &node->minute, node->description);
		InsertionSort(node);
	}
	fclose(ptrFile);
}

/*
  Assigns the location of the last node in linked-list to *ptrLast
  I/P: None 
  O/P: None
  Assumptions: There exists a *ptrFirst and *ptrLast, each pointing to 
  				self-referential struct event
*/ 
void SetLast()
{
	if (ptrFirst == NULL)
		return;

	ptrLast = ptrFirst;
	while (ptrLast->next != NULL)
		ptrLast = ptrLast->next;
}

/*
  Inserts a node into an event linked-list, sorted by time using an insertion sort algorithm
  I/P: A pointer to a struct event 
  O/P: None 
  Assumptions: There exists a *ptrFirst and *ptrLast, each pointing to 
  				self-referential struct event
*/  
void InsertionSort(Event *node)
{
	SetLast();

	if (ptrFirst == NULL)	
		// Place first list item
		ptrFirst = node;	
	else if (node->hour < ptrFirst->hour || (node->hour == ptrFirst->hour && node->minute < ptrFirst->minute))	
	{
		// Place at beginning of list if smallest
		node->next = ptrFirst;	
		ptrFirst = node;
	}
	else if (ptrLast->hour < node->hour || (node->hour == ptrFirst->hour && ptrLast->minute < node->minute))	
		// Adding to end of list
		ptrLast->next = node;
	else
	{
		// Adding to middle of list
		Event *ptrCurrent = ptrFirst;
		
		while (ptrCurrent->next->hour < node->hour || (node->hour == ptrCurrent->next->hour && node->minute < ptrCurrent->next->minute)) 
		// If next time less than node time
			ptrCurrent = ptrCurrent->next; // Advance to that position, 

		//if not, leave and place in that position.
		node->next = ptrCurrent->next;
		ptrCurrent->next = node;
	}
}

/*
  Removes duplicates from a linked-list.	
  I/P: None 
  O/P: None
  Assumptions: There exists a *ptrFirst and *ptrLast, each pointing to 
  				self-referential struct event. Linked-list is pre-sorted by time.
*/ 
void RemoveRedundant()
{
	Event *current = ptrFirst;

	while (current != NULL)	// Go through sorted list
	{
		if (current->next == NULL)	// if list of 1, no redundant records possible.
			return;

		// check if two touching nodes have the same attributes, delete them if so
		if ((current->hour == current->next->hour) && (current->minute == current->next->minute) && (strcmp(current->description, current->next->description)==0))
		{
			Event *ptrDelete = current->next;
			current->next = current->next->next;
			free(ptrDelete); 
		}
		current = current->next;
	}
	SetLast(); // reset *ptrLast
}

/*
  Prints the contents of a linked-list to a text file.	
  I/P: None 
  O/P: None 
  Assumptions: There exists a *ptrFirst pointing to self-referential struct event
*/ 
void Print()
{
	FILE *ptrFile;
	ptrFile = fopen("mylist.txt", "w");

	Event *ptrCurrent = ptrFirst;

	while (ptrCurrent != NULL)	// go through linked list
	{
		if (ptrCurrent == ptrFirst)
			fprintf(ptrFile, "%d %d %s", ptrCurrent->hour, ptrCurrent->minute, ptrCurrent->description);
		else
			fprintf(ptrFile, "\n%d %d %s", ptrCurrent->hour, ptrCurrent->minute, ptrCurrent->description);

		ptrCurrent = ptrCurrent->next;
	}
	puts("");	// display new line
}

/*
  Deallocates memory used by linked-list, effectively deleting list.	
  I/P: None 
  O/P: None
  Assumptions: There exists a *ptrFirst pointing to self-referential struct event
*/ 
void ClearList()
{
	Event *ptrDelete = ptrFirst;

	while (ptrFirst != NULL)
	{
		ptrDelete = ptrFirst;
		ptrFirst = ptrFirst->next;
		free(ptrDelete);
	}
	ptrFirst = NULL;
}