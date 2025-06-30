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
#include <algorithm>
#include "Graphics/Shapes/Line2D.h"

using namespace std;

vector<Star2D> GetSortedStars(unsigned int starNum)
{
	vector<Star2D> stars;
	for (unsigned int i = 0; i < starNum; ++i)
	{
		stars.push_back(Star2D::GenerateStar());
	}
	//sort the stars by radius
	std::sort(stars.begin(), stars.end(), [](const Star2D& a, const Star2D& b) {
		return a.GetRadius() < b.GetRadius();
	});
	return stars;
}

int main(int argc, char* argv[])
{
    // Use the singleton instance of Screen
    Screen::Instance().Init(224, 288, 2);


	Triangle2D triangle(Vector2D(10, 10), Vector2D(20, 10), Vector2D(30, 40));
	Rectangle2D rectangle(Vector2D(50, 50), Vector2D(100, 100));
	Screen::Instance().Draw(&rectangle, Color::Blue(), true, Color::Blue(), true);
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




