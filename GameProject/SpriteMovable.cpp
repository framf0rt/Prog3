#include "SpriteMovable.h"
#include <iostream>
#include <SDL.h>


namespace engine {
	SpriteMovable::SpriteMovable(const SDL_Rect& r, std::string path, SDL_Renderer* re) :Sprite(r, path,re)
	{
		setPixelColliders();
	}


	void SpriteMovable::setPixelColliders() {
		SDL_Rect r = getRect();
		int pixelsWithoutAlpha = 0;
		int width = 0;
		int offset = 0;
		bool found = false;
		SDL_Rect rect = { 0,0,0,0 };
		for (int y = 0; y < r.h; y++) {
			for (int x = 0; x < r.w; x++) {
				if (getAlphaXY(x, y) > 0) {
					found = true;
				}
				else {
					if (!found) {
						offset++;
					}
					pixelsWithoutAlpha++;
				}
				width++;
			}
			rect = { offset,y,width - pixelsWithoutAlpha,1 };
			pixelCollisionRects.push_back(rect);
			pixelsWithoutAlpha = 0;
			offset = 0;
			width = 0;
			found = false;
		}
	}



	void SpriteMovable::draw() {
		SDL_Rect *dstRect = &getRect();
		SDL_Texture *texture = getTexture();

		if (textureSwap == true) {
			if (direction == 1) {
				texture = textureMoving;
				SDL_RenderCopyEx(getRen(), texture, nullptr, dstRect, rotation, nullptr, SDL_FLIP_HORIZONTAL);
			}
			else if (direction == -1) {
				SDL_RenderCopyEx(getRen(), texture, nullptr, dstRect, rotation, nullptr, SDL_FLIP_NONE);
			}
		}
		else {
			SDL_RenderCopyEx(getRen(), texture, nullptr, dstRect, rotation, nullptr, SDL_FLIP_NONE);
		}
		if (alphaModifier != 255.0) {
			SDL_SetTextureAlphaMod(texture, alphaModifier);
		}

	}

	SpriteMovable::~SpriteMovable()
	{
	}
}
