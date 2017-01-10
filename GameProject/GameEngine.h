
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Sprite.h"
#include <vector>
class Sprite;


namespace engine {


	class GameEngine
	{
	public:
		void run();
		void pixelCollision(Sprite * player, Sprite * enemy);
		void addSprite(Sprite* s);
		SDL_Renderer* getRen() const { return ren; }
		GameEngine();
		~GameEngine();
		void deltaTime();
		inline float getDeltaTime() const { return dt; };

	private:
	
		std::vector<Sprite*> sprites;
		SDL_Window* win;
		SDL_Renderer* ren;
		long last = SDL_GetTicks();
		float dt;

	};
	extern GameEngine ge;
}

#endif

