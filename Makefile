# Make File for Lumpsort

# Define the C++ compiler
CXX = g++

# Define the name of the final executable.
TARGET = lumpsort

# Define the source and object files, and link objects and output
SRC_FUN = src/fun.cpp
SRC_MAIN = src/main.cpp
OBJ_FUN = objects/fun.o
OBJ_MAIN = objects/main.o
ALL_OBJS = $(OBJ_FUN) $(OBJ_MAIN)
OUTPUT_FLDR = output

# Phony targets
.PHONY: all clean

# Default target: build the program
# This rule states that 'lumpsort' depends on all object files.
# It also depends on the 'objects' directory existing before linking.
$(TARGET): objects $(ALL_OBJS)
	$(CXX) $(ALL_OBJS) -o $(TARGET)

# Rule to compile fun.cpp into fun.o
# This rule states that 'objects/fun.o' depends on 'src/fun.cpp'
# and the headers it includes: 'include/node.h' and 'include/lump.h'.
$(OBJ_FUN): $(SRC_FUN) include/node.h include/lump.h
	$(CXX) -Iinclude -c $(SRC_FUN) -o $(OBJ_FUN)

# Rule to compile main.cpp into main.o
# This rule states that 'objects/main.o' depends on 'src/main.cpp'
# and the header it includes: 'include/fun.h'.
$(OBJ_MAIN): $(SRC_MAIN) include/fun.h
	$(CXX) -Iinclude -c $(SRC_MAIN) -o $(OBJ_MAIN)

# Clean target: remove compiled files and the objects directory
# This rule removes all object files, the final executable, and the 'objects' directory.
clean:
	rm -f $(ALL_OBJS) $(TARGET) $(OUTPUT_FLDR)/*