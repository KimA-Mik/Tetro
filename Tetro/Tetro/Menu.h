#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <array>
#include "LTexture.h"
#include "GameClass.h"
class Menu : public GameClass
{
public:
	Menu(SDL_Renderer* Renderer, bool* PorgramStatus);
	~Menu();
	int Run();

private:
	//проверка на вхождение координат в четырехугольник
	bool IsPointInRect(int x, int y, SDL_Rect& TarRect);
	
	//фон
	void UpdateBackground();
	void DrawBackgound();

	//вынесем, чтобы избежать псотоянного выделения места
	//массив, содержащий зоны вырезания для одинаковых кнопок
	std::array<SDL_Rect, 2> PButtonClip;
	//данные для вырезания соответствующих кнопок
	std::array<SDL_Rect, 2> SGButtonClip;
	std::array<SDL_Rect, 2> EGButtonClip;
	void DrawButtons();

	Uint32 PTimestamp = 0;
	int xPos = 0;
	int yPos = 0;
	void HandleEvents(SDL_Event& E);




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

	//четырехугольники с размерами и местоположением кнопок
	SDL_Rect OPButton;
	SDL_Rect TPButton;
	SDL_Rect SGButton;
	SDL_Rect EGButton;

	//кол-во игроков, по дефолту 1
	int PlayerSelect = 1;

	//выбранный пункт меню
	//1 начать игру
	//0 выйти
	int MenuSelect = 1;

	std::array<std::array<int, 23>, 40> aBackgroundField;

	bool IsMenuNeeded = true;

};
//UTF-8 Коммент
