#include "Menu.h"
//UTF-8 Коммент

Menu::Menu(SDL_Renderer* Renderer, bool* PorgramStatus)
{
	mRenderer = Renderer;
	IsRunning = PorgramStatus;
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

	for (int x = 0; x < 40; x++)
		for (int y = 0; y < 23; y++)
			aBackgroundField[x][y] = rand() % 7;
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
	while (*IsRunning) {
		
		while (SDL_PollEvent(&E) != 0) {
			if (E.type == SDL_QUIT)
				*(IsRunning) = false;
		}

		Uint32 NewTick = SDL_GetTicks();

		//обновляем фон каждые 5 секунд
		if (NewTick - LastUpdate > 5000) {
			LastUpdate = NewTick;
			for (int x = 0; x < 40; x++)
				for (int y = 0; y < 23; y++)
					aBackgroundField[x][y] = rand() % 7;
		}

		//рисуем фон
		for (int x = 0; x < 40; x++)
			for (int y = 0; y < 23; y++) {
				SDL_Rect Clip = { aBackgroundField[x][y] * 32,0,32,32 };
				Blocks.render(x * 32, y * 32, &Clip);
			}


		//рисуем кнопки 
		//todo работа с кнопками
		Logo.render(1280 / 2 - Logo.getWidth() / 2, 75);
		SDL_Rect ButtonClip = { 0,0,OnePButton.getWidth(),OnePButton.getHeight() / 2 };
		OnePButton.render(OPButton.x, OPButton.y, &ButtonClip);
		TwoPButton.render(TPButton.x, TPButton.y, &ButtonClip);

		SDL_Rect SGClip = { 0,75, StartGame.getWidth(), StartGame.getHeight() / 2 };
		StartGame.render(SGButton.x, SGButton.y, &SGClip);

		SDL_Rect EGClip = { 0,0,ExitGame.getWidth(),ExitGame.getHeight() / 2 };
		ExitGame.render(EGButton.x, EGButton.y, &EGClip);

		SDL_RenderPresent(mRenderer);
		SDL_Delay(16);
	}


	return 0;
}

bool Menu::IsPointInRect(int x, int y, SDL_Rect &TarRect)
{
	return (x > TarRect.x && x < TarRect.x + TarRect.w
		&& y > TarRect.y && y < TarRect.y + TarRect.h);
}
