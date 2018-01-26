EXENAME = lab_intro
OBJS = main.o PNG.o HSLAPixel.o lodepng.o lab_intro.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp lab_intro.h cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) main.cpp 

lab_intro.o : lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) lab_intro.cpp
	
PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp


test: basic.o PNG.o HSLAPixel.o lodepng.o lab_intro.o
	$(LD) basic.o PNG.o HSLAPixel.o lodepng.o lab_intro.o $(LDFLAGS) -o test

basic.o : tests/basic.cpp tests/catch.hpp
	$(CXX) $(CXXFLAGS) tests/basic.cpp


clean :
	-rm -f *.o $(EXENAME) test
