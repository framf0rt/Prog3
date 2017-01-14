#include "SpriteEnemy.h"

#include <iostream>
#include <math.h>
using namespace std;
namespace engine {

	SpriteEnemy::SpriteEnemy(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, shared_ptr<SpritePlayer> p, SDL_Renderer* re) :SpriteMovable(r, path, re)
	{
		startY = rect.y;
		startX = rect.x;
		this->hp = hp;
		this->player = p;
		textureMoving = IMG_LoadTexture(getRen(), pathMoving.c_str());
		textureStationary = IMG_LoadTexture(getRen(), path.c_str());
		
	}
	void SpriteEnemy::tick(float dt) {

		
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
		if (rect.y >= startY + 50 ) {
			directionY = 1;
		} 
		if (rect.y <= startY - 50) {
			directionY = -1;
		}
		if (directionY == -1) {
			rect.y += (int)(dt * -125 * direction);
		}
		if (directionY == 1) {
			rect.y += (int)(dt * 125 * direction);
		}
		if (rect.x < - 200) {
			rect.x = startX;
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
	shared_ptr<SpriteEnemy> SpriteEnemy::getInstance(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, shared_ptr<SpritePlayer> p,SDL_Renderer* re) {
		return shared_ptr<SpriteEnemy>(new SpriteEnemy(r, path, pathMoving, hp, p, re));
	}
	int SpriteEnemy::getHp() {
		return hp;
	}
	SpriteEnemy::~SpriteEnemy()
	{

	}
}
