#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "GameEngine.h"
namespace engine {
	class Sprite
	{
	public:
		SDL_Rect getRect() const { return rect; }
		int getAlphaXY(int x, int y);
		void draw();
		virtual void keyDown(const SDL_Event& eve) {};
		virtual void tick() {};

	protected:
		
		~Sprite();
		Sprite(const SDL_Rect& r, std::string path);
		virtual void move(const SDL_Event& eve) {};
		void animation(SDL_Texture &anitexture);
		SDL_Texture* getTexture() const { return texture; }
		SDL_Rect rect;
	private:
		
		SDL_Texture* texture;
		SDL_Surface* surface;
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;
	};
}
#endif

