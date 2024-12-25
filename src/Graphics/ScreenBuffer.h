#pragma once
#include <stdint.h>
#include "Color.h"

struct  SDL_Surface;

class ScreenBuffer
{
	SDL_Surface* surface_;

	uint32_t GetPixelIndex(uint32_t row, uint32_t column);
public:
	ScreenBuffer() : surface_(nullptr){}
	ScreenBuffer(const ScreenBuffer& buffer);
	ScreenBuffer& operator=(const ScreenBuffer& buffer);
	~ScreenBuffer();

	void Init( uint32_t format ,uint32_t width, uint32_t height);
	
	void Clear(Color color = Color::Black());
	void SetPixel(uint32_t y, uint32_t x, Color color = Color::Black());
};
