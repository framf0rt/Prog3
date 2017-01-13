#include "SpritePlayer.h"
#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include "SpriteEnemy.h"
#include <map>
#include "math.h"
using namespace std;



namespace engine {


	SpritePlayer* SpritePlayer::getInstance(const SDL_Rect& r, std::string path, std::string pathMoving, float colliderSize, std::map<int, std::map<int, void(*)(SpritePlayer&)>>& f) {
		return new SpritePlayer(r, path, pathMoving, colliderSize, f);
	}


	void SpritePlayer::keyDown(const SDL_Event& eve) {

	}


	void SpritePlayer::move(const SDL_Event& eve) {

		if (commands.count(eve.type)) {
			if (commands[eve.type].count(eve.key.keysym.sym)) {
				commands[eve.type][eve.key.keysym.sym](*this);
			}
		}
	}
	void SpritePlayer::setInvunerability() {
		invulnerable = true;
		fadeOutIn = true;
	}

	void SpritePlayer::speedOnCollision() {
		ySpeed = -0.6*(ySpeed + ge.getTimeSinceEvent() * 600);
	}

	void SpritePlayer::tick() {
		float dt = ge.getDeltaTime();
		float edt = ge.getTimeSinceEvent();

		if (alphaModifier <= 256 && alphaModifier > 125 && fadeOutIn == true) {
			alphaModifier -= 100 * dt;
		}
		else if (alphaModifier < 255) {
			alphaModifier += 100 * dt;
			fadeOutIn = false;
			if (alphaModifier >= 254) {
				invulnerable = false;
			}
		}

		if (moving) {
			rect.x += (int)(dt*MOVEMENT_SPEED*direction);
			if (direction < 1) {

				if (rotation < -360) {
					rotation = 0;
				}
				else {
					rotation -= (int)(dt * 400);
				}
			}
			else {

				if (rotation > 360) {
					rotation = 0;
				}
				else {
					rotation += (int)(dt * 400);
				}
			}
		}
		/*	if (jumped && (dropped == false)) {
				rect.y = yCoordAtEvent + edt * ySpeed + (600*edt*edt/2);
			}

			if (dropped) {
				rect.y = yCoordAtEvent + ySpeed*edt + (edt*edt*600/2);
			}
			if (falling) {
				cout << "faller" << endl;
				rect.y = yCoordAtEvent + ySpeed*edt +(edt*edt*600/2);
			}*/
		if (jumped || dropped || falling) {
			rect.y = yCoordAtEvent + ySpeed*edt + (edt*edt * 600 / 2);
		}


	}

	void SpritePlayer::grounded() {
		jumped = false;
		dropped = false;
		falling = false;
	}

	void SpritePlayer::ungrounded() {
		falling = true;
		jumped = false;
		dropped = false;
		ge.resetTimeSinceEvent();
		setYCoordAtEvent();
	}



	void SpritePlayer::onCollision(Sprite* spriteA, Sprite* spriteB) {
		float dt = ge.getDeltaTime();

		//Kollar om det är en spelare och spritestationary som kolliderat
		SpriteStationary *ground = dynamic_cast<SpriteStationary*>(spriteB);
		SpriteEnemy *enemy = dynamic_cast<SpriteEnemy*>(spriteB);


		if (ground != NULL)
		{
			if (ground->getIsKillZone() == 1) {
			
			}

			else if (ground->getIsBounceable() == 1 && ground->getIsGround() != 0 && ground->getIsKillZone() != 1) {

				if (!(jumped && dropped && falling)) {

					speedOnCollision();
					//jumped = false;
					//dropped = false;
					//falling = true;
					//cout << ySpeed << endl;
					rect.y -= 2;
					yCoordAtEvent = rect.y;
					//cout << ySpeed << endl;

					if (abs(ySpeed) < 70) {

						ySpeed = 0;
						SDL_Rect groundR = ground->getCollider();
						rect.y = groundR.y - rect.h + 1;
						grounded();

					}
					ge.resetTimeSinceEvent();

					return;
				}
			}
			else if (ground->getIsBounceable() == 0 && ground->getIsGround() == 1 && ground->getIsKillZone() != 1) {
				SDL_Rect groundR = ground->getCollider();
				rect.y = groundR.y - rect.h + 1;
				grounded();
			}
			else if (ground->getIsGround() == 0 && ground->getIsKillZone() != 1) {
				SDL_Rect* gRect = &(ground->getRect());
				for (SDL_Rect pRect : pixelCollisionRects) {
					pRect = { pRect.x + rect.x - pRect.x,pRect.y + rect.y,pRect.w,pRect.h };
					SDL_Rect *A = &(pRect);
					if (SDL_HasIntersection(A, gRect)) {
						if (rect.x < gRect->x) {
							rect.x = rect.x - 1;
							return;
						}
						else if (rect.x + rect.w > gRect->x) {
							rect.x = rect.x + 1;
							return;
						}
					}
				}
			}
		}

		if (enemy != NULL) {
			std::vector<SDL_Rect> pixelCollisionRectsB = enemy->getPixelCollisionRects();
			for (SDL_Rect aRect : pixelCollisionRects) {
				aRect = { aRect.x + rect.x - aRect.x,aRect.y + rect.y,aRect.w,aRect.h };
				for (SDL_Rect bRect : pixelCollisionRectsB) {
					SDL_Rect enemyRect = enemy->getRect();
					bRect = { bRect.x + enemyRect.x - bRect.x,bRect.y + enemyRect.y,bRect.w,bRect.h };
					SDL_Rect *A = &(aRect);
					SDL_Rect *B = &(bRect);
					if (SDL_HasIntersection(A, B)) {
						SDL_Rect result = { 0,0,0,0 };
						SDL_Rect* r = &(result);
						SDL_UnionRect(A, B, r);
						setInvunerability();
						return;
					}
				}
			}
		}
	}


	void SpritePlayer::kill() {

		std::cout << startPosX << startPosY << std::endl;
		falling = true;
		jumped = false;
		dropped = false;
		ge.resetTimeSinceEvent();
		rect.x = 0;
		std::cout << rect.x << rect.y << std::endl;
	
	}

	SDL_Rect SpritePlayer::getCollider() {
		SDL_Rect A = getRect();
		int size = static_cast<int>(A.w*colliderSize);
		//std::cout << size << std::endl;
		int middlePoint = A.w / 2;
		boxCollider = { A.x + middlePoint - (size / 2),A.y + A.h - 2,size,2 };
		return boxCollider;
	}


	SpritePlayer::SpritePlayer(const SDL_Rect& r, std::string path, std::string pathMoving, float colliderSize, std::map<int, std::map<int, void(*)(SpritePlayer&)>>& f) :SpriteMovable(r, path), commands(f)
	{
		this->colliderSize = colliderSize;
		textureMoving = IMG_LoadTexture(ge.getRen(), pathMoving.c_str());
		textureStationary = IMG_LoadTexture(ge.getRen(), path.c_str());
		textureSwap = false;
		startPosX = r.x;
		startPosY = r.y;
		player = true;
	}




	SpritePlayer::~SpritePlayer()
	{
	}
}
