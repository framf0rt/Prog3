#include "SpriteMovable.h"
#include <iostream>
#include <SDL.h>


namespace engine {
	SpriteMovable::SpriteMovable(const SDL_Rect& r, std::string path) :Sprite(r, path)
	{
	}



	void SpriteMovable::draw() {
		SDL_Rect *dstRect = &getRect();
		SDL_Texture *texture = getTexture();

		//std::cout << rotation << std::endl;
		
		if (textureSwap == true) {
			if (direction == 1) {
				texture = textureMoving;
				SDL_RenderCopyEx(ge.getRen(), texture, nullptr, dstRect, rotation, nullptr, SDL_FLIP_HORIZONTAL);
			}
			else if (direction == -1) {
				SDL_RenderCopyEx(ge.getRen(), texture, nullptr, dstRect, rotation, nullptr, SDL_FLIP_NONE);
			}
		}
		else {
			SDL_RenderCopyEx(ge.getRen(), texture, nullptr, dstRect, rotation, nullptr, SDL_FLIP_NONE);
		}
		if (alphaModifier != 255.0) {
			SDL_SetTextureAlphaMod(texture, alphaModifier);
		}

	}

	SpriteMovable::~SpriteMovable()
	{
	}
}
