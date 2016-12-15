#ifndef SPRITEPLAYER_H
#define SPRITEPLAYER_H
#include "Sprite.h"

namespace engine {
	class SpritePlayer :
		public Sprite
	{

	public:
		static SpritePlayer* getInstance(const SDL_Rect& r, std::string t);
		~SpritePlayer();
		void keyDown(const SDL_Event& eve);
		void tick();
		void move(const SDL_Event& eve);
	protected:
		SpritePlayer(const SDL_Rect& r, std::string path);
	private:
		void deltaTime();
		float dtJump();
		Uint32 timeOfJump;
		const int JUMP_SPEED = 300;
		long last;
		float dt;
		bool jumped;
		int direction;
		const int MOVEMENT_SPEED = 150;
		bool moving;
	

	};
}
#endif

