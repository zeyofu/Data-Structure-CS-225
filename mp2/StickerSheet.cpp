#include <iostream>
#include "StickerSheet.h"

using namespace std;
namespace cs225 {
  void StickerSheet::_copy(StickerSheet const & other){
    sticker_max = other.sticker_max;
    sticker_ct = other.sticker_ct;
    //lowest = other.lowest;
    count = new int[sticker_max];
    stickers = new Image*[sticker_max];
    xPos = new int[sticker_max];
    yPos = new int[sticker_max];
    picture = new Image(*(other.picture));
    for (unsigned i = 0; i < sticker_max ; i++) {
      if (other.count[i] != 0){
        stickers[i] = new Image(*(other.stickers[i]));
        xPos[i] = other.xPos[i];
        yPos[i] = other.yPos[i];
        count[i] = other.count[i];
      } else{
        count[i] = 0;
        xPos[i] = 0;
        yPos[i] = 0;
        stickers[i] = NULL;
      }
    }
  }

  void StickerSheet::_destroy() {
    for (unsigned i = 0; i < sticker_max; i++) {
      if (count[i] != 0) {
        delete stickers[i];
        stickers[i] = NULL;
      }
    }
    delete[] stickers;
    delete[] xPos;
    delete[] yPos;
    delete[] count;
    delete picture;
    stickers = NULL;
    xPos = NULL;
    yPos = NULL;
    count = NULL;
    picture = NULL;
    }

  StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    sticker_ct = 0;
    sticker_max = max;
    xPos = new int[sticker_max];
    yPos = new int[sticker_max];
    count = new int[sticker_max];
    stickers = new Image*[sticker_max];
    for (unsigned i = 0; i < max; i++) {
	     stickers[i] = NULL;
       count[i] = 0;
	     xPos[i] = 0;
	     yPos[i] = 0;
    }
    this->picture = new Image(picture);
  }

  StickerSheet::~StickerSheet() {
    _destroy();
  }

  StickerSheet::StickerSheet(const StickerSheet & other) {
    _copy(other);
  }

  const StickerSheet& StickerSheet::operator=(const StickerSheet & other){
      if (this == &other) {
	       return *this;
      } else {
      _destroy();
      //picture = NULL;
      _copy(other);
      return *this;
      }
  }

  void StickerSheet::changeMaxStickers(unsigned max){

    if (max == sticker_max) return;

    Image* *newStickers = new Image*[max];
    int* newX = new int[max];
    int* newY = new int[max];
    int* newC = new int[max];
    unsigned newSticker_ct = 0;
    Image* newPicture = new Image(*picture);

    if (max < sticker_max) {
      for (unsigned j = max; j < sticker_max; j++){
        if (count[j] != 0) {
          delete stickers[j];
          stickers[j] = NULL;
          count[j]--;
        }
      }
      sticker_max = max;
    }
    if (max > sticker_max) {
      for (unsigned j = 0; j < max; j++){
          newStickers[j] = NULL;
          newC[j] = 0;
        }
      }
      for (unsigned i = 0; i < sticker_max ; i++) {
        if (count[i]!=0){
          newStickers[i] = new Image(*stickers[i]);
          newX[i] = xPos[i];
          newY[i] = yPos[i];
          newC[i] = count[i];
          newSticker_ct++;
        }
        else{
          newC[i] = 0;
        }
      }
    _destroy();
    sticker_max = max;
    stickers = newStickers;
    xPos = newX;
    yPos = newY;
    count = newC;
    sticker_ct = newSticker_ct;
    picture = newPicture;
  }

  int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
    if (sticker_ct < sticker_max) {
      for (unsigned i = 0; i < sticker_max; i++){
	       if (count[i] == 0) {
		         stickers[i] = new Image(sticker);
		         xPos[i] = x;
		         yPos[i] = y;
             count[i]++;
             sticker_ct ++;
             return i;
	       }
       }
     }
     return -1;
  }

  bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if (index < sticker_max && count[index] != 0) {
      xPos[index] = x;
      yPos[index] = y;
      return true;
    } else return false;
  }

  void StickerSheet::removeSticker(unsigned index){
    if (index < sticker_max && count[index] != 0){
	     delete stickers[index];
       stickers[index] = NULL;
	     xPos[index] = 0;
	     yPos[index] = 0;
       count[index]--;
     	 sticker_ct--;
	//for (unsigned i = index; i < sticker_ct; i++){
	//  stickers[i] = stickers[i+1];
	//  xPos[i] = xPos[i+1];
	//  yPos[i] = yPos[i+1];}
    }
  }

  Image * StickerSheet::getSticker(unsigned index) const{
    if (index >= sticker_max || count[index] == 0) return NULL;
    return stickers[index];
  }

  Image StickerSheet::render() const{
//Get the width and height of the output image, considering all stickers.
    unsigned xMost = picture->width();
    unsigned yMost = picture->height();
    for (unsigned i = 0; i < sticker_max; i++){
// cout<<i<<endl;
// cout<<sticker_max<<endl;
      if (count[i] != 0){
        unsigned x = xPos[i] + stickers[i]->width();
        unsigned y = yPos[i] + stickers[i]->height();
        if (xMost < x) xMost = x;
        if (yMost < y) yMost = y;
      }
    }
    Image *output = new Image(*picture);
    output->resize(xMost,yMost);

    //Loop through the stickers and change the hsla pixel values in output.
    for (unsigned j = 0; j < sticker_max; j++) {
      if (count[j] != 0) {
      Image sticker = *stickers[j];
      for (unsigned m = xPos[j]; m < xPos[j] + sticker.width(); m++) {
        for (unsigned n = yPos[j]; n < yPos[j] + sticker.height(); n++) {
          HSLAPixel *pixel = sticker.getPixel(m-xPos[j],n-yPos[j]);
          HSLAPixel *curr = output->getPixel(m,n);
		      if (pixel->a != 0) {
//cout<<curr->h<<endl;
//cout<<pixel->h<<endl;
		      curr->h = pixel->h;
		      curr->s = pixel->s;
		      curr->l = pixel->l;
          	      curr->a = pixel->a;
//cout<<curr->h<<endl;
		     }
        }
      }
    }
    }
    Image toOut = *output;
    delete output;
    output = NULL;
    return toOut;
  }
}
