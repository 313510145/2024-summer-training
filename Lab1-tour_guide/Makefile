# Define phony targets, which don't correspond to real files
.PHONY: all check verify run generate clean

# Compiler and flags used for compilation
CXX = g++
CXX_FLAG = -Wall -std=c++11 -g
INCLUDE_PATH = -Iheader

# Memory check tool and flags for valgrind
CHECKCC = valgrind
CHECKCC_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# Static analysis tool (cppcheck) and flags
CPPCHECK = ../../cppcheck-2.13.0/cppcheck
CPPCHECK_FLAG = --enable=all --inconclusive --suppress=missingIncludeSystem

# Directories for organizing output, object files, and logs
GOLDEN_DIRECTORY = golden
MEMORY_DIRECTORY = memory
OBJECT_DIRECTORY = object
OUTPUT_DIRECTORY = output
VERIFICATION_DIRECTORY = verification

# Directory containing source files
SOURCE_DIRECTORY = source

# Define all source files and corresponding object files
SOURCE = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECT = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(SOURCE))

# Define test case input files
TESTCASE = $(wildcard testcase/*)

# Target executable and generator script
TARGET = Lab1
GENERATOR = script/golden_generate

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

# Rule to compile the target executable, linking object files
$(TARGET): main.cpp $(OBJECT)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $^ -o $@

# Rule to compile individual source files into object files
$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(OBJECT_DIRECTORY)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) -c $< -o $@

# Run static analysis using cppcheck
check:
	./$(CPPCHECK) $(CPPCHECK_FLAG) $(INCLUDE_PATH) .

# Verify output against golden reference by running and generating output, then comparing with golden files
verify: run generate | $(VERIFICATION_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		diff $(OUTPUT_DIRECTORY)/"$$testcase_base".out $(GOLDEN_DIRECTORY)/"$$testcase_base".gold | tee $(VERIFICATION_DIRECTORY)/"$$testcase_base".log; \
	done

# Run the program with memory check (valgrind) on all test cases
run: $(TARGET) | $(MEMORY_DIRECTORY) $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		$(CHECKCC) $(CHECKCC_FLAG) --log-file=$(MEMORY_DIRECTORY)/"$$testcase_base.log" ./$(TARGET) "$$testcase" $(OUTPUT_DIRECTORY)/"$$testcase_base".out; \
	done

# Generate golden output for each test case using the generator script
generate: | $(GOLDEN_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		./$(GENERATOR) "$$testcase" $(GOLDEN_DIRECTORY)/"$$testcase_base".gold; \
	done

# Clean up generated files and directories
clean:
	rm -rf $(TARGET) $(GOLDEN_DIRECTORY) $(MEMORY_DIRECTORY) $(OBJECT_DIRECTORY) $(OUTPUT_DIRECTORY) $(VERIFICATION_DIRECTORY)
