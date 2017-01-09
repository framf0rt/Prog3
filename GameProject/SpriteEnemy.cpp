#include "SpriteEnemy.h"

#include <iostream>
#include <math.h>

namespace engine {

	SpriteEnemy::SpriteEnemy(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, SpritePlayer* p) :SpriteMovable(r, path)
	{
		startY = rect.y;
		this->hp = hp;
		this->player = p;
		textureMoving = IMG_LoadTexture(ge.getRen(), pathMoving.c_str());
		textureStationary = IMG_LoadTexture(ge.getRen(), path.c_str());
		
	}
	void SpriteEnemy::tick() {
		deltaTime();
		
		// Animation
		animationCount += 3;
		if (animationCount > 100) {
			animation(*textureMoving);
			animationCount = 0;
		}
		if (animationCount > 50 && animationCount < 100) {
			animation(*textureStationary);
		}

		// Movement 
		rect.x += (int)(dt*150*direction);
		std::cout << rect.y << " "<< startY <<std::endl;
		if (rect.y == startY + 50 ) {
			directionY = 1;
		} 
		if (rect.y == startY - 50) {
			directionY = -1;
		}
		if (directionY == -1) {
			rect.y += (int)(dt * -125 * direction);
		}
		if (directionY == 1) {
			rect.y += (int)(dt * 125 * direction);
		}



		//if (player != nullptr) {
		//	SDL_Rect pr = player->getRect();
		//	int px = pr.x + (pr.w/2);
		//	int py = pr.y + (pr.h/2);
		//	//float distance = sqrt(((rect.x+(rect.w/2)) - px) ^ 2 + ((rect.y+(rect.h/2)) - pr.y) ^ 2);
		//	float distance =  sqrt(pow(((rect.x + rect.w / 2) - px), 2)+ pow(((rect.y + rect.h / 2) - py), 2));
		//	if (distance < 100) {
		//	//	std::cout << "rör sig mot target" << std::endl;
		//	}
		//}
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
