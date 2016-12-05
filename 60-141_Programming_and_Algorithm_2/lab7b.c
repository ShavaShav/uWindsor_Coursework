#include <stdio.h>
#include <ctype.h>

// Structure definition - employee record
struct employee
{
	int id;
	char firstname[40];
	char lastname[40];
	float wage;
};

typedef struct employee Employee;

//Function prototypes
int ReadRecords(Employee *emplist);
void WordCap(char *name);
int SaveEmpList(const Employee *emplist, const char *filename);

int main()
{
	Employee emplist[3];

	printf("%d records read.\n", ReadRecords(emplist));

	for (size_t i = 0; i < 3; i++)
	{
		WordCap(emplist[i].firstname);
		WordCap(emplist[i].lastname);
	}

	if(SaveEmpList(emplist, "employee.dat") == 0)
		printf("File saved to \"%s\".", "employee.dat");
	else
		puts("Error saving file.");
	return 0;
}

/*
OBJECTIVE: Read employee records into array
INPUT: Employee array, and it's size
OUTPUT: Number of records read
ASUMPTIONS: There exists a file employee.dat
*/
int ReadRecords(Employee *emplist)
{
	FILE *ptr_file;
	ptr_file = fopen("employee.dat", "r");
	char buffer[100];
	size_t i;
	for (i = 0; i < 3; i++)
	{
		fgets(buffer, 80, ptr_file); // read line into buffer
		// Using sscanf with strings, and comma as delimiter, must use [^,] to tokenize
		sscanf(buffer, "%d,%[^,],%[^,],%f", &emplist[i].id, emplist[i].firstname, emplist[i].lastname, &emplist[i].wage);		
	}
	fclose(ptr_file);
	return (int) (i);
}

/*
OBJECTIVE: Capitalize the first letter in a string
INPUT: String
Output: void
Assumptions: string contains alpha
*/
void WordCap(char *name)
{
	name[0] = toupper(name[0]);
}

/*
  OBJECTIVES: Save employee records to file
  INPUT: employee records (Employee array) and a file name (string)
  OUTPUT: 0 if saved properly
  ASSUMPTIONS: number of records is stored globally
*/
int SaveEmpList(const Employee *emplist, const char *filename)
{
	FILE *ptr_file;
	ptr_file = fopen(filename, "w");
	for (size_t i = 0; i < 3; i++)
		fprintf(ptr_file, "%d %s %s %0.2f\n", emplist[i].id, emplist[i].firstname, emplist[i].lastname, emplist[i].wage);
	return fclose(ptr_file);
}