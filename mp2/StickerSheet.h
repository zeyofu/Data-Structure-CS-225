#ifndef STICKERSHEET_H
#define STICKERSHEET_H
#include "Image.h"

using namespace std;
namespace cs225 {
class StickerSheet{
  public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet& operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index) const;
    Image render() const;

  private:
    Image* *stickers;
    void _copy(StickerSheet const & other);
    void _destroy();
    unsigned sticker_max;
    unsigned sticker_ct;
    int *xPos;
    int *yPos;
    Image *picture;
    int *count;
    //unsigned lowest;
};
}
#endif
