

#include "GameEngine.h"
#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include <SDL_image.h>
using namespace std;

namespace engine {
	//void GameEngine::addSprite(Sprite* sprite) {
		//sprites.push_back(sprite);
	//}
	
	void GameEngine::run() {
		SDL_RenderClear(getRen());
		//SDL_Texture* text = IMG_LoadTexture(ren, "c:/Prog3/assets/Sprites/Player.png");
		
		Sprite* s = new Sprite({ 100, 100, 100, 100 }, "c:/Prog3/assets/Sprites/Player.png");
		
		// yvghj
		s->draw();
		//SDL_RenderCopy(ren, text, NULL, NULL);
		SDL_RenderPresent(getRen());

		SDL_Delay(5000);

		//SDL_DestroyTexture(text);
		
	}
	



	GameEngine::GameEngine()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("GameEngine", 100, 100, 500, 500, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
	}


	GameEngine::~GameEngine()
	{
		
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
	}
	GameEngine ge;
}