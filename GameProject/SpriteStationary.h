#ifndef SPRITESTATIONARY_H
#define SPRITESTATIONARY_H
#include "Sprite.h"
#include <SDL.h>

namespace engine {
	class SpriteStationary :
		public Sprite
	{
	public:
		static SpriteStationary* getInstance(const SDL_Rect& r, std::string t);
		~SpriteStationary();
		
	protected:
		SpriteStationary(const SDL_Rect& r, std::string path);
		
	};
}

#endif