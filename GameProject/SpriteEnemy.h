#ifndef SPRITEENEMY_H
#define SPRITEENEMY_H
#include "Sprite.h"
namespace engine {
	class SpriteEnemy :
		public Sprite
	{
	public:
		static SpriteEnemy* getInstance(const SDL_Rect& r, std::string path, int hp);
		~SpriteEnemy();
		int getHp();

	protected:
		SpriteEnemy(const SDL_Rect& r, std::string path, int hp);

	private:
		int hp;
		int direction = 1;
		int speed;
	};
}
#endif
