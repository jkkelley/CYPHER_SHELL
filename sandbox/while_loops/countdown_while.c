/* countdown_while.c */
#include <stdio.h>

int main()
{
    int x;
    
    x = 10;

    while(x > -1)
    {
        if (x == 0)
        {    
            printf("%d\n", x);
            break;
        }
        else
        {
            printf("%d\n", x);
            x--;
        }
    }
    
    printf("BOOM\n");

    return 0;
}    
