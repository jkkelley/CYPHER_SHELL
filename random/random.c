/* random.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Function for randomness*/
int our_random_function(int max)
{  
    int x;
    
    x = rand() % max + 1;

    return x;
}

int main()
{
    int random;

    srand(getpid());
    random = our_random_function(10);
    printf("%d", random);

    return 0;
}