#yarinkash1@gmail.com

# flags:
CXXFLAGS = -std=c++11 -Wall -Wextra
# compiler:
CXX = g++

# Valgrind configuration
VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
VALGRIND_DETAILED_FLAGS = $(VALGRIND_FLAGS) --track-fds=yes --show-reachable=yes

# Executable names
MAIN_EXE = MyContainer_exe
TEST_EXE = tests_exe

all: $(MAIN_EXE) $(TEST_EXE)

test: $(TEST_EXE)

MyContainer_exe: MyContainer.o main.o
	$(CXX) $(CXXFLAGS) -o MyContainer_exe MyContainer.o main.o

tests_exe: MyContainer.o tests.o
	$(CXX) $(CXXFLAGS) -o tests_exe MyContainer.o tests.o

MyContainer.o: MyContainer.cpp MyContainer.hpp
	$(CXX) $(CXXFLAGS) -c MyContainer.cpp

tests.o: tests.cpp MyContainer.hpp
	$(CXX) $(CXXFLAGS) -c tests.cpp

main.o: main.cpp MyContainer.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

valgrind: $(MAIN_EXE)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(MAIN_EXE)

valgrind-test: $(TEST_EXE)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(TEST_EXE)

valgrind-detailed: $(MAIN_EXE)
	$(VALGRIND) $(VALGRIND_DETAILED_FLAGS) ./$(MAIN_EXE)

valgrind-test-detailed: $(TEST_EXE)
	$(VALGRIND) $(VALGRIND_DETAILED_FLAGS) ./$(TEST_EXE)

# Shortcut aliases
vg: valgrind
vg-test: valgrind-test
vg-detail: valgrind-detailed
vg-test-detail: valgrind-test-detailed


clean:
	rm -f *.o MyContainer_exe tests_exe

.PHONY: all clean