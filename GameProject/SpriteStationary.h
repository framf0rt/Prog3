#ifndef SPRITESTATIONARY_H
#define SPRITESTATIONARY_H
#include "Sprite.h"
#include <SDL.h>

namespace engine {
	class SpriteStationary :
		public Sprite
	{
	public:
		static SpriteStationary* getInstance(const SDL_Rect& r, std::string path, bool isGround, bool isBounceable, bool isKillZone);
		~SpriteStationary();
		void draw();
		bool getIsBounceable() { return isBounceable; }
		bool getIsGround() { return isGround; }
		bool getIsKillZone() { return isKillZone;  }
		SDL_Rect getCollider();
	protected:
		SpriteStationary(const SDL_Rect& r, std::string path, bool isGround, bool isBounceable, bool isKillZone);
		SDL_Rect boxCollider;
	private:
		bool isBounceable;
		bool isGround;
		bool isKillZone;
	};
}

#endif