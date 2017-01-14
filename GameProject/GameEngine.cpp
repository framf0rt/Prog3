

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

	void GameEngine::addLevel(shared_ptr<Level> l)
	{
		levels.push_back(l);
	}

	void GameEngine::run() {
		vector<SDL_Event> events;
		bool running = true;
		last = SDL_GetTicks();

		const int TIDPERVARV = 1000 / FPS;
		dt = (float)TIDPERVARV / 1000;

		setLevel(0);
		while (running) {

			Uint32 nextTick = SDL_GetTicks() + TIDPERVARV;
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				events.push_back(event);
			}

			for (int i = 0; i < events.size(); i++) {
				//här anropas callBack funktioner till main
				if (!callBack.empty()) {
					if (callBack.count(events[i].type)) {
						if (callBack[events[i].type].count(events[i].key.keysym.sym)) {
							callBack[events[i].type][events[i].key.keysym.sym]();
						}
					}
				}

				switch (events[i].type)
				{
				case SDL_KEYDOWN:
					if (events[i].key.keysym.sym == pauseKey) {
						((*this).*pausePointer)();
					}
					break;
				case SDL_QUIT:
					running = false;
					break;
				default:
					break;
				}
			}

			if (!paused) {

				for (unsigned i = 0; i < sprites.size(); i++) {
					shared_ptr<Sprite> spriteA = sprites[i];
					for (unsigned x = 0; x < sprites.size(); x++) {
						shared_ptr<Sprite> spriteB = sprites[x];
						shared_ptr<SpritePlayer> player = dynamic_pointer_cast<SpritePlayer>(spriteA);
						shared_ptr<SpriteStationary> ground = dynamic_pointer_cast<SpriteStationary>(spriteB);
						shared_ptr<SpriteEnemy> enemy = dynamic_pointer_cast<SpriteEnemy>(spriteB);

						if (ground != NULL && player != NULL && ground->getIsVictoryCond() == true){
							if (player->victoryCollision(ground) == true) {
								getNextLevel(levelNumber += 1);
							}
						}

						if (ground != NULL && player != NULL && ground->getIsKillZone() == true) {
							if (ground->getIsGround() == 0) {
								player->onCollision(spriteA, spriteB, dt);
							}
						}

						if (ground != NULL && player != NULL) {
							SDL_Rect *groundCollider = &(player->getCollider());
							SDL_Rect *playerCollider = &(ground->getCollider());
							if (SDL_HasIntersection(playerCollider, groundCollider)) {
								player->onCollision(spriteA, spriteB,dt);
							}
						}
						else {

							if (player != NULL) {
								if (!player->hasGravity()) {
									player->ungrounded(); 
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
				for (unsigned i = 0; i < sprites.size(); i++) {
					shared_ptr<Sprite> sprite = sprites[i];
					shared_ptr<SpritePlayer> playerMove = dynamic_pointer_cast<SpritePlayer>(sprite);
					shared_ptr<SpriteLabel> label = dynamic_pointer_cast<SpriteLabel>(sprite);
					shared_ptr<SpriteLabelEditable> labelEdit = dynamic_pointer_cast<SpriteLabelEditable>(sprite);
					if (playerMove != NULL) {
						//SDL_Event eve;

						playerMove->move(events);

					}
					if (label != NULL && start == false) {
						for (int i = 0; i < events.size(); i++) {
							switch (events[i].type)
							{
							case SDL_QUIT:
								running = false;
								break;
							case SDL_TEXTINPUT:
								if (labelEdit != NULL) {
									labelEdit->addCharacter(events[i]);
								}
								break;

							case SDL_KEYDOWN:
								if (events[i].key.keysym.sym == SDLK_RETURN) {
									if (labelEdit != NULL) {
										labelEdit->emptyText(events[i]);

										getNextLevel(levelNumber+=1);

									}
								}
								else {
									if (labelEdit != NULL) {
										labelEdit->removeCharacter(events[i]);
									}
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
			for (unsigned i = 0; i < sprites.size(); i++) {
				shared_ptr<Sprite> sprite = dynamic_pointer_cast<Sprite>(sprites[i]);
				shared_ptr<SpriteMovable> movable = dynamic_pointer_cast<SpriteMovable>(sprites[i]);
				shared_ptr<SpriteLabel> label = dynamic_pointer_cast<SpriteLabel>(sprites[i]);
				shared_ptr<SpriteLabelEditable> labelEdit = dynamic_pointer_cast<SpriteLabelEditable>(sprites[i]);
				if (movable != NULL)
				{
					movable->tick(dt);
					movable->draw();
				}
				else if (labelEdit != NULL || label != NULL) {

					if (labelEdit != NULL) {
						labelEdit->draw();
					}
					else {
						label->draw();
					}
				}

				else if (sprite != NULL && labelEdit == NULL && label == NULL) {
					sprite->tick(dt);
					sprite->draw();
				}
			}
			SDL_RenderPresent(getRen());
			// RENDERING END

			} // DELAY START
			events.clear();
			Uint32 before = SDL_GetTicks();
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0) {
				SDL_Delay(delay);
			}
			Uint32 timeOfDelay = SDL_GetTicks() - before;
		} // DELAY END
	}


	void GameEngine::getNextLevel(int level) {
		setLevel(level);
	}

	void GameEngine::setLevel(int level) {
		int size = levels.size();
	
		if (level < levels.size()) {
			sprites.assign(levels[level]->getSprites().begin(), levels[level]->getSprites().end());
		}

	}

	void GameEngine::pixelCollision(shared_ptr<Sprite> player, shared_ptr<Sprite> enemy) {
		shared_ptr<SpritePlayer> p = dynamic_pointer_cast<SpritePlayer>(player);
		shared_ptr<SpriteEnemy> e = dynamic_pointer_cast<SpriteEnemy>(enemy);
		SDL_Rect *A = &(p->getRect());
		SDL_Rect *B = &(e->getRect());
		if (SDL_HasIntersection(A, B)) {
			p->onCollision(p, e,dt);
		}
	}

	void GameEngine::deltaTime() {
		Uint32 now = SDL_GetTicks();
		if (now > last) {
			dt = ((float)(now - last )) / 1000;
			//+timeOfDelay
			last = now;
		}
	}

	void GameEngine::pause() {
		pauseTime = SDL_GetTicks();
		paused = true;
		pausePointer = &GameEngine::resume;

	}
	
	void GameEngine::resume() {
		last += SDL_GetTicks() - pauseTime;
		paused = false;
		pausePointer = &GameEngine::pause;
	}

	GameEngine::GameEngine()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 750, 0);
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