# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -O3 -std=c++17

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Target executable name (root directory)
TARGET = register

# Locate all .cpp files in src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Map source files to object files in the obj/ directory
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
