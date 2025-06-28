#include "Color.h"
#include "SDL.h"

const SDL_PixelFormat* Color::format_ = nullptr;

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SetRGBA(r, g, b, a);
}

void Color::SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	if (format_)
	{
		color_ = SDL_MapRGBA(format_, r, g, b, a);
	}

}

Color Color::AlphaBlend(const Color& newColor, const Color& currentColor)
{
	//mixColor =  newColor * newColorAlpha + currentColor * (1 - newColorAlpha)
	Color mixedColor;
	float newColorAlpha = static_cast<float>(newColor.GetAlpha()) / 255.0f;
	float destAlpha = 1.0f - newColorAlpha;
	mixedColor.SetAlpha(255);
	mixedColor.SetRed(static_cast<float>(newColor.GetRed()) * newColorAlpha + static_cast<float>(currentColor.GetRed()) * destAlpha);
	mixedColor.SetBlue(static_cast<float>(newColor.GetBlue()) * newColorAlpha + static_cast<float>(currentColor.GetBlue()) * destAlpha);
	mixedColor.SetGreen(static_cast<float>(newColor.GetGreen()) * newColorAlpha + static_cast<float>(currentColor.GetGreen()) * destAlpha);

	return mixedColor;
}

void Color::SetRed(uint8_t red)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(color_, format_, &r, &g, &b, &a);

	SetRGBA(red, g, b, a);
}

void Color::SetGreen(uint8_t green)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(color_, format_, &r, &g, &b, &a);

	SetRGBA(r, green, b, a);
}

void Color::SetBlue(uint8_t blue)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(color_, format_, &r, &g, &b, &a);

	SetRGBA(r, g, blue, a);
}

void Color::SetAlpha(uint8_t alpha)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(color_, format_, &r, &g, &b, &a);

	SetRGBA(r, g, b, alpha);
}

uint8_t Color::GetRed() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(color_, format_, &r, &g, &b, &a);
	return r;
}

uint8_t Color::GetGreen() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(color_, format_, &r, &g, &b, &a);
	return g;
}

uint8_t Color::GetBlue() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(color_, format_, &r, &g, &b, &a);
	return b;
}

uint8_t Color::GetAlpha() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(color_, format_, &r, &g, &b, &a);
	return a;
}



