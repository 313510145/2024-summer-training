# Define phony targets, which represent commands rather than files
.PHONY: all check verify run run_valgrind case_generate clean

# Set the compiler and its flags
CXX = g++
CXX_FLAG = -Wall -std=c++11 -g
INCLUDE_PATH = -Iheader

# Define memory checker tool (valgrind) and its flags
CHECKCC = valgrind
CHECKCC_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# Set static analysis tool (cppcheck) and its flags
CPPCHECK = ../../cppcheck-2.13.0/cppcheck
CPPCHECK_FLAG = --enable=all --inconclusive --suppress=missingIncludeSystem

# Directories for output, logs, object files, and golden files
GOLDEN_DIRECTORY = golden
MEMORY_DIRECTORY = memory
OBJECT_DIRECTORY = object
OUTPUT_DIRECTORY = output
VERIFICATION_DIRECTORY = verification

# Directories for scripts, source files, and test cases
SCRIPT_DIRECTORY = script
SOURCE_DIRECTORY = source
TESTCASE_DIRECTORY = testcase

# Define the list of source files and corresponding object files
SOURCE = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECT = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(SOURCE))

# Define test case input files
TESTCASE = $(wildcard $(TESTCASE_DIRECTORY)/*)

# Define the target executable, case generator, number of cases, and golden generator
TARGET = Lab3
CASE_GENERATOR = $(SCRIPT_DIRECTORY)/case_generate
NUM_CASE = 10
GOLDEN_GENERATOR = $(SCRIPT_DIRECTORY)/golden_generate

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

# Verify program output against golden reference files
verify: run golden_generate | $(VERIFICATION_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		diff $(OUTPUT_DIRECTORY)/"$$testcase_base".out $(GOLDEN_DIRECTORY)/"$$testcase_base".gold | tee $(VERIFICATION_DIRECTORY)/"$$testcase_base".log; \
	done

# Run the program and generate output for each test case
run: $(TARGET) case_generate | $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		./$(TARGET) "$$testcase" $(OUTPUT_DIRECTORY)/"$$testcase_base".out; \
	done

# Run the program with valgrind and generate output for each test case
run_valgrind: $(TARGET) case_generate | $(MEMORY_DIRECTORY) $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		$(CHECKCC) $(CHECKCC_FLAG) --log-file=$(MEMORY_DIRECTORY)/"$$testcase_base.log" ./$(TARGET) "$$testcase" $(OUTPUT_DIRECTORY)/"$$testcase_base".out; \
	done

# Generate test cases from 3 to NUM_CASE using the case generator script
case_generate: $(CASE_GENERATOR)
	((i = 3)); while [ $$i -le $(NUM_CASE) ]; do \
		./$(CASE_GENERATOR) testcase/"$$i".in; \
		((i = i + 1)); \
	done

# Generate golden output for each test case using the golden generator script
golden_generate: $(GOLDEN_GENERATOR) | $(GOLDEN_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		./$(GOLDEN_GENERATOR) "$$testcase" $(GOLDEN_DIRECTORY)/"$$testcase_base".gold; \
	done

# Clean up all generated files, including test cases 3 to NUM_CASE
clean:
	rm -rf $(TARGET) $(GOLDEN_DIRECTORY) $(MEMORY_DIRECTORY) $(OBJECT_DIRECTORY) $(OUTPUT_DIRECTORY) $(VERIFICATION_DIRECTORY)
	((i = 3)); while [ $$i -le $(NUM_CASE) ]; do \
		rm -rf $(TESTCASE_DIRECTORY)/"$$i".in; \
		((i = i + 1)); \
	done
