#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define UNIVERSAL_SET_SIZE 10000	// number of integers in Universal set to be hashed

// Function prototypes
int findNextPrime(int n);
float BuildHashTable_Linear(int hashTable[], int hashTableSize);
float BuildHashTable_Quadratic(int hashTable[], int hashTableSize);

int main(int argc, char* argv[])
{
	float loadFactor = 1;	// load factor of hashtable, to be input be user (illegal preset)
	int hashTableSize;	// size of hash table, to be determined by size of set and load factor
    int probingScheme = 0;  // 1 for linear, 2 for quadratic (illegal preset)

	// check if load factor input from command line
	if (argv[1] != NULL)
	{
		float loadInput;
		sscanf(argv[1], "%f", &loadInput);	// parse integer from first input arg
		loadFactor = loadInput;
		printf("Load factor of %.1f entered.\n", loadFactor);
		if (argv[2] != NULL)
        {
            int probeInput;
            sscanf(argv[2], "%d", &probeInput);
            probingScheme = probeInput;
            printf("Probing scheme #%d entered.\n", probingScheme);
        }
	}

	// get load factor from user until legal entry
	while (loadFactor >= 1 || loadFactor <= 0)
	{
		printf("Enter load factor (0 < a < 1) for the hash table: ");
		scanf("%f", &loadFactor);
	}

	// Hash Table size will be next prime greater than the Universal Set Size / load Factor
	hashTableSize = findNextPrime((int)(UNIVERSAL_SET_SIZE/loadFactor));
	printf("\nSize of hash table will be %d (Universal set size: %d)\n", hashTableSize, UNIVERSAL_SET_SIZE);

	// theoretical number of linear probes in a successful search of hashtable
	float expectedNumberOfProbes = (1 + (1 / (1 - loadFactor))) / 2;
	printf("Expected number of linear probes = %0.1f\n\n", expectedNumberOfProbes);

    // get probing scheme from user until legal entry
	while (probingScheme < 1 || probingScheme > 2)
	{
		printf("Enter probing scheme (1 - Linear, 2 - Quadratic): ");
		scanf("%d", &probingScheme);
	}

	int hashTable[hashTableSize]; // hash table

    switch (probingScheme)
    {   // Linear probing scheme
        case 1: puts("\nBuilding hash table with linear probing scheme...");
                float linearProbes = BuildHashTable_Linear(hashTable, hashTableSize);
                printf("Took %.1f linear probes on average.\n", linearProbes);
                break;
        // Quadratic probing scheme
        case 2: puts("\nBuilding hash table with quadratic probing scheme...");
                float quadraticProbes = BuildHashTable_Quadratic(hashTable, hashTableSize);
                printf("Took %.1f quadratic probes on average.\n", quadraticProbes);
                break;
        default: puts("Error.");
    }
	return 0;
}

// populate a hash table with random integers given array &
// size of hash table, and returns the average number of probes
float BuildHashTable_Quadratic(int hashTable[], int hashTableSize)
{
	srand(time(NULL));	//set random seed
	size_t i = 0;	// array counter
	// intiliaze hash table with empty (-1) values
	for (; i < hashTableSize; i++)	hashTable[i] = -1;

	float avgNumOfProbes = 0;	// total probes / set size
	int totalNumOfProbes = 0;

	// populate hashtable with random intergers
	for (i = 0; i < UNIVERSAL_SET_SIZE; i++)
	{
		int key = rand();	// set key to random integer
		int numOfProbes = 1;	// number of probes needed to place key
		// Hash function is key mod size
		int initialHashIndex = key % hashTableSize;
		int auxConstant = 0;	// to be used in quadratic hash function
		int hashIndex = initialHashIndex;
		// check if location is free (basic op)	or out of bounds
		while(hashTable[hashIndex] != -1)
		{
			numOfProbes++;	// increment number of probes
			auxConstant++;	// increment the auxillary constant
			// Quadratic Probing Scheme repeats hash function using altered hash function:
			// (initial hash index + the aux constant squared) mod table size
			hashIndex = (initialHashIndex + (auxConstant * auxConstant)) % hashTableSize;
		}
		// place key in hashed location
		hashTable[hashIndex] = key;
		// add number of probes to the total
		totalNumOfProbes += numOfProbes;
	}
	// return the average number of probes
	avgNumOfProbes = (float) (totalNumOfProbes) / UNIVERSAL_SET_SIZE;
	return avgNumOfProbes;
}

// populate a hash table with random integers given array &
// size of hash table, and returns the average number of probes
float BuildHashTable_Linear(int hashTable[], int hashTableSize)
{
	srand(time(NULL));	//set random seed
	size_t i = 0;	// array counter
	// intiliaze hash table with empty (-1) values
	for (; i < hashTableSize; i++)	hashTable[i] = -1;

	float avgNumOfProbes = 0;	// total probes / set size
	int totalNumOfProbes = 0;

	// populate hashtable with random intergers
	for (i = 0; i < UNIVERSAL_SET_SIZE; i++)
	{
		int numOfProbes = 1;	// number of probes needed to place key
		int key = rand();	// set key to random integer
		// Hash function is key mod size
		int hashIndex = key % hashTableSize;
		// check if location is free (basic op)
		while(hashTable[hashIndex] != -1)
		{
			numOfProbes++;	// increment number of probes
			// Linear Probing Scheme increments index until free spot found
			hashIndex++;
			// end of table case, "wrap around" index
			if (hashIndex > hashTableSize)
				hashIndex = 0;
		}
		// place key in hashed location
		hashTable[hashIndex] = key;
		// add number of probes to the total
		totalNumOfProbes += numOfProbes;
	}
	// return the average number of probes
	avgNumOfProbes = (float) (totalNumOfProbes) / UNIVERSAL_SET_SIZE;
	return avgNumOfProbes;
}

// returns the next prime after given n
int findNextPrime(int n)
{
	int nextPrime = -1;

	// if less than 2, next prime is 2. Increment to next n
	if (n < 2) nextPrime = 2;
	else
	{
		int checkPrime = 0;	// flag to be changed when prime found
		while (checkPrime == 0)	// loop until next prime found
		{
			/*
			 * only need to check trial divisions to the square root of n,
			 * since any division with rem. 0 after is just a repeat
			 */
			int div = 2;	// divide by 2 all the way to sqrt of n
			for (; div <= sqrt(n); div++)
			{
				if (n % div == 0)	// if divisible
				{
					checkPrime = 0;	// set flag to false (Not Prime)
					break;				// stop checking
				}
				else checkPrime = 1;	// set flag to true (Possible prime so far)
			}
			// end divisible checking loop, checkPrime flag now has final result

			if (checkPrime == 1)	// check flag, if true then n is Prime
				nextPrime = n;
			else n++;				// else repeat on next number
		}
	}
	return nextPrime;	// return the result
}
