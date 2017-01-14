#include "SpritePlayer.h"
#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include "SpriteEnemy.h"
#include <map>
#include "math.h"
using namespace std;



namespace engine {


	shared_ptr<SpritePlayer> SpritePlayer::getInstance(const SDL_Rect& r, std::string path, std::string pathMoving, float colliderSize, std::map<int, std::map<int, void(*)(SpritePlayer&)>>& f, map<string, int> comms, SDL_Renderer* re) {
		return shared_ptr<SpritePlayer>(new SpritePlayer(r, path, pathMoving, colliderSize, f, comms,re));
	}


	void SpritePlayer::move(const vector<SDL_Event>& eve) {
		for (int i = 0; i < eve.size(); i++) {
			if (commands.count(eve[i].type)) {
				if (commands[eve[i].type].count(eve[i].key.keysym.sym)) {
					commands[eve[i].type][eve[i].key.keysym.sym](*this);
				}
			}
			auto it = events.find(eve[i].type);
			if (it != events.end()) {
				auto it2 = it->second.find(eve[i].key.keysym.sym);
				if (it2 != it->second.end()) {
					(this->*(it2->second))();
				}
			}
		}

	}
	void SpritePlayer::setInvunerability() {
		invulnerable = true;
		fadeOutIn = true;
	}

	void SpritePlayer::speedOnCollision() {
		ySpeed = -0.6*(ySpeed + getTimeSinceEvent() * 600);
	}

	void SpritePlayer::tick(float dt) {
		updateTimeSinceEvent(dt);
		float edt = getTimeSinceEvent();

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
	
		if (hasGravity()) {
			rect.y = getYDistance();
		}
		


	}

	void SpritePlayer::moveLeft() {
		setDirection(-1);
		setTimeKeyDownLeft(SDL_GetTicks());
		setMoving(true);
	}

	void SpritePlayer::moveRight() {
		setDirection(1);
		setTimeKeyDownRight(SDL_GetTicks());
		setMoving(true);
	}

	void SpritePlayer::jump() {
		if (!hasGravity()) {
			resetTimeSinceEvent();
			setYSpeed(getJumpSpeed());
			setGravity(true);
		
			setYCoordAtEvent();
		}
	}

	void SpritePlayer::drop() {
		if (!hasGravity()) {
			resetTimeSinceEvent();
			setGravity(true);
		
			setYSpeed(200);
			setRectY(getRectY() + 10);
			setYCoordAtEvent();
		}
	}
	void SpritePlayer::leftUp() {
		if ((SDL_GetTicks() - getTKeyDownRight()) > 60) {
			setMoving(false);
		}
	}

	void SpritePlayer::rightUp() {
		if ((SDL_GetTicks() - getTKeyDownLeft()) > 60) {
			setMoving(false);
		}
	}
	void SpritePlayer::grounded() {
		setGravity(false);
	
	}

	void SpritePlayer::ungrounded() {
		setGravity(true);
		
		ySpeed = 0;
		resetTimeSinceEvent();
		setYCoordAtEvent();
	}

	

	void SpritePlayer::onCollision(shared_ptr<Sprite> spriteA, shared_ptr<Sprite> spriteB, float dt) {

		//Kollar om det är en spelare och spritestationary som kolliderat
		shared_ptr<SpriteStationary> ground = dynamic_pointer_cast<SpriteStationary>(spriteB);
		shared_ptr<SpriteEnemy> enemy = dynamic_pointer_cast<SpriteEnemy>(spriteB);


		if (ground != NULL)
		{
			if (ground->getIsKillZone() == 1) {
				killZoneCollision(ground);
				return;
			}

			else if (ground->getIsBounceable() == 1 && ground->getIsGround() != 0 && ground->getIsKillZone() != 1) {

				if (hasGravity()) {
					speedOnCollision();
					rect.y -= 250*dt;
					yCoordAtEvent = rect.y;
					

					if (abs(ySpeed) < 70) {

						ySpeed = 0;
						SDL_Rect groundR = ground->getCollider();
						rect.y = groundR.y - rect.h + 1;
						grounded();

					}
					resetTimeSinceEvent();

					return;
				}
			}
			else if (ground->getIsBounceable() == 0 && ground->getIsGround() == 1 && ground->getIsKillZone() != 1) {
				SDL_Rect groundR = ground->getCollider();
				rect.y = groundR.y - rect.h + 1;
				yCoordAtEvent = rect.y;
				grounded();
			}
			else if (ground->getIsGround() == 0 && ground->getIsKillZone() != 1) {
				SDL_Rect* gRect = &(ground->getRect());
				for (SDL_Rect pRect : pixelCollisionRects) {
					pRect = { pRect.x + rect.x - pRect.x,pRect.y + rect.y,pRect.w,pRect.h };
					SDL_Rect *A = &(pRect);
					if (SDL_HasIntersection(A, gRect)) {
						if (rect.x < gRect->x) {
							rect.x -= dt * MOVEMENT_SPEED;
							return;
						}
						else if (rect.x + rect.w > gRect->x) {
							rect.x += dt * MOVEMENT_SPEED;
							return;
						}
					}
				}
			}
		}

		if (enemy != NULL) {
			enemyCollision(spriteB);
		}
	}

	void SpritePlayer::enemyCollision(std::shared_ptr<Sprite> spriteB) {
		shared_ptr<SpriteEnemy> enemy = dynamic_pointer_cast<SpriteEnemy>(spriteB);
		SDL_Rect aRect = { 0,0,0,0 };
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


	void SpritePlayer::killZoneCollision(std::shared_ptr<SpriteStationary> killzone) {
		SDL_Rect aRect = { 0,0,0,0 };
		for (SDL_Rect aRect : pixelCollisionRects) {
			aRect = { aRect.x + rect.x - aRect.x,aRect.y + rect.y,aRect.w,aRect.h };
			SDL_Rect *A = &(aRect);
			SDL_Rect *B = &(killzone->getRect());
			if (SDL_HasIntersection(A, B)) {
				kill();
			}
		}
			
	}

	void SpritePlayer::kill() {

		setGravity(true);
		ungrounded();
		ySpeed = 0;
		yCoordAtEvent = startPosY;
		resetTimeSinceEvent();
		rect.x = startPosX;
		setInvunerability();
	}

	SDL_Rect SpritePlayer::getCollider() {
		SDL_Rect A = getRect();
		int size = static_cast<int>(A.w*colliderSize);
		int middlePoint = A.w / 2;
		boxCollider = { A.x + middlePoint - (size / 2),A.y + A.h - 2,size,2 };
		return boxCollider;
	}


	SpritePlayer::SpritePlayer(const SDL_Rect& r, std::string path, std::string pathMoving, float colliderSize, std::map<int, std::map<int, void(*)(SpritePlayer&)>>& f, map<string,int> comms, SDL_Renderer* re) :SpriteMovable(r, path,re), commands(f)
	{	
		map<int, void (SpritePlayer::*)()> keyUp;
		map<int, void (SpritePlayer::*)()> keyDown;
		if (comms.count("moveLeft")) {
			keyDown.insert(make_pair(comms["moveLeft"], &SpritePlayer::moveLeft));
			keyUp.insert(make_pair(comms["moveLeft"], &SpritePlayer::leftUp));
		}
		if (comms.count("moveRight")) {
			keyDown.insert(make_pair(comms["moveRight"], &SpritePlayer::moveRight));
			keyUp.insert(make_pair(comms["moveRight"], &SpritePlayer::rightUp));
		}
		if (comms.count("jump")) {
			keyDown.insert(make_pair(comms["jump"], &SpritePlayer::jump));
		}
		if (comms.count("drop")) {
			keyDown.insert(make_pair(comms["drop"], &SpritePlayer::drop));
		}
		events.insert(make_pair(SDL_KEYUP, keyUp));
		events.insert(make_pair(SDL_KEYDOWN, keyDown));
		this->colliderSize = colliderSize;
		textureMoving = IMG_LoadTexture(getRen(), pathMoving.c_str());
		textureStationary = IMG_LoadTexture(getRen(), path.c_str());
		textureSwap = false;
		startPosX = r.x;
		startPosY = r.y;
		player = true;
	}




	SpritePlayer::~SpritePlayer()
	{
	}
}
