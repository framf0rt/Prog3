

#include "GameEngine.h"
#include <SDL.h>
#include <vector>
#include "SpritePlayer.h"
#include <SDL_image.h>
using namespace std;

#define FPS 60

namespace engine {
	//void GameEngine::addSprite(Sprite* sprite) {
		//sprites.push_back(sprite);
	//}
	
	void GameEngine::run() {
		bool running = true;
		

		SpritePlayer* s = SpritePlayer::getInstance({ 100, 100, 100, 100 }, "c:/Prog3/assets/Sprites/Player.png");

		const int TIDPERVARV = 1000 / FPS;
		while (running) {
			Uint32 nextTick = SDL_GetTicks() + TIDPERVARV;
			s->tick();
			SDL_Event eve;
			while (SDL_PollEvent(&eve)) {
				switch (eve.type)
				{
				case SDL_KEYDOWN:
					s->keyDown(eve);
					break;
				case SDL_QUIT:
					running = false;
					break;
				default:
					break;
				}
			
			}

			SDL_RenderClear(getRen());
			s->draw();
			SDL_RenderPresent(getRen());

		
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);

		}

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