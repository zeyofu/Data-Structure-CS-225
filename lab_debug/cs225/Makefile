#
# CS 225 Library Makefile
#

CPP_FILES = $(wildcard *.cpp) lodepng/lodepng.cpp
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))
CXX = clang++

CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm


all: $(OBJ_FILES)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
