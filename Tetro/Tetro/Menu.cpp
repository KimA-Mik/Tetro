#include "Menu.h"
//UTF-8 Коммент

Menu::Menu(SDL_Renderer* Renderer, bool* PorgramStatus) : GameClass(Renderer, PorgramStatus)
{
	Blocks.loadFromFile(mRenderer, "Assets/Images/Tetro.png");
	Logo.loadFromFile(mRenderer, "Assets/Images/Logo.png");
	OnePButton.loadFromFile(mRenderer, "Assets/Images/OnePButton.png");
	TwoPButton.loadFromFile(mRenderer, "Assets/Images/TwoPButton.png");
	StartGame.loadFromFile(mRenderer, "Assets/Images/StartGame.png");
	ExitGame.loadFromFile(mRenderer, "Assets/Images/ExitGame.png");


	int TempButtonDist = 50;

	OPButton = { TempButtonDist,200,OnePButton.getWidth(),OnePButton.getHeight() / 2 };
	TPButton = { 1280 - TempButtonDist - TwoPButton.getWidth(),200,TwoPButton.getWidth(),TwoPButton.getHeight() / 2 };

	SGButton = { 1280 / 2 - StartGame.getWidth() / 2,400,StartGame.getWidth(),StartGame.getHeight() };
	EGButton = { 1280 / 2 - ExitGame.getWidth() / 2,600,ExitGame.getWidth(),ExitGame.getHeight() };

	PButtonClip[0] = { 0,0,OnePButton.getWidth(),OnePButton.getHeight() / 2 };
	PButtonClip[1] = { 0,OnePButton.getHeight() / 2,OnePButton.getWidth(),OnePButton.getHeight() / 2 };

	SGButtonClip[0] = { 0,0,StartGame.getWidth(),StartGame.getHeight() / 2 };
	SGButtonClip[1] = { 0,StartGame.getHeight() / 2,StartGame.getWidth(),StartGame.getHeight() / 2 };

	EGButtonClip[0] = { 0,0,ExitGame.getWidth(),ExitGame.getHeight() / 2 };
	EGButtonClip[1] = { 0,ExitGame.getHeight() / 2,ExitGame.getWidth(),ExitGame.getHeight() / 2 };

	UpdateBackground();
}

Menu::~Menu()
{
	Blocks.free();
	Logo.free();
	OnePButton.free();
	TwoPButton.free();
	StartGame.free();
	ExitGame.free();
}

int Menu::Run()
{
	SDL_Event E;
	Uint32 LastUpdate = SDL_GetTicks();
	while (*IsRunning && IsMenuNeeded) {
		while (SDL_PollEvent(&E)) {
			HandleEvents(E);
		}

		Uint32 NewTick = SDL_GetTicks();
		//обновляем фон каждые 5 секунд
		if (NewTick - LastUpdate > 5000) {
			LastUpdate = NewTick;
			UpdateBackground();
		}

		//рисуем фон
		DrawBackgound();
		Logo.render(1280 / 2 - Logo.getWidth() / 2, 75);

		//рисуем кнопки 
		DrawButtons();
		
		SDL_RenderPresent(mRenderer);
		SDL_Delay(16);
	}


	return PlayerSelect;
}

bool Menu::IsPointInRect(int x, int y, SDL_Rect &TarRect)
{
	return (x > TarRect.x && x < TarRect.x + TarRect.w
		&& y > TarRect.y && y < TarRect.y + TarRect.h);
}

void Menu::UpdateBackground()
{
	for (int x = 0; x < 40; x++)
		for (int y = 0; y < 23; y++)
			aBackgroundField[x][y] = rand() % 7;
}

void Menu::DrawBackgound()
{
	SDL_Rect Clip;
	for (int x = 0; x < 40; x++)
		for (int y = 0; y < 23; y++) {
			Clip = { aBackgroundField[x][y] * 32,0,32,32 };
			Blocks.render(x * 32, y * 32, &Clip);
		}
}

void Menu::DrawButtons()
{
	
	if (PlayerSelect == 1) {
		OnePButton.render(OPButton.x, OPButton.y, &PButtonClip[1]);
		TwoPButton.render(TPButton.x, TPButton.y, &PButtonClip[0]);
	}
	else {
		OnePButton.render(OPButton.x, OPButton.y, &PButtonClip[0]);
		TwoPButton.render(TPButton.x, TPButton.y, &PButtonClip[1]);
	}

	if (MenuSelect) {
		StartGame.render(SGButton.x, SGButton.y, &SGButtonClip[1]);
		ExitGame.render(EGButton.x, EGButton.y, &EGButtonClip[0]);
	}
	else {
		StartGame.render(SGButton.x, SGButton.y, &SGButtonClip[0]);
		ExitGame.render(EGButton.x, EGButton.y, &EGButtonClip[1]);
	}
}

void Menu::HandleEvents(SDL_Event& E)
{
	switch (E.type)
	{
	case SDL_KEYDOWN:
		switch (E.key.keysym.sym)
		{
		case SDLK_UP:
			MenuSelect = (MenuSelect) ? 0 : 1;
			break;

		case SDLK_DOWN:
			MenuSelect = (MenuSelect) ? 0 : 1;
			break;

		case SDLK_LEFT:
			PlayerSelect = (PlayerSelect == 1) ? 2 : 1;
			break;

		case SDLK_RIGHT:
			PlayerSelect = (PlayerSelect == 1) ? 2 : 1;
			break;

		case SDLK_RETURN:
			//продублирую
			//выбранный пункт меню
			//1 начать игру
			//0 выйти
			switch (MenuSelect)
			{
			case 0:
				//закрываем игру
				*IsRunning = false;
				break;

			case 1:
				//закрываем меню
				IsMenuNeeded = false;
				break;
			}
			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&xPos, &yPos);

		if (IsPointInRect(xPos, yPos, OPButton))
			PlayerSelect = 1;
		else if (IsPointInRect(xPos, yPos, TPButton))
			PlayerSelect = 2;
		else if (IsPointInRect(xPos, yPos, SGButton))
			IsMenuNeeded = false;
		else if (IsPointInRect(xPos, yPos, EGButton))
			*IsRunning = false;
		break;
	case SDL_QUIT:
		*IsRunning = false;
		break;
	}
}
