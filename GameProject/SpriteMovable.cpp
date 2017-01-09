#include "SpriteMovable.h"
#include <iostream>
#include <SDL.h>


namespace engine {
	SpriteMovable::SpriteMovable(const SDL_Rect& r, std::string path):Sprite(r,path)
	{
	}
	void SpriteMovable::deltaTime() {
		Uint32 now = SDL_GetTicks();
		if (now > last) {
			dt = ((float)(now - last)) / 1000;
			last = now;
		}
	}

	
	void SpriteMovable::draw() {
		SDL_Rect *dstRect = &getRect();
		SDL_Texture *texture = getTexture();

			std::cout << rotation << std::endl;
			if(textureSwap == true){
				if (direction == 1) {
					texture = textureMoving;
					SDL_RenderCopyEx(ge.getRen(), texture, nullptr, dstRect, rotation, nullptr, SDL_FLIP_HORIZONTAL);
				}
				else if(direction == -1){
					SDL_RenderCopyEx(ge.getRen(), texture, nullptr, dstRect, rotation, nullptr, SDL_FLIP_NONE);
				}
			}
			else {
					SDL_RenderCopyEx(ge.getRen(), texture, nullptr, dstRect, rotation, nullptr, SDL_FLIP_NONE);
			}
	}

	SpriteMovable::~SpriteMovable()
	{
	}
}
