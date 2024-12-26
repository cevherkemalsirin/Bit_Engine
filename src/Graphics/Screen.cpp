#include "Screen.h"
#include "Vector2D.h"
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
	height_ = h;
	width_ = w;
	
	window_ = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height_ * zoom, width_ * zoom, 0);
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
		backBuffer_.SetPixel(point.GetX(), point.GetY(), color);
	}
}


void Screen::ClearScreen()
{
	SDL_SetRenderDrawColor(renderer_, clearColor_.GetRed(), clearColor_.GetGreen(), clearColor_.GetBlue(), clearColor_.GetAlpha());
	SDL_RenderClear(renderer_);
}
