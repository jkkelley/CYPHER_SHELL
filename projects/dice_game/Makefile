CC=gcc
# The -I flag tells gcc to look inside the 'include' folder for .h files
CFLAGS=-Wall -Wextra -Iinclude

# Define our directories
SRC_DIR=src
BUILD_DIR=build
TEST_DIR=tests

# Define our final executables
TARGET=$(BUILD_DIR)/dice_game
TEST_TARGET=$(BUILD_DIR)/test_logic

# Define our object files
OBJS=$(BUILD_DIR)/dice_game.o $(BUILD_DIR)/game_logic.o

# The default rule runs when you just type 'make'
all: $(TARGET) $(TEST_TARGET)

# This rule creates the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the main game executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile dice_game.c into an object file
$(BUILD_DIR)/dice_game.o: $(SRC_DIR)/dice_game.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/dice_game.c -o $(BUILD_DIR)/dice_game.o

# Compile game_logic.c into an object file
$(BUILD_DIR)/game_logic.o: $(SRC_DIR)/game_logic.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/game_logic.c -o $(BUILD_DIR)/game_logic.o

# Build the Unit Test executable
$(TEST_TARGET): $(TEST_DIR)/test_logic.c $(BUILD_DIR)/game_logic.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_logic.c $(BUILD_DIR)/game_logic.o -o $(TEST_TARGET)

# Run the unit tests and the bash script
test: $(TARGET) $(TEST_TARGET)
	./$(TEST_TARGET)
	chmod +x $(TEST_DIR)/test.sh
	./$(TEST_DIR)/test.sh

# Wipe the build directory clean
clean:
	rm -rf $(BUILD_DIR)/*
