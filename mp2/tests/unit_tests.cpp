#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Image.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

using namespace cs225;

Image createRainbowImage() {
  Image png;
  png.resize(360, 100);

  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel * pixel = png.getPixel(x, y);
      pixel->h = x;
      pixel->s = y / 100.0;
      pixel->l = y / 100.0;
    }
  }
  return png;
}


//
// lighten, darken
//
TEST_CASE("Image lighten() lightens pixels by 0.1", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.lighten();

  REQUIRE( img.getPixel(10, 10)->l + 0.1 == result.getPixel(10, 10)->l );
}

TEST_CASE("Image lighten() does not lighten a pixel above 1.0", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.lighten();

  REQUIRE( 1.0 == result.getPixel(10, 95)->l );
}

TEST_CASE("Image darken(0.2) darkens pixels by 0.2", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.darken(0.2);

  REQUIRE( img.getPixel(50, 50)->l - 0.2 == result.getPixel(50, 50)->l );
}

TEST_CASE("Image darken(0.2) does not darken a pixel below 0.0", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.darken(0.2);

  REQUIRE( 0 == result.getPixel(5, 5)->l );
}


//
// saturate, desaturate
//
TEST_CASE("Image saturate() saturates a pixels by 0.1", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.saturate();

  REQUIRE( img.getPixel(10, 10)->s + 0.1 == result.getPixel(10, 10)->s );
}


//
// rotateColor
//
TEST_CASE("Image rotateColor(double) rotates the color", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.rotateColor(90);

  REQUIRE( img.getPixel(90, 90)->h + 90 == result.getPixel(90, 90)->h );
}

TEST_CASE("Image rotateColor(double) keeps the hue in the range [0, 360]", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.rotateColor(90);
  REQUIRE( result.getPixel(340, 90)->h == 70 );

  result.rotateColor(-180);
  REQUIRE( result.getPixel(10, 90)->h == 280 );
}


//
// scale
//
TEST_CASE("Image scale(2.0) results in the correct width/height", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(2.0);

  REQUIRE( img.height() * 2 == result.height() );
}

TEST_CASE("Image scale(0.5) results in the correct width/height", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(0.5);

  REQUIRE( img.height() * 0.5 == result.height() );
}

TEST_CASE("Image scale(2) scales pixel data in a reasonable way", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(2);

  REQUIRE( result.getPixel(100, 100)->h > 40 );
  REQUIRE( result.getPixel(100, 100)->h < 60 );
}

TEST_CASE("Image scale(0.5) scales pixel data in a reasonable way", "[weight=1][part=1]") {
  Image img = createRainbowImage();
  
  Image result = createRainbowImage();
  result.scale(0.5);

  REQUIRE( result.getPixel(100, 20)->h > 180 );
  REQUIRE( result.getPixel(100, 20)->h < 220 );
}


// Part 2 Testing:
#include "../StickerSheet.h"


TEST_CASE("A basic StickerSheet works", "[weight=5][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  Image expected;
  expected.readFromFile("tests/expected.png");
  
  REQUIRE( sheet.render() == expected );
}


TEST_CASE("StickerSheet::changeMaxStickers() does not discard stickers when resized larger", "[weight=1][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  
  sheet.changeMaxStickers(7);
  
  Image expected;
  expected.readFromFile("tests/expected.png");
  
  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::changeMaxStickers() does not discard original stickers when resized smaller", "[weight=1][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  
  sheet.changeMaxStickers(3);
  
  Image expected;
  expected.readFromFile("tests/expected.png");
  
  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::changeMaxStickers() can increase the number of stickers on an image", "[weight=1][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 1);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(2);
  sheet.addSticker(i, 40, 200);
  
  Image expected;
  expected.readFromFile("tests/expected-2.png");
  
  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::changeMaxStickers() discards stickers beyond the end of a smaller StickerSheet", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.changeMaxStickers(1);  
  
  REQUIRE( sheet.render() == expected );
}







//
// test removeSticker
//
TEST_CASE("StickerSheet::removeSticker() can remove the last sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200); 
  sheet.addSticker(i, 50, 200);
  sheet.removeSticker(1);

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::removeSticker() can remove the first sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200); 
  sheet.addSticker(i, 20, 200);
  sheet.removeSticker(0);

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::removeSticker() can remove all stickers", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200); 
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 80, 200);
  sheet.removeSticker(2);
  sheet.removeSticker(1);
  sheet.removeSticker(0);
  
  REQUIRE( sheet.render() == alma );
}



//
// test that getSticker works
//
TEST_CASE("StickerSheet::getSticker() returns the sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200); 

  REQUIRE( *(sheet.getSticker(0)) == i );
}

TEST_CASE("StickerSheet::getSticker() returns NULL for a non-existant sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200); 

  REQUIRE( sheet.getSticker(1) == NULL );  
}

TEST_CASE("StickerSheet::getSticker() returns NULL for a removed sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200); 
  sheet.removeSticker(0);
  
  REQUIRE( sheet.getSticker(0) == NULL );  
}


//
// translate
//
TEST_CASE("StickerSheet::translate() translates a sticker's location", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 0, 0);
  sheet.translate(0, 20, 200);
  
  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::translate() returns false for a non-existant sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  
  REQUIRE( sheet.translate(3, 20, 200) == false );
}


//
// render
//
TEST_CASE("A complex StickerSheet is correct", "[weight=5][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected-3.png");
  
  StickerSheet sheet(alma, 100);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.addSticker(i, 80, 200);
  sheet.addSticker(i, 100, 200);
  sheet.addSticker(i, 120, 200);
  sheet.addSticker(i, 140, 200);
  sheet.removeSticker(3);
  sheet.translate(0, 0, 0);
  
  REQUIRE( sheet.render() == expected );
}


//
// copy ctor
//
TEST_CASE("StickerSheet's copy constructor makes an independent copy", "[weight=2][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  Image expected2; expected2.readFromFile("tests/expected-2.png");
  
  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(s1);
  s2.removeSticker(1);
  
  REQUIRE( s1.render() == expected2 );
  REQUIRE( s2.render() == expected );  
}

TEST_CASE("StickerSheet's assignment operator makes an independent copy", "[weight=2][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  Image expected2; expected2.readFromFile("tests/expected-2.png");
  
  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(alma, 5);
  s2 = s1;
  s2.removeSticker(1);
  
  REQUIRE( s1.render() == expected2 );
  REQUIRE( s2.render() == expected );  
}

