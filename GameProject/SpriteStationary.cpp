#include "SpriteStationary.h"

namespace engine {

	SpriteStationary* SpriteStationary::getInstance(const SDL_Rect& r, std::string path) {
		return new SpriteStationary(r, path);
	}

	SpriteStationary::SpriteStationary(const SDL_Rect& r, std::string path):Sprite(r, path)
	{
	}

	void SpriteStationary::draw() {
	SDL_Rect *rect = &getRect();
	SDL_Texture *texture = getTexture();
	SDL_RenderCopyEx(ge.getRen(), texture, nullptr, rect, 0, nullptr, SDL_FLIP_NONE);
		
	}


	SpriteStationary::~SpriteStationary()
	{
	}


}