#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <array>
#include "LTexture.h"
//UTF-8 Коммент

class Game
{
public:
	Game();
	~Game();
	

	void Init(SDL_Renderer* Renderer);
	void Run();


	//исправить размер field
	void DrawField(int FieldX, int FieldY, std::array<std::array<int, 20>, 20> Field); 

	void Draw();
	void HandleEvents(SDL_Event& e);

	void Clear();



private:
	bool* IsRunning;
	
	bool GameRunning;

	SDL_Renderer* mRenderer = nullptr;


	LTexture TetroBlocks;

};



