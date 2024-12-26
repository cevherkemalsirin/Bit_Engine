#pragma once

#include "ScreenBuffer.h"

class Vector2D;
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

	void ClearScreen();
	
public:
	Screen();
	~Screen();
	
	inline uint32_t GetHeight() const { return height_;}
	inline uint32_t Getwidth() const { return width_;}
	inline void SetClearColor(const Color& color) { clearColor_ = color;}
	void Init(uint32_t w, uint32_t h, uint8_t zoom);
	void RenderScreen();

	void Draw(int x, int y, const Color& color);
	void Draw(const Vector2D& point, const Color& color);


};

