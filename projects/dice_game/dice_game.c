/* dice_game.c */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 
 Function to take user bet
 */
int what_is_user_bet(int current_balance, FILE *stream, void (*handler)())
{

    int bet;
    int status;

    while (1)
    {
        printf("\nYou're current balance: %d\n", current_balance);
        printf("\nYour bet... $");
        fflush(stdout);

        status = fscanf(stream, "\n%d", &bet);

        if (status == 1)
        {
            if (bet <= 0)
            {
                printf("\nError: You must bet at least $1.\n");
            }
            else if (bet > current_balance)
            {
                printf("\nError: Insufficient funds! You only have %d.\n", current_balance);
            }
            else
            {
                printf("\nBet confirmed: %d\n", bet);
                return bet;
            }
        }
        else
        {
            printf("\nError: Please enter a numeric value.\n");
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
        printf("\nGuess number between 1-6, zero for Quitters: ");
        fflush(stdout);

        status = fscanf(stream, "\n%d", &guess);

        if (status == 1) // Success! We got an integer
        {
            if (guess == 0)
            {    
                printf("\nQuitting game...\n");
                exit(0);
            }
            if (guess >= 1 && guess <= 6)
            {
                return guess; // Valid range
            }
            printf("\nInvalid range, try staying between 1 and 6.\n");
        }
        else
        {
            printf("\nError: That wasn't a number. Try again.\n");
            handler();
        }
    }
}

/* Clear the file and buffer */
void clear_input_buffer()
{
    int c;
    // Keep reading characters until we hit a newline or End Of File
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    int balance;
    bool is_game_on;
    
    // Standard I/O streams are just pointers, so we pass 'stdin' here    
    FILE *input_source = stdin;

    balance = 1000;
    is_game_on = true;

    while(is_game_on)
    {
        int guess;
        int current_bet;
        
        current_bet = what_is_user_bet(balance, input_source, clear_input_buffer);
        guess = what_is_user_guess(guess, input_source, clear_input_buffer);

        printf("\nWhat is guess: %d\n", guess);

        printf("\nCurrent bet: %d\n", current_bet);

        is_game_on = false;
    }

    return 0;
}
