#pragma once
#include "Game.h"
class P2Game :
    public Game
{
	//UTF-8 коммент
public:
	P2Game(SDL_Renderer* Renderer, bool* PorgramStatus);
	~P2Game();
	void Init();
	int Run();

private:
	void HandleEvents(SDL_Event& E);

	bool bP1inGame = true;
	bool bP2inGame = true;

	
	void GameOver();


	void DrawNextBlock();
	void DrawScore();
	void UpdateScore(int nLines, int Player);

	Tetromino* P2CurBlock = nullptr;
	Tetromino* P2NextBlock = nullptr;
	FieldArray P2Field;

	int P2xPos = 3;
	int P2yPos = 0;
	int P2GameScore = 0;
	int P2FieldXPos = 0;
	int P2FieldYPos = 0;

	std::vector<int> vP2Lines;




	int P2Score = 2;
	LTexture P2ScoreImage;
};

