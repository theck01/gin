#-----------------------------------------------------------------------------
# CONFIGURATION
#-----------------------------------------------------------------------------

# Directories
BIN = bin
BIN_BASE = $(BIN)/base
BIN_TESTS = $(BIN)/tests
INCLUDE = include
INCLUDE_BASE = $(INCLUDE)/base
SRC = src
SRC_BASE = $(SRC)/base
TESTS = tests
TESTS_BASE = $(TESTS)/base

# Compiler Information
CC = clang++
CFLAGS = -Wall -Wextra -g -std=c++0x
OFLAGS = $(CFLAGS) -c


#-----------------------------------------------------------------------------
# OBJECT AND EXECUTABLE ENUMERATION
#-----------------------------------------------------------------------------

# base
BASE_INCLUDES := $(wildcard $(INCLUDE_BASE)/*.hpp)
BASE_SOURCES := $(wildcard $(SRC_BASE)/*.cpp)
BASE_OBJECTS = $(patsubst $(SRC_BASE)/%.cpp, $(BIN_BASE)/%.o, \
	$(BASE_SOURCES))
BASE_TESTS_SRC := $(wildcard $(TESTS_BASE)/*.cpp)
BASE_TESTS = $(patsubst $(TESTS_BASE)/%.cpp, $(BIN_TESTS)/%, \
	$(BASE_TESTS_SRC))


#-----------------------------------------------------------------------------
# BUILD RULES
#-----------------------------------------------------------------------------

# main build
all: prepare $(BASE_OBJECTS) $(BASE_TESTS)

# Build base objects
$(BIN_BASE)/%.o: $(SRC_BASE)/%.cpp $(INCLUDE_BASE)/%.hpp
	$(CC) $(OFLAGS) $< -o $@

# Build base tests
$(BIN_TESTS)/%_tests: $(BIN_BASE)/%.o $(TESTS_BASE)/%_tests.cpp
	$(CC) $(CFLAGS) $^ -o $@

# clean build
clean: rmbin prepare

# "full" build, remove previous builds and run tests after completion
full: clean all test

# rebuild bin subdirectory tree
prepare:
	@scripts/prepare.sh

# remove bin subdirectory, the first half of clean
rmbin:
	@rm -rf bin

# Run all tests
test:
	@echo "Running unit tests..."
	@echo 
	@scripts/run_bin.sh $(BIN_TESTS)
