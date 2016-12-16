#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>
#include "GameEngine.h"
namespace engine {
	class Sprite
	{
	public:
		SDL_Rect getRect() const { return rect; }
		void draw();
		virtual void keyDown(const SDL_Event& eve) {};
		virtual void tick() {};

	protected:
		
		~Sprite();
		Sprite(const SDL_Rect& r, std::string path);
		virtual void move(const SDL_Event& eve) {};
		
		SDL_Rect rect;
	private:
		
		SDL_Texture* texture;

		
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;
	};
}
#endif

