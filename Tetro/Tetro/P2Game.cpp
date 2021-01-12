#include "P2Game.h"
//UTF-8 коммент

P2Game::P2Game(SDL_Renderer* Renderer, bool* PorgramStatus) : Game(Renderer, PorgramStatus)
{
	FieldXPos = 0;
	FieldYPos = 50;
	P2FieldXPos = 400;
	P2FieldYPos = 50;
}

P2Game::~P2Game()
{
	delete P2NextBlock;
	delete P2CurBlock;
}

void P2Game::Init()
{
	for (int i = 0; i < 10; i++) {
		Field.at(i) = { 0 };
		P2Field.at(i) = { 0 };
	}

	UpdateScore(0, 1);
	UpdateScore(0, 2);
}

int P2Game::Run()
{
	CurBlock = new Tetromino;
	NextBlock = new Tetromino;
	CurBlock->StartMoving(Field);

	P2CurBlock = new Tetromino;
	P2NextBlock = new Tetromino;
	P2CurBlock->StartMoving(P2Field);

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
			pieceCount++;
			if (pieceCount % 50 == 0)
				if (Speed >= 10) Speed--;
			//каждые 50 спучков повышаем сложность

			// Проверяем, можно ли сдвинуть вниз
			if (CurBlock->DoesItFit(xPos, yPos + 1)) {
				//если да - двигаем
				yPos++;
			}//если нет, значит блок достиг дна
			else {
				//закрепляем его на поле
				TetroArray CurFigure = CurBlock->GetFigure();
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++) {
						if (CurFigure[j][i])
							Field[xPos + i][yPos + j] = CurFigure[j][i];
					}

				//вызываем новый блок
				delete CurBlock;
				CurBlock = NextBlock;
				NextBlock = new Tetromino;
				CurBlock->StartMoving(Field);
				xPos = 3;
				yPos = 0;

				if (!CurBlock->DoesItFit(xPos, yPos)) {
					GameOver();
					IsGameRunning = false;
				}

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
					UpdateScore(vLines.size(), 1);

			}

			if (P2CurBlock->DoesItFit(P2xPos, P2yPos + 1)) {
				//если да - двигаем
				P2yPos++;
			}//если нет, значит блок достиг дна
			else {
				//закрепляем его на поле
				TetroArray CurFigure = CurBlock->GetFigure();
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++) {
						if (CurFigure[j][i])
							P2Field[P2xPos + i][P2yPos + j] = CurFigure[j][i];
					}

				//вызываем новый блок
				delete P2CurBlock;
				P2CurBlock = P2NextBlock;
				P2NextBlock = new Tetromino;
				P2CurBlock->StartMoving(Field);
				P2xPos = 3;
				P2yPos = 0;

				if (!P2CurBlock->DoesItFit(xPos, yPos)) {
					GameOver();
					IsGameRunning = false;
				}

				//проверяем линии
				for (int y = 0; y < 20; y++) {
					bool bLine = true;
					for (int x = 0; x < 10; x++) {
						bLine = P2Field[x][y] && bLine;
					}
					if (bLine) {
						vP2Lines.push_back(y);
					}
				}

				if (!vP2Lines.empty())
					UpdateScore(vP2Lines.size(), 2);

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

		if (!vP2Lines.empty()) {

			for (auto& Line : vP2Lines) {
				for (int x = 0; x < 10; x++) {
					for (int y = Line; y > 0; y--) {
						P2Field[x][y] = P2Field[x][y - 1];
					}
					P2Field[x][0] = 0;
				}
			}

			P2CurBlock->StartMoving(P2Field);
			vP2Lines.clear();
		}


		SDL_SetRenderDrawColor(mRenderer, 245, 246, 250, 255);
		SDL_RenderClear(mRenderer);

		DrawField(FieldXPos, FieldYPos, Field);
		DrawTetromino(FieldXPos + 32 * xPos, FieldYPos + 32 * yPos, CurBlock);
		DrawScore();
		DrawNextBlock();





		SDL_RenderPresent(mRenderer);



	}





	
	return 0;
}

void P2Game::HandleEvents(SDL_Event& E)
{
	switch (E.type)
	{
	case SDL_QUIT:
		*IsRunning = false;
		break;
	case SDL_KEYUP:
		switch (E.key.keysym.sym)
		{
		case SDLK_w:
			CurBlock->Rotate(xPos, yPos);
			break;

		case SDLK_s:
			yPos += (CurBlock->DoesItFit(xPos, yPos + 1)) ? 1 : 0;
			break;

		case SDLK_a:
			xPos -= (CurBlock->DoesItFit(xPos - 1, yPos)) ? 1 : 0;
			break;

		case SDLK_d:
			xPos += (CurBlock->DoesItFit(xPos + 1, yPos)) ? 1 : 0;
			break;

		case SDLK_UP:
			P2CurBlock->Rotate(xPos, yPos);
			break;

		case SDLK_DOWN:
			P2yPos += (P2CurBlock->DoesItFit(xPos, yPos + 1)) ? 1 : 0;
			break;

		case SDLK_LEFT:
			P2xPos -= (P2CurBlock->DoesItFit(xPos - 1, yPos)) ? 1 : 0;
			break;

		case SDLK_RIGHT:
			P2xPos += (P2CurBlock->DoesItFit(xPos + 1, yPos)) ? 1 : 0;
			break;
		}
		break;
	}
}

void P2Game::DrawNextBlock()
{

}

void P2Game::DrawScore()
{
}

void P2Game::UpdateScore(int nLines, int Player)
{
	int* ChangingScore = nullptr;
	switch (Player)
	{
	case 1:
		ChangingScore = &GameScore;
		break;

	case 2:
		ChangingScore = &P2GameScore;
		break;

	default:
		return;
	}


	switch (nLines)
	{
	case 0:
		*ChangingScore = 0;
		break;
	case 1:
		*ChangingScore += 100;
		break;
	case 2:
		*ChangingScore += 300;
		break;
	case 3:
		*ChangingScore += 700;
		break;
	case 4:
		*ChangingScore += 1500;
		break;
	}

	std::string Score = "Текущий счет: " + std::to_string(GameScore);
	ScoreImage.loadFromRenderedText(mRenderer, scoreFont, Score, scoreColor);

	Score.clear();
	Score = "Текущий счет: " + std::to_string(P2GameScore);
	P2ScoreImage.loadFromRenderedText(mRenderer, scoreFont, Score, scoreColor);

}
