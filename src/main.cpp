#include <iostream>
#include "Math/Vector2D.h"
#include "Game.h"

using namespace std;

int main()
{
	Game game;
	game.Initialize("tycoon");
	game.Run();

}