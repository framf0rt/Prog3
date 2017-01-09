#include "SpritePlayer.h"
#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include "SpriteEnemy.h"



namespace engine {


	SpritePlayer* SpritePlayer::getInstance(const SDL_Rect& r, std::string path, std::string pathMoving, float colliderSize) {
		return new SpritePlayer(r, path, pathMoving, colliderSize);
	}

	//void SpritePlayer::deltaTime() {
	//	Uint32 now = SDL_GetTicks();
	//	if (now > last) {
	//		dt = ((float)(now - last)) / 1000;
	//			last = now;
	//	}
	//}

	void SpritePlayer::draw() {
		
	}

	float SpritePlayer::dtJump() {
		float jdt = 0;
		Uint32 now = SDL_GetTicks();
		if (now > timeOfJump) {
			jdt = ((float)(now - timeOfJump)) / 1000;
		}
		return jdt;
	}
	float SpritePlayer::dtFall() {
		float fdt = 0;
		Uint32 now = SDL_GetTicks();
		if (now > timeOfFall) {
			fdt = ((float)(now - timeOfFall)) / 1000;
		}
		return fdt;
	}
	float SpritePlayer::dtDrop() {
		float ddt = 0;
		Uint32 now = SDL_GetTicks();
		if (now > timeOfDrop) {
			ddt = ((float)(now - timeOfDrop)) / 1000;
		}
		return ddt;
	}

	void SpritePlayer::keyDown(const SDL_Event& eve) {
		
	}

	
	void SpritePlayer::move(const SDL_Event& eve) {
		switch (eve.type)
		{
		case SDL_KEYUP:
			switch (eve.key.keysym.sym) {
			case SDLK_LEFT:
				if (SDL_GetTicks() - tKeyDownRight > 60) {
					moving = false;
					//std::cout << "left upp" << std::endl;
					//std::cout << SDL_GetTicks() << std::endl;
				}
				break;
			case SDLK_RIGHT:
				if (SDL_GetTicks() - tKeyDownLeft > 60) {
					//std::cout << "right up" << std::endl;
					//std::cout << SDL_GetTicks() << std::endl;
					moving = false;
				}
				break;
			default:
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch (eve.key.keysym.sym)
			{
			case SDLK_RIGHT:
				//rect.x += (int)(300 * dt);
				//std::cout << "RIGHT"<<std::endl;
				direction = 1;
				moving = true;
				tKeyDownRight = SDL_GetTicks();
				//std::cout << "Right" << std::endl;
				//std::cout << SDL_GetTicks() << std::endl;

				break;
			case SDLK_LEFT:
				direction = -1;
				tKeyDownLeft = SDL_GetTicks();
				moving = true;

				//std::cout << "LEFT" << std::endl;
				//std::cout << SDL_GetTicks() << std::endl;
				break;
			case SDLK_SPACE:
				timeOfJump = SDL_GetTicks();
				jumped = true;
				dropped = false;
				falling = false;
				
				std::cout << "SPACE" << std::endl;
				break;
			case SDLK_DOWN: // Neråt från en platform man står på
				timeOfDrop = SDL_GetTicks();
				dropped = true;
				rect.y += 10;
				//std::cout << "SPACE" << std::endl;
				break;
			default:
				break;
			}
			
			break;
		

		default:
			break;
		}
		
	}
	void SpritePlayer::tick() {
		float dt = ge.getDeltaTime();
		if (moving) {
			rect.x += (int)(dt*MOVEMENT_SPEED*direction);

			if (direction < 1) {
				if (rotation == 360) {
					rotation = 0;
				}
				else {
					rotation -= 5;
				}
			}
			else {
				if (rotation == 360) {
					rotation = 0;
				}
				else {
					rotation += 5;
				}
			}
			
			

			//if (animationCount > 100) {
			//	animation(*textureMoving); // Animation, byter texture
			//	animationCount = 0;
			//}
			//if (animationCount > 50 && animationCount < 100) {
			//	animation(*textureStationary); // Animation, byter texture
			//}

		}
		if (jumped && (dropped == false)) {
			rect.y -= (dt * JUMP_SPEED - (dtJump() * 5));
		}

		if (dropped) {
			rect.y -= (dt *- (JUMP_SPEED) - (dtDrop() * 5));
		}
		if (falling) {
			rect.y -= (dt *-JUMP_SPEED - (dtFall() * 5));
		}
		
	}

	void SpritePlayer::grounded() {
		jumped = false;
		dropped = false; 
		falling = false;
	}

	void SpritePlayer::ungrounded() {
		falling = true;
		timeOfFall = SDL_GetTicks();
	}

	void SpritePlayer::onCollision(Sprite* spriteA, Sprite* spriteB) {

		//Kollar om det är en spelare och spritestationary som kolliderat
		SpriteGround *ground = dynamic_cast<SpriteGround*>(spriteB);
		SpriteEnemy *enemy = dynamic_cast<SpriteEnemy*>(spriteB);
		if (ground != NULL)
		{
			if (!(jumped && dropped && falling)) {
				SDL_Rect groundR = ground->getCollider();
				rect.y = groundR.y - rect.h + 1;
				grounded();
				return;
			}
		}

		if(enemy != NULL){
			// What do we do know?
			std::cout << "Enemy hit" << std::endl;
		}


	}

	SDL_Rect SpritePlayer::getCollider() {
		SDL_Rect A = getRect();
		int size =static_cast<int>(A.w*colliderSize);
		//std::cout << size << std::endl;
		int middlePoint = A.w / 2;
		boxCollider = {A.x + middlePoint-(size/2),A.y + A.h-2,size,2 };
		return boxCollider;
	}


	SpritePlayer::SpritePlayer(const SDL_Rect& r, std::string path, std::string pathMoving, float colliderSize):SpriteMovable(r,path)
	{
	this->colliderSize = colliderSize;
	textureMoving = IMG_LoadTexture(ge.getRen(), pathMoving.c_str());
	textureStationary = IMG_LoadTexture(ge.getRen(), path.c_str());
	textureSwap = false;
	}

	


	SpritePlayer::~SpritePlayer()
	{
	}
}
