#include "tilemap/tilemap.h"
#include "tileset/tileset.h"
#include "fstream"


TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet): Component(associated){
    Load(file);
    SetTileSet(tileSet);
}
void TileMap::Load(std::string file){
    std::ifstream mapFile(file);
    if (!mapFile.is_open()) return;

    char comma;

    mapFile >> mapWidth >> comma
            >> mapHeight >> comma
            >> mapDepth;

    tileMatrix.clear();

    int tile;
    while (mapFile >> comma >> tile) {
        this->tileMatrix.push_back(tile-1);
    }
    mapFile.close();

}
void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z){
    int index = z * mapWidth * mapHeight
              + y * mapWidth
              + x;

    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer){
    if(!tileSet) return;
    int tileH = this->tileSet.get()->GetTileHeight();
    int tileW = this->tileSet.get()->GetTileWidth();

    for(int y =0; y < GetHeight(); y++){
        for (int x = 0; x < GetWidth(); x++){
            int index = At(x,y,layer);
            if(index == -1) continue;
            int tileIndex = At(x,y,layer);
            float worldX = associated.box.getX() + x * tileW;
            float worldY = associated.box.getY() + y * tileH;
            tileSet->RenderTile(tileIndex,worldX,worldY);
        }
    }
}

void TileMap::Render(){
    for(int z = 0; z < GetDepth(); z++){
        RenderLayer(z);
    }
}

void TileMap::Update(float dt){}

int TileMap::GetWidth(){
    return this->mapWidth;
}
int TileMap::GetHeight(){
    return this->mapHeight;
}
int TileMap::GetDepth(){
    return this->mapDepth;
}   