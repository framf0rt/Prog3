

#include "GameEngine.h"
#include <SDL.h>
#include <vector>
#include "SpritePlayer.h"
#include <SDL_image.h>
#include "SpriteEnemy.h"
#include "SpriteStationary.h"
#include "SpriteGround.h"
#include <iostream>
using namespace std;


#define FPS 120

namespace engine {


	void GameEngine::addSprite(Sprite* s) {
		sprites.push_back(s);
	}
	
	void GameEngine::run() {
		bool running = true;


		const int TIDPERVARV = 1000 / FPS;
		dt = (float)TIDPERVARV / 1000;
		while (running) {
			//deltaTime();
			
			//cout << dt << " " << timeSinceEvent << endl;
			
			Uint32 nextTick = SDL_GetTicks() + TIDPERVARV;

			//COLLISION START 
			for (unsigned i = 0; i < sprites.size(); i++) {
				Sprite* spriteA = sprites[i];
				for (unsigned x = 0; x < sprites.size(); x++) {
					Sprite* spriteB = sprites[x];
					SpritePlayer *player = dynamic_cast<SpritePlayer*>(spriteA);
					SpriteGround *ground = dynamic_cast<SpriteGround*>(spriteB);
					SpriteEnemy *enemy = dynamic_cast<SpriteEnemy*>(spriteB);
					if (ground != NULL && player != NULL) {
						SDL_Rect *groundCollider = &(player->getCollider());
						SDL_Rect *playerCollider = &(ground->getCollider());
						if (SDL_HasIntersection(playerCollider, groundCollider)) {
							player->onCollision(spriteA, spriteB);
						}
					}
					else {
						if (player != NULL) {
							if (!player->hasJumped() && !player->hasDropped() && !player->isFalling()) {
								player->ungrounded(); // Startar fall
							}
						}
					}
					if (enemy != NULL && player != NULL) {
						if (player->hasInvunerability() == false) {
							pixelCollision(player, enemy);
						}
					}
				}


			}//COLLISION END

			// MOVEMENT START
			for (Sprite *sprite : sprites) {
				SpritePlayer *playerMove = dynamic_cast<SpritePlayer*>(sprite);
				if (playerMove != NULL) {
					SDL_Event eve;
					while (SDL_PollEvent(&eve)) {
						switch (eve.type)
						{
						case SDL_KEYDOWN:
							playerMove->move(eve);
							break;
						case SDL_KEYUP:
							playerMove->move(eve);
							break;
						case SDL_QUIT:
							running = false;
							break;
						default:
							break;
						}
					}
				}
			} // MOVEMENT END

			// RENDERING START
			updateTimeSinceEvent();
			SDL_RenderClear(getRen());
			for (Sprite *sprite : sprites) {

				SpriteMovable *movable = dynamic_cast<SpriteMovable*>(sprite);
				if (movable != NULL)
				{
					movable->tick();
					movable->draw();
				}
				else {
					sprite->tick();
					sprite->draw();
				}
			}
			SDL_RenderPresent(getRen());
			// RENDERING END






			Uint32 before = SDL_GetTicks();
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0) {
				SDL_Delay(delay);
			}
			Uint32 timeOfDelay = SDL_GetTicks() - before;
			//cout << timePassed << endl;
		}
	}

	void GameEngine::pixelCollision(Sprite* player, Sprite* enemy) {
		SpritePlayer *p = dynamic_cast<SpritePlayer*>(player);
		SpriteEnemy *e = dynamic_cast<SpriteEnemy*>(enemy);
		SDL_Rect *A = &(p->getRect());
		SDL_Rect *B = &(e->getRect());
		if (SDL_HasIntersection(A, B)) {
			p->onCollision(p, e);
		}
	}

	void GameEngine::deltaTime() {
		Uint32 now = SDL_GetTicks();
		if (now > last) {
			dt = ((float)(now - last + timeOfDelay)) / 1000;
			last = now;
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