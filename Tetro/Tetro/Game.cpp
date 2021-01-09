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
	NextBlockText.free();
}

void Game::Init()
{
	//поле
	
	for (int i = 0; i < 10; i++)
		Field.at(i) = { 0 };
	
	//счет
	for (int i = 0; i < 7; i++) {
		aScoreTetromino[i] = new Tetromino(i + 1);
		std::string Score = "x" + std::to_string(TetroCount[i]);
		CountText[i].loadFromRenderedText(mRenderer, ScoreFont, Score, ScoreColor);
	}

	StatsText.loadFromRenderedText(mRenderer, ScoreFont, "Статистика", ScoreColor);

	UpdateScore(0);

	NextBlockText.loadFromRenderedText(mRenderer, ScoreFont, "Следующий блок", ScoreColor);

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
	NextBlock = new Tetromino;
	CurBlock->StartMoving(Field);
	CurBlock->Rotate();
	
	while (IsGameRunning && *IsRunning)
	{
		SDL_Delay(25);//тик
		SpeedCount++;
		bForceDown = (SpeedCount == Speed);
		//каждый Speed тиков блок опускается на еденицу
		
		//обработка ввода
		while (SDL_PollEvent(&E)) {
			HandleEvents(E);
		}
		
		if (bForceDown) {
			SpeedCount = 0;
			PieceCount++;
			if (PieceCount % 50 == 0)
				if (Speed >= 10) Speed--;
			//каждые 50 спучков повышаем сложность

			// Проверяем, можно ли сдвинуть вниз
			if (CurBlock->DoesItFit(xPos, yPos + 1)) {
				//если да - двигаем
				yPos++;
				CurBlock->SetYPos(yPos);
			}//если нет, значит блок достиг дна
			else {
				//закрепляем его на поле
				TetroArray CurFigure = CurBlock->GetFigure();
				for(int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++) {
						if (CurFigure[j][i])
							Field[xPos + i][yPos + j] = CurFigure[j][i];
					}

				++TetroCount[CurBlock->GetType() - 1];
				UpdateTetroCount();
				//вызываем новый блок
				delete CurBlock;
				CurBlock = NextBlock;
				NextBlock = new Tetromino;
				CurBlock->StartMoving(Field);
				xPos = 3;
				yPos = 0;

				//проверяем линии
				for (int y = 0; y < 20; y++) {
					bool bLine = true;
					for (int x = 0; x < 10; x++) {
						bLine = Field[x][y] && bLine;
					}
					if (bLine) {
						vLines.push_back(y);
						//сюда можно вставить анимацию
					}
				}

				if (!vLines.empty())
					UpdateScore(vLines.size());

			}
		}
		
		if (!vLines.empty()) {
			
			for (auto& Line : vLines) {
				for (int x = 0; x < 10; x++) {
					for (int y = Line; y > 0; y--) {
						Field[x][y] = Field[x][y - 1];
					}
					Field[x][0] = 0;
				}
			}
			
			CurBlock->StartMoving(Field);
			vLines.clear();
		}
		
		
		
		SDL_SetRenderDrawColor(mRenderer, 245, 246, 250, 255);
		SDL_RenderClear(mRenderer);
		
		DrawField(FieldXPos, FieldYPos, Field);
		DrawTetromino(FieldXPos + 32 * xPos, FieldYPos + 32 * yPos, CurBlock);
		DrawTetroCount();
		DrawScore();
		DrawNextBlock();

		
		
		
		
		SDL_RenderPresent(mRenderer);
	}
}

void Game::DrawField(int FieldX, int FieldY, FieldArray DrawableField)
{
	SDL_Rect Back = { FieldX,FieldY, 10 * 32,20 * 32 };
	SDL_SetRenderDrawColor(mRenderer, 220, 221, 225, 255);
	SDL_RenderFillRect(mRenderer, &Back);
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
			yPos += (CurBlock->DoesItFit(xPos, yPos + 1)) ? 1 : 0;
			CurBlock->SetYPos(yPos);
			break;
		
		case SDLK_LEFT:
			xPos -= (CurBlock->DoesItFit(xPos - 1, yPos)) ? 1 : 0;
			CurBlock->SetXPos(xPos);//косяк
			break;

		case SDLK_RIGHT:
			xPos += (CurBlock->DoesItFit(xPos + 1, yPos)) ? 1 : 0;
			CurBlock->SetXPos(xPos);
			break;
		}
		break;
	}
}

void Game::DrawTetromino(int xPos, int yPso, Tetromino* Target)
{
	if (Target == nullptr)
		return;

	std::array<std::array<int, 4>, 4> Figure = Target->GetFigure();
	for(int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (Figure[y][x])
				TetroBlocks.render(xPos + 32 * x, yPso + 32 * y, &BlocksClip[Figure[y][x] - 1]);
		}
}

void Game::UpdateTetroCount()
{
	for (int i = 0; i < 7; i++) {
		std::string Score = "x" + std::to_string(TetroCount[i]);
		CountText[i].loadFromRenderedText(mRenderer, ScoreFont, Score, ScoreColor);
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

void Game::UpdateScore(int LinesCount)
{
	switch (LinesCount)
	{
	case 0:
		GameScore = 0;
		break;
	case 1:
		GameScore += 100;
		break;
	case 2:
		GameScore += 300;
		break;
	case 3:
		GameScore += 700;
		break;
	case 4:
		GameScore += 1500;
		break;
	}

	std::string Score = "Текущий счет: " + std::to_string(GameScore);
	ScoreImage.loadFromRenderedText(mRenderer, ScoreFont, Score, ScoreColor);
}

void Game::DrawScore()
{
	ScoreImage.render(FieldXPos, 10);
}

void Game::DrawNextBlock()
{
	int x = FieldXPos + 32 * 10 + 100;
	NextBlockText.render(x, 100);
	DrawTetromino(x, 150, NextBlock);
}
