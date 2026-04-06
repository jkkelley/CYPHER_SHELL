/* test_logic.c */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
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

// Test that generate_guess_one_to_six returns values in range 1-6
void test_generate_guess_range() {
    srand(42); // Seed for reproducibility
    bool all_in_range = true;
    int min_value = 7, max_value = 0;
    
    for (int i = 0; i < 100; i++) {
        int result = generate_guess_one_to_six(6);
        if (result < min_value) min_value = result;
        if (result > max_value) max_value = result;
        
        if (result < 1 || result > 6) {
            all_in_range = false;
            printf("❌ test_generate_guess_range: Failed (Got %d on iteration %d)\n", result, i);
            return;
        }
    }
    
    if (all_in_range) {
        printf("✅ test_generate_guess_range: Passed (Range: %d-%d over 100 calls)\n", min_value, max_value);
    }
}

// Test edge case where max=1 should always return 1
void test_generate_guess_max_one() {
    srand(123); // Seed for reproducibility
    bool all_ones = true;
    
    for (int i = 0; i < 20; i++) {
        int result = generate_guess_one_to_six(1);
        if (result != 1) {
            all_ones = false;
            printf("❌ test_generate_guess_max_one: Failed (Expected 1, got %d)\n", result);
            return;
        }
    }
    
    if (all_ones) {
        printf("✅ test_generate_guess_max_one: Passed\n");
    }
}

// Test distribution of generate_guess_one_to_six over many trials
void test_generate_guess_distribution() {
    srand(999); // Seed for reproducibility
    int counts[7] = {0}; // Index 0 unused, 1-6 for actual counts
    int trials = 6000;
    int expected = trials / 6; // 1000 per value
    double tolerance = 0.30; // 30% tolerance
    
    for (int i = 0; i < trials; i++) {
        int result = generate_guess_one_to_six(6);
        counts[result]++;
    }
    
    bool distribution_ok = true;
    for (int i = 1; i <= 6; i++) {
        int diff = abs(counts[i] - expected);
        double percent_diff = (double)diff / expected;
        
        if (percent_diff > tolerance) {
            distribution_ok = false;
            printf("❌ test_generate_guess_distribution: Failed (Value %d appeared %d times, expected ~%d, %.1f%% off)\n", 
                   i, counts[i], expected, percent_diff * 100);
        }
    }
    
    if (distribution_ok) {
        printf("✅ test_generate_guess_distribution: Passed (");
        for (int i = 1; i <= 6; i++) {
            printf("%d:%d ", i, counts[i]);
        }
        printf(")\n");
    }
}

// Test the wrapper function return_guess_one_to_six
void test_return_guess_range() {
    // Seed once before testing to get variety
    srand(time(NULL));
    
    bool all_in_range = true;
    int min_value = 7, max_value = 0;
    int counts[7] = {0};  // Track distribution
    
    for (int i = 0; i < 50; i++) {
        int result = return_guess_one_to_six();
        if (result < min_value) min_value = result;
        if (result > max_value) max_value = result;
        counts[result]++;
        
        if (result < 1 || result > 6) {
            all_in_range = false;
            printf("❌ test_return_guess_range: Failed (Got %d on iteration %d)\n", result, i);
            return;
        }
    }
    
    if (all_in_range) {
        int unique_values = 0;
        for (int i = 1; i <= 6; i++) {
            if (counts[i] > 0) unique_values++;
        }
        printf("✅ test_return_guess_range: Passed (Range: %d-%d, %d unique values in 50 calls)\n", 
               min_value, max_value, unique_values);
    }
}

int main() {
    printf("=== Running Unit Tests ===\n\n");
    
    // Section 1: User Input Tests
    printf("--- User Input Tests ---\n");
    test_valid_bet();
    test_valid_guess();
    test_quit_guess();
    
    printf("\n--- Random Number Generation Tests ---\n");
    test_generate_guess_range();
    test_generate_guess_max_one();
    test_generate_guess_distribution();
    test_return_guess_range();
    
    printf("\n=== Unit Tests Complete ===\n");
    return 0;
}
