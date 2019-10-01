#include "MyGame.h"



MyGame::MyGame() {
}


MyGame::~MyGame() {
}

void MyGame::OnStart() {
	std::vector<Vector2> points = std::vector<Vector2>();
	points.push_back(Vector2(-5, 5));
	points.push_back(Vector2(5, 5));
	points.push_back(Vector2(5, -5));
	points.push_back(Vector2(-5, -5));

	//myGameObject = Object2D(Vector2(10, 10), points, 0x2588, Colour::FG_RED);
	//myGameObject = Object2D(Vector2(10, 10), VectorShapes::Square(15, 3), 0x2588, Colour::FG_RED);

	//mySquareObject = Square(Vector2(10, 10), Vector2(5, 5), 0x2588, Colour::FG_RED);
	//myCircleObject = Circle(Vector2(10, 10), 10, 0x2588, Colour::FG_RED);
	//myLineObject = Line(Vector2(50, 70), 10, 0, 0x2588, Colour::FG_RED);

	myBox = Object2DManager()->CreateCircle(Vector2(GetScreenResolution().X / 2.0f - 60, -10.0f), 5, 0x2588, PaletteIndex::FG_BLUE);
	//myBox->UsePhysics(true);
	//myBox->UseCollision(true);

	Object2D* box1 = Object2DManager()->CreateCircle(Vector2(GetScreenResolution().X / 2.0f - 40, -10.0f), 5, 0x2588, PaletteIndex::FG_RED);
	Object2D* box2 = Object2DManager()->CreateCircle(Vector2(GetScreenResolution().X / 2.0f - 20, -10.0f), 5, 0x2588, PaletteIndex::FG_PURPLE);
	//Object2D* box3 = Object2DManager()->CreateCircle(Vector2(GetScreenResolution().X / 2.0f - 0,  10.0f), 5, 0x2588, Colour::FG_GREEN);
	Object2D* box4 = Object2DManager()->CreateCircle(Vector2(GetScreenResolution().X / 2.0f + 20, -10.0f), 5, 0x2588, PaletteIndex::FG_YELLOW);
	Object2D* box5 = Object2DManager()->CreateCircle(Vector2(GetScreenResolution().X / 2.0f + 40, -10.0f), 5, 0x2588, PaletteIndex::FG_CYAN);
	Object2D* box6 = Object2DManager()->CreateCircle(Vector2(GetScreenResolution().X / 2.0f + 60, -10.0f), 5, 0x2588, PaletteIndex::FG_GREY);

	//box1->UseCollision(true);
	//box2->UseCollision(true);
		//box3->UseCollision(true);
	//box4->UseCollision(true);
	//box5->UseCollision(true);
	//box6->UseCollision(true);
	//
	//box1->UsePhysics(true);
	//box2->UsePhysics(true);
		//box3->UsePhysics(true);
	//box4->UsePhysics(true);
	//box5->UsePhysics(true);
	//box6->UsePhysics(true);
	
	//Object2DManager()->CreateLine(Vector2(0, GetScreenResolution().Y / 2), Vector2(GetScreenResolution().X / 2, GetScreenResolution().Y - 1), 0x2588, Colour::FG_GREEN)->UseCollision(true);
	//Object2DManager()->CreateLine(Vector2(GetScreenResolution().X / 2, GetScreenResolution().Y - 1), Vector2(GetScreenResolution().X, GetScreenResolution().Y / 2), 0x2588, Colour::FG_GREEN)->UseCollision(true);


	ColourPalette palette = ColourPalette();
	palette.AddPalette("C:/Users/Rhys/Desktop/rcengine/zelda_palette.bmp");	
	RCSetPalette(palette);



	sheet = new SpriteSheet();
	sheet->LoadSpriteSheet(5, 4, 16, 16, "C:/Users/Rhys/Desktop/rcengine/zelda_tilemap.bmp", palette.ColourRef);


	sprite = Sprite();
	sprite2 = Sprite();

	sprite.LoadSprite("C:/Users/Rhys/Desktop/rcengine/spritesheet.bmp", true);
	sprite2.LoadSprite("C:/Users/Rhys/Desktop/rcengine/tile_1.bmp", true);



	map = new TileMap();
	map->LoadMap("C:/Users/Rhys/Desktop/rcengine/mapdata.txt", sheet);

}

void MyGame::OnUpdate() {
	RCClear();
	//RCDrawSquare(0, 0, GetScreenResolution().X, GetScreenResolution().Y, 0x2588, RCColours::FG_BLACK);
	
	//RCDrawLine(GetScreenResolution().X / 2, GetScreenResolution().Y / 2, position.X, position.Y, 0x2588, Colour::FG_RED);
	
	Vector2 vec = Vector2();
	float speed = 30.0f;

	//RCDrawSprite(Vector2(30, 10), sheet->GetSprite(0), 0x2588);
	//RCDrawSprite(Vector2(30, 20), sheet->GetSprite(1), 0x2588);
	//RCDrawSprite(Vector2(30, 30), sheet->GetSprite(2), 0x2588);
	//RCDrawSprite(Vector2(30, 40), sheet->GetSprite(3), 0x2588);
	RCDrawTileMap(map);

	//for (int i = 0; i < 32; i++) {
	//	RCDrawChar(i, 25, 0x2588, i);
	//}

	// Scale
	if (Input()->IsKeyHeld(KeyCodes::KEY_R)) {
		myBox->Scale(Vector2(0.1f, 0.1f));
	}
	if (Input()->IsKeyHeld(KeyCodes::KEY_F)) {
		myBox->Scale(Vector2(-0.1f, -0.1f));
	}

	if (Input()->IsKeyHeld(KeyCodes::KEY_G)) {
		myBox->AddForce(Vector2(0, -500));
	}

	// Movement
	if (Input()->IsKeyHeld(KeyCodes::KEY_W)) {
		vec.Y -= 1;
	}
	
	if (Input()->IsKeyHeld(KeyCodes::KEY_S)) {
		vec.Y += 1;
	}
	
	if (Input()->IsKeyHeld(KeyCodes::KEY_D)) {
		vec.X += 1;
	}
	
	if (Input()->IsKeyHeld(KeyCodes::KEY_A)) {
		vec.X -= 1;
	}
	
	if (Input()->IsKeyHeld(KeyCodes::KEY_E)) {
		myBox->Rotate(0.1f);
	} else if (Input()->IsKeyHeld(KeyCodes::KEY_Q)) {
		myBox->Rotate(-0.1f);
	}
	
	
	if (myBox->GetPosition().Y > GetScreenResolution().Y + 15) {
		myBox->SetPosition(Vector2(myBox->GetPosition().X, -15.0f));
	}
	
	vec *= speed * RCEngine::DeltaTime();
	myBox->Translate(vec);
}

void MyGame::OnExit() {
}
