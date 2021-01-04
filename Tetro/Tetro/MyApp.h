#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Tetromino.h"
#include "Menu.h"

//мое приложение
class MyApp
{
public:
	MyApp();
	~MyApp();
	void Run();

	static int MyEventFilter(void* userdata, SDL_Event* event);



private:
	static bool IsRunning;

	SDL_Window* mWindow = nullptr;

	SDL_Renderer* mRenderer = nullptr;

	SDL_Event e;

};

