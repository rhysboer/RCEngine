#pragma once
#include "RCEngine.h"
#include <iostream>

#include "SpriteSheet.h"
#include "TileMap.h"

class MyGame : public RCEngine {
public:
	MyGame();
	~MyGame();

private:
	// Inherited via RCEngine
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;


	//Circle myCircleObject;
	//Square* mySquareObject;
	//Line myLineObject;
	Object2D* myBox;
	Sprite sprite;
	Sprite sprite2;

	bool render = true;

	SpriteSheet* sheet = nullptr;
	TileMap* map = nullptr;
	ColourPalette palette;

	Vector2 position = Vector2();
};

