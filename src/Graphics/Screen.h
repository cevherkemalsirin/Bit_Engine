#pragma once

#include "ScreenBuffer.h"

class Vector2D;
class Line2D;
class Star2D;
class Triangle2D;
class Rectangle2D;
class Shape;
class Circle2D;
struct SDL_Window;
struct SDL_Renderer;

class Screen
{
	uint32_t height_;
	uint32_t width_;
	Color clearColor_;
	ScreenBuffer backBuffer_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	void ClearScreen(const Color& color = Color::Black());
	void Fill(const Shape* shape, const Color& color = Color::White());
public:
	Screen();
	~Screen();
	
	inline uint32_t GetHeight() const { return height_;}
	inline uint32_t Getwidth() const { return width_;}
	inline void SetClearColor(const Color& color) { clearColor_ = color;}
	SDL_Window* Init(uint32_t w, uint32_t h, uint8_t zoom = 3);
	void RenderScreen();

	void Draw(int x, int y, const Color& color = Color::White());
	void Draw(const Vector2D& point, const Color& color = Color::White());
	//DDA algorithm more info at https://tinyurl.com/2r79nsnh
	void Draw(const Line2D& line, const Color& color = Color::White());
	/*
	void Draw(const Star2D& star, const Color& color = Color::White());
	void Draw(const Triangle2D& triangle, const Color& color = Color::White());
	void Draw(const Rectangle2D& rectangle, const Color& color = Color::White());
	*/
	void Draw(const Shape* shape, const Color& color = Color::White(), bool fill = false, const Color& fillColor = Color::White(), bool DrawBoundingBox = false);
	void Draw(const Circle2D& circle, float drawingAngle ,const Color& color = Color::White(), bool fill = false, const Color& fillColor = Color::White(), bool frawBoundingBox = false);


private:
	Screen(const Screen&) = delete;
	Screen& operator=(const Screen&) = delete;
};

