#include "SpriteMovable.h"


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

	
	void SpriteMovable ::draw() {
		

		SDL_Rect *rect = &getRect();
		SDL_Texture *texture = getTexture();
		if (direction == 1) {
			SDL_RenderCopyEx(ge.getRen(), texture, nullptr, rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else {
			SDL_RenderCopyEx(ge.getRen(), texture, nullptr, rect, 0, nullptr, SDL_FLIP_NONE);
		}
	}

	SpriteMovable::~SpriteMovable()
	{
	}
}
