#pragma once
#include <vector>
#include <fstream>
#include "SpriteSheet.h"
#include "Tile.h"

struct TileData {
	int spriteIndex;
	Tile* tile;
};

class TileMap {
public:
	TileMap();
	~TileMap();
	
	bool LoadMap(const char* path, SpriteSheet* sprites);

	const std::vector<TileData> GetTiles() const;

	Tile* TileAtIndex(Vector2 index) const;
	Tile* GetNearestTile(Vector2 pos) const;


private:

	std::string m_name;
	Vector2 m_position;	// Top left position of the map
	Vector2 m_size; // Amount of tiles width/height in the map

	std::vector<TileData> m_data;

	bool m_renderCollision;
};

