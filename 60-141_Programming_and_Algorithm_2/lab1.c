#include <stdio.h>
#include <string.h>

// Function declarations
int Sum(int n);			// Summation
int Fact(int n);		// Factorial
int Fibb(int n);		// Fibbonacci
int GCD(int n, int m);		// Greatest Common Denominator
int Power(int n, int m);	// Power of

// Global variables
int x;						// For loop counter

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
	int sum = 0;
	for (x = 1; x <= n; x++)
	{
		sum += x;
	}
	return sum;
}

// Factorial returns product of all numbers from 1 to n
// Takes input n. "fact" starts at 1, and is multiplied by n, as n is decremented to 1.
// For ex: n=5 -> fact = 1 * 5 * 4 * 3 * 2 * 1
int Fact(int n)
{
	int fact = 1;
	for (x = n; x > 0; x--)
	{
		fact = fact * x;
	}
	return fact;
}

// Returns fibbonacci number from it's position (n), inputed by user
// If n=1, then x=n so loop skipped and a=0 is returned (first fibonacci).
// For each iteration from 1 to n, "c" adds the two digits, and "a" is replaced 
// with "b", and "b" is replaced with "c", creating the fibonacci sequence.  
int Fibb(int n)
{
	int a = 0;
	int b = 1;
	int c = 0;
	for (x = 1; x < n; x++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return a;
}

//Takes integer inputs n and m, returns the largest positive integer that divides the numbers without a remainder
int GCD(int n, int m)
{
	x = 0;
	while ( n != 0 ) 
	{
		// Divisor is stored temporarily in (x)
		x = n; 
		// If Dividend (m) % Divisor (n) != 0, then the remainder becomes the new divisor for next iteration.
		// If Dividend (m) % Divisor (n) = 0 then loop ends after iteration.  
		n = m % n;  
		// Dividend (m) is replaced with old divisor (x).
		m = x;
  	}
  	// Return divisor once remainder is 0
 	return m; 
}

// Takes integer inputs n and m, returns n to the power of m.
// If base is 0, then skip loop and return n=0.
// If exponent is 0, then skip internal loop and return pow=1
// Otherwise, loop multiplies n * n, m many times to create the power. 
int Power(int n, int m)
{
	if (n > 0 & m >= 0)
	{
		int pow = 1;
		for (x = 0; x < m; x++)
		{
			pow = pow * n;		
		}
	return pow;	
	}
	else
	{
	return n;	
	}
}
