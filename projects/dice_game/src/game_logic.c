#include "dice_game.h"
#include <stdlib.h>

/* Function to take user bet */
int what_is_user_bet(int current_balance, FILE *stream, void (*handler)())
{
    
    int bet;
    int status;
    
    while (1)
    {
        printf("\nCurrent balance: %d\nYour bet... $", current_balance);
        F_OUT(); // Using our alias

        status = fscanf(stream, "%d", &bet);

        if (status == 1) {
            if (bet > 0 && bet <= current_balance) return bet;
            printf("\nError: Invalid bet amount.\n");
        } else {
            printf("\nError: Numeric value required.\n");
            handler();
        }
    }
}

/* Gets user guess and passes it on */
int what_is_user_guess(int guess, FILE *stream, void (*handler)())
{
    int status;

    while (1)
    {
        printf("\nGuess (1-6, 0 to quit): ");
        F_OUT();

        status = fscanf(stream, "%d", &guess);

        if (status == 1) {
            if (guess == 0) return 0; 
            
            if (guess >= 1 && guess <= 6) return guess;
            printf("\nInvalid range.\n");
        } else {
            printf("\nError: Not a number.\n");
            handler();
        }
    }
}

/* Clear the file and buffer */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
