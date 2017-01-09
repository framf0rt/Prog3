#ifndef SPRITEPLAYER_H
#define SPRITEPLAYER_H
#include "Sprite.h"
#include "SpriteMovable.h"
#include "SpriteStationary.h"
#include "SpriteGround.h"


namespace engine {
	class SpritePlayer :
		public SpriteMovable
	{

	public:
		static SpritePlayer* getInstance(const SDL_Rect& r, std::string t, std::string pathMoving, float colliderSize);
		void grounded();
		void ungrounded();
		void draw();
		void onCollision(Sprite* spriteA, Sprite* spriteB);
		SDL_Rect getCollider();
		~SpritePlayer();
		void keyDown(const SDL_Event& eve);
		void tick();
		bool isFalling() const { return falling; };
		bool hasJumped() const { return jumped; };
		bool hasDropped() const { return dropped; };
		void move(const SDL_Event& eve);

	protected:
		SpritePlayer(const SDL_Rect& r, std::string path, std::string pathMoving, float colliderSize);
	private:
		//void deltaTime();
		float dtJump();
		float dtFall();
		float dtDrop();
		Uint32 timeOfJump;
		Uint32 timeOfFall = SDL_GetTicks();
		Uint32 timeOfDrop;
		const int JUMP_SPEED = 300;
		/*long last;
		float dt;*/
		bool jumped;
		bool dropped;
		bool falling;
		const int MOVEMENT_SPEED = 150;
		bool moving;
		SDL_Rect boxCollider;
		float colliderSize;

		Uint32 tKeyDownRight;
		Uint32 tKeyDownLeft;
		

	};
}
#endif

