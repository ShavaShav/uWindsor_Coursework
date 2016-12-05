#include <stdio.h>
#include <string.h>

// Function declarations
int Sum(int n);			// Summation
int Fact(int n);		// Factorial
int Fibb(int n);		// Fibbonacci
int GCD(int n, int m);		// Greatest Common Denominator
int Power(int n, int m);	// Power of

// Control function
// Prints menu, and reads in numbers to be used by modules, prints results.
int main()
{	
	int n; 			// First digit
	int m;			// Second digit
	int option;		// Menu option
	char line[100]; //Line of asterisks to help divide up the program visually
	char menu[150];	// Menu string for multiple use
	strcpy(line, "\n******************************************\n");
	strcpy(menu, "CALCULATOR - Lab 1 for 60-141\n\n1 - Summation\n2 - Factorial\n3 - Fibonacci\n4 - Greatest Common Denominator\n5 - Power\n0 - Exit\n\n Please choose option: ");
	printf("%s%s", line, menu); 
	scanf("%d", &option);
	printf("%s", line);
	// Based on option, switch to appropriate function. Exit when user inputs 0
	while (option != 0)
	{
		switch (option)
		{
			case 1:	printf("SUMMATION\n\nPlease enter number for summation: ");
				scanf("%d", &n);
				printf("\nThe summation of %d is %d\n", n, Sum(n));
				break;
			case 2: printf("FACTORIAL\n\nPlease enter number for it's factorial: ");
				scanf("%d", &n);
				printf("\nThe factorial of %d is %d\n", n, Fact(n));
				break;
			case 3: printf("FIBONACCI\n\nPlease enter index number to find it's fibonacci number: ");
				scanf("%d", &n);
				printf("\nThe fibonacci number for position %d is %d\n", n, Fibb(n));
				break;
			case 4: printf("GREATEST COMMON DENOMINATOR\n\nPlease enter 2 numbers to find their greatest common denominator: ");
				scanf("%d %d", &n, &m);
				printf("\nThe greatest common denominator between %d and %d is %d\n", n, m, GCD(n, m));
				break;
			case 5: printf("POWER\n\n Please enter a base number: ");
				scanf("%d", &n);
				printf("Please enter an exponent number for %d: ", n);
				scanf("%d", &m);
				printf("\n%d to the power of %d is %d\n", n, m, Power(n, m));
				break;
			// For catching inputs != 0-5
			default:printf("Invalid Input");
				break;
		}
		// Reprint menu after chosen module is finished.
		printf("%s%s", line, menu);
		scanf("%d", &option);
		printf("%s", line);
	}
return 0;
}


// Takes number, returns sum of all numbers from 1 to n
// "sum" accumulates "x" as "x" increments by 1 to "n"
int Sum(int n)
{
	if (n == 1)
		return 1;
	else
		return n + Sum(n-1);
}

// Factorial returns product of all numbers from 1 to n
// Takes input n.
// For ex: n=5 -> returns 5 * 4 * 3 * 2 * 1
int Fact(int n)
{
	if (n == 1)
		return 1;
	else
		return n * Fact(n-1);
}

// Returns fibbonacci number from it's position (n), inputed by user
// Recursion adds previous two digits, all the way down to the base,
// creating a sort of parse.
int Fibb(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return Fibb(n-1) + Fibb(n-2);                                                                     
}

//Takes integer inputs n and m, returns the largest positive integer that divides the numbers without a remainder
int GCD(int n, int m)
{
		// If Dividend (m) % Divisor (n) = 0 then recursion ends
		if (n == 0)
			return m; 
		// new Dividend, Dividend (m) is replaced with old divisor (n).
		else 
			GCD(m % n, n);
}

// Takes integer inputs n and m, returns n to the power of m.
// If base is 0, then skip loop and return n=0.
// If exponent is 0, then skip internal loop and return pow=1
// Otherwise, loop multiplies n * n, m many times to create the power. 
int Power(int n, int m)
{
	if (n == 0)
		return 0;
	else if (m == 0)
		return 1;
	else
	{
		return n * Power(n, m-1);	
	}
}
