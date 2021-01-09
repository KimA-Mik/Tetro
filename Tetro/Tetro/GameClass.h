#pragma once
#include <SDL.h>
class GameClass
{
public:
	GameClass(SDL_Renderer* Renderer, bool* PorgramStatus)
	{
		mRenderer = Renderer;
		IsRunning = PorgramStatus;
	}
	virtual ~GameClass() {}

	virtual void Init() {}
	virtual int Run() { return 0; }
protected:
	SDL_Renderer* mRenderer = nullptr;
	bool* IsRunning = nullptr;
};

