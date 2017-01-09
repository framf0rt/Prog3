#pragma once
#include "SpriteStationary.h"
namespace engine {

	class SpriteGround :
		public SpriteStationary
	{
	public:
		static SpriteGround* getInstance(const SDL_Rect& r, std::string t);
		SDL_Rect getCollider();
	protected:
		SpriteGround(const SDL_Rect& r, std::string path);
		~SpriteGround();
	private:
		SDL_Rect boxCollider;
	};
}

