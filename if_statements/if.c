/* if.c */
#include <stdio.h>

int main()
{
    int x;

    x = 5;
    
    // Only happens if the condition is met
    // In this case, x must equal 5
    if (x == 5)
    {
        printf("It is %d\n", x);
    }

    return 0;
}
