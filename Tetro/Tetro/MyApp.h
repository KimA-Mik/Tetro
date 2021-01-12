#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "GameClass.h"
#include "Menu.h"
#include "P2Game.h"

//мое приложение
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

	SDL_Event e;

};

