#include "GameEngine.h"
#include <SDL.h>



int main(int argvc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* win = SDL_CreateWindow("GameEngine", 100, 100, 500, 500, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	
	

	SDL_Delay(5000);

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}


GameEngine::GameEngine()
{
}


GameEngine::~GameEngine()
{
}
