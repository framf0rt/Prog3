#include "SpriteEnemy.h"

#include <iostream>
#include <math.h>
using namespace std;
namespace engine {

	SpriteEnemy::SpriteEnemy(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, shared_ptr<SpritePlayer> p, SDL_Renderer* re, bool g) :SpriteMovable(r, path, re, g)
	{
		startY = rect.y;
		startX = rect.x;
		this->hp = hp;
		this->player = p;
		textureMoving = IMG_LoadTexture(getRen(), pathMoving.c_str());
		textureStationary = IMG_LoadTexture(getRen(), path.c_str());

	}
	void SpriteEnemy::tick(float dt) {

		//cout << rect.x<< " " << rect.y << endl;
		// Animation
		animationCount += 3;
		if (animationCount > 100) {
			animation(*textureMoving);
			animationCount = 0;
		}
		if (animationCount > 50 && animationCount < 100) {
			animation(*textureStationary);
		}

		if (movementPointer != 0) {
			movementPointer(*this);
		}
			// Movement 
		rect.x += (int)(dt * 150 * direction);
		if (rect.y >= startY + 50) {
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
		else {
			// Movement 
			rect.x += (int)(dt * 150 * direction);
		}
				//std::cout << rect.y << " "<< startY <<std::endl;
		if (rect.y >= startY + 50) {
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
		if (rect.x < -200) {
			rect.x = startX;
		}
	}

	
	

	shared_ptr<SpriteEnemy> SpriteEnemy::getInstance(const SDL_Rect& r, std::string path, std::string pathMoving, int hp, shared_ptr<SpritePlayer> p, SDL_Renderer* re, bool g) {
			return shared_ptr<SpriteEnemy>(new SpriteEnemy(r, path, pathMoving, hp, p, re, g));
	}
	int SpriteEnemy::getHp() {
		return hp;
	}
	SpriteEnemy::~SpriteEnemy()
	{

	}
}
