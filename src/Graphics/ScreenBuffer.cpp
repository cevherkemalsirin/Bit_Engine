#include "ScreenBuffer.h"
#include "SDL.h"

ScreenBuffer::ScreenBuffer(const ScreenBuffer& buffer): surface_(nullptr)
{
	if (buffer.surface_)
	{
		Init(buffer.surface_->format->format, buffer.surface_->w, buffer.surface_->h);
		SDL_BlitSurface(buffer.surface_ , nullptr, surface_, nullptr);
    }
}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& buffer)
{
	if (this == &buffer)
	{
		return *this;
	}

	if (surface_)
	{
		SDL_FreeSurface(surface_);
		surface_ = nullptr;
	}

	if (buffer.surface_)
	{
		Init(buffer.surface_->format->format, buffer.surface_->w, buffer.surface_->h);
		SDL_BlitSurface(buffer.surface_, nullptr, surface_, nullptr);
	}

	return *this;
}

ScreenBuffer::~ScreenBuffer()
{
	if (surface_)
	{
		SDL_FreeSurface(surface_);
		surface_ = nullptr;
	}
}

void ScreenBuffer::Init( uint32_t format, uint32_t width, uint32_t height)
{
	surface_ = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
	Clear();
}

void ScreenBuffer::Clear(Color color)
{
	if (surface_)
	{
		SDL_FillRect(surface_, nullptr, color.GetPixelColor());
	}
}

void ScreenBuffer::SetPixel(uint32_t x, uint32_t y, Color color)
{
	if (surface_)
	{
		SDL_LockSurface(surface_);
		uint32_t* pixels = static_cast<uint32_t*>(surface_->pixels);
		pixels[GetPixelIndex(y, x)] = color.GetPixelColor();
		SDL_UnlockSurface(surface_);
	}

}

uint32_t ScreenBuffer::GetPixelIndex(uint32_t row, uint32_t column)
{
	if (surface_ && row < static_cast<uint32_t>(surface_->h) && column < static_cast<uint32_t>(surface_->w))
	{
			return row * surface_->w + column;
	}
	return 0;
}

