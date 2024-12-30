# Define directories
SRC_DIR := src
LIB_DIR := lib
DIST_DIR := dist
OBJ_DIR := $(DIST_DIR)/obj

# Define source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
LIB_WINDOW_MANAGER_SRC := $(wildcard $(LIB_DIR)/window_manager/*.cpp)
LIB_UTILITY_SRC := $(wildcard $(LIB_DIR)/utility/*.cpp)
ALL_SRC_FILES := $(SRC_FILES) $(LIB_WINDOW_MANAGER_SRC) $(LIB_UTILITY_SRC)

OBJ_FILES := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(ALL_SRC_FILES))
EXECUTABLE := $(DIST_DIR)/cpwm

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -O2 -lX11

# Rule to create object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D) # Create the object directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $@

# Target to create all object files and the executable
all: $(EXECUTABLE)

# Clean rule to remove object files and executable
clean:
	rm -rf $(DIST_DIR)

# Phony target to prevent accidental file creation
.PHONY: all clean
