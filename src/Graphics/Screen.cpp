#include "Screen.h"
#include <vector>
#include "Vector2D.h"
#include "Shapes/ILineShape.h"
#include "Shapes/Line2D.h"
#include "Shapes/Star2D.h"
#include "Shapes/rectangle2D.h"
#include "Shapes/Triangle.h"
#include "SDL.h"

Screen::Screen():window_(nullptr),renderer_(nullptr),height_(0),width_(0)
{
}

Screen::~Screen()
{
	if (window_)
	{
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}
	if (renderer_)
	{
		SDL_DestroyRenderer(renderer_);
		renderer_ = nullptr;
	}
	SDL_Quit();
}

void Screen::Init(uint32_t w, uint32_t h, uint8_t zoom)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		//return nullptr;
		return;
	}
	width_ = w;
	height_ = h;

	window_ = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_ * zoom, height_ * zoom,0 /*SDL_WINDOW_FULLSCREEN_DESKTOP*/);
	renderer_ = SDL_CreateRenderer(window_, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!window_ || !renderer_)
	{
		//return nullptr;
		return;
	}

	SDL_PixelFormat* format = SDL_GetWindowSurface(window_)->format;
	Color::Init(format);
	clearColor_ = Color::Black();
	backBuffer_.Init(format->format, width_, height_);
	backBuffer_.Clear(clearColor_);

	//nearest used for pixel art style games when scaling, Linear is used for modern
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_RenderSetLogicalSize(renderer_, width_, height_);
	//return window_;
}

void Screen::RenderScreen()
{
	if (window_ && renderer_)
	{
		ClearScreen();
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, backBuffer_.GetSurface());
		SDL_RenderCopy(renderer_, texture, nullptr, nullptr);
		SDL_DestroyTexture(texture);
		SDL_RenderPresent(renderer_);
		backBuffer_.Clear(clearColor_);
	}
}

void Screen::Draw(int x, int y, const Color& color)
{
	if (window_ && renderer_)
	{
		backBuffer_.SetPixel(x, y, color);
	}
}

void Screen::Draw(const Vector2D& point, const Color& color)
{
	if (window_ && renderer_)
	{
		Draw(point.GetX(), point.GetY(), color);
	}
}

void Screen::Draw(const Line2D& line, const Color& color)
{
	if (window_ && renderer_)
	{ 
		float x =  line.GetPointStart().GetX();
		float y = line.GetPointStart().GetY();
		float dx = std::roundf(line.GetPointEnd().GetX() - line.GetPointStart().GetX());
		float dy = std::roundf(line.GetPointEnd().GetY() - line.GetPointStart().GetY());

		int steps = static_cast<int>(std::max(std::abs(dx), std::abs(dy)));

		float xstep = dx / steps;
		float ystep = dy / steps;
	    
		Draw(x,y,color);
		for (int i = 1; i < steps; ++i)
		{
			x += xstep;
			y += ystep;
			Draw(std::roundf(x), std::roundf(y),color);
		}

	}
}

void Screen::Draw(const ILineShape* shape, const Color& color)
{
	for (const auto& line : shape->GetLines())
	{
		Draw(line, color);
	}
}
/*
void Screen::Draw(const Star2D& star, const Color& color)
{
	for (Line2D line : star.GetLines())
	{
		Draw(line, color);
	}
}

void Screen::Draw(const Triangle2D& triangle, const Color& color)
{
	for (Line2D line : triangle.GetLines())
	{

	}
}

void Screen::Draw(const Rectangle2D& rectangle, const Color& color)
{
	for ( const auto & line : rectangle.GetLines())
	{
		Draw(line, color);
	}

}

*/
void Screen::ClearScreen(const Color & color)
{
	SDL_SetRenderDrawColor(renderer_,color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
	SDL_RenderClear(renderer_);
}
