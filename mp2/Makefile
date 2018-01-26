EXENAME = mp2
OBJS += PNG.o HSLAPixel.o lodepng.o
OBJS += Image.o StickerSheet.o main.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

# mp2
main.o : main.cpp Image.h StickerSheet.h
	$(CXX) $(CXXFLAGS) main.cpp

Image.o : Image.cpp Image.h cs225/PNG.h
	$(CXX) $(CXXFLAGS) Image.cpp

StickerSheet.o : StickerSheet.cpp StickerSheet.h Image.h
	$(CXX) $(CXXFLAGS) StickerSheet.cpp

mp2-1.o: mp2-1.cpp Image.h
	$(CXX) $(CXXFLAGS) mp2-1.cpp

mp2-1: mp2-1.o Image.o PNG.o HSLAPixel.o lodepng.o
	$(LD) $^ $(LDFLAGS) -o mp2-1	


# cs225 
PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp


# test cases
unit_tests.o : $(OBJS)
	$(CXX) $(CXXFLAGS) tests/unit_tests.cpp
	
test : unit_tests.o PNG.o HSLAPixel.o lodepng.o Image.o StickerSheet.o
	$(LD) $^ $(LDFLAGS) -o test


clean :
	-rm -f *.o $(EXENAME) test
