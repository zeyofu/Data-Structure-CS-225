#include <string>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;
using namespace std;

void rotate(std::string inputFile, std::string outputFile) {
  
    PNG* original = new PNG();
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();

    PNG* output = new PNG(width, height);

    for (unsigned x=0; x<width;x++){
	for (unsigned y=0;y<height;y++){
	HSLAPixel* prev = original->getPixel(x,y);
	HSLAPixel* out = output->getPixel(width-1-x,height-1-y);
	*out = *prev;
	}
    }

    output->writeToFile(outputFile);

    delete output;
    delete original;
}
