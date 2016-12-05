#include <stdio.h>
#include <stdlib.h>

typedef struct event
{
	
} Event;


// Global Variables
Event *ptrFirst = NULL;	// pointer to first node
Event *ptrLast = NULL;	// pointer to last node

void ClearList()
{
	Event *ptrDelete = ptrFirst;

	while (ptrFirst != NULL)
	{
		ptrDelete = ptrFirst;
		ptrFirst = ptrFrist->next;
		free(ptrDelete);
	}
	ptrFirst = NULL;
}

void ClearListRR1()
{
	Event *ptrDelete = ptrFirst;

	if (ptrDelete == NULL)
		return;
	else
	{
		ptrFirst = ptrFirst->next;
		free(ptrDelete);
		ClearList();
	}
	ptrFirst = NULL;
}

void ClearListRR2(ptrDelete)
{
	if (ptrDelete == NULL)
		return;
	else
	{
		ClearListRR2(ptrDelete->next);
		free(ptrDelete);
	}
	ptrFirst = NULL;
}