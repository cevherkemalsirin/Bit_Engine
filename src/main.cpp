#include <iostream>
#include "Math/Vector2D.h"
#include "Game.h"
#include "Graphics/Color.h"
#include "Graphics/Screen.h"
#include "stdint.h"
#include "SDL.h"
#include "Graphics/Shapes/Line2D.h"

using namespace std;

int main(int argc, char* argv[])
{
    Screen thescreen;
    thescreen.Init(224, 288, 10);
    thescreen.Draw(112, 144, Color::Orange());
    thescreen.RenderScreen();
   
	Line2D line1(3, 5, 14, 12);
	Vector2D point(6, 14);

	line1.ClosestPoint(point);

	SDL_Event sdlEvent;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
				case SDL_QUIT:
				{
					running = false;
					break;
				}
				case SDL_KEYDOWN:
				{
					if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					{
						running = false;
						break;
					}
				}
			}
		}
	}


	return 0;
}