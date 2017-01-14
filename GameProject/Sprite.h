#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>
#include <memory>

namespace engine {
	class Sprite
	{
	public:
		SDL_Rect getRect() const { return rect; }
		int getAlphaXY(int x, int y);
		void draw();
		void onCollision(std::shared_ptr<Sprite> spriteA, std::shared_ptr<Sprite> spriteB);
		virtual void keyDown(const SDL_Event& eve) {};
		virtual void tick(float dt) {};
		void setRectY(int y) { rect.y = y; }
		int getRectY() const { return rect.y; }
	protected:
		SDL_Renderer* getRen() { return rend; }
		~Sprite();
		Sprite(const SDL_Rect& r, std::string path, SDL_Renderer* re);
		virtual void move(const SDL_Event& eve) {};
		void animation(SDL_Texture &anitexture);
		SDL_Texture* getTexture() const { return texture; }
		void setTexture(SDL_Texture* tex) { texture = tex; }
		SDL_Rect rect;
	
	private:
		SDL_Renderer* rend;
		SDL_Texture* texture;
		SDL_Surface* surface;
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;
		
	};
}
#endif

