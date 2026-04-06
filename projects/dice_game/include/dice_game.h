#ifndef DICE_GAME_H
#define DICE_GAME_H

#include <stdio.h>

// Alias macro
#define F_OUT() fflush(stdout)

// Function prototypes
int what_is_user_bet(int current_balance, FILE *stream, void (*handler)());
int what_is_user_guess(int guess, FILE *stream, void (*handler)());
void clear_input_buffer();
int generate_guess_one_to_six(int max);
int return_guess_one_to_six();

// Game logic functions
int calculate_loss(int balance, int bet);
int calculate_winnings(int balance, int bet);
int check_game_result(int guess, int dice_roll, int balance, int bet, int *new_balance);

#endif
