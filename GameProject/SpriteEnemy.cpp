#include "SpriteEnemy.h"

#include <iostream>
#include <math.h>

namespace engine {

	SpriteEnemy::SpriteEnemy(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, SpritePlayer* p) :SpriteMovable(r, path)
	{
		this->hp = hp;
		this->player = p;
		textureMoving = IMG_LoadTexture(ge.getRen(), pathMoving.c_str());
		textureStationary = IMG_LoadTexture(ge.getRen(), path.c_str());
		
	}
	void SpriteEnemy::tick() {
		deltaTime();



		if (player != nullptr) {
			SDL_Rect pr = player->getRect();
			int px = pr.x + (pr.w/2);
			int py = pr.y + (pr.h/2);
			//float distance = sqrt(((rect.x+(rect.w/2)) - px) ^ 2 + ((rect.y+(rect.h/2)) - pr.y) ^ 2);
			float distance =  sqrt(pow(((rect.x + rect.w / 2) - px), 2)+ pow(((rect.y + rect.h / 2) - py), 2));
			if (distance < 100) {
				std::cout << "rör sig mot target" << std::endl;
			}

		}
	}
	SpriteEnemy* SpriteEnemy::getInstance(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, SpritePlayer* p) {
		return new SpriteEnemy(r, path, pathMoving, hp, p);
	}
	int SpriteEnemy::getHp() {
		return hp;
	}
	SpriteEnemy::~SpriteEnemy()
	{

	}
}
