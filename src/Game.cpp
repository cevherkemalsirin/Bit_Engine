#include "Game.h"
#include <SDL.h>
#include <iostream>
Game::Game():isRunning(false)
{
}

Game::~Game()
{
}

bool Game::Initialize(std::string_view gameTitle, int width, int height)
{
	//SDL window creation
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cerr << " SDL initializing failed!. " << std::endl;
		return false;
	}
	
	SDLWindow = SDL_CreateWindow(gameTitle.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_INPUT_FOCUS);
	if (!SDLWindow)
	{
		std::cerr << " Error creating SDL Window Failed! " << std::endl;
		return false;
	}

	SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLRenderer)
	{
		std::cerr << " Error creating SDL Renderer Failed! " << std::endl;
		return false;
	}
	//Creating SDL surface, prefer renderer but it is another way. sdlSurface 1D array of pixels CPU
	SDLSurface = SDL_GetWindowSurface(SDLWindow);
   

	SDL_SetWindowFullscreen(SDLWindow, SDL_WINDOW_FULLSCREEN);
	isRunning = true;
	return isRunning;

}

void Game::Run()
{
	while (isRunning)
	{
		this->ProcessInput();
		this->Update();
		this->Render();
	}
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
		{
			switch (sdlEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				isRunning = false;
			}break;
		}
		break;
		default:
			break;
		}
	}

}

void Game::Update()
{

}

void Game::Render()
{
	SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, 255); //set render color
	SDL_RenderClear(SDLRenderer); // clear window

	//TODO: Render game objects
	

	SDL_RenderPresent(SDLRenderer); // paint window
}

void Game::Destroy()
{
	SDL_DestroyRenderer(SDLRenderer);
	SDL_DestroyWindow(SDLWindow);
	SDL_Quit();
}
