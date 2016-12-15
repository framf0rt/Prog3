#include "SpriteEnemy.h"

namespace engine {

	SpriteEnemy::SpriteEnemy(const SDL_Rect& r, std::string path, int hp) :Sprite(r, path)
	{
		this->hp = hp;
	}

	SpriteEnemy* SpriteEnemy::getInstance(const SDL_Rect& r, std::string path, int hp) {
		return new SpriteEnemy(r, path, hp);
	}
	int SpriteEnemy::getHp() {
		return hp;
	}
	SpriteEnemy::~SpriteEnemy()
	{
	}
}
