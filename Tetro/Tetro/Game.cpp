#include "Game.h"
//UTF-8 Коммент

Game::Game(SDL_Renderer* Renderer, bool* PorgramStatus)
{
	IsRunning = PorgramStatus;
	mRenderer = Renderer;
	TetroBlocks.loadFromFile(mRenderer, "Assets/Images/Tetro.png");
	ScoreFont = TTF_OpenFont("Assets/Fonts/Codename.ttf", 32);
	if (ScoreFont == nullptr)
		SDL_Log("Unable to load font Assets/Fonts/Codename.ttf\n");
	
	for (int i = 0; i < 7; i++)
		BlocksClip[i] = { i * 32,0,32,32 };
}

Game::~Game()
{
	TetroBlocks.free();
	for (int i = 0; i < 7; i++) {
		delete aScoreTetromino[i];
		CountText[i].free();
	}
	TTF_CloseFont(ScoreFont);
}

void Game::Init()
{
	//поле
	/*
	for (int i = 0; i < 10; i++)
		Field.at(i) = { 0 };
	*/
	for(int x = 0;x<10;x++)
		for (int y = 0; y < 20; y++) {
			Field[x][y] = 0;
		}

	Field[0][0] = 1;
	Field[9][0] = 1;
	Field[0][1] = 1;
	Field[9][1] = 1;
	
	
	//счет
	for (int i = 0; i < 7; i++) {
		aScoreTetromino[i] = new Tetromino(i + 1);
		std::string Score = "x" + std::to_string(TetroCount[i]);
		CountText[i].loadFromRenderedText(mRenderer, ScoreFont, Score, ScoreColor);
	}

	StatsText.loadFromRenderedText(mRenderer, ScoreFont, "Статистика", ScoreColor);

	aScoreTetromino[0]->ForceRotate();
	aScoreTetromino[1]->ForceRotate();
	aScoreTetromino[3]->ForceRotate();
	aScoreTetromino[4]->ForceRotate();
	aScoreTetromino[5]->ForceRotate();
	aScoreTetromino[6]->ForceRotate();
	


}

void Game::Run()
{

	CurBlock = new Tetromino;
	CurBlock->StartMoving(Field);
	CurBlock->Rotate();
	
	while (IsGameRunning && *IsRunning)
	{
		while (SDL_PollEvent(&E)) {
			HandleEvents(E);
		}
		SDL_SetRenderDrawColor(mRenderer, 245, 246, 250, 255);
		SDL_RenderClear(mRenderer);
		
		DrawField(FieldXPos, FieldYPos, Field);
		DrawTetromino(FieldXPos + 32 * xPos, FieldYPos + 32 * yPos, CurBlock);
		DrawTetroCount();
		
		
		
		SDL_RenderPresent(mRenderer);
	}
}

void Game::DrawField(int FieldX, int FieldY, FieldArray DrawableField)
{
	for(int x = 0; x < 10; x++)
		for (int y = 0; y < 20; y++) {
			if(DrawableField[x][y])
				TetroBlocks.render(FieldX + 32 * x, FieldY + 32 * y, &BlocksClip[DrawableField[x][y] - 1]);
		}
}

void Game::HandleEvents(SDL_Event& E)
{
	switch (E.type)
	{
	case SDL_QUIT:
		*IsRunning = false;
		break;
	case SDL_KEYUP:
		switch (E.key.keysym.sym)
		{
		case SDLK_UP:
			CurBlock->Rotate();
			break;

		case SDLK_DOWN:
			break;
		//todo расширить размер массива под поля для служебных блоков
		//чтоб не втыкаться в невидимые стены
		case SDLK_LEFT:
			SDL_Log("xPos = %d\n", xPos);
			xPos -= (CurBlock->DoesItFit(xPos - 1, yPos)) ? 1 : 0;
			CurBlock->SetXPos(xPos);//косяк
			break;

		case SDLK_RIGHT:
			SDL_Log("xPos = %d\n", xPos);
			xPos += (CurBlock->DoesItFit(xPos + 1, yPos)) ? 1 : 0;
			CurBlock->SetXPos(xPos);
			break;
		}
		break;
	}
}

void Game::DrawTetromino(int xPos, int yPso, Tetromino* Target)
{
	std::array<std::array<int, 4>, 4> Figure = Target->GetFigure();
	for(int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (Figure[y][x])
				TetroBlocks.render(xPos + 32 * x, yPso + 32 * y, &BlocksClip[Figure[y][x] - 1]);
		}
}

void Game::DrawTetroCount()
{
	int xCoords = 0;
	int yCoords = 15;
	//aScoreTetromino[1]->Rotate();
	for (int i = 0; i < 7; i++) {
		DrawTetromino(xCoords, yCoords + 96 * i, aScoreTetromino[i]);
		CountText[i].render(xCoords + 128, 64 +  yCoords + 96 * i);
	}

	StatsText.render(xCoords, yCoords);

}
