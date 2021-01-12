#include "P2Game.h"
//UTF-8 коммент

P2Game::P2Game(SDL_Renderer* Renderer, bool* PorgramStatus) : Game(Renderer, PorgramStatus)
{

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
}

int P2Game::Run()
{
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
}
