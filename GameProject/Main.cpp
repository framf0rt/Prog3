#pragma once
#include "GameEngine.h"
#include <iostream>
#include "SpritePlayer.h"
#include "SpriteGround.h"
#include "SpriteEnemy.h"
#include <map>

using namespace std;
using namespace engine;

//typedef void (*Func)(SpritePlayer&);
void moveLeft(SpritePlayer& p) {
	p.setDirection( -1);
	p.setTimeKeyDownLeft(SDL_GetTicks());
	p.setMoving(true);
}

void moveRight(SpritePlayer& p) {
	p.setDirection(1);
	p.setTimeKeyDownRight(SDL_GetTicks());
	p.setMoving(true);
}

void jump(SpritePlayer& p) {
	if (!p.hasJumped()) {
		ge.resetTimeSinceEvent();
		p.setJumped(true);
		p.setDropped(false);
		p.setFalling(false);
		p.setYCoordAtEvent();
	}
}




void drop(SpritePlayer& p) {
	if (!p.hasJumped()) {
		ge.resetTimeSinceEvent();
		p.setDropped(true);
		p.setRectY(p.getRectY() + 10);
		p.setYCoordAtEvent();
	}
}

void leftUp(SpritePlayer& p) {
	if (SDL_GetTicks() - p.getTKeyDownRight() > 60) {
		p.setMoving(false);
	}
}
void rightUp(SpritePlayer& p) {
	if (SDL_GetTicks() - p.getTkeyDownLeft() > 60) {
		p.setMoving(false);
	}
}
int main(int argvc, char* argv[]) {
	map<int, map<int, void (*)(SpritePlayer&)>> events;
	map<int, void (*)(SpritePlayer&)> keyUpFuncs;
	map<int, void (*)(SpritePlayer&)> keyDownFuncs;
	
	keyUpFuncs.insert(make_pair(SDLK_LEFT, leftUp));
	keyUpFuncs.insert(make_pair(SDLK_RIGHT, rightUp));
	keyDownFuncs.insert(make_pair(SDLK_LEFT, moveLeft));
	keyDownFuncs.insert(make_pair(SDLK_RIGHT, moveRight));
	keyDownFuncs.insert(make_pair(SDLK_SPACE, jump));
	keyDownFuncs.insert(make_pair(SDLK_DOWN, drop));
	events.insert(make_pair(SDL_KEYUP, keyUpFuncs));
	events.insert(make_pair(SDL_KEYDOWN, keyDownFuncs));
	
	
	void (*p)(SpritePlayer&) = leftUp;
	SpritePlayer* s = SpritePlayer::getInstance({ 100, 50, 92, 92 }, "c:/Prog3/assets/Sprites/BallSprite_Cut.png", "c:/Prog3/assets/Sprites/BallSprite_Cut.png", 0.4,events);
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
