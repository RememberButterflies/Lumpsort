# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) main.cpp

# Object files
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# Executable
EXEC = $(BIN_DIR)/main

# Default target
all: $(EXEC)

# Build executable
$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build object files
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
