CC=gcc
# The -I flag tells gcc to look inside the 'include' folder for .h files
CFLAGS=-Wall	-Wextra -Iinclude

# Define our directories
SRC_DIR=src
BUILD_DIR=build
TEST_DIR=tests

# Define our file names
BUILD_NAME=instance_costs

# Define our final executables
TARGET=$(BUILD_DIR)/instance_costs

# Define our object files
OBJS=$(BUILD_DIR)/$(BUILD_NAME).o

# The default rule runs when you just type 'make'
all: $(TARGET)

# This rule creates the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the main executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile instance_costs.c into an object file
$(BUILD_DIR)/instance_costs.o: $(SRC_DIR)/instance_costs.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/instance_costs.c -o $(BUILD_DIR)/instance_costs.o

# Build the Unit Test executable
$(TEST_TARGET): $(TEST_DIR)/test_logic.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_logic.c -o $(TEST_TARGET)

# Run the unit tests and the bash script
test: $(TARGET) $(TEST_TARGET)
	./$(TEST_TARGET)
	chmod +x $(TEST_DIR)/test.sh
	./$(TEST_DIR)/test.sh

# Wipe the build directory clean
clean:
	rm -rf $(BUILD_DIR)/*