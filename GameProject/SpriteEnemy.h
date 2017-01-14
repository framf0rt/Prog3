#ifndef SPRITEENEMY_H_INCLUDED
#define SPRITEENEMY_H_INCLUDED
#include "Sprite.h"
#include "SpriteMovable.h"
#include "SpritePlayer.h"
#include <memory>

namespace engine {
	class SpriteEnemy :
		public SpriteMovable
	{
	public:
		static std::shared_ptr<SpriteEnemy> getInstance(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, std::shared_ptr<SpritePlayer> p, SDL_Renderer* re, bool g);
		~SpriteEnemy();
		int getHp();
		void tick(float dt);
		void installMovement(void(*move)(SpriteEnemy&)) { movementPointer = move; }

	protected:
		SpriteEnemy(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, std::shared_ptr<SpritePlayer> p, SDL_Renderer* re, bool g);

	private:
		void(*movementPointer)(SpriteEnemy&);
		int hp;
		int direction = -1;
		int directionY = -1;
		int speed;
		int startY;
		int startX;
		std::shared_ptr<SpritePlayer> player;
	};
}
#endif
