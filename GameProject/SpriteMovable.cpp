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

	SpriteMovable::~SpriteMovable()
	{
	}
}
