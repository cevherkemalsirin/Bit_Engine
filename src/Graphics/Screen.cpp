#include "Screen.h"
#include <vector>
#include "Vector2D.h"
#include "Shapes/Line2D.h"
#include "Shapes/Star2D.h"
#include "Shapes/rectangle2D.h"
#include "Shapes/Circle2D.h"
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

void Screen::Draw(const Shape* shape, const Color& color, bool fill, const Color& fillColor, bool drawBoundingBox)
{

	if (shape)
	{
		for (const auto& line : shape->GetLines())
		{
			Draw(line, color);
		}

		if (fill)
		{
			Fill(shape, fillColor);
		}
		
		if (drawBoundingBox)
		{
			Rectangle2D  box = shape->GetBoundingBox();
			Draw(&box, Color::Red());
		}
	}

}

void Screen::Draw(const Circle2D& circle, float drawingAngle, const Color& color, bool fill, const Color& fillColor, bool drawBoundingBox)
{
	float fullDegree = 360.0f;
	float quarterDegree = fullDegree / 4.0f;
	Vector2D rightEnd(circle.GetCenter().GetX() + circle.GetRadius(), circle.GetCenter().GetY());
	Vector2D topEnd(circle.GetCenter().GetX(), circle.GetCenter().GetY() - circle.GetRadius());
	Vector2D leftEnd(circle.GetCenter().GetX() - circle.GetRadius(), circle.GetCenter().GetY());
	Vector2D bottomEnd(circle.GetCenter().GetX(), circle.GetCenter().GetY() + circle.GetRadius());
	for (float i = 0.0f; i < quarterDegree; i += drawingAngle / fullDegree)
	{
		rightEnd.RotateVector(drawingAngle, circle.GetCenter());
		topEnd.RotateVector(drawingAngle, circle.GetCenter());
		leftEnd.RotateVector(drawingAngle, circle.GetCenter());
		bottomEnd.RotateVector(drawingAngle, circle.GetCenter());
		Draw(rightEnd, color);
		Draw(topEnd, color);
		Draw(leftEnd, color);
		Draw(bottomEnd, color);
	}
	if (fill)
	{
		Fill(&circle, fillColor);
	}
	if (drawBoundingBox)
	{
		Rectangle2D  box = circle.GetBoundingBox();
		Draw(&box, Color::Red());
	}
}


void Screen::ClearScreen(const Color & color)
{
	SDL_SetRenderDrawColor(renderer_,color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
	SDL_RenderClear(renderer_);
}



void Screen::Fill(const Shape* shape, const Color& color)
{
	if (shape)
	{
		Rectangle2D  box = shape->GetBoundingBox();
		int rowStart = static_cast<int>(box.GetTopLeftPoint().GetY());
		int rowEnd = static_cast<int>(box.GetBottomRightPoint().GetY());
		int colStart = static_cast<int>(box.GetTopLeftPoint().GetX());
		int colEnd = static_cast<int>(box.GetBottomRightPoint().GetX());
		for (int y = rowStart; y < rowEnd; ++y)
		{
			for (int x = colStart; x < colEnd; ++x)
			{
				Vector2D currentPoint(x, y);
				if (shape->ContainsPoint(currentPoint))
				{
					Draw(currentPoint, color);
				}
			}
		}
	}
}
