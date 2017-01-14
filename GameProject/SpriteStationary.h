#ifndef SPRITESTATIONARY_H_INCLUDED
#define SPRITESTATIONARY_H_INCLUDED
#include "Sprite.h"
#include <SDL.h>
#include <memory>

namespace engine {
	class SpriteStationary :
		public Sprite
	{
	public:
		static std::shared_ptr<SpriteStationary> getInstance(const SDL_Rect& r, std::string path, bool isGround, bool isBounceable, bool isKillZone, bool isVictoryCond, SDL_Renderer* re);
		~SpriteStationary();
		void draw();
		bool getIsBounceable() { return isBounceable; }
		bool getIsGround() { return isGround; }
		bool getIsKillZone() { return isKillZone;  }
		bool getIsVictoryCond() { return isVictoryCond; }
		SDL_Rect getCollider();
	protected:
		SpriteStationary(const SDL_Rect& r, std::string path, bool isGround, bool isBounceable, bool isKillZone, bool isVictoryCond, SDL_Renderer* re);
		SDL_Rect boxCollider;
	private:
		bool isBounceable;
		bool isGround;
		bool isKillZone;
		bool isVictoryCond;
	};
}

#endif