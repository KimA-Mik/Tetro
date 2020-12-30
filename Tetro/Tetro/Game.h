#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "LTexture.h"
//UTF-8 Коммент

class Game
{
public:
	Game();
	~Game();
	

	void Init(SDL_Renderer* Renderer);
	void Run();

	void Draw();
	void HandleEvents(SDL_Event& e);

	void Clear();



private:
	bool* IsRunning;
	
	bool GameRunning;

	SDL_Renderer* mRenderer = nullptr;


	LTexture TetroBlocks;

};



