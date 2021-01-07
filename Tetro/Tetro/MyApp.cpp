#include "MyApp.h"


MyApp::MyApp()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		IsRunning = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: Linear texture filtering not enabled!");

		mWindow = SDL_CreateWindow("Tetro Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
		if (mWindow == nullptr) {
			printf("Windows could not be created! SDL Error: %s\n", SDL_GetError());
			IsRunning = false;
		}
		else {
			
			
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
			if (mRenderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				IsRunning = false;
			}
			else {

				//Загрузка PNG
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					IsRunning = false;
				}
				//SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					IsRunning = false;
				}
			}
		}
	}
}

MyApp::~MyApp()
{

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void MyApp::Run()
{
	Menu* MyMenu = nullptr;
	Game* MyGame = nullptr;
	while(IsRunning) {
		while (SDL_PollEvent(&e) != 0){
		}

		//Меню, в нем что-от бует
		MyMenu = new Menu(mRenderer, &IsRunning);
		int PlayerSelect = MyMenu->Run();
		delete MyMenu;
		//Возвращаемое значение будет определять дальнейший ход программ
		MyGame = new Game(mRenderer, &IsRunning);
		MyGame->Init();
		MyGame->Run();
		delete MyGame;
		//Отдельный класс с игрой, все в нем, до гейм овера


	}
}

