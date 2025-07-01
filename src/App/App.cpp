#include "App.h"
#include "Shapes/rectangle2D.h"
#include "Color.h"
#include "Shapes/Circle2D.h"
#include "Vector2D.h"
#include "Shapes/Star2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/Line2D.h"
#include "SDL.h" 

bool App::Init(uint32_t height, uint32_t width, uint8_t zoom)
{
	if (screen_.Init(width, height, zoom))
	{
		return true;
	}
	return false;
}

void App::Run()
{
	screen_.RenderScreen();
	
	Triangle2D triangle(Vector2D(10, 10), Vector2D(20, 10), Vector2D(30, 40));
	Rectangle2D rectangle(Vector2D(50, 50), Vector2D(100, 100));
	screen_.Draw(&rectangle, Color::Blue(), true, Color::Blue(), true);
	screen_.Draw(&triangle, Color::Green(), true, Color::Green(), true);

	screen_.RenderScreen();

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



}