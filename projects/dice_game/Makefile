CC=gcc
CFLAGS=-Wall -Wextra

all: dice_game

dice_game: dice_game.c
	$(CC) $(CFLAGS) dice_game.c -o dice_game

test: dice_game
	chmod +x test.sh
	./test.sh

clean:
	rm -f dice_game
