#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Sprite.h"
#include <vector>


namespace engine {


	class GameEngine
	{
	public:
		void run();
		//void addSprite(Sprite*);
		SDL_Renderer* getRen() const { return ren; }
		GameEngine();
		~GameEngine();

	private:
		//std::vector<Sprite*> sprites;
		SDL_Window* win;
		SDL_Renderer* ren;

	};
	extern GameEngine ge;
}

#endif

