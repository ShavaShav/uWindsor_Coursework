#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 40

struct student {
   int ID;
   char name[NAMESIZE];
   struct student *next;
};
typedef struct student Student;

unsigned int listsize = 0;	// for keeping track of list size

int getChoice();
Student *addToList(Student *List);
void printList(Student *List);
void printListRR(Student *List);
void searchList(Student *List);

int main() {
    int choice = 0;
    Student *SLIST = NULL;

    choice = getChoice();

    while(choice >= 0) {
        switch(choice) {
            case 0 : printf("Bye...\n"); exit(0);
            case 1 : SLIST = addToList(SLIST); break;
            case 2 : printList(SLIST); break;
          	case 3 : printListRR(SLIST); break;
            case 4 : searchList(SLIST); break;
            default: printf("That is not a valid choice\n");
        }
        choice = getChoice();
    }

    if(SLIST) free(SLIST); // INVALID
    
    return 0;
}

int getChoice() {
    int choice = 0;

    printf("\n****** MENU ******\n");
    printf("1. Add new student to list.\n");
    printf("2. Print the student list, beginning to end.\n");
    printf("3. Recursively print the student list from the end.\n");
    printf("4. Search the list for a student.\n");
    printf("0. Quit.\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
   // getchar();	//consume \n left in stdin by scanf

    return choice;
}

Student *addToList(Student *List)
{
	Student *node = malloc(sizeof(Student));	// allocate memory

	if (node == NULL)
	{
		puts("Insufficient amount of memory.");
		return List;	// if no more memory, return unaltered list
	}
	// Read node input from user
	puts("\n***Enter Student Record***\nID:");
	scanf("%d", &node->ID);
	getchar();		//consume leftover \n in stdin left by scanf
	
	puts("Name:");
	scanf("%[^\n]", node->name);	// read string to newline

	node->next = NULL;		// setting next node to NULL, as it will be last

	// Add node to linked list
	listsize++;
	if (List == NULL)	// if List empty, place node in first position
	{
		List = node;
		puts("First Record added.");
	}	
	else	// loop through the list to empty spot
	{
		Student *current = List;	// set current pointer to first node
		while (current->next != NULL)	// check if next node exists
		{
			// advance current pointer to next node
			current = current->next;
		} 
		// when next node doesn't exist, place record there
		current->next = node; 
		printf("Record No.%d added.", listsize);
	} 
	return List;
}

void printList(Student *List)
{
	// Empty list case
	if (List == NULL)		
		puts("No records to display.");
	else
	{
		// display list header
		puts("ID\tName\n--\t----");

		// display list
		Student *current = List;	// set current pointer to first node
		while (current != NULL)	// if current node exists
		{
			printf("%d\t%s\n", current->ID, current->name);	// display current node
			current = current->next;	// advance current pointer to next node
		}
	}
}

void printListRR(Student *List)
{
	// Empty list case
	if (List == NULL)		
		puts("No records to display.");
	else
	{
		Student *current = List;
		if (current->next == NULL)	// Base case -> List of 1
			printf("ID\tName\n--\t----\n%d\t%s\n", current->ID, current->name);
		else
		{
			// Recursive step
			printListRR(current->next);	// run function on next node
			printf("%d\t%s\n", current->ID, current->name);	// print current node
		}	
	}
}

// OBJECTIVE: Return first occurance of a user-inputted search key in a list of records
// Input: List of records (Student struct)
// Output: Void
// Assumptions: List is a linked list


void searchList(Student *List)
{
	// Empty list case
	if (List == NULL)		
		puts("No records to search for.");
	else
	{
		int ID_key = 0;
		puts("Enter ID you would like to search for:");
		scanf("%d", &ID_key);

		Student *current = List;	// set current point to first node
		while (current != NULL)
		{
			if (current->ID == ID_key)	// If match, display record and exit function
			{
				printf("%d\t%s\n", current->ID, current->name);
				return;
			}
			current = current->next; // advance pointer to next node
		}
		printf("ID\"%d\" not found.", ID_key);
	}		
}
