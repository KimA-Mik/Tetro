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

	bool IsPointInRect(int x, int y, SDL_Rect &TarRect);
private:
	//стандартные блоки, складываютч в мозайку
	LTexture Blocks;

	//логотоип, всегда по центру
	LTexture Logo;

	//размер кнопок 200 на 200
	//изображение 200 на 400
	LTexture OnePButton;
	LTexture TwoPButton;

	//410 на 75
	LTexture StartGame;

	//480 на 75
	LTexture ExitGame;

	//четырехугольники с размерами кнопок
	SDL_Rect OPButton;
	SDL_Rect TPButton;
	SDL_Rect SGButton;
	SDL_Rect EGButton;

	std::array<std::array<int, 23>, 40> aBackgroundField;

	bool* IsRunning = nullptr;

	SDL_Renderer* mRenderer = nullptr;
};
//UTF-8 Коммент
