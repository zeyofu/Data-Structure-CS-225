#include "HSLAPixel.h"
namespace cs225{
	HSLAPixel::HSLAPixel(){
		a=1.0;
		h=0.0;
		s=0.0;
		l=1.0;
	}

	HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
		a=1.0;
		s=saturation;
		l=luminance;
		h=hue;
	}

	HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
		h=hue;
		s=saturation;
		l=luminance;
		a=alpha;
	}
}
	
