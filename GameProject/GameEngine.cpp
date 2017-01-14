

#include "GameEngine.h"
#include <SDL.h>
#include <vector>
#include "SpritePlayer.h"
#include <SDL_image.h>
#include "SpriteEnemy.h"
#include "SpriteStationary.h"
#include "SpriteLabel.h"
#include "SpriteLabelEditable.h"
#include <iostream>

using namespace std;


#define FPS 60

namespace engine {


	void GameEngine::addSprite(shared_ptr<Sprite> s) {
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

			for (unsigned i = 0; i < sprites.size(); i++) {
				shared_ptr<Sprite> spriteA = sprites[i];
				for (unsigned x = 0; x < sprites.size(); x++) {
					shared_ptr<Sprite> spriteB = sprites[x];
					shared_ptr<SpritePlayer> player = dynamic_pointer_cast<SpritePlayer>(spriteA);
					shared_ptr<SpriteStationary> ground = dynamic_pointer_cast<SpriteStationary>(spriteB);
					shared_ptr<SpriteEnemy> enemy = dynamic_pointer_cast<SpriteEnemy>(spriteB);
					if (ground != NULL && player != NULL) {
						SDL_Rect *groundCollider = &(player->getCollider());
						SDL_Rect *playerCollider = &(ground->getCollider());
						if (SDL_HasIntersection(playerCollider, groundCollider)) {
							player->onCollision(spriteA, spriteB);
						}
					}
					else {
						
						if (player != NULL) {
							if (!player->hasGravity()) {
								player->ungrounded(); // Startar fall
							}
						}
					}
					if (enemy != NULL && player != NULL) {
						if (player->hasInvunerability() == false) {
							pixelCollision(player, enemy);
						}
					}

					if (ground != NULL && player != NULL) {
						if (ground->getIsGround() == 0) {
							player->onCollision(spriteA, spriteB);
						}
					}
				}


			}//COLLISION END

			// MOVEMENT START
			for (shared_ptr<Sprite> sprite : sprites) {
				shared_ptr<SpritePlayer> playerMove = dynamic_pointer_cast<SpritePlayer>(sprite);
				shared_ptr<SpriteLabelEditable> labelEdit = dynamic_pointer_cast<SpriteLabelEditable>(sprite);
				if (playerMove != NULL) {
					SDL_Event eve;
					while (SDL_PollEvent(&eve)) {
						switch (eve.type)
						{
						case SDL_QUIT:
							running = false;
						break;
						default:
							break;
						}
						playerMove->move(eve);
					}
				}
				if ( labelEdit != NULL && start == false) {
					SDL_Event e;
					while (SDL_PollEvent(&e)) {
						switch (e.type)
						{
						case SDL_QUIT:
							running = false;
							break;
						case SDL_TEXTINPUT:
							labelEdit->addCharacter(e);
						break;
						case SDL_KEYDOWN:
							if (e.key.keysym.sym == SDLK_RETURN) {
								start = true;
								labelEdit->emptyText(e);
							}
							else {
							labelEdit->removeCharacter(e);
								}
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
			for (shared_ptr<Sprite> sprite : sprites) {

				shared_ptr<SpriteMovable> movable = dynamic_pointer_cast<SpriteMovable>(sprite);
				shared_ptr<SpriteLabel> label = dynamic_pointer_cast<SpriteLabel>(sprite);
				shared_ptr<SpriteLabelEditable> labelEdit = dynamic_pointer_cast<SpriteLabelEditable>(sprite);
				if (movable != NULL && start != false)
				{
					movable->tick();
					movable->draw();
				}
				else if ((labelEdit != NULL || label != NULL) && start != true) {
					
					if (labelEdit != NULL) {
						labelEdit->draw();
					}
					else {
						label->draw();
					}
				}

				else if (start != false && labelEdit == NULL && label == NULL){
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

	void GameEngine::pixelCollision(shared_ptr<Sprite> player, shared_ptr<Sprite> enemy) {
		shared_ptr<SpritePlayer> p = dynamic_pointer_cast<SpritePlayer>(player);
		shared_ptr<SpriteEnemy> e = dynamic_pointer_cast<SpriteEnemy>(enemy);
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