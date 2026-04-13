#include "tileset/tileset.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) :
      tileWidth(tileWidth),
      tileHeight(tileHeight),
      tileCount(0)
{
    tileSet.Open(file);
    if (tileSet.isOpen()) {
        int cols = tileSet.GetWidth() / tileWidth;
        int rows    = tileSet.GetHeight() / tileHeight;

        tileCount = cols * rows;

        tileSet.SetFrameCount(cols, rows);
    }
}

void TileSet::RenderTile (unsigned index, float x, float y ){
    if (index >= (unsigned)tileCount) return; 
    tileSet.SetFrame(index);
    tileSet.Render((int)x,(int)y,GetTileWidth(),GetTileHeight());
}

int TileSet::GetTileWidth (){
    return this->tileWidth;
}

int TileSet::GetTileHeight(){
    return this->tileHeight;
}