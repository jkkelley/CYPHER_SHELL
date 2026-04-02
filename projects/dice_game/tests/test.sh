#!/bin/bash

echo "Running Test 1: Quitting with 0"
# Feed '5' for bet and '0' for guess to the program
# Look for the output main() prints when it receives a 0
printf "5\n0\n" | ./build/dice_game | grep -q "Thanks for playing!"

if [ $? -eq 0 ]; then
    echo "✅ Test Passed: Program quit correctly."
else
    echo "❌ Test Failed: Program did not quit."
fi

echo "Running Test 2: Invalid Bet (Over Balance)"
# Bet 2000 (over 1000 balance), then 10, then 0 to quit
# Update the grep string to match the new game_logic.c output
echo -e "2000\n10\n0" | ./build/dice_game | grep -q "Invalid bet amount"

if [ $? -eq 0 ]; then
    echo "✅ Test Passed: Over-bet handled."
else
    echo "❌ Test Failed: Over-bet allowed."
fi
