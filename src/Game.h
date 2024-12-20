//============================================================================
// Name        : Game.h
// Author      : Cevher Kemal Sirin
// Version     : 1.0
// Copyright   : MIT
// Description : Main Game class.
// Date: 2023
//============================================================================

#pragma once
#include <string_view>


class SDL_Window;
class SDL_Renderer;
class SDL_Surface;

class Game
{
private:
	//game
	bool isRunning;
	//window
	SDL_Window* SDLWindow;
	SDL_Renderer* SDLRenderer;
	SDL_Surface* SDLSurface;
	int windowWidth;
	int WindowHeight;

	void ProcessInput();
	void Update();
	void Render();
public:
	Game();
	~Game();

	/*
	@returns 
	true if everything okey.
	*/
	bool Initialize(std::string_view gameTitle, int width = 800, int height = 600);

	void Run();
	void Destroy();
};

