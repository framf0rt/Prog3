#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include "Sprite.h"
#include "Level.h"
#include <vector>
#include <memory>
#include <map>


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
		void changePauseKey(int i) { pauseKey = i; }
		void installCallBackFunctions(std::map<int, std::map<int, void(*)()>>& f) { callBack = f; }
		void addLevel(std::shared_ptr<Level> l);
	private:
		std::string playerName = " ";
		void getNextLevel(int level);
		void setLevel(int level);
		int pauseKey=SDLK_ESCAPE;
		bool victoryCondition = true;
		std::map<int, std::map<int, void(*)()>> callBack;
		void pause();
		void resume();
		bool paused = false;
		bool start = false;
		std::vector<std::shared_ptr<Level>> levels;
		std::vector<std::shared_ptr<Sprite>> sprites;
		SDL_Window* win;
		SDL_Renderer* ren;
		long last = SDL_GetTicks();
		float dt;
		float timeSinceEvent;
		Uint32 timeOfDelay;
		void(GameEngine::*pausePointer)() = &GameEngine::pause;
		int levelNumber = 0;
		Uint32 pauseTime;
	};
	extern GameEngine ge;
}

#endif

