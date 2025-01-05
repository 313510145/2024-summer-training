# Define phony targets, these are not files but commands
.PHONY: all check verify run run_valgrind generate clean

# Set the compiler and its flags
CXX = g++
CXX_FLAG = -Wall -Wextra -std=c++11 -g
INCLUDE_PATH = -Iheader

# Define memory checker tool (valgrind) and its options
CHECKCC = valgrind
CHECKCC_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# Set static analysis tool (cppcheck) and its flags
CPPCHECK = ../../cppcheck-2.13.0/cppcheck
CPPCHECK_FLAG = --enable=all --inconclusive --suppress=missingIncludeSystem

# Directories for output, logs, and object files
GOLDEN_DIRECTORY = golden
MEMORY_DIRECTORY = memory
OBJECT_DIRECTORY = object
OUTPUT_DIRECTORY = output
VERIFICATION_DIRECTORY = verification

# Directory containing source files
SOURCE_DIRECTORY = source

# Define the list of source files and their corresponding object files
SOURCE = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECT = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(SOURCE))

# Define test case input files
TESTCASE = $(wildcard testcase/*)

# Define target executable and generator script
TARGET = Lab2
GENERATOR = script/golden_generator

# Default target to build the project
all: $(TARGET)

# Rules to create directories if they don't exist
$(GOLDEN_DIRECTORY):
	mkdir $(GOLDEN_DIRECTORY)

$(MEMORY_DIRECTORY):
	mkdir $(MEMORY_DIRECTORY)

$(OBJECT_DIRECTORY):
	mkdir $(OBJECT_DIRECTORY)

$(OUTPUT_DIRECTORY):
	mkdir $(OUTPUT_DIRECTORY)

$(VERIFICATION_DIRECTORY):
	mkdir $(VERIFICATION_DIRECTORY)

# Rule to compile the target executable by linking object files
$(TARGET): main.cpp $(OBJECT)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $^ -o $@

# Rule to compile each source file into an object file
$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(OBJECT_DIRECTORY)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) -c $< -o $@

# Run static analysis using cppcheck
check: $(CPPCHECK)
	./$(CPPCHECK) $(CPPCHECK_FLAG) $(INCLUDE_PATH) .

# Verify the output by comparing program results with golden reference
verify: run generate | $(VERIFICATION_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		diff $(OUTPUT_DIRECTORY)/"$$testcase_base".out $(GOLDEN_DIRECTORY)/"$$testcase_base".gold | tee $(VERIFICATION_DIRECTORY)/"$$testcase_base".log; \
	done

# Run the target for all test cases
run: $(TARGET) | $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		./$(TARGET) "$$testcase" $(OUTPUT_DIRECTORY)/"$$testcase_base".out; \
	done

# Run the target with valgrind for all test cases and log memory checks
run_valgrind: $(TARGET) | $(MEMORY_DIRECTORY) $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		$(CHECKCC) $(CHECKCC_FLAG) --log-file=$(MEMORY_DIRECTORY)/"$$testcase_base.log" ./$(TARGET) "$$testcase" $(OUTPUT_DIRECTORY)/"$$testcase_base".out; \
	done

# Generate golden outputs using the generator script for test cases
generate: $(GENERATOR) | $(GOLDEN_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		./$(GENERATOR) "$$testcase" $(GOLDEN_DIRECTORY)/"$$testcase_base".gold; \
	done

# Clean up generated files and directories
clean:
	rm -rf $(TARGET) $(GOLDEN_DIRECTORY) $(MEMORY_DIRECTORY) $(OBJECT_DIRECTORY) $(OUTPUT_DIRECTORY) $(VERIFICATION_DIRECTORY)
