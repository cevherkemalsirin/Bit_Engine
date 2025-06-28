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
    Screen thescreen;
    thescreen.Init(224, 288, 2);
	/*
	
	//thescreen.SetClearColor(Color::Orange());
	Line2D line(Vector2D(112,40), Vector2D(112, 90));
	float rotateAngle = 0.005f;
	
	Star2D star(Vector2D(112, 144), 7);
	thescreen.Draw(star, Color::Green());
	line.Rotate(0.63,line.GetPointStart());
	thescreen.Draw(line, Color::Purple());

	Vector2D point = Vector2D(105,50);

	*/
	Star2D star2D(Vector2D(112, 144), 5);
	Rectangle2D starBox = star2D.GetBoundingBox();
	thescreen.Draw(&star2D, Color::Green(), true);
	thescreen.Draw(&starBox, Color::Green(), false);

	//Triangle2D* tri = new Triangle2D(Vector2D(112, 40), Vector2D(112, 10), Vector2D(150, 40));
	Triangle2D tri2(Vector2D(112, 40), Vector2D(112, 10), Vector2D(150, 40));
	Circle2D circ(Vector2D(112, 144), 50.0f);
	//Rectangle2D rec(Vector2D(50, 50), Vector2D(100, 100));
	thescreen.Draw(&tri2, Color::Orange(), true, Color(255,0,0,125));
	thescreen.Draw(circ, 0.5f, Color::Blue(), true, Color(255, 0, 0, 150));
	thescreen.RenderScreen();

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