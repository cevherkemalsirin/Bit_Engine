#pragma once
#include <stdint.h>

struct SDL_PixelFormat;

class Color
{
	uint32_t color_;
	static const SDL_PixelFormat* format_;
public:
	Color():Color(0) {};
	Color(uint32_t color) : color_(color) {};
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	inline bool operator==(const Color& color)const { return color_ == color.color_; }
	inline bool operator!=(const Color& color)const { return !(*this == color); }

	void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	inline static void Init(SDL_PixelFormat* format) { format_ = format; }

	static Color EvaluateSourceAlpha(const Color& source, const Color& destination);

	void SetRed(uint8_t red);
	void SetGreen(uint8_t green);
	void SetBlue(uint8_t blue);
	void SetAlpha(uint8_t alpha);

	inline uint32_t GetPixelColor() const { return color_; }
	uint8_t GetRed() const;
	uint8_t GetGreen() const;					  
	uint8_t GetBlue() const;
	uint8_t GetAlpha() const;

	static Color Black() { return Color(0, 0, 0, 255); }
	static Color White() { return Color(255, 255, 255, 255); }
	static Color Blue() { return Color(0, 0, 255, 255); }
	static Color Red() { return Color(255, 0, 0, 255); }
	static Color Green() { return Color(0, 255, 0, 255); }
	static Color Yellow() { return Color(255, 255, 0, 255); }
	static Color Purple() { return Color(255, 0, 255, 255); }
	static Color Cyan() { return Color(37, 240, 217, 255); }
	static Color Pink() { return Color(205, 128, 213, 255); }
	static Color Orange() { return Color(255, 102, 0, 255); }
};	



