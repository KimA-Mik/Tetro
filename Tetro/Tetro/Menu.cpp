#include "Menu.h"
//UTF-8 Коммент

Menu::Menu(SDL_Renderer* Renderer, bool* PorgramStatus)
{
	mRenderer = Renderer;
	IsRunning = PorgramStatus;
	Blocks.loadFromFile(mRenderer, "Assets/Images/Tetro.png");

	for (int x = 0; x < 40; x++)
		for (int y = 0; y < 23; y++)
			aBackgroundField[x][y] = rand() % 7;
}

Menu::~Menu()
{
	Blocks.free();
	//Background.free();
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


		for (int x = 0; x < 40; x++)
			for (int y = 0; y < 23; y++) {
				SDL_Rect Clip = { aBackgroundField[x][y] * 32,0,32,32 };
				Blocks.render(x * 32, y * 32, &Clip);
			}
		SDL_RenderPresent(mRenderer);
		SDL_Delay(16);
	}


	return 0;
}
