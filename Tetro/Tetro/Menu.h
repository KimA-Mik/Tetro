#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <array>
#include "LTexture.h"
class Menu
{
public:
	Menu(SDL_Renderer* Renderer, bool* PorgramStatus);
	~Menu();
	int Run();
private:
	LTexture Blocks;
	std::array<std::array<int, 23>, 40> aBackgroundField;

	bool* IsRunning = nullptr;

	SDL_Renderer* mRenderer = nullptr;
	//LTexture Background;
};
//UTF-8 Коммент
