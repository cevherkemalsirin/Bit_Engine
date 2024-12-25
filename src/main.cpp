#include <iostream>
#include "Math/Vector2D.h"
#include "Game.h"
#include "Graphics/Color.h"

using namespace std;

int main()
{
	Game game;
	game.Initialize("tycoon");
	game.Run();

}