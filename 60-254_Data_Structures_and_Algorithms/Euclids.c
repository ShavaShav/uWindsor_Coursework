#include <stdio.h>

int EuclidIterative(int m, int n);
int EuclidRecursive(int m, int n);
int EuclidTreatise(int m, int n);

int main ()
{
    while (1)
    {
        int m, n;
        printf("***************\nEnter 2 numbers: ");
        scanf("%d %d", &m , &n);
        printf("You entered %d and %d\n\n", m, n);

        puts("They're GCD is:");
        printf("Recursive: %d\n", EuclidRecursive(m, n));
        printf("Iterative: %d\n", EuclidIterative(m, n));
        printf("Treatise: %d\n", EuclidTreatise(m, n));
    }
    return 0;
}

int EuclidIterative(int m, int n)
{
    int r = 1; // intialise remainder to NOT 0

    while (r != 0)
    {
        r = m%n;
        m = n;
        n = r;
    }
    return m;
}

int EuclidRecursive(int m, int n)
{
    if (n == 0)
        return m;
    else
        EuclidRecursive(n, m%n);
}

// Performs algorithim as Euclid presented in treatise, using only subtraction
int EuclidTreatise(int m, int n)
{
	int r = 1;

	while (r != 0)
	{
		r = m;				// perform modulas by subtraction.
		while (r-n >= 0)	// subtract m from n until result is between n and 0.
			r = r-n;
		
		m = n;				
		n = r;
	}
	return m;
}
