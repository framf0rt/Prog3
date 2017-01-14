
#include "SpriteStationary.h"
using namespace std;

namespace engine {

	

	shared_ptr<SpriteStationary> SpriteStationary::getInstance(const SDL_Rect& r, std::string path, bool isGround, bool isBounceable, bool isKillZone, bool isVictoryCond, SDL_Renderer* re) {
		return shared_ptr<SpriteStationary>(new SpriteStationary(r, path, isGround, isBounceable, isKillZone, isVictoryCond,re));
	}

	SpriteStationary::SpriteStationary(const SDL_Rect& r, std::string path, bool isGround, bool isBounceable, bool isKillZone, bool isVictoryCond, SDL_Renderer* re):Sprite(r, path,re)
	{
		this->isBounceable = isBounceable;
		this->isGround = isGround;
		this->isKillZone = isKillZone;
		this->isVictoryCond = isVictoryCond;
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
	SDL_RenderCopyEx(getRen(), texture, nullptr, rect, 0, nullptr, SDL_FLIP_NONE);
		
	}


	SpriteStationary::~SpriteStationary()
	{
	}


}
