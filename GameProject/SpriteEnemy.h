#ifndef SPRITEENEMY_H
#define SPRITEENEMY_H
#include "Sprite.h"
#include "SpriteMovable.h"
#include "SpritePlayer.h"

namespace engine {
	class SpriteEnemy :
		public SpriteMovable
	{
	public:
		static SpriteEnemy* getInstance(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, SpritePlayer* p);
		~SpriteEnemy();
		int getHp();
		void tick();

	protected:
		SpriteEnemy(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, SpritePlayer* p);

	private:
		int hp;
		int direction = 1;
		int speed;
		SpritePlayer* player;
	};
}
#endif
