#pragma once
#include "gameObject/gameObject.h"
#include "tileset/tileset.h"
#include <vector>
#include <memory>

class TileMap : public Component{
    public:
        TileMap(GameObject & associated, std::string file, TileSet* tileSet);
        void Load(std::string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        void Update(float dt);
        void Render();
        void RenderLayer(int layer);
        int GetWidth();
        int GetHeight();
        int GetDepth();

    private:
        std::vector<int> tileMatrix;
        std::unique_ptr<TileSet> tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
};