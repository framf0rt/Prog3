

#include "GameEngine.h"
#include <SDL.h>
#include <vector>
#include "SpritePlayer.h"
#include <SDL_image.h>
#include "SpriteEnemy.h"
#include "SpriteStationary.h"
#include <iostream>
using namespace std;

#define FPS 120

namespace engine {


	//void GameEngine::addSprite(Sprite* sprite) {
	//	sprites.push_back(sprite);
	//}
	
	void GameEngine::run() {
		bool running = true;
		
		

		SpritePlayer* s = SpritePlayer::getInstance({ 100, 100, 100, 100 }, "c:/Prog3/assets/Sprites/BirdEnemyIdleSprite.png", "c:/Prog3/assets/Sprites/BirdEnemyFlapSprite.png");
		SpriteEnemy* se = SpriteEnemy::getInstance({ 200,200, 100, 100 }, "c:/Prog3/assets/Sprites/BirdEnemyIdleSprite.png", "c:/Prog3/assets/Sprites/BirdEnemyFlapSprite.png", 20, s);
		SpriteStationary* sg = SpriteStationary::getInstance({ 300,300,100,100 }, "c:/Prog3/assets/Sprites/GrassSprite.png");
	
		cout << se->getHp() << endl;

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
			se->tick();
			
			SDL_RenderClear(getRen());
			
			s->draw();
			se->draw();
			sg->draw();

			
			SDL_RenderPresent(getRen());




			//COLLISION START 
			SDL_Rect *A = &(s->getRect());
			SDL_Rect *B = &(sg->getRect());
			SDL_Rect result = { 0,0,0,0 };
			SDL_Rect *r = &(result);


			if (SDL_HasIntersection(A, B)) {

				SDL_UnionRect(A, B, r); 
				if ((result.x > 10) && (result.y > 10)) {
					if ((A->y + (A->h - 4)) < (B->y)) { // Höjden på A måste tas bort för att översta vänstra hörnet räknas. 
						s->onCollision(s,sg);
						
											
					}
				
				}
				else {
					int y = 0;
					for (int x = 0; x < result.x + 1; x++) {
						for (; y < result.y + 1; y++) {
							int alphaS = s->getAlphaXY(x, y);
							int alphaT = se->getAlphaXY(x, y);
							if (alphaS > 0 && alphaT > 0) {
								// DO SOMETHING ON PER PIXEL COLLISION
								//s->ground();
								break;
							}
						}
					}
				}
			}
			else {
			//	cout << "FALL" << endl;
				s->ungrounded(); // Startar fall
			}
			//COLLISION END
		
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);

		}

	}
	



	GameEngine::GameEngine()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("GameEngine", 100, 100, 1000, 1000, 0);
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