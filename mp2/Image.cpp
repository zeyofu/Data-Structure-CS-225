#include <iostream>
#include "Image.h"
#include <math.h>

using namespace std;
namespace cs225 {
  //
  // Image(unsigned int width, unsigned int height){
  //
  // }

  void Image::lighten(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel ->l += 0.1;
          if (pixel->l > 1) pixel->l=1;
      }
    }
  }

  void Image::lighten(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel ->l += amount;
          if (pixel->l > 1) pixel->l=1;
      }
    }
  }

  void Image::darken(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel ->l -= 0.1;
          if (pixel->l < 0) pixel->l=0;
      }
    }
  }

  void Image::darken(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel ->l -= amount;
          if (pixel->l < 0) pixel->l=0;
      }
    }
  }

  void Image::saturate(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel ->s += 0.1;
          if (pixel->s > 1) pixel->s=1;
      }
    }
  }

  void Image::saturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel ->s += amount;
          if (pixel->s > 1) pixel->s=1;
      }
    }
  }

  void Image::desaturate(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel ->s -= 0.1;
          if (pixel->s < 0) pixel->s = 0;
      }
    }
  }

  void Image::desaturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel ->s -= amount;
          if (pixel->s < 0) pixel->s = 0;
      }
    }
  }

  void Image::grayscale(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel ->s -= 0;
      }
    }
  }

  void Image::rotateColor(double degrees){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          pixel->h += degrees;
          while (pixel->h < 0){
            pixel->h+=360;
          }
          pixel->h = fmod( pixel->h, 360);
      }
    }
  }

  void Image::illinify(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *pixel = this->getPixel(x, y);
          if (pixel->h >= 114 && pixel->h <= 243) pixel->h = 216;
          else pixel->h = 11;
      }
    }
  }

//when the function scales down, it uses the first pixel in each block and therefore loses 75% original data...
  void  Image::scale(double factor) {
    //cout<<factor<<endl;
    PNG * original = new PNG(*this);
    this->resize(ceil(factor*width()),ceil(factor*height()));
    if (factor > 0 && factor < 1) {
      cout<<width()<<height()<<endl;
      for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
          HSLAPixel *newPixel = this->getPixel(x,y);
          HSLAPixel *pixel = original->getPixel(ceil(x/factor), ceil(y/factor));
          newPixel->h = pixel->h;
          newPixel->s = pixel->s;
          newPixel->l = pixel->l;
          newPixel->a = pixel->a;
        }
      }
    }
    if (factor > 1){
      for (unsigned x = 0; x < (width()/factor); x++) {
        for (unsigned y = 0; y < (height()/factor); y++) {
          HSLAPixel pixel = *(original->getPixel(x, y));
          for (unsigned i =0; i < ceil(factor); i++){
            for (unsigned j =0; j < ceil(factor); j++){
                HSLAPixel *newPixel = this->getPixel(x*factor+i,y*factor+j);
                //*newPixel = *pixel;
                newPixel->h = pixel.h;
                newPixel->s = pixel.s;
                newPixel->l = pixel.l;
                newPixel->a = pixel.a;
            }
          }
        }
      }
    }

    delete original;
    original = NULL;
  }

  void Image::scale (unsigned w, unsigned h){
    double wF = ((double)(w*1.0)) / ((double)width()*1.0);
    double hF = ((double)(h*1.0)) / ((double)height()*1.0);
    //cout<<wF<<hF<<endl;
    if (wF < hF)
      scale(wF);
    else scale(hF);
  }
}
