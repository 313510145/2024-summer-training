.PHONY: all check verify run run_valgrind generate install clean

CXX = g++
CXX_FLAG = -Wall -Wextra -std=c++14 -g -static
INCLUDE_PATH = -Iheader

CHECKCC = valgrind
CHECKCC_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
CPPCHECK = ../../cppcheck-2.13.0/cppcheck
CPPCHECK_FLAG = --enable=all --inconclusive --suppress=missingIncludeSystem

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

SOURCE = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECT = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(SOURCE))
DEPENDENCY = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.d, $(SOURCE))

TESTCASE = $(wildcard $(TESTCASE_VERILOG_DIRECTORY)/*)

define GET_TESTCASE_BASE
testcase_base=$$(basename $$testcase); \
testcase_base=$${testcase_base%.*}
endef

TARGET = Lab9
ABC = $(LIBRARY_DIRECTORY)/abc/abc

all: $(TARGET)

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

$(TARGET): main.cpp $(OBJECT)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) $^ -o $@

-include $(DEPENDENCY)

$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(OBJECT_DIRECTORY)
	$(CXX) $(CXX_FLAG) $(INCLUDE_PATH) -MMD -c $< -o $@

check: $(CPPCHECK)
	./$(CPPCHECK) $(CPPCHECK_FLAG) $(INCLUDE_PATH) .

verify: run generate $(ABC) | $(VERIFICATION_DIRECTORY)
	for testcase in $(TESTCASE); do \
		$(GET_TESTCASE_BASE); \
		./$(ABC) -c "cec $(OUTPUT_DIRECTORY)/$${testcase_base}.blif $(TESTCASE_BLIF_DIRECTORY)/$${testcase_base}.blif" | tee $(VERIFICATION_DIRECTORY)/$${testcase_base}.equiv; \
		./$(ABC) -c "read_blif $(OUTPUT_DIRECTORY)/$${testcase_base}.blif; st; ps;" | tee $(OUTPUT_DIRECTORY)/$${testcase_base}.size; \
		diff $(OUTPUT_DIRECTORY)/$${testcase_base}.size $(GOLDEN_DIRECTORY)/$${testcase_base}.size | tee $(VERIFICATION_DIRECTORY)/$${testcase_base}.size; \
	done
	rm -rf abc.history

run: $(TARGET) | $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		$(GET_TESTCASE_BASE); \
		./$(TARGET) $$testcase $(OUTPUT_DIRECTORY)/$${testcase_base}.blif; \
	done

run_valgrind: $(TARGET) | $(MEMORY_DIRECTORY) $(OUTPUT_DIRECTORY)
	for testcase in $(TESTCASE); do \
		$(GET_TESTCASE_BASE); \
		$(CHECKCC) $(CHECKCC_FLAG) --log-file=$(MEMORY_DIRECTORY)/$${testcase_base}.log ./$(TARGET) $$testcase $(OUTPUT_DIRECTORY)/$${testcase_base}.blif; \
	done

generate: $(ABC) | $(GOLDEN_DIRECTORY)
	for testcase in $(TESTCASE); do \
		$(GET_TESTCASE_BASE); \
		./$(ABC) -c "read_blif $(TESTCASE_BLIF_DIRECTORY)/$${testcase_base}.blif; st; ps;" | tee $(GOLDEN_DIRECTORY)/$${testcase_base}.size; \
	done
	rm -rf abc.history

install: | $(LIBRARY_DIRECTORY)
	git clone https://github.com/berkeley-abc/abc.git $(LIBRARY_DIRECTORY)/abc
	cd $(LIBRARY_DIRECTORY)/abc; \
	make -j

clean:
	rm -rf $(TARGET) $(GOLDEN_DIRECTORY) $(MEMORY_DIRECTORY) $(OBJECT_DIRECTORY) $(OUTPUT_DIRECTORY) $(LIBRARY_DIRECTORY) $(VERIFICATION_DIRECTORY)
