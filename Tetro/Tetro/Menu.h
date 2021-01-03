#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "LTexture.h"
class Menu
{
public:
	Menu();
	~Menu();
	int Run();
private:
	LTexture Background;
};
//UTF-8 Коммент
