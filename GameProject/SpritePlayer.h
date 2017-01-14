#ifndef SPRITEPLAYER_H_INCLUDED
#define SPRITEPLAYER_H_INCLUDED
#include "Sprite.h"
#include "SpriteMovable.h"
#include "SpriteStationary.h"
#include <map>


namespace engine {
	class SpritePlayer :
		public SpriteMovable
	{

	public:
		static std::shared_ptr<SpritePlayer> getInstance(const SDL_Rect& r, std::string t, std::string pathMoving, float colliderSize, std::map<int, std::map<int, void(*)(SpritePlayer&)>>& f, std::map<std::string, int> comms, SDL_Renderer* re,bool g);
		
		void ungrounded();
		void onCollision(std::shared_ptr<Sprite> spriteA, std::shared_ptr<Sprite> spriteB, float dt);
		SDL_Rect getCollider();
		~SpritePlayer();
		void tick(float dt);
		
		bool hasInvunerability() const { return invulnerable; };
		void setInvunerability();
		void move(const std::vector<SDL_Event>& eve);
		void setTimeKeyDownLeft(Uint32 time) { tKeyDownLeft = time; }
		void setTimeKeyDownRight(Uint32 time) { tKeyDownRight = time; }
		void setMoving(bool m) { moving = m; }
		Uint32 getTKeyDownRight() const { return tKeyDownRight; }
		Uint32 getTKeyDownLeft() const { return tKeyDownLeft; }
		void setYCoordAtEvent() { yCoordAtEvent = rect.y; }
		void speedOnCollision();
		void setYSpeed(int i) { ySpeed = i; }
		int getJumpSpeed() const { return JUMP_SPEED; }
		bool victoryCollision(std::shared_ptr<SpriteStationary> victory);
	protected:
		SpritePlayer(const SDL_Rect& r, std::string path, std::string pathMoving, float colliderSize, std::map<int, std::map<int, void(*)(SpritePlayer&)>>& f, std::map<std::string, int> comms, SDL_Renderer* re, bool g);
	private:
		void enemyCollision(std::shared_ptr<Sprite> spriteB);

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
		const int JUMP_SPEED = -500;
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

