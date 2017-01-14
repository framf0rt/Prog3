#pragma once
#include "GameEngine.h"
#include <iostream>
#include "SpritePlayer.h"
#include "SpriteEnemy.h"
#include "SpriteLabel.h"
#include "SpriteLabelEditable.h"
#include "Level.h"
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
	if (!p.hasGravity()) {
		p.resetTimeSinceEvent();
		p.setYSpeed(p.getJumpSpeed());
		p.setGravity(true);
		//p.setDropped(false);
		//p.setFalling(false);
		p.setYCoordAtEvent();
	}
}




void drop(SpritePlayer& p) {
	if (!p.hasGravity()) {
		p.resetTimeSinceEvent();
		p.setGravity(true);
		//p.setJumped(false);
		//p.setFalling(false);
		p.setYSpeed(200);
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
	if (SDL_GetTicks() - p.getTKeyDownLeft() > 60) {
		p.setMoving(false);
	}
}
int main(int argvc, char* argv[]) {
	map<int, map<int, void (*)(SpritePlayer&)>> events;
	map<int, void (*)(SpritePlayer&)> keyUpFuncs;
	map<int, void (*)(SpritePlayer&)> keyDownFuncs;
	
	//Dessa tar emot egen funktionalitet f�r spelaren
	keyUpFuncs.insert(make_pair(-1, leftUp));
	keyUpFuncs.insert(make_pair(-1, rightUp));
	keyDownFuncs.insert(make_pair(-1, moveLeft));
	keyDownFuncs.insert(make_pair(-1, moveRight));
	keyDownFuncs.insert(make_pair(SDLK_SPACE, jump));
	keyDownFuncs.insert(make_pair(-1, drop));
	events.insert(make_pair(SDL_KEYUP, keyUpFuncs));
	events.insert(make_pair(SDL_KEYDOWN, keyDownFuncs));
	
	
	//spelarens inbyggda funktionalitet
	map<string, int> comms;
	comms.insert(make_pair("moveLeft", SDLK_LEFT));
	comms.insert(make_pair("moveRight", SDLK_RIGHT));
	comms.insert(make_pair("jump", -1));
	comms.insert(make_pair("drop", SDLK_DOWN));
	void (*p)(SpritePlayer&) = leftUp;

	shared_ptr<Level> level1 = Level::getInstance();


	shared_ptr<SpritePlayer> s = SpritePlayer::getInstance({ 100, 50, 92, 92 }, "c:/Prog3/assets/Sprites/BallSprite_Cut.png", "c:/Prog3/assets/Sprites/BallSprite_Cut.png", 0.4,events,comms);
	shared_ptr<SpriteEnemy> se = SpriteEnemy::getInstance({ 600,200, 113, 67 }, "c:/Prog3/assets/Sprites/BirdEnemyIdleSprite_Cut.png", "c:/Prog3/assets/Sprites/BirdEnemyFlapSprite_Cut.png", 20, s);

	shared_ptr<SpriteLabel> text1 = SpriteLabel::getInstance({ 0,0,100,50 }, "", 300, 50, "Enter Name:", 16);
	shared_ptr<SpriteLabelEditable> textEdit = SpriteLabelEditable::getInstance({ 0,0,100,50 }, "",300,100,"Name here", 16);
	shared_ptr<SpriteLabel> text2 = SpriteLabel::getInstance({ 0,0,100,50 }, "", 300, 200, "Press return to play", 100);

	shared_ptr<SpriteStationary> sg = SpriteStationary::getInstance({ 300,200,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false);
	shared_ptr<SpriteStationary> sg1 = SpriteStationary::getInstance({ 100,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false);
	shared_ptr<SpriteStationary> sg2 = SpriteStationary::getInstance({ 200,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, false, false);
	shared_ptr<SpriteStationary> sg3 = SpriteStationary::getInstance({ 400,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, false, false);
	shared_ptr<SpriteStationary> wall = SpriteStationary::getInstance({ 300,400,100,50 }, "", false, true, false);
	
	shared_ptr<SpriteStationary> kill = SpriteStationary::getInstance({ 200,400,100,50 }, "", true, false, true);

	ge.addSprite(text1);
	ge.addSprite(text2);
	ge.addSprite(textEdit);
	ge.addSprite(s);
	ge.addSprite(se);
	ge.addSprite(sg);
	ge.addSprite(sg1);
	ge.addSprite(sg2);
	ge.addSprite(sg3);
	ge.addSprite(kill);
	ge.addSprite(wall);


	level1->addSp(wall);



	ge.run();
	

	return 0;
}
