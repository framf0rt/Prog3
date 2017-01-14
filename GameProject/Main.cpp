
#include "GameEngine.h"
#include "Level.h"
#include <iostream>
#include "SpritePlayer.h"
#include "SpriteEnemy.h"
#include "SpriteLabel.h"
#include "SpriteLabelEditable.h"
#include <map>


using namespace std;
using namespace engine;

//används inte, men visar på hur man skulle kunna ändra beteende
void moveLeft(SpritePlayer& p) {
	p.setDirection( -1);
	p.setTimeKeyDownLeft(SDL_GetTicks());
	p.setMoving(true);
}
//används inte, men visar på hur man skulle kunna ändra beteende
void moveRight(SpritePlayer& p) {
	p.setDirection(1);
	p.setTimeKeyDownRight(SDL_GetTicks());
	p.setMoving(true);
}
//har samma beteende som är implementerat i player, men visar hur denna går att använda istället
void jump(SpritePlayer& p) {
	if (!p.hasGravity()) {
		p.resetTimeSinceEvent();
		p.setYSpeed(p.getJumpSpeed());
		p.setGravity(true);
		p.setYCoordAtEvent();
	}
}
//Implementera om du vill att fienden ska röra sig på något annat sätt
void moveEnemy(SpriteEnemy& e) {
	cout << "Fågeln flyger" << endl;
}

//används inte, men visar på hur man skulle kunna ändra beteende
void drop(SpritePlayer& p) {
	if (!p.hasGravity()) {
		p.resetTimeSinceEvent();
		p.setGravity(true);
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
	map<int, map<int, void (*)(SpritePlayer&)>> callBackPlayer;
	map<int, void (*)(SpritePlayer&)> keyUpFuncs;
	map<int, void (*)(SpritePlayer&)> keyDownFuncs;
	
	//Dessa tar emot funktionalitet till player och enemy som kan skapas i main.cpp
	//samma mapstruktur kan användas för att installera egna funktioner till spelmotorn
	//pekaren blir dock void(*)() eftersom det finns åtkomst till gameEngine i main.cpp
	//använd i så fall ge.installCallBackFunctions(mapName);
	keyUpFuncs.insert(make_pair(-1, leftUp));
	keyUpFuncs.insert(make_pair(-1, rightUp));
	keyDownFuncs.insert(make_pair(-1, moveLeft));
	keyDownFuncs.insert(make_pair(-1, moveRight));
	keyDownFuncs.insert(make_pair(-1, jump));
	keyDownFuncs.insert(make_pair(-1, drop));
	callBackPlayer.insert(make_pair(SDL_KEYUP, keyUpFuncs));
	callBackPlayer.insert(make_pair(SDL_KEYDOWN, keyDownFuncs));
	
	
	//spelarens inbyggda funktionalitet
	map<string, int> comms;
	comms.insert(make_pair("moveLeft", SDLK_LEFT));
	comms.insert(make_pair("moveRight", SDLK_RIGHT));
	comms.insert(make_pair("jump", SDLK_UP	));
	comms.insert(make_pair("drop", SDLK_DOWN));

	//kontroller för en andra spelare om man vill
	/*map<string, int> comms2;
	comms2.insert(make_pair("moveLeft", SDLK_a));
	comms2.insert(make_pair("moveRight", SDLK_d));
	comms2.insert(make_pair("jump", SDLK_w));
	comms2.insert(make_pair("drop", SDLK_s));
*/
	//void(*enemyMovementPointer)(SpriteEnemy&) = moveEnemy;

	//void (*p)(SpritePlayer&) = leftUp;

	shared_ptr<Level> level1 = Level::getInstance(0);
	shared_ptr<Level> level2 = Level::getInstance(0);



	//sätter pauseknapp i gameEngine
	ge.changePauseKey(SDLK_ESCAPE);
	shared_ptr<SpritePlayer> s = SpritePlayer::getInstance({ 100, 100, 92, 92 }, "c:/Prog3/assets/Sprites/BallSprite_Cut.png", "c:/Prog3/assets/Sprites/BallSprite_Cut.png", 0.4,callBackPlayer,comms,ge.getRen(), false);
	//shared_ptr<SpritePlayer> s2 = SpritePlayer::getInstance({ 100, 50, 92, 92 }, "c:/Prog3/assets/Sprites/BallSprite_Cut.png", "c:/Prog3/assets/Sprites/BallSprite_Cut.png", 0.4, callBackPlayer, comms2, ge.getRen());
	shared_ptr<SpriteEnemy> se = SpriteEnemy::getInstance({ 600,200, 113, 67 }, "c:/Prog3/assets/Sprites/BirdEnemyIdleSprite_Cut.png", "c:/Prog3/assets/Sprites/BirdEnemyFlapSprite_Cut.png", 20, s, ge.getRen(), false);
	//se->installMovement(moveEnemy);
	shared_ptr<SpriteLabel> text1 = SpriteLabel::getInstance({ 0,0,100,50 }, "", 300, 50, "Enter Name:", 16, ge.getRen());
	shared_ptr<SpriteLabelEditable> textEdit = SpriteLabelEditable::getInstance({ 0,0,100,50 }, "",300,100,"Name here", 16, ge.getRen());
	shared_ptr<SpriteLabel> text2 = SpriteLabel::getInstance({ 0,0,100,50 }, "", 300, 200, "Press return to play", 100, ge.getRen());

	shared_ptr<SpriteStationary> sg = SpriteStationary::getInstance({ 300,200,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, ge.getRen());
	shared_ptr<SpriteStationary> sg1 = SpriteStationary::getInstance({ 100,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, ge.getRen());
	shared_ptr<SpriteStationary> sg2 = SpriteStationary::getInstance({ 300,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg3 = SpriteStationary::getInstance({ 400,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> wall = SpriteStationary::getInstance({ 300,400,100,50 }, "", false, true, false, ge.getRen());
	
	//shared_ptr<SpriteStationary> kill = SpriteStationary::getInstance({ 200,400,100,50 }, "", true, false, true, ge.getRen());



	//
	//level1->addSp(text1);
	//level1->addSp(text2);
	//level1->addSp(textEdit);
	//ge.addLevel(level1);
	//

	shared_ptr<SpriteLabelEditable> textEdit2 = SpriteLabelEditable::getInstance({ 0,0,100,50 }, "", 300, 100, "Name here", 16, ge.getRen());
	level2->addSp(textEdit2);
	level2->addSp(s);
	level2->addSp(se);
	level2->addSp(sg);
	level2->addSp(sg1);
	level2->addSp(sg2);
	level2->addSp(sg3);
	//level2->addSp(kill);
	level2->addSp(wall);
	ge.addLevel(level2);


	ge.run();
	

	return 0;
}
