

#include "GameEngine.h"
#include <SDL.h>
#include <vector>
#include "SpritePlayer.h"
#include <SDL_image.h>
#include "SpriteEnemy.h"
#include <iostream>
using namespace std;

#define FPS 120

namespace engine {
	//void GameEngine::addSprite(Sprite* sprite) {
		//sprites.push_back(sprite);
	//}
	
	void GameEngine::run() {
		bool running = true;
		
		SpriteEnemy* se = SpriteEnemy::getInstance({ 200,200, 100, 100 }, "c:/Prog3/assets/Sprites/BirdEnemyFlapSprite.png", 20);
		cout << se->getHp() << endl;

		SpritePlayer* s = SpritePlayer::getInstance({ 100, 100, 100, 100 }, "c:/Prog3/assets/Sprites/Player.png");
		

		const int TIDPERVARV = 1000 / FPS;
		while (running) {
			Uint32 nextTick = SDL_GetTicks() + TIDPERVARV;
			
			SDL_Event eve;
			while (SDL_PollEvent(&eve)) {
				switch (eve.type)
				{
				case SDL_KEYDOWN:
					s->move(eve);
					break;
				case SDL_KEYUP:
					s->move(eve);
					break;
				case SDL_QUIT:

					running = false;
					break;
				default:
					break;
				}
			
			}
			s->tick();
			
			SDL_RenderClear(getRen());
			
			s->draw();
			se->draw();
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