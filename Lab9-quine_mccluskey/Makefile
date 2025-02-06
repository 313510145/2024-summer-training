# Target names for different tasks and phony targets
.PHONY: all check verify run run_valgrind generate install clean

# Compiler and flags for C++ source code
CXX = g++
CXX_FLAG = -Wall -Wextra -std=c++14 -g -static
INCLUDE_PATH = -Iheader

# Tools and their configurations for checking memory leaks and code quality
CHECKCC = valgrind
CHECKCC_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
CPPCHECK = ../../cppcheck-2.13.0/cppcheck
CPPCHECK_FLAG = --enable=all --inconclusive --suppress=missingIncludeSystem

# Directory variables to organize output, verification, and sources
GOLDEN_DIRECTORY = golden
MEMORY_DIRECTORY = memory
OBJECT_DIRECTORY = object
OUTPUT_DIRECTORY = output
LIBRARY_DIRECTORY = library
VERIFICATION_DIRECTORY = verification
SOURCE_DIRECTORY = source
TESTCASE_DIRECTORY = testcase
TESTCASE_VERILOG_DIRECTORY = $(TESTCASE_DIRECTORY)/verilog
TESTCASE_BLIF_DIRECTORY = $(TESTCASE_DIRECTORY)/blif

# Define the lists of source files, object files, and dependency files with paths mapped between source and object directories.  
SOURCE = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECT = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(SOURCE))
DEPENDENCY = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.d, $(SOURCE))

# Define test case input files
TESTCASE = $(wildcard $(TESTCASE_VERILOG_DIRECTORY)/*)

# Define common testcase base transformation
define GET_TESTCASE_BASE
testcase_base=$$(basename $$testcase); \
testcase_base=$${testcase_base%.*}
endef

# Main executable target and library dependencies
TARGET = Lab9
ABC = $(LIBRARY_DIRECTORY)/abc/abc

# Default target: Build the executable
all: $(TARGET)

# Create necessary directories
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

$(LIBRARY_DIRECTORY):
	mkdir $(LIBRARY_DIRECTORY)

# Compile main executable with object files
$(TARGET): main.cpp $(OBJECT)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $^ -o $@

# Include dependency files to track header dependencies and ensure automatic recompilation when headers change.  
-include $(DEPENDENCY)

# Compile each source file (*.cpp) into an object file (*.o) with dependency generation (-MMD), ensuring the output is stored in the object directory.  
$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(OBJECT_DIRECTORY)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) -MMD -c $< -o $@

# Check code quality using cppcheck
check: $(CPPCHECK)
	./$(CPPCHECK) $(CPPCHECK_FLAG) $(INCLUDE_PATH) .

# Verify results by comparing outputs with golden references
verify: run generate $(ABC) | $(VERIFICATION_DIRECTORY)
	for testcase in $(TESTCASE); do \
		$(GET_TESTCASE_BASE); \
		./$(ABC) -c "cec $(OUTPUT_DIRECTORY)/$${testcase_base}.blif $(TESTCASE_BLIF_DIRECTORY)/$${testcase_base}.blif" | tee $(VERIFICATION_DIRECTORY)/$${testcase_base}.equiv; \
		./$(ABC) -c "read_blif $(OUTPUT_DIRECTORY)/$${testcase_base}.blif; st; ps;" | tee $(OUTPUT_DIRECTORY)/$${testcase_base}.size; \
		diff $(OUTPUT_DIRECTORY)/$${testcase_base}.size $(GOLDEN_DIRECTORY)/$${testcase_base}.size | tee $(VERIFICATION_DIRECTORY)/$${testcase_base}.size; \
	done
	rm -rf abc.history

# Run the main executable with testcases
run: $(TARGET) | $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		$(GET_TESTCASE_BASE); \
		./$(TARGET) $$testcase $(OUTPUT_DIRECTORY)/$${testcase_base}.blif; \
	done

# Run the main executable with Valgrind for memory checking
run_valgrind: $(TARGET) | $(MEMORY_DIRECTORY) $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		$(GET_TESTCASE_BASE); \
		$(CHECKCC) $(CHECKCC_FLAG) --log-file=$(MEMORY_DIRECTORY)/$${testcase_base}.log ./$(TARGET) $$testcase $(OUTPUT_DIRECTORY)/$${testcase_base}.blif; \
	done

# Generate golden reference outputs using ABC tool
generate: $(ABC) | $(GOLDEN_DIRECTORY)
	for testcase in $(TESTCASE); do \
		$(GET_TESTCASE_BASE); \
		./$(ABC) -c "read_blif $(TESTCASE_BLIF_DIRECTORY)/$${testcase_base}.blif; st; ps;" | tee $(GOLDEN_DIRECTORY)/$${testcase_base}.size; \
	done
	rm -rf abc.history

# Install ABC tool from GitHub repository
install: | $(LIBRARY_DIRECTORY)
	git clone https://github.com/berkeley-abc/abc.git $(LIBRARY_DIRECTORY)/abc
	cd $(LIBRARY_DIRECTORY)/abc; \
	make -j

# Clean all generated files and directories
clean:
	rm -rf $(TARGET) $(GOLDEN_DIRECTORY) $(MEMORY_DIRECTORY) $(OBJECT_DIRECTORY) $(OUTPUT_DIRECTORY) $(LIBRARY_DIRECTORY) $(VERIFICATION_DIRECTORY)
