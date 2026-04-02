/* test_logic.c */
#include <stdio.h>
#include <stdlib.h>
#include "dice_game.h"

// Helper function to create a fake input stream from a string
FILE* mock_input(const char* input_string) {
    FILE *tmp = tmpfile(); // Creates a temporary file that auto-deletes when closed
    if (tmp) {
        fputs(input_string, tmp);
        rewind(tmp); // Rewind the file pointer back to the start for reading
    }
    return tmp;
}

// Dummy buffer clearer for testing (we don't need to clear actual stdin here)
void mock_clear_buffer() {
    // Do nothing
}

void test_valid_bet() {
    // We mock the user typing "500" and hitting Enter
    FILE *in = mock_input("500\n");

    int result = what_is_user_bet(1000, in, mock_clear_buffer);

    if (result == 500) {
        printf("✅ test_valid_bet: Passed\n");
    } else {
        printf("❌ test_valid_bet: Failed (Expected 500, got %d)\n", result);
    }
    fclose(in);
}

void test_valid_guess() {
    // We mock the user typing "4" and hitting Enter
    FILE *in = mock_input("4\n");

    int result = what_is_user_guess(0, in, mock_clear_buffer);

    if (result == 4) {
        printf("✅ test_valid_guess: Passed\n");
    } else {
        printf("❌ test_valid_guess: Failed (Expected 4, got %d)\n", result);
    }
    fclose(in);
}

void test_quit_guess() {
    // We mock the user typing "0" to quit
    FILE *in = mock_input("0\n");

    int result = what_is_user_guess(0, in, mock_clear_buffer);

    // Since game_logic.c now returns 0 instead of calling exit(0), we can test it!
    if (result == 0) {
        printf("✅ test_quit_guess: Passed\n");
    } else {
        printf("❌ test_quit_guess: Failed (Expected 0, got %d)\n", result);
    }
    fclose(in);
}

int main() {
    printf("--- Running Unit Tests ---\n");
    test_valid_bet();
    test_valid_guess();
    test_quit_guess();
    printf("--- Unit Tests Complete ---\n\n");
    return 0;
}
