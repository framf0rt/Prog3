#pragma once
#include "GameEngine.h"
#include <iostream>
#include "SpritePlayer.h"
#include "SpriteGround.h"
#include "SpriteEnemy.h"


using namespace engine;

int main(int argvc, char* argv[]) {

	
	SpritePlayer* s = SpritePlayer::getInstance({ 100, 100, 92, 92 }, "c:/Prog3/assets/Sprites/BallSprite_Cut.png", "c:/Prog3/assets/Sprites/BallSprite_Cut.png", 0.4);
	SpriteEnemy* se = SpriteEnemy::getInstance({ 600,200, 113, 67 }, "c:/Prog3/assets/Sprites/BirdEnemyIdleSprite_Cut.png", "c:/Prog3/assets/Sprites/BirdEnemyFlapSprite_Cut.png", 20, s);
	SpriteGround* sg = SpriteGround::getInstance({ 300,300,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png");
	SpriteGround* sg1 = SpriteGround::getInstance({ 100,300,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png");
	SpriteGround* sg2 = SpriteGround::getInstance({ 200,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png");

	ge.addSprite(s);
	ge.addSprite(se);
	ge.addSprite(sg);
	ge.addSprite(sg1);
	ge.addSprite(sg2);

	ge.run();
	

	return 0;
}
