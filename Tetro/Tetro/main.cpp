#define SDL_MAIN_HANDLED
#include "MyApp.h"
#undef main

//мейн
int SDL_main(int argc, char* argv[])

{
	MyApp App;
	App.Run();
	return 0;
}