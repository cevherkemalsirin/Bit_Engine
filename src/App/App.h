#pragma once  
#include <stdint.h>   
#include "Screen.h"  

struct SDL_Window;
class App  
{  
	Screen screen_;
	//SDL_Window* window_;
public:  
	bool Init(uint32_t height, uint32_t width, uint8_t zoom);
	void Run();
	
	inline uint32_t GetWidth() const { return screen_.Getwidth(); }
	inline uint32_t GetHeight() const { return screen_.GetHeight(); }

	//singleton pattern to ensure only one instance of App exists
	static App& Instance() {
		static App AppInstance;
		return AppInstance;
	}
};
