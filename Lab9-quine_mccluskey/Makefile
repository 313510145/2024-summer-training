# Define phony targets, which are not real files but command actions
.PHONY: all check verify run run_valgrind generate install clean

# Set the compiler and its flags
CXX = g++
CXX_FLAG = -Wall -std=c++11 -g
INCLUDE_PATH = -Iheader

# Define memory checker tool (valgrind) and its flags
CHECKCC = valgrind
CHECKCC_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# Define static analysis tool (cppcheck) and its flags
CPPCHECK = ../../cppcheck-2.13.0/cppcheck
CPPCHECK_FLAG = --enable=all --inconclusive --suppress=missingIncludeSystem

# Set directories for output, memory logs, object files, golden files, and verification logs
MEMORY_DIRECTORY = memory
OBJECT_DIRECTORY = object
OUTPUT_DIRECTORY = output
LIBRARY_DIRECTORY = library
VERIFICATION_DIRECTORY = verification

# Define the directory for source files and test cases
SOURCE_DIRECTORY = source
TESTCASE_DIRECTORY = testcase

# Gather all source files and create a list of corresponding object files
SOURCE = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECT = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(SOURCE))

# Collect all test case files from the 'testcase' directory
TESTCASE = $(wildcard $(TESTCASE_DIRECTORY)/verilog/*)

TARGET = Lab9
ABC = $(LIBRARY_DIRECTORY)/abc/abc

# Default target to build the project
all: $(TARGET)

# Rules to create necessary directories if they don't exist
$(MEMORY_DIRECTORY):
	mkdir -p $(MEMORY_DIRECTORY)

$(OBJECT_DIRECTORY):
	mkdir -p $(OBJECT_DIRECTORY)

$(OUTPUT_DIRECTORY):
	mkdir -p $(OUTPUT_DIRECTORY)

$(VERIFICATION_DIRECTORY):
	mkdir -p $(VERIFICATION_DIRECTORY)

# Rule to compile the target executable from main.cpp and object files
$(TARGET): main.cpp $(OBJECT)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $^ -o $@

# Rule to compile each source file into an object file
$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(OBJECT_DIRECTORY)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) -c $< -o $@

# Run static analysis using cppcheck
check:
	./$(CPPCHECK) $(CPPCHECK_FLAG) $(INCLUDE_PATH) .

# Verify program output against golden reference files
verify: run | $(VERIFICATION_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		./$(ABC) -c "cec $(OUTPUT_DIRECTORY)/"$$testcase_base".blif $(TESTCASE_DIRECTORY)/blif/"$$testcase_base".blif" | tee $(VERIFICATION_DIRECTORY)/"$$testcase_base".equiv; \
		./$(ABC) -c "read_blif $(OUTPUT_DIRECTORY)/"$$testcase_base".blif; st; ps;" | tee $(VERIFICATION_DIRECTORY)/"$$testcase_base".size; \
	done
	rm -rf abc.history

# Run the program for each test case
run: $(TARGET) | $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		./$(TARGET) "$$testcase" $(OUTPUT_DIRECTORY)/"$$testcase_base".blif; \
	done

# Run the program with valgrind for each test case
run_valgrind: $(TARGET) | $(MEMORY_DIRECTORY) $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		testcase_base=$$(basename "$$testcase"); \
		testcase_base=$${testcase_base%.*}; \
		$(CHECKCC) $(CHECKCC_FLAG) --log-file=$(MEMORY_DIRECTORY)/"$$testcase_base.log" ./$(TARGET) "$$testcase" $(OUTPUT_DIRECTORY)/"$$testcase_base".blif; \
	done

# Install ABC library from GitHub
install:
	mkdir -p $(LIBRARY_DIRECTORY)
	git clone https://github.com/berkeley-abc/abc.git $(LIBRARY_DIRECTORY)/abc
	cd $(LIBRARY_DIRECTORY)/abc; \
	make -j

# Clean up all generated files and directories
clean:
	rm -rf $(TARGET) $(MEMORY_DIRECTORY) $(OBJECT_DIRECTORY) $(OUTPUT_DIRECTORY) $(LIBRARY_DIRECTORY) $(VERIFICATION_DIRECTORY)
