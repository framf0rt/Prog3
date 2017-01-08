#include "SpritePlayer.h"
#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include "SpriteEnemy.h"



namespace engine {


	SpritePlayer* SpritePlayer::getInstance(const SDL_Rect& r, std::string path, std::string pathMoving) {
		return new SpritePlayer(r, path, pathMoving);
	}

	//void SpritePlayer::deltaTime() {
	//	Uint32 now = SDL_GetTicks();
	//	if (now > last) {
	//		dt = ((float)(now - last)) / 1000;
	//			last = now;
	//	}
	//}

	float SpritePlayer::dtJump() {
		float jdt = 0;
		Uint32 now = SDL_GetTicks();
		if (now > timeOfJump) {
			jdt = ((float)(now - timeOfJump)) / 1000;
		}
		return jdt;
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
					std::cout << "left upp" << std::endl;
					std::cout << SDL_GetTicks() << std::endl;
				}
				break;
			case SDLK_RIGHT:
				if (SDL_GetTicks() - tKeyDownLeft > 60) {
					std::cout << "right up" << std::endl;
					std::cout << SDL_GetTicks() << std::endl;
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
				std::cout << "Right" << std::endl;
				std::cout << SDL_GetTicks() << std::endl;

				break;
			case SDLK_LEFT:
				direction = -1;
				tKeyDownLeft = SDL_GetTicks();
				moving = true;

				std::cout << "LEFT" << std::endl;
				std::cout << SDL_GetTicks() << std::endl;
				break;
			case SDLK_SPACE:
				timeOfJump = SDL_GetTicks();
				jumped = true;
				std::cout << "SPACE" << std::endl;
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
		deltaTime();
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
		if (jumped) {
			rect.y -= (dt * JUMP_SPEED - (dtJump() * 10));
		}
		
	}

	void SpritePlayer::grounded() {
		jumped = false;
	}

	void SpritePlayer::ungrounded() {
		jumped = true;
	}

	void SpritePlayer::onCollision(Sprite* spriteA, Sprite* spriteB) {

		//Kollar om det är en spelare och spritestationary som kolliderat
		SpriteStationary *ground = dynamic_cast<SpriteStationary*>(spriteB);
		SpriteEnemy *enemy = dynamic_cast<SpriteEnemy*>(spriteB);
		if (ground != NULL)
		{
			grounded();
			return;
		}

		if(enemy != NULL){
			// What do we do know?
		std::cout << "Enemy hit" << std::endl;
		}


	}


	SpritePlayer::SpritePlayer(const SDL_Rect& r, std::string path, std::string pathMoving):SpriteMovable(r,path)
	{
	textureMoving = IMG_LoadTexture(ge.getRen(), pathMoving.c_str());
	textureStationary = IMG_LoadTexture(ge.getRen(), path.c_str());
	}

	


	SpritePlayer::~SpritePlayer()
	{
	}
}
