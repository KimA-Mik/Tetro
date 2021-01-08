#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <array>
#include <vector>
#include "LTexture.h"
#include "Tetromino.h"
#define FieldArray std::array<std::array<int,20>,10>
#define TetroArray std::array<std::array<int, 4>, 4>
#define FieldXPos 500
#define FieldYPos 50

//UTF-8 Коммент


class Game
{
public:
	Game(SDL_Renderer* Renderer, bool* PorgramStatus);
	~Game();
	

	void Init();
	void Run();


	//исправить размер field
	void DrawField(int FieldX, int FieldY, FieldArray Field);

	void Draw();
	

	void Clear();



private:
	//тут элементы, которые не нужны для совместного режима
	std::array<int, 7> NumOfTetromino;

	int xPos = 3;
	int yPos = 0;

	//стстистика установленныъ блоков
	std::array<Tetromino*, 7> aScoreTetromino = { 0 };
	std::array<int, 7> TetroCount = { 0 };
	std::array<LTexture, 7> CountText;
	LTexture StatsText;

protected:
	void HandleEvents(SDL_Event& E);
	SDL_Event E;

	void DrawTetromino(int xPos, int yPso, Tetromino* Target);
	void UpdateTetroCount();
	void DrawTetroCount();
	void UpdateScore(int LinesCount);
	void DrawScore();
	void DrawNextBlock();
	LTexture NextBlockText;

	int Speed = 40;
	int SpeedCount = 0;
	bool bForceDown = false;
	int PieceCount = 0;

	std::vector<int> vLines;

	bool* IsRunning = nullptr;
	
	bool IsGameRunning = true;

	TTF_Font* ScoreFont = nullptr;
	SDL_Color ScoreColor = { 12, 36, 97,255 };
	int GameScore = 0;
	LTexture ScoreImage;

	std::array<SDL_Rect, 7> BlocksClip;
	FieldArray Field;
	Tetromino* CurBlock = nullptr;
	Tetromino* NextBlock = nullptr;
	
	SDL_Renderer* mRenderer = nullptr;
	LTexture TetroBlocks;

};



