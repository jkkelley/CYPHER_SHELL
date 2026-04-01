#!/bin/bash

# Compile the latest version
gcc dice_game.c -o dice_game

echo "Running Test 1: Quitting with 0"
# Feed '5' for bet and '0' for guess to the program
echo -e "5\n0" | ./dice_game | grep -q "Quitting game..."

if [ $? -eq 0 ]; then
    echo "✅ Test Passed: Program quit correctly."
else
    echo "❌ Test Failed: Program did not quit."
fi

echo "Running Test 2: Invalid Bet (Over Balance)"
# Bet 2000 (over 1000 balance), then 10, then 0 to quit
echo -e "2000\n10\n0" | ./dice_game | grep -q "Insufficient funds"

if [ $? -eq 0 ]; then
    echo "✅ Test Passed: Over-bet handled."
else
    echo "❌ Test Failed: Over-bet allowed."
fi
