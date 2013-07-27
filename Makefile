#-----------------------------------------------------------------------------
# CONFIGURATION
#-----------------------------------------------------------------------------

# Directories
BIN = bin
BIN_BASE = $(BIN)/base
BIN_GEOM = $(BIN)/geom
BIN_TESTS = $(BIN)/tests
BIN_TESTS_BASE = $(BIN_TESTS)/base
BIN_TESTS_GEOM = $(BIN_TESTS)/geom
BIN_TESTS = $(BIN)/tests
INCLUDE = include
INCLUDE_BASE = $(INCLUDE)/base
INCLUDE_GEOM = $(INCLUDE)/geom
SRC = src
SRC_BASE = $(SRC)/base
SRC_GEOM = $(SRC)/geom
TESTS = tests
TESTS_BASE = $(TESTS)/base
TESTS_GEOM = $(TESTS)/geom

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
BASE_TESTS = $(patsubst $(TESTS_BASE)/%.cpp, $(BIN_TESTS_BASE)/%, \
	$(BASE_TESTS_SRC))

# geom
GEOM_INCLUDES := $(wildcard $(INCLUDE_GEOM)/*.hpp)
GEOM_SOURCES := $(wildcard $(SRC_GEOM)/*.cpp)
GEOM_OBJECTS = $(patsubst $(SRC_GEOM)/%.cpp, $(BIN_GEOM)/%.o, \
	$(GEOM_SOURCES))
GEOM_TESTS_SRC := $(wildcard $(TESTS_GEOM)/*.cpp)
GEOM_TESTS = $(patsubst $(TESTS_GEOM)/%.cpp, $(BIN_TESTS_GEOM)/%, \
	$(GEOM_TESTS_SRC))

# all binary objects
OBJECTS=$(BASE_OBJECTS) $(GEOM_OBJECTS)

# all test executables
TEST_EXES=$(BASE_TESTS) $(GEOM_TESTS)

#-----------------------------------------------------------------------------
# BUILD RULES
#-----------------------------------------------------------------------------

# main build
all: prepare $(OBJECTS) $(TEST_EXES)

# Build base objects
$(BIN_BASE)/%.o: $(SRC_BASE)/%.cpp $(INCLUDE_BASE)/%.hpp
	$(CC) $(OFLAGS) $< -o $@

# Build geom objects
$(BIN_GEOM)/%.o: $(SRC_GEOM)/%.cpp $(INCLUDE_GEOM)/%.hpp
	$(CC) $(OFLAGS) $< -o $@

# Build base tests
$(BIN_TESTS_BASE)/%_tests: $(BIN_BASE)/%.o $(TESTS_BASE)/%_tests.cpp
	$(CC) $(CFLAGS) $^ -o $@

# Build geom tests
$(BIN_TESTS_GEOM)/%_tests: $(BIN_GEOM)/%.o $(BIN_BASE)/Meta.o \
	$(TESTS_GEOM)/%_tests.cpp
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
