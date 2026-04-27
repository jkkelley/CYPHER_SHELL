/* binary_search.c */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define SIZE 1000000000  // This creates a constant

int binary_search(int list[], int size, int item)
{
	int low, mid, high, steps;
	
	steps = 1;
	low = 0;
	high = size - 1;
	
	while (low <= high)
	{
		// Add low and high, then
		// divide by 2 to get your mid point
		mid = (low + high) / 2;
		long guess = list[mid];

		printf("\nguess: %'ld\n", guess);

		// Found item
		if (guess == item)
		{
			printf("Found mid: %'d\n", mid);
			printf("Step %'d\n", steps);
			return mid;
		}
		else if (guess > item)
		{
			high = mid - 1;
			printf("high: %'d\n", high);
			printf("Step %'d\n", steps);
			steps++;
		}
		else
		{
			low = mid + 1;
			printf("low: %'d\n", low);
			printf("Step %'d\n", steps);
			steps++;
		}
	}

	return -1;
}


int main()
{
	// Sets to your system's default formatting
	setlocale(LC_NUMERIC, "en_US.utf8");
	int *my_list;
	clock_t start, end;
	double cpu_time_used;
	
	my_list = malloc(SIZE * sizeof(int)); // Asks the computer for 4MB of Heap space
	
	if (my_list == NULL)
	{
		printf("Memory allocation failed!");
		return 1; 
	}
	
	start = clock(); // Start the "stopwatch"

	// Fill the array with sorted numbers
	for (int i = 0; i < SIZE; i++)
	{
		my_list[i] = i;
	}
	
	int target = 700000; // The number we've choosen
	
	int result = binary_search(my_list, SIZE, target);
	
	if (result != -1)
	{
		printf("\nItem found at index: %'d\n", result);
	}
	else
	{
		printf("\nItem not found.\n");
	}
	
	end = clock();   // Stop the "stopwatch"

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Search took %f seconds\n", cpu_time_used);

	// Give back what you take
	free(my_list);
	return 0;
}
