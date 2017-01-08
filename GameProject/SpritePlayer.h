#ifndef SPRITEPLAYER_H
#define SPRITEPLAYER_H
#include "Sprite.h"
#include "SpriteMovable.h"
#include "SpriteStationary.h"

namespace engine {
	class SpritePlayer :
		public SpriteMovable
	{

	public:
		static SpritePlayer* getInstance(const SDL_Rect& r, std::string t, std::string pathMoving);
		void grounded();
		void ungrounded();
		void onCollision(Sprite* spriteA, Sprite* spriteB);
		~SpritePlayer();
		void keyDown(const SDL_Event& eve);
		void tick();
		
		void move(const SDL_Event& eve);
	protected:
		SpritePlayer(const SDL_Rect& r, std::string path, std::string pathMoving);
	private:

		//void deltaTime();
		float dtJump();
		Uint32 timeOfJump;
		const int JUMP_SPEED = 300;
		/*long last;
		float dt;*/
		bool jumped;
		
		const int MOVEMENT_SPEED = 150;
		bool moving;
		Uint32 tKeyDownRight;
		Uint32 tKeyDownLeft;
		

	};
}
#endif
