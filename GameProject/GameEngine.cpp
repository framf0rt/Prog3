

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
		
		

		SpritePlayer* s = SpritePlayer::getInstance({ 100, 100, 100, 100 }, "c:/Prog3/assets/Sprites/BallSprite_cut_0.png", "c:/Prog3/assets/Sprites/BallSprite_cut_180.png");
		SpriteEnemy* se = SpriteEnemy::getInstance({ 200,200, 100, 100 }, "c:/Prog3/assets/Sprites/BirdEnemyIdleSprite.png", "c:/Prog3/assets/Sprites/BirdEnemyFlapSprite.png", 20, s);
		SpriteStationary* sg = SpriteStationary::getInstance({ 300,300,200,100 }, "c:/Prog3/assets/Sprites/GrassSprite.png");
		SpriteStationary* sg1 = SpriteStationary::getInstance({ 300,300,200,100 }, "c:/Prog3/assets/Sprites/GrassSprite.png");
		cout << se->getHp() << endl;


		std::vector<Sprite*> sprites;
		sprites.push_back(s);
		sprites.push_back(se);
		sprites.push_back(sg);


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

			// RENDERING START
			SDL_RenderClear(getRen());
			for(Sprite *sprite : sprites) {
				SpriteMovable *p = dynamic_cast<SpriteMovable*>(sprite);
				if (p != NULL)
				{
					p->tick();
					p->draw();
				}
				else {
				sprite->tick();
				sprite->draw();
				}
			}
			SDL_RenderPresent(getRen());
			// RENDERING END

			

	

			//COLLISION START 
			for (unsigned i = 0; i < sprites.size(); i++) {
				Sprite* spriteA = sprites[0];
				Sprite* spriteB = sprites[2];

				
				SDL_Rect *A = &(spriteA->getRect());
				SDL_Rect *B = &(spriteB->getRect());
				SDL_Rect result = { 0,0,0,0 };
				SDL_Rect *r = &(result);


				if (SDL_HasIntersection(A, B)) {

					SDL_UnionRect(A, B, r);
					if ((result.x > 10) && (result.y > 10)) {
						if ((A->y + (A->h - 4)) < (B->y)) { // H�jden p� A m�ste tas bort f�r att �versta v�nstra h�rnet r�knas. 
							s->onCollision(s, sg);
						}

					}
					else {
						int y = 0;
						for (int x = 0; x < result.x + 1; x++) {
							for (; y < result.y + 1; y++) {
								int alphaS = s->getAlphaXY(x, y);
								int alphaT = se->getAlphaXY(x, y);
								if (alphaS > 0 && alphaT > 0) {
									s->onCollision(s, se);
									se->onCollision(se, s);
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

	}
	



	GameEngine::GameEngine()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("GameEngine", 100, 100, 600, 600, 0);
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