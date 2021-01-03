#include "MyApp.h"

bool MyApp::IsRunning = true;

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

				SDL_SetEventFilter(MyEventFilter, nullptr);
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
	Tetromino A;
	A.Rotate();
	A.Rotate();
	A.Rotate();
	A.Rotate();
	while(IsRunning) {
		while (SDL_PollEvent(&e) != 0){
		}

		//Меню, в нем что-от бует
		//Возвращаемое значение будет определять дальнейший ход программ
		
		//Отдельный класс с игрой, все в нем, до гейм овера


	}
}

int MyApp::MyEventFilter(void* userdata, SDL_Event* event)
{
	
	if (event->type == SDL_QUIT)
		IsRunning = false;
	return 0;
}
