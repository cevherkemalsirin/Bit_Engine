#include <iostream>
#include "Math/Vector2D.h"
#include "Shapes/Star2D.h"
#include "Shapes/Triangle.h"
#include "Game.h"
#include "Shapes/rectangle2D.h"
#include "Graphics/Color.h"
#include "Graphics/Screen.h"
#include "Shapes/Circle2D.h"
#include "stdint.h"
#include "SDL.h"
#include "Graphics/Shapes/Line2D.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Use the singleton instance of Screen
    Screen::Instance().Init(224, 288, 2);


	Triangle2D triangle(Vector2D(10, 10), Vector2D(20, 10), Vector2D(15, 20));
	Screen::Instance().Draw(&triangle, Color::Green(), true, Color::Green(), true);


	Screen::Instance().RenderScreen();

	SDL_Event sdlEvent;
	bool running = true;
	while (running)
	{
		/*line.Rotate(rotateAngle, point);
		Screen::Instance().Draw(line);

	   */
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