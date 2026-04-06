/* dice_game.c */
#include "dice_game.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main()
{ 
    // Seed random number generator once at program start
    srand(time(NULL));
    
    int balance = 1000;
    bool is_game_on = true;

    while(is_game_on)
    {
        int current_bet = what_is_user_bet(balance, stdin, clear_input_buffer);
        int guess = what_is_user_guess(0, stdin, clear_input_buffer);
        
        if (guess == 0)
        {
            printf("Thanks for playing!\n");
            return 0; // Exit here 
        }

        printf("\nGuess: %d | Bet: %d\n", guess, current_bet);
        
        sleep(2);

        int dice_roll = return_guess_one_to_six();

        printf("\ndice roll: %d\n", dice_roll);

        is_game_on = false;
    }
    return 0;
}
