#include "SpritePlayer.h"
#include <SDL.h>
#include <iostream>



namespace engine {


	SpritePlayer* SpritePlayer::getInstance(const SDL_Rect& r, std::string path) {
		return new SpritePlayer(r, path);
	}

	void SpritePlayer::deltaTime() {
		Uint32 now = SDL_GetTicks();
		if (now > last) {
			dt = ((float)(now - last)) / 1000;
				last = now;
		}
	}

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

		case SDL_KEYDOWN:
			switch (eve.key.keysym.sym)
			{
			case SDLK_RIGHT:
				//rect.x += (int)(300 * dt);
				//std::cout << "RIGHT"<<std::endl;
				direction = 1;
				moving = true;

				break;
			case SDLK_LEFT:
				direction = -1;
				moving = true;

				std::cout << "LEFT" << std::endl;
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
		case SDL_KEYUP:
			switch (eve.key.keysym.sym) {
			case SDLK_LEFT:
				moving = false;
				std::cout << "left upp" << std::endl;
				break;
			case SDLK_RIGHT:
				moving = false;
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
		if (moving) {
			rect.x += (int)(dt*MOVEMENT_SPEED*direction);
		}
		deltaTime();
		if (jumped) {
			std::cout << "hoppar" << std::endl;
			rect.y -= (dt * JUMP_SPEED - (dtJump() * 10));
		}
		
	}


	SpritePlayer::SpritePlayer(const SDL_Rect& r, std::string path):Sprite(r,path)
	{

	}


	SpritePlayer::~SpritePlayer()
	{
	}
}
