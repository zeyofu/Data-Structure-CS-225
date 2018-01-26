#include "StickerSheet.h"
using namespace cs225;
using namespace std;

int main() {
  Image picture;
  Image sticker1;
  Image sticker2;
  Image sticker3;
  picture.readFromFile("alma.png");

// cout<<picture.width()<<picture.getPixel(12,52)->h<<endl;
// cout<<picture.width()<<picture.getPixel(12,52)->l<<endl;
// cout<<picture.width()<<picture.getPixel(402,52)->h<<endl;
// cout<<picture.width()<<picture.getPixel(402,52)->l<<endl;

//picture.writeToFile("base.png");

  sticker1.readFromFile("Wade2.png");

// cout<<sticker1.width()<<sticker1.getPixel(2,2)->h<<endl;
// cout<<sticker1.width()<<sticker1.getPixel(2,2)->l<<endl;


  sticker2.readFromFile("Biubiu.png");
  sticker3.readFromFile("3.png");

  StickerSheet sheet(picture, 5);

  sheet.addSticker(sticker1, 400, 50);
  // sheet.addSticker(sticker1, 400, 50);
  // sheet.addSticker(sticker1, 310, 450);

  sheet.addSticker(sticker2, 100, 350);
  sheet.addSticker(sticker3, 600, 340);
  Image output = sheet.render();
// cout<<output.width()<<output.getPixel(12,52)->h<<endl;
// cout<<output.width()<<output.getPixel(12,52)->l<<endl;
// cout<<output.width()<<output.getPixel(402,52)->h<<endl;
// cout<<output.width()<<output.getPixel(402,52)->l<<endl;


  output.writeToFile("myImage.png");
  return 0;
}
