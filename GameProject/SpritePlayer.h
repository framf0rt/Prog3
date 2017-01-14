#ifndef SPRITEPLAYER_H
#define SPRITEPLAYER_H
#include "Sprite.h"
#include "SpriteMovable.h"
#include "SpriteStationary.h"
#include <map>


namespace engine {
	//using Func = void(*)(SpritePlayer&);
	//typedef void (*Func)(SpritePlayer&);
	class SpritePlayer :
		public SpriteMovable
	{

	public:
		static std::shared_ptr<SpritePlayer> getInstance(const SDL_Rect& r, std::string t, std::string pathMoving, float colliderSize, std::map<int, std::map<int, void(*)(SpritePlayer&)>>& f, std::map<std::string, int> comms);
		
		void ungrounded();
		void draw();
		void onCollision(std::shared_ptr<Sprite> spriteA, std::shared_ptr<Sprite> spriteB);

		void enemyCollision(std::shared_ptr<Sprite> spriteB);
		
		
		SDL_Rect getCollider();
		~SpritePlayer();
		void keyDown(const SDL_Event& eve);
		void tick();
		
		//bool hasJumped() const { return jumped; };
		//bool hasDropped() const { return dropped; };
		bool hasInvunerability() const { return invulnerable; };
		void setInvunerability();
		void move(const std::vector<SDL_Event>& eve);
		void setTimeKeyDownLeft(Uint32 time) { tKeyDownLeft = time; }
		void setTimeKeyDownRight(Uint32 time) { tKeyDownRight = time; }
		//void setMoving(bool moving) { this->moving = moving; }
		//void setTimeOfJump(Uint32 time) { timeOfJump = time; }
		
		//void setDropped(bool d) { dropped = d; }
		//void setFalling(bool f) { falling = f; }
		//void setTimeOfDrop(Uint32 time) { timeOfDrop = time; }
		void setMoving(bool m) { moving = m; }
		Uint32 getTKeyDownRight() const { return tKeyDownRight; }
		Uint32 getTKeyDownLeft() const { return tKeyDownLeft; }
		void setYCoordAtEvent() { yCoordAtEvent = rect.y; }
		void speedOnCollision();
		void setYSpeed(int i) { ySpeed = i; }
		int getJumpSpeed() const { return JUMP_SPEED; }

	protected:
		SpritePlayer(const SDL_Rect& r, std::string path, std::string pathMoving, float colliderSize, std::map<int, std::map<int, void(*)(SpritePlayer&)>>& f, std::map<std::string, int> comms);
	private:
		void killZoneCollision(std::shared_ptr<SpriteStationary> killzone);
		std::map<int, std::map<int, void(SpritePlayer::*)() >> events;
		void moveLeft();
		void moveRight();
		void jump();
		void drop();
		void leftUp();
		void rightUp();
		void grounded();
		void kill();

		//void deltaTime();
		/*float dtJump();
		float dtFall();
		float dtDrop();*/
		//Uint32 timeOfJump;
		//Uint32 timeOfFall = SDL_GetTicks();
		//Uint32 timeOfDrop;
		const int JUMP_SPEED = -500;
		
		/*long last;
		float dt;*/
		
		//bool dropped;
		//bool falling;
		
		
		int startPosX;
		int startPosY;
		const int MOVEMENT_SPEED = 150;
		bool moving;
		SDL_Rect boxCollider;
		float colliderSize;

		Uint32 tKeyDownRight;
		Uint32 tKeyDownLeft;
		std::map<int, std::map<int, void(*)(SpritePlayer&)>> commands;
		

	};
}
#endif

