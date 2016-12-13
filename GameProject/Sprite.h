#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>
#include "GameEngine.h"
namespace engine {
	class Sprite
	{
	public:
		Sprite(const SDL_Rect& r, std::string path);
		SDL_Rect getRect() const { return rect; }
		void draw();

		~Sprite();
		
	private:
		SDL_Rect rect;
		SDL_Texture* texture;


	};
}
#endif

