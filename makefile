#yarinkash1

# flags:
CXXFLAGS = -std=c++11 -Wall -Wextra
# compiler:
CXX = g++

all: MyContainer_exe tests_exe

test: tests_exe

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

clean:
	rm -f *.o MyContainer_exe tests_exe

.PHONY: all clean