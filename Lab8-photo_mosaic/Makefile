# Define phony targets, which are not real files but command actions
.PHONY: all check run run_valgrind install clean

# Compiler and flags
CXX = g++
CXX_FLAG = -Wall -Wextra -std=c++14 -g
INCLUDE_PATH = -Iheader -Ilibrary/CImg -Ilibrary/libjpeg
OPTIMIZATION_FLAG = -march=native -pthread -flto -funroll-loops -finline-functions -ffast-math -O3

# Linker flags
LINKER = -lX11 -Llibrary/libjpeg -ljpeg -lpng

# Tools for checking and analysis
CHECKCC = valgrind
CHECKCC_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# Define static analysis tool (cppcheck) and its flags
CPPCHECK = ../../cppcheck-2.13.0/cppcheck
CPPCHECK_FLAG = --enable=all --inconclusive --suppress=missingIncludeSystem

# Directory paths
MEMORY_DIRECTORY = memory
OBJECT_DIRECTORY = object
OUTPUT_DIRECTORY = output
LIBRARY_DIRECTORY = library
SOURCE_DIRECTORY = source

# File lists
SOURCE = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECT = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(SOURCE))
DEPENDENCY = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.d, $(SOURCE))
TARGET = Lab8
INPUT_IMAGE = image/owl.jpg

# Default target: build the executable
all: $(TARGET)

# Rules to create directories if they don't exist
$(MEMORY_DIRECTORY):
	mkdir $(MEMORY_DIRECTORY)

$(OBJECT_DIRECTORY):
	mkdir $(OBJECT_DIRECTORY)

$(OUTPUT_DIRECTORY):
	mkdir $(OUTPUT_DIRECTORY)

$(LIBRARY_DIRECTORY):
	mkdir $(LIBRARY_DIRECTORY)

# Build the target executable from the source and object files
$(TARGET): main.cpp $(OBJECT)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $(OPTIMIZATION_FLAG) $^ -o $@ $(LINKER)

# Include dependency files to track header dependencies and ensure automatic recompilation when headers change.  
-include $(DEPENDENCY)

# Compile each source file (*.cpp) into an object file (*.o) with dependency generation (-MMD), ensuring the output is stored in the object directory.  
$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(OBJECT_DIRECTORY)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $(OPTIMIZATION_FLAG) -MMD -c $< -o $@

# Run static code analysis with cppcheck
check: $(CPPCHECK)
	./$(CPPCHECK) $(CPPCHECK_FLAG) $(INCLUDE_PATH) .

# Run the program
run: $(TARGET) | $(OUTPUT_DIRECTORY)
	./$(TARGET) $(INPUT_IMAGE) $(OUTPUT_DIRECTORY)/

# Run the program with memory checks using valgrind
run_valgrind: $(TARGET) | $(MEMORY_DIRECTORY) $(OUTPUT_DIRECTORY)
	$(CHECKCC) $(CHECKCC_FLAG) --log-file=$(MEMORY_DIRECTORY)/$(MEMORY_DIRECTORY).log ./$(TARGET) $(INPUT_IMAGE) $(OUTPUT_DIRECTORY)/

# Clone and build required external libraries
install: | $(LIBRARY_DIRECTORY)
	git clone https://github.com/GreycLab/CImg $(LIBRARY_DIRECTORY)/CImg
	git clone https://github.com/kornelski/libjpeg $(LIBRARY_DIRECTORY)/libjpeg
	cd $(LIBRARY_DIRECTORY)/libjpeg; \
	./configure; \
	make -j; \
	make test; \
	cd ../../
	git clone https://github.com/posva/catimg $(LIBRARY_DIRECTORY)/catimg
	cd $(LIBRARY_DIRECTORY)/catimg; \
	cmake .; \
	make -j

# Clean up generated files and directories
clean:
	rm -rf $(TARGET) $(MEMORY_DIRECTORY) $(OBJECT_DIRECTORY) $(OUTPUT_DIRECTORY) $(LIBRARY_DIRECTORY)
