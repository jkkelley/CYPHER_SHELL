/* recursion.c */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int BOX_COUNTER = 0;

// --- THE BLUEPRINTS ---
typedef enum { BOX, KEY } ItemType;

typedef struct Box {
	ItemType type;
	struct Box* contents[5]; // Each box can hold 5 things
	int itemCount;				
} Box;

// Helper to check if something is a box
bool is_a_box(Box* b) { return b->type == BOX; }
bool is_a_key(Box* b) { return b->type == KEY; }

// --- LOOKING FOR THAT KEY
void look_for_key(Box* main_box)
{
	Box* pile[100]; // Our manual "pile"
	int top = -1;

	pile[++top] = main_box; // Put the first box in
	
	while (top >= 0)
	{
		Box* current = pile[top--]; // Grab a box
		// printf("Checking a box...\n");

		for (int i = 0; i < current->itemCount; i++)
		{
			Box* item = current->contents[i];

			if (is_a_box(item))
			{
				// printf("  -> Found another box! Adding to the pile.\n");
				pile[++top] = item;
			}
			else
			{
				printf("FOUND THE KEY!\n");
				return;
			}
		}
	}
}

Box* create_random_nest(int depth)
{
	// 1. Allocate memory for a new box
	Box* new_box = malloc(sizeof(Box));
	if (new_box == NULL) return NULL;

	BOX_COUNTER++;

	if(depth <= 0)
	{
		// We reach the bottom! Put the key here.
		new_box->type = KEY;
		new_box->itemCount = 0;
		printf("\t(System: Key hidden at the bottom)\n\n");
	}
	else
	{
		// Still going! Make this a box and put another box inside it.
		new_box->type = BOX;
		new_box->itemCount = 1;

		// This is the "magic" line: a box contains a box contains a box...
		new_box->contents[0] = create_random_nest(depth - 1);
	}

	return new_box;
}

void free_everything(Box* current_box)
{
	if (current_box == NULL) return;

	// 1. If it's a box, we must free what's INSIDE it first
	if (current_box->type == BOX)
	{
		for (int i = 0; i < current_box->itemCount; i++)
		{
			free_everything(current_box->contents[i]);
		}
	}

	// 2. Once the inside is clear, free the current container
	// TODO: PUT BACK ON -->> printf("Freeing a %s...\n", current_box->type == BOX ? "Box" : "Key");
	BOX_COUNTER--;
	free(current_box);
}

// ################################
// ###  --- RECURSION BELOW --- ###
//#################################
int get_the_key(Box* current_box)
{
	// 1. Safety check (The "Base Case")
	if (current_box == NULL) return 0;

//	printf("Checking a box...\n");

	// 2. The Loop: Look at each item in the current box
	for (int i = 0; i < current_box->itemCount; i++)
	{
		Box* item = current_box->contents[i];

		if (is_a_key(item))
		{
			printf("\tFOUND THE KEY!\n");
			return 1; // We found it! This "unwinds" the search
		}
		else
		{
//			printf("  -> Found another box! Going deeper...\n");
			if (get_the_key(item) == 1)
			{
				return 1;
			}
		}
	}
	return 0; // Looked at everything in this box and found nothing
}


// --- THE SETUP (The "Game" starts here) ---
int main()
{	
	// Seed the random number generator so it's different every time
	srand(time(NULL));

	// Random depth between 1 and 10
	int random_depth = (rand() % 50000) + 1;
	printf("\n\n\tBuilding a mystery box with %d layers...\n", random_depth);

	// Generate the nested boxes
	Box* start_box = create_random_nest(random_depth);

	printf("\tStarting search...\n");
	// look_for_key(start_box);
	// NEW FUNCTIONALITY BELOW
	get_the_key(start_box);

	printf("\n\tCleaning up memory...\n");
	// free_everything(start_box);
	// FREE WILLY HERE PLEASE
	free_everything(start_box);

	printf("\n\tFINAL CHECK: %d boxes remaining in memory.\n", BOX_COUNTER);

	if (BOX_COUNTER == 0)
	{
		printf("\tClean exit! No leaks detected.\n\n");
	}
	else
	{
		printf("\n\tWARNING: Memory leak detected! %d boxes left behind.\n\n", BOX_COUNTER);
	}

	return 0;
}
