#include "TileMap.h"

TileMap::TileMap() {
	//m_tiles = std::vector<Tile*>();
	m_data = std::vector<TileData>();
}

TileMap::~TileMap() {
}

bool TileMap::LoadMap(const char * path, SpriteSheet* sprites) {
	if (sprites == nullptr)
		return false;

	// Map Data
	std::fstream file;
	file.open(path, std::fstream::in);

	if (file.is_open()) {

		const char div = '|';
		const char brk = ',';

		int width = -1;
		int height = -1;

		std::string buffer = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();

		if (buffer.length() <= 0)
			return false;

		int eol = buffer.find(div, 0); // End of line index
		if (eol <= 0)
			return false;

		// Find tile width
		std::string line; // Current line
		line = buffer.substr(0, eol);

		int break1 = line.find(brk, 0);
		int break2;
		int eolNext;

		width = std::stoi(line.substr(0, break1));
		height = std::stoi(line.substr(break1 + 1));
		
		eolNext = buffer.find(div, eol + 1);
		if (eolNext <= 0 || width <= 0 || height <= 0)
			return false;

		line = buffer.substr(eol + 1, eolNext - eol - 1);
		eol = eolNext;

		int index = 0;

		// SPRITE_INDEX, COLLISION, LAYER|
		while(line.length() > 0) {
			break1 = line.find(brk, 0);
			//break2 = line.find(brk, break1 + 1);

			std::string data;

			// Sprite Index
			data = line.substr(0, break1);
			int spriteIndex = std::stoi(data);
			
			// Collision
			data = line.substr(break1 + 1, eolNext);
			int collision = std::stoi(data);
		
			// Add data
			TileData maptile = TileData();
			maptile.spriteIndex = spriteIndex;

			Vector2 pos;
			pos.Y = floor(index / width) * sprites->GetTileSize().Y;
			pos.X = (index % width) * sprites->GetTileSize().X;

			Tile* tile = new Tile(sprites->GetSprite(spriteIndex), pos, 0x2588);
			tile->SetCollision(collision);

			maptile.tile = tile;

			m_data.push_back(maptile);

			// Get next line
			eolNext = buffer.find(div, eol + 1);
			if (eolNext <= 0)
				break;

			line = buffer.substr(eol + 1, eolNext - eol - 1);
			eol = eolNext;
			index++;
		}


		return true;
	}

	return false;
}

const std::vector<TileData> TileMap::GetTiles() const {
	return m_data;
}
