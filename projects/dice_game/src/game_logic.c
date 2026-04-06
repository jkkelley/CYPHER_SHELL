#include "dice_game.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

/* Generate random number between 1-6 */
int generate_guess_one_to_six(int max)
{
    int generated_number;

    generated_number = rand() % max + 1;

    return generated_number;
}

/* Return guess between 1-6 */
int return_guess_one_to_six()
{
    int random_number;
    
    // Returns number 1-6
    random_number = generate_guess_one_to_six(6);
 
    printf("\nrandom number: %d\n", random_number);    

    // Return the randomized number back to the game
    return random_number;
}

/* Calculate new balance after a loss */
int calculate_loss(int balance, int bet)
{
    return balance - bet;
}

/* Calculate new balance after a win (bet * 3 + balance) */
int calculate_winnings(int balance, int bet)
{
    return (bet * 3) + balance;
}

/* Check game result and update balance
 * Returns: 1 if won, 0 if lost, -1 if game over
 * Updates new_balance via pointer
 */
int check_game_result(int guess, int dice_roll, int balance, int bet, int *new_balance)
{
    // Win condition
    if (guess == dice_roll) {
        *new_balance = calculate_winnings(balance, bet);
        return 1;  // Win
    }
    
    // Loss condition
    *new_balance = calculate_loss(balance, bet);
    
    // Check if game over
    if (*new_balance <= 0) {
        return -1;  // Game over
    }
    
    return 0;  // Lost but can continue
}


