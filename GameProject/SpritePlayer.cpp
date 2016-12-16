#include "SpritePlayer.h"
#include <SDL.h>
#include <iostream>




namespace engine {


	SpritePlayer* SpritePlayer::getInstance(const SDL_Rect& r, std::string path) {
		return new SpritePlayer(r, path);
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
		}
		
		if (jumped) {
			//std::cout << "hoppar" << std::endl;
			rect.y -= (dt * JUMP_SPEED - (dtJump() * 10));
		}
		
	}


	SpritePlayer::SpritePlayer(const SDL_Rect& r, std::string path):SpriteMovable(r,path)
	{

	}


	SpritePlayer::~SpritePlayer()
	{
	}
}
