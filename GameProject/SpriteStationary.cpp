#include "SpriteStationary.h"

namespace engine {

	

	SpriteStationary* SpriteStationary::getInstance(const SDL_Rect& r, std::string path, bool isGround, bool isBounceable, bool isKillZone) {
		return new SpriteStationary(r, path, isGround, isBounceable, isKillZone);
	}

	SpriteStationary::SpriteStationary(const SDL_Rect& r, std::string path, bool isGround, bool isBounceable, bool isKillZone):Sprite(r, path)
	{
		this->isBounceable = isBounceable;
		this->isGround = isGround;
		this->isKillZone = isKillZone;
	}

	SDL_Rect SpriteStationary::getCollider() {
		SDL_Rect A = getRect();

		if (isGround == true) {
			boxCollider = { A.x, A.y + 10, A.w, 10 };
		}
		if (isGround == false) {
			boxCollider = { A.x,A.y,A.w,A.h };
		}
		return boxCollider;
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