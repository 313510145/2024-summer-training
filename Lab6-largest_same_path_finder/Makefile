# Define phony targets, which are not real files but command actions
.PHONY: all check verify run run_valgrind generate clean

# Set the compiler and its flags
CXX = g++
CXX_FLAG = -Wall -Wextra -std=c++11 -g
INCLUDE_PATH = -Iheader

# Define memory checker tool (valgrind) and its flags
CHECKCC = valgrind
CHECKCC_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# Define static analysis tool (cppcheck) and its flags
CPPCHECK = ../../cppcheck-2.13.0/cppcheck
CPPCHECK_FLAG = --enable=all --inconclusive --suppress=missingIncludeSystem

# Set directories for output, memory logs, object files, golden files, and verification logs
GOLDEN_DIRECTORY = golden
MEMORY_DIRECTORY = memory
OBJECT_DIRECTORY = object
OUTPUT_DIRECTORY = output
VERIFICATION_DIRECTORY = verification

# Define the directory for source files
SOURCE_DIRECTORY = source

# Define the lists of source files, object files, and dependency files with paths mapped between source and object directories.  
SOURCE = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECT = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(SOURCE))
DEPENDENCY = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.d, $(SOURCE))

# Collect all test case files from the 'testcase' directory
TESTCASE = $(wildcard testcase/*)

# Define the target executable and the golden file generator script
TARGET = Lab6
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

# Rule to compile the target executable from main.cpp and object files
$(TARGET): main.cpp $(OBJECT)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $^ -o $@

# Include dependency files to track header dependencies and ensure automatic recompilation when headers change.  
-include $(DEPENDENCY)

# Compile each source file (*.cpp) into an object file (*.o) with dependency generation (-MMD), ensuring the output is stored in the object directory.  
$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(OBJECT_DIRECTORY)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) -MMD -c $< -o $@

# Run static analysis using cppcheck
check: $(CPPCHECK)
	./$(CPPCHECK) $(CPPCHECK_FLAG) $(INCLUDE_PATH) .

# Verify program output against golden reference files
verify: run generate | $(VERIFICATION_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		diff $(OUTPUT_DIRECTORY)/"$$testcase_base".out $(GOLDEN_DIRECTORY)/"$$testcase_base".gold | tee $(VERIFICATION_DIRECTORY)/"$$testcase_base".log; \
	done

# Run the program for each test case
run: $(TARGET) | $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		./$(TARGET) "$$testcase" $(OUTPUT_DIRECTORY)/"$$testcase_base".out; \
	done

# Run the program with valgrind for each test case
run_valgrind: $(TARGET) | $(MEMORY_DIRECTORY) $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		$(CHECKCC) $(CHECKCC_FLAG) --log-file=$(MEMORY_DIRECTORY)/"$$testcase_base.log" ./$(TARGET) "$$testcase" $(OUTPUT_DIRECTORY)/"$$testcase_base".out; \
	done

# Generate golden output files for each test case
generate: $(GENERATOR) | $(GOLDEN_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		./$(GENERATOR) "$$testcase" $(GOLDEN_DIRECTORY)/"$$testcase_base".gold; \
	done

# Clean up all generated files and directories
clean:
	rm -rf $(TARGET) $(GOLDEN_DIRECTORY) $(MEMORY_DIRECTORY) $(OBJECT_DIRECTORY) $(OUTPUT_DIRECTORY) $(VERIFICATION_DIRECTORY)
