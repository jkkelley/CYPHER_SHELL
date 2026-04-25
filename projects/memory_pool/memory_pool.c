/* memory_pool.c */
#include <stdio.h>
#include <stdlib.h>

// Define memory allocation
// Size of block
// Pointer to the next node
typedef struct FreeBlock {
    size_t size;
    struct FreeBlock *next;
} FreeBlock;

// Gives exact byte sizing
// Clean casting to other types
unsigned char memory_pool[1024];
FreeBlock *free_list;

void pool_init()
{
    // Point the free list to the start of our memory pool
    // This treats the raw bytes as a FreeBlock node
    free_list = (FreeBlock *)memory_pool;
    
    // The whole pool is free at the start
    // Subtract the size of the header since it lives inside the pool
    free_list->size = 1024 - sizeof(FreeBlock);

    // No other free blocks exist yet
    free_list->next = NULL;
}

void *pool_alloc(size_t size)
{
    // Start traversal at the beginning of the free list
    FreeBlock *current = free_list;

    // Walk the free list looking for a block large enough
    while(current != NULL)
    {
        // Checking to see if we have any free space
        // against whats held in FreeBlock currently
        if (current->size >= size + sizeof(FreeBlock))
        {
            // Start at current
            // + jump over current's header
            // + jump over the user's requested data
            // = land exactly here, this is where new_block will live
            FreeBlock *new_block = (FreeBlock *)((unsigned char *)current + sizeof(FreeBlock) + size);

            // We have the total free space available, then
            // We minus the 'size' the user is asking for, then
            // Minus the space the new header needs
            // This sets the new_block size
            new_block->size = current->size - size - sizeof(FreeBlock);

            // Link new_block into the free list, inheriting current's next pointer
            new_block->next = current->next;

            // Update free list to start at new_block, since current is now allocated
            free_list = new_block;

            // Set the size of the block
            current->size = size;

            // Return the next usable block
            return (void *)(current + 1);
        }

        // Move pointer to next 'node'
        current = current->next;
    }

    // We've error'ed out of nothing to return
    return NULL;
}

void pool_free(void *ptr)
{
    if (ptr == NULL) 
    {
        // We want to know whats going on before exit
        fprintf(stderr, "pool_free: cannot free NULL pointer\n");
        return; // exit if they pass us a NULL pointer
    }

    // Need to get the previous header
    FreeBlock *block = (FreeBlock *)ptr - 1;

    // Prepend block back to the front of the free list
    block->next =  free_list;
    free_list = block;
}

void pool_stats()
{
    size_t total;
    size_t largest;
    int count;
    int frag;

    total = 0;
    largest = 0;
    count = 0;

    FreeBlock *current = free_list;

    while (current != NULL)
    {
        total += current->size;

        if (current->size > largest)
        {
            largest = current->size;
        }
        count ++;

        current = current->next;
    }

    frag = total > 0 ? (int)(100 * (total - largest) / total) : 0;

    printf("Total free: %zu bytes\nLargest block: %zu bytes\nFree blocks: %d\nFragmentation: %d%%\n", 
        total, largest, count, frag);
}

int main()
{   
    // // Setting the stage
    // pool_init();

    // // Looking at our stats
    // pool_stats();

    // // Creating a pointer with 100 bytes
    // void *a = pool_alloc(100);

    // // Looking at the stats again
    // pool_stats();

    // // Free our pointer up
    // pool_free(a);

    // // Looking at the stats one final time
    // pool_stats();        

    pool_init();
    printf("=== INITIAL STATE ===\n");
    pool_stats();

    void *a = pool_alloc(496);
    printf("=== AFTER alloc(496) ===\n");
    pool_stats();

    void *b = pool_alloc(50);
    (void)b;  // suppress unused warning
    printf("=== AFTER alloc(50) ===\n");
    pool_stats();

    void *c = pool_alloc(50);
    (void)c;  // suppress unused warning
    printf("=== AFTER alloc(50) ===\n");
    pool_stats();

    pool_free(a);
    printf("=== AFTER free(496) ===\n");
    pool_stats();

    void *d = pool_alloc(312);
    printf("=== AFTER alloc(312) ===\n");
    pool_stats();

    void *e = pool_alloc(25);
    (void)e;  // suppress unused warning
    printf("=== AFTER alloc(25) ===\n");
    pool_stats();

    pool_free(d);
    printf("=== AFTER free(312) ===\n");
    pool_stats();


    // We're outta of here
    return 0;
}