#include "SpriteGround.h"
namespace engine {


	SDL_Rect SpriteGround::getCollider() {
		SDL_Rect A = getRect();
		boxCollider = { A.x,A.y+10,A.w,10};
		return boxCollider;
	}

	SpriteGround* SpriteGround::getInstance(const SDL_Rect& r, std::string path) {
		return new SpriteGround(r, path);
	}

	SpriteGround::SpriteGround(const SDL_Rect& r, std::string path) : SpriteStationary(r, path)
	{
	
	}


	SpriteGround::~SpriteGround()
	{
	}

}
