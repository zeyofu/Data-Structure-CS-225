/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    if (theTiles.empty()) return NULL;

    map<Point<3>, int> tileMap;
    vector<Point<3>> tiles;
    tiles.resize(theTiles.size());
    for (size_t i = 0; i < theTiles.size(); i++) {
      HSLAPixel p = theTiles[i].getAverageColor();
      double arr [3] = { p.h / 360, p.s, p.l};
      Point<3> point(arr);
// cout<<point<<endl;
      tiles.push_back(point);
      tileMap[point] = i;
    }
    KDTree<3> tree(tiles);
// cout<<tree<<endl;
    int row = theSource.getRows();
    int col = theSource.getColumns();
    MosaicCanvas* canvas = new MosaicCanvas(row, col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        HSLAPixel pixel = theSource.getRegionColor(i, j);
        Point<3> query(pixel.h * 1.0 / 360, pixel.s * 1.0, pixel.l * 1.0);
        canvas->setTile(i, j, theTiles[tileMap[tree.findNearestNeighbor(query)]]);
      }
    }
    return canvas;
}
