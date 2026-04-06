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

        // Check the comparsion of numbers
        // If they don't match, sub from the balance
        while (1)
        {
            if (guess != dice_roll && balance >= 0)
            {
                printf("\nSorry you lost\n");
                // Subtract the bet from the balance
                balance -= current_bet;
                if (balance <= 0)
                {
                    printf("\nGame is over, balance went to $%d\n", balance);
                    return 0; // Exit here if balance is 0 or less
                }
                break;
            }
            // If they DO match, multiply bet by three
            // & add to the balance
            else if (guess == dice_roll)
            {
                int user_winnings_before_balance = (current_bet * 3);
                int user_winnings = (current_bet * 3) + balance;
                printf("\nYou won $%d!\n", user_winnings_before_balance);
                balance = user_winnings;
                break;
            }
        }
    }
    return 0;
}
