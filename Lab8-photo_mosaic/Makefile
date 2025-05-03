.PHONY: all check run run_valgrind install clean

CXX = g++
CXX_FLAG = -Wall -Wextra -std=c++14 -g
INCLUDE_PATH = -Iheader -Ilibrary/CImg -Ilibrary/libjpeg
OPTIMIZATION_FLAG = -march=native -pthread -flto -funroll-loops -finline-functions -ffast-math -O3

LINKER = -lX11 -Llibrary/libjpeg -ljpeg -lpng

CHECKCC = valgrind
CHECKCC_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

CPPCHECK = ../../cppcheck-2.13.0/cppcheck
CPPCHECK_FLAG = --enable=all --inconclusive --suppress=missingIncludeSystem

MEMORY_DIRECTORY = memory
OBJECT_DIRECTORY = object
OUTPUT_DIRECTORY = output
LIBRARY_DIRECTORY = library
SOURCE_DIRECTORY = source

SOURCE = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECT = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(SOURCE))
DEPENDENCY = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.d, $(SOURCE))
TARGET = Lab8
INPUT_IMAGE = image/owl.jpg

all: $(TARGET)

$(MEMORY_DIRECTORY):
	mkdir $(MEMORY_DIRECTORY)

$(OBJECT_DIRECTORY):
	mkdir $(OBJECT_DIRECTORY)

$(OUTPUT_DIRECTORY):
	mkdir $(OUTPUT_DIRECTORY)

$(LIBRARY_DIRECTORY):
	mkdir $(LIBRARY_DIRECTORY)

$(TARGET): main.cpp $(OBJECT)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $(OPTIMIZATION_FLAG) $^ -o $@ $(LINKER)

-include $(DEPENDENCY)

$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(OBJECT_DIRECTORY)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $(OPTIMIZATION_FLAG) -MMD -c $< -o $@

check: $(CPPCHECK)
	./$(CPPCHECK) $(CPPCHECK_FLAG) $(INCLUDE_PATH) .

run: $(TARGET) | $(OUTPUT_DIRECTORY)
	./$(TARGET) $(INPUT_IMAGE) $(OUTPUT_DIRECTORY)/

run_valgrind: $(TARGET) | $(MEMORY_DIRECTORY) $(OUTPUT_DIRECTORY)
	$(CHECKCC) $(CHECKCC_FLAG) --log-file=$(MEMORY_DIRECTORY)/$(MEMORY_DIRECTORY).log ./$(TARGET) $(INPUT_IMAGE) $(OUTPUT_DIRECTORY)/

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

clean:
	rm -rf $(TARGET) $(MEMORY_DIRECTORY) $(OBJECT_DIRECTORY) $(OUTPUT_DIRECTORY) $(LIBRARY_DIRECTORY)
