/* if.c */
#include <stdio.h>

int main()
{
    // int x;

    // x = 5;
    
    // // Only happens if the condition is met
    // // In this case, x must equal 5
    // if (x == 5)
    // {
    //     printf("It is %d\n", x);
    // }

    int velocity;
    printf("How fast are you in km/h?\n");
    scanf("%d", &velocity);

    if (velocity > 100)
    {
        printf("You are driving too fast!\n");
    }
    
    else if (velocity > 80)
    {
        printf("You are driving safely\n");
    }
    // Catch all statement if previous conditions
    // are not met
    else
    {
        printf("Ok\n");
    }

    printf("\n\nYou've reached the end of the line\n\n");

    return 0;
}
