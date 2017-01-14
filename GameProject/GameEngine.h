#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Sprite.h"
#include <vector>
#include <memory>
class Sprite;


namespace engine {


	class GameEngine
	{
	public:
		void run();
		void pixelCollision(std::shared_ptr<Sprite> player, std::shared_ptr<Sprite> enemy);
		void addSprite(std::shared_ptr<Sprite> s);
		SDL_Renderer* getRen() const { return ren; }
		GameEngine();
		~GameEngine();
		void deltaTime();
		inline float getDeltaTime() const { return dt; };
		void updateTimeSinceEvent() { timeSinceEvent += dt; }
		float getTimeSinceEvent() const { return timeSinceEvent;}
		void resetTimeSinceEvent() { timeSinceEvent = 0; }
		SDL_Window* getWindow()const { return win; }
	private:
		bool start = false;
		//std::vector<std::shared_ptr<Level>> levels;
		std::vector<std::shared_ptr<Sprite>> sprites;
		SDL_Window* win;
		SDL_Renderer* ren;
		long last = SDL_GetTicks();
		float dt;
		float timeSinceEvent;
		Uint32 timeOfDelay;
	};
	extern GameEngine ge;
}

#endif

