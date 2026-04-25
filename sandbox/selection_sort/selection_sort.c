/* selection_sort.c */
#include <stdio.h>

int find_smallest (int arr[], int size)
{
	int smallest, smallest_index;

	smallest = arr[0];
	smallest_index = 0;

	for (int i = 0; i < size; i++)
	{
		printf("smallest: %d\n", smallest);
		printf("smallest_index: %d\n", smallest_index);
		printf("position in array: %d\n", i+1);
		printf("current index value: %d\n\n", arr[i]);

		if (arr[i] < smallest)
		{
			smallest = arr[i];
			smallest_index = i;
		}
	}

	printf("\nThe smallest integer: %d\n", smallest);

	return smallest_index;
}

void selection_sort(int arr[], int size)
{
	int min_index, temp;

	for (int i = 0; i < size - 1; i++)
	{
		// 1. Find the min ele in the remaining unsorted array
		min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		// 2. Swap the found min ele w/ the first ele
		// This is the C ver of "pop and append"
		temp = arr[min_index];
		arr[min_index] = arr[i];
		arr[i] = temp;
	}

}

int main()
{
	int array_size;

	int my_unsorted_list[] = {10, 15, 25, 99, 5, 64, 79, 23, 3, 4, 100};
	
	// sizeof(my_unsorted_list): Returns the total memory (e.g. 9 integers x 4 bytes = 36)
	// sizeof(my_unsorted_list[0]): Returns the size of one integer (4 bytes)
	// 36/4 = 9
	array_size = sizeof(my_unsorted_list) / sizeof(my_unsorted_list[0]); 

	int find_smallest_result = find_smallest(my_unsorted_list, array_size);

	printf("What spot the value is positioned at: %d\n\n", find_smallest_result+1);

	// Gives back sorted array
	selection_sort(my_unsorted_list, array_size);
	
	printf("Sorted array: \n");
	for (int i = 0; i < array_size; i++)
	{
		printf("%d ", my_unsorted_list[i]);
		if (i < array_size - 1)
		{
			printf(" "); // Only print space if it's NOT the last ele
		}
	}
	printf("\n");

	return 0;
}
