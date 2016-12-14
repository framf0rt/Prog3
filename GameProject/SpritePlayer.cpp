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
		switch (eve.type)
		{
			
		case SDL_KEYDOWN:
			switch (eve.key.keysym.sym)
			{
			case SDLK_RIGHT:
				rect.x += (int)(300 * dt);
				std::cout << "RIGHT"<<std::endl;
				break;
			case SDLK_LEFT:
				rect.x -= 4;
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

		default:
			break;
		}
	}

	void SpritePlayer::tick() {
		deltaTime();
		if (jumped) {
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
