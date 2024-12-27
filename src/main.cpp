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
    thescreen.Init(224, 288, 2);
	//thescreen.SetClearColor(Color::Orange());
	thescreen.Draw(Line2D(Vector2D(0, 0), Vector2D(224, 288)));
    thescreen.RenderScreen();
   

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