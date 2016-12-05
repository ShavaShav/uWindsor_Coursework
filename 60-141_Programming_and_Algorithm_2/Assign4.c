#include <stdio.h>
#include <string.h>

#define MAX 5 // Tested up to 100 records
#define DSLEN 41 // Length of description / file name

// Struct definition of an event aggregate date type
struct event 
{
	int hour;				// storing hour, 0 to 23 inclusive
	int minute;				// storing minute, 0 to 59 inclusive
	char description[DSLEN];	// valid string describing event
};

// Alias definition
typedef struct event Event;

// Function prototypes
 // Base functions (input/add/sort/delete functionality)
int inputRange(int min, int max);
Event* inputEvent(Event *newEvent);
int addEventAtIndex(Event list[], Event *e, int i);
int insertionSortEvent(Event list[], int size);
void displayEvent(Event e);
void displayEventList(Event list[], int size);
int deleteEvent(Event list[], int i, int *p_size);
 // Bonus functions (sequential text file read/write functionality)
int saveEventList(char *filename, Event list[], int size);
int loadEventList(char *filename, Event list[], int *p_size);
char* encode(char *s);
char* decode(char *s);

// Control function
int main()
{
	Event eventlist[MAX];	// storing list of events
	Event e;				// storing single event
	int eventlist_counter = 0;
	int option;
	char filename[DSLEN];
	do
	{	//Display Menu
		puts("\n__= Scheduler v1.0 =__\n\t1. Schedule an event.\n\t2. Delete and event.");
		puts("\t3. Display Schedule\n\t4. Save Schedule\n\t5. Load Schedule\n\t6. Exit");
		option = inputRange(1, 6);	// read menu choice from user
		switch (option)
		{
			// Schedule Event
			case 1: if (eventlist_counter >= MAX)
					{
						puts("Record limit reached");
						break;
					}	
					else
					{
						addEventAtIndex(eventlist, inputEvent(&e), eventlist_counter);
						eventlist_counter++;
						insertionSortEvent(eventlist, eventlist_counter);
						break;
					}
			// Delete Event		
			case 2:	if (eventlist_counter > 0)
					{
						displayEventList(eventlist, eventlist_counter);
						puts("Enter event to delete or -1 to exit:");
						int index = inputRange(-1, eventlist_counter-1);
						if (index >= 0)
						{
							if (deleteEvent(eventlist, index, &eventlist_counter) == -1)
								printf("Could not delete event at %d\n", index);
							else printf("Event at index %d deleted.\n", index);
							
							break;
						}	
					}
					else{
						puts("No records to delete");
						break;
					} 
			// Display the event list
			case 3: displayEventList(eventlist, eventlist_counter);		
					break;
			// Save event
			case 4: printf("Enter file name (Max %d chars): ", DSLEN-1);
					fgets(filename, 41, stdin);
					printf("%d records saved.\n", saveEventList(filename, eventlist, eventlist_counter));
					break;		
			// Load event
			case 5:	printf("Enter file name (Max %d chars): ", DSLEN-1);
					fgets(filename, 41, stdin);
					printf("%d records loaded.\n", loadEventList(filename, eventlist, &eventlist_counter));
					insertionSortEvent(eventlist, eventlist_counter);
					break;
			// Exit
			case 6: return 0;
			default: puts("Invalid Input");
		}
	} while (option != 6);
	return 0;
}

// Prompts user for an integer between min and max.
// Input: range consisting of minimum and maximum
// Output: integer input from user
int inputRange(int min, int max)
{
	if (min > max)		// switch min and max if order invalid
	{
		int temp = max;
		max = min;
		min = temp;
	}

	int input;
	int done = 0;		// to be updated when valid user input
	while (done != 1)
	{
		/* NOTE FOR SELF
		MUST use fgets and sscanf to read int in order to use fgets later! 
		scanf leaves a stray '\n' in the input stream after reading int, so
		using fgets will just read that from the input stream and return it.
		Could use getchar() to read excessive '\n' after scanf, 
		but this wont take into account possible extra chars */

		char buffer[50]={0};  			// initialize buffer for fgets/sscanf
		printf("Please enter integer between %d and %d:", min, max);
		fgets(buffer, sizeof(buffer), stdin); 	// read user input into buffer
		sscanf(buffer, "%d", &input);			// parse integer from buffer
		
		if (input < min || input > max)
			puts("Invalid Input.");
		else
			done = 1;
	}
	return input;
}

// Prompts user for hour, minute, and description
// Input: pointer to event to be populated with user values
// Output: pointer to same event
Event* inputEvent(Event *newEvent)
{
	if (newEvent != NULL) // check if pointer valid
	{
		puts("Enter event time:");
		newEvent->hour = inputRange(0, 23);
		newEvent->minute = inputRange(0, 59);
		puts("Enter description of event:");
		fgets(newEvent->description, DSLEN, stdin);
	}
	return newEvent;
}

// Writes event to specified location in list
// Input: event list, a populated event, and an index position
// Output: same index position, -1 if failure
int addEventAtIndex(Event list[], Event *e, int i)
{
	if (i < 0 || i >= MAX)	// function exits as failure if index doesn't exit
		return -1;

	list[i].hour = e->hour;
	list[i].minute = e->minute;
	strcpy(list[i].description, e->description);

	return i; 
}

// Sorts event list by ascending time (0:00 -> 23:99) using insertion sort.
// Input: event list
// Output: index position of last event to be inserted in list
int insertionSortEvent(Event list[], int size)
{
	if (size < 2)
		return 0;

	size_t i, j; 
	int timef[size];

	// Combine hours and minutes in one int array for easier sorting (format: HHMM)
	for (i = 0; i < size; i++)
		timef[i] =  (list[i].hour * 100) + list[i].minute;

	int temp_timef;
	Event temp_record;

	for (i = 1; i <= size - 1; i++) // Pass over each element
	{
		j = i;
		// if time is less than previous, switch
		while (timef[j] < timef[j-1] && j > 0) 
		{
			temp_timef = timef[j];
			timef[j] = timef[j-1];
			timef[j-1] = temp_timef;
			
			temp_record = list[j];
			list[j] = list[j-1];
			list[j-1] = temp_record;
			
			// repeat to beginning of list/ smaller time
			j--;
		}
	}
	return (int) j;
}

// Formatted display of event (hh:mm description)
// Input: an event
// Output: void
void displayEvent(Event e)
{
	if (&e == NULL)
		puts ("No record to display");
	else
		printf("%02d:%02d %s", e.hour, e.minute, e.description);
}

// Displays list of events
// Input: event list and it's size
// Output: void
void displayEventList(Event list[], int size)
{
	if (size < 1)
		puts ("No records to display");
	else
	{
		size_t record;
		for (record = 0; record < size; record++)
		{
			printf("[%d] ", (int) record);
			displayEvent(list[record]);
		}	
	}
}

// Deletes event at given index, updates size of list
// Input: event list, index position, pointer to size of list
// Output: index position, or -1 if failure 
int deleteEvent(Event list[], int i, int *p_size)
{
	if (*p_size < 1)
	{
		puts("No records to delete.");
		return -1;
	}
	else if (i < 0 || i > MAX)
	{
		puts("Index does not exist");
		return -1;
	}
	else
	{
		int j;
		for (j = i; j < *p_size; j++)	// from given index to end of list
		{
			list[j] = list[j+1];			// copy next record to current
		}
		(*p_size)--;	// decrement list size
	}
	return i;	// returns index deleted
}

// Saves event list to a text file, specified by user.
// Input: file name string, event list, size of event list
// Output: number of records saved, or -1 if failure
int saveEventList(char *filename, Event list[], int size)
{ 
	FILE* ptr_file;
	ptr_file = fopen(filename, "w"); // creates specified file name for writing
	size_t i = 0;
	for(i = 0; i < size; i++)
	{
		char string[DSLEN+10]; // buffer for time and description
		sprintf(string, "%d %d %s", list[i].hour, list[i].minute, list[i].description);
		fprintf(ptr_file, "%s", encode(string));
	}
	fclose(ptr_file);

	return (int) i;
}

// Loads event list from a text file, overwriting previous and updating size
// Input: file name string, event list, size of event list
// Output: number of records retrieved, or -1 if failur
int loadEventList(char *filename, Event list[], int *p_size)
{
	FILE* ptr_file;
	ptr_file = fopen(filename, "r"); // creates specified file name for writing
	size_t i = 0;
	while (!feof(ptr_file))
	{
		char string[DSLEN+10]; // buffer for time and description
		fgets(string, DSLEN+10, ptr_file);
		sscanf(decode(string), "%d %d %[^\n]", &list[i].hour, &list[i].minute, list[i].description);
		strcat(list[i].description, "\n");
		i++;
	}
	i--; //cleanup
	fclose(ptr_file);
	*p_size = (int) i;
	return (int) i;
}

// Replaces spaces with underscores in a given string, for saving
// Input: string
// Output: pointer to same string
char* encode(char *s)
{
	char *ptr_s = s;
	while (*ptr_s != '\0')
	{
		if (*ptr_s == ' ')
		{
			*ptr_s = '_';
		}
		ptr_s++;
	}
	return s;
}

// Replaces underscore with spaces in a given string, for loading
// Input: string
// Output: pointer to same string
char* decode(char *s)
{
	char *ptr_s = s;
	while (*ptr_s != '\0')
	{
		if (*ptr_s == '_')
		{
			*ptr_s = ' ';
		}
		ptr_s++;
	}
	return s;
}