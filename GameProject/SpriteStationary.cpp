#include "SpriteStationary.h"

namespace engine {

	SpriteStationary* SpriteStationary::getInstance(const SDL_Rect& r, std::string path) {
		return new SpriteStationary(r, path);
	}

	SpriteStationary::SpriteStationary(const SDL_Rect& r, std::string path):Sprite(r, path)
	{
	}


	SpriteStationary::~SpriteStationary()
	{
	}


}