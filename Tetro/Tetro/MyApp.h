#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

class MyApp
{
public:
	MyApp();
	~MyApp();
	void Run();

private:
	bool IsRunning = true;

	SDL_Window* mWindow = nullptr;

	SDL_Renderer* mRenderer = nullptr;

};

