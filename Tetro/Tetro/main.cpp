#define SDL_MAIN_HANDLED
#include "MyApp.h"
#undef main
#include <ctime>
//мейн
int SDL_main(int argc, char* argv[])

{
	srand(time(nullptr));
	MyApp App;
	App.Run();
	return 0;
}