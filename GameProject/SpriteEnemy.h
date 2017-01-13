#ifndef SPRITEENEMY_H
#define SPRITEENEMY_H
#include "Sprite.h"
#include "SpriteMovable.h"
#include "SpritePlayer.h"
#include <memory>

namespace engine {
	class SpriteEnemy :
		public SpriteMovable
	{
	public:
		static std::shared_ptr<SpriteEnemy> getInstance(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, std::shared_ptr<SpritePlayer> p);
		~SpriteEnemy();
		int getHp();
		void tick();

	protected:
		SpriteEnemy(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, std::shared_ptr<SpritePlayer> p);

	private:
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
