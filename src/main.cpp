#include <iostream>
#include "Math/Vector2D.h"
#include "Shapes/Star2D.h"
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
    thescreen.Init(224, 288, 3);
	//thescreen.SetClearColor(Color::Orange());
	Line2D line(Vector2D(112,40), Vector2D(112, 90));
	float rotateAngle = 0.005f;
	
	Star2D star(Vector2D(112, 144), 7);
	thescreen.Draw(star, Color::Green());
	line.Rotate(0.63,line.GetPointStart());
	thescreen.Draw(line, Color::Purple());
	thescreen.RenderScreen();


	Vector2D point = Vector2D(105,50);

	SDL_Event sdlEvent;
	bool running = true;
	while (running)
	{
		/*line.Rotate(rotateAngle, point);
		thescreen.Draw(line);

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