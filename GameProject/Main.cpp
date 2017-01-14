
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
	shared_ptr<Level> level3 = Level::getInstance(0);
	shared_ptr<Level> level4 = Level::getInstance(0);



	//sätter pauseknapp i gameEngine
	ge.changePauseKey(SDLK_ESCAPE);

	shared_ptr<SpriteLabel> text1 = SpriteLabel::getInstance({ 0,0,100,50 }, "", 750, 50, "Enter Name:", 16, ge.getRen());
	shared_ptr<SpriteLabelEditable> textEdit = SpriteLabelEditable::getInstance({ 0,0,100,50 }, "",750,100,"Name here", 16, ge.getRen());
	shared_ptr<SpriteLabel> text2 = SpriteLabel::getInstance({ 0,0,100,50 }, "", 750, 200, "Press return to play", 100, ge.getRen());

	level1->addSp(text1);
	level1->addSp(text2);
	level1->addSp(textEdit);
	ge.addLevel(level1);
	


	shared_ptr<SpritePlayer> s = SpritePlayer::getInstance({ 100, 50, 92, 92 }, "c:/Prog3/assets/Sprites/BallSprite_Cut.png", "c:/Prog3/assets/Sprites/BallSprite_Cut.png", 0.4, callBackPlayer, comms, ge.getRen(),false);
	
	shared_ptr<SpriteStationary> sg = SpriteStationary::getInstance({ 300,700,100,50 }, "c:/Prog3/assets/Sprites/PlankSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg1 = SpriteStationary::getInstance({ 100,200,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg2 = SpriteStationary::getInstance({ 10,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg3 = SpriteStationary::getInstance({ 400,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> wall = SpriteStationary::getInstance({ 350,10,40,600 }, "c:/Prog3/assets/Sprites/ColumnSprite_Cut.png", false, true, false, false, ge.getRen());

	shared_ptr<SpriteStationary> Ice = SpriteStationary::getInstance({ 380,300,150,100 }, "c:/Prog3/assets/Sprites/IceSprite_Cut.png", false, false, true, false, ge.getRen());
	shared_ptr<SpriteStationary> sg4 = SpriteStationary::getInstance({ 620,650,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg5 = SpriteStationary::getInstance({ 690,450,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg6 = SpriteStationary::getInstance({ 570,330,70,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg7 = SpriteStationary::getInstance({ 380,150,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg8 = SpriteStationary::getInstance({ 680,100,100,50 }, "c:/Prog3/assets/Sprites/PlankSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> wall1 = SpriteStationary::getInstance({ 800,200,40,600 }, "c:/Prog3/assets/Sprites/ColumnSprite_Cut.png", false, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg9 = SpriteStationary::getInstance({ 820,100,700,50 }, "c:/Prog3/assets/Sprites/PlankSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg10 = SpriteStationary::getInstance({ 820,300,700,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg11 = SpriteStationary::getInstance({ 820,650,700,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> sg12 = SpriteStationary::getInstance({ 820,500,100,50 }, "c:/Prog3/assets/Sprites/IceSprite_Cut.png", false, false, true, false, ge.getRen());
	shared_ptr<SpriteStationary> sg13 = SpriteStationary::getInstance({ 1020,500,200,50 }, "c:/Prog3/assets/Sprites/IceSprite_Cut.png", false, false, true, false, ge.getRen());
	shared_ptr<SpriteStationary> sg14 = SpriteStationary::getInstance({ 1320,500,200,50 }, "c:/Prog3/assets/Sprites/IceSprite_Cut.png", false, false, true, false, ge.getRen());
	shared_ptr<SpriteStationary> sg15 = SpriteStationary::getInstance({ 1220,370,100,50 }, "c:/Prog3/assets/Sprites/IceSprite_Cut.png", false, false, true, false, ge.getRen());
	shared_ptr<SpriteStationary> coin = SpriteStationary::getInstance({ 1220,450,100,100 }, "c:/Prog3/assets/Sprites/CoinSprite_Cut.png", true, false, false, true, ge.getRen());

	shared_ptr<SpriteStationary> kill = SpriteStationary::getInstance({ -200,720,2000,500 }, "", false, false, true, false, ge.getRen());
	shared_ptr<SpriteEnemy> se = SpriteEnemy::getInstance({ 1600,200, 113, 67 }, "c:/Prog3/assets/Sprites/BirdEnemyIdleSprite_Cut.png", "c:/Prog3/assets/Sprites/BirdEnemyFlapSprite_Cut.png", 20, s, ge.getRen(), false);


	level2->addSp(s);
	
	level2->addSp(sg);
	level2->addSp(sg1);
	level2->addSp(sg2);
	level2->addSp(sg3);
	level2->addSp(sg4);
	level2->addSp(sg5);
	level2->addSp(sg6);
	level2->addSp(sg7);
	level2->addSp(sg8);
	level2->addSp(sg9);
	level2->addSp(sg10);
	level2->addSp(sg11);
	level2->addSp(sg12);
	level2->addSp(sg13);
	level2->addSp(sg14);
	level2->addSp(sg15);
	level2->addSp(coin);
	level2->addSp(kill);
	level2->addSp(wall);
	level2->addSp(wall1);
	level2->addSp(Ice);
	level2->addSp(se);
	ge.addLevel(level2);

	shared_ptr<SpritePlayer> L2s = SpritePlayer::getInstance({ 100, 50, 92, 92 }, "c:/Prog3/assets/Sprites/BallSprite_Cut.png", "c:/Prog3/assets/Sprites/BallSprite_Cut.png", 0.4, callBackPlayer, comms, ge.getRen(),false);
	
	shared_ptr<SpriteStationary> L2sg = SpriteStationary::getInstance({ 350,70,100,50 }, "c:/Prog3/assets/Sprites/PlankSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg1 = SpriteStationary::getInstance({ 100,200,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg5 = SpriteStationary::getInstance({ 750,70,100,50 }, "c:/Prog3/assets/Sprites/PlankSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg13 = SpriteStationary::getInstance({ 800,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg6 = SpriteStationary::getInstance({ 900,200,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg7 = SpriteStationary::getInstance({ 1000,250,400,50 }, "c:/Prog3/assets/Sprites/PlankSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg4 = SpriteStationary::getInstance({ 500,200,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg2 = SpriteStationary::getInstance({ 10,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg3 = SpriteStationary::getInstance({ 400,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2wall = SpriteStationary::getInstance({ 350,350 ,40,250 }, "c:/Prog3/assets/Sprites/ColumnSprite_Cut.png", false, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg10 = SpriteStationary::getInstance({ 1400,100,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg11 = SpriteStationary::getInstance({ 1400,700,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg14 = SpriteStationary::getInstance({ 1200,500,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg15 = SpriteStationary::getInstance({ 1050,600,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg16 = SpriteStationary::getInstance({ 875,700,100,50 }, "c:/Prog3/assets/Sprites/PlankSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg17 = SpriteStationary::getInstance({ 700,575,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg18 = SpriteStationary::getInstance({ 600,650,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg19 = SpriteStationary::getInstance({ 325,700,100,50 }, "c:/Prog3/assets/Sprites/PlankSprite_Cut.png", true, false, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg21 = SpriteStationary::getInstance({ 260,570,100,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg22 = SpriteStationary::getInstance({ 110,450,150,50 }, "c:/Prog3/assets/Sprites/GrassSprite_Cut.png", true, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2wall1 = SpriteStationary::getInstance({ 900,350,40,250 }, "c:/Prog3/assets/Sprites/ColumnSprite_Cut.png", false, true, false, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg12 = SpriteStationary::getInstance({ 0,300,1350,50 }, "c:/Prog3/assets/Sprites/Lava.png", false, false, true, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg9 = SpriteStationary::getInstance({ 1070,100,210,20 }, "c:/Prog3/assets/Sprites/Lava.png", false, false, true, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg8 = SpriteStationary::getInstance({ 1380,150,20,150 }, "c:/Prog3/assets/Sprites/Lava.png", false, false, true, false, ge.getRen());
	shared_ptr<SpriteStationary> L2sg20 = SpriteStationary::getInstance({ 180,500,20,200 }, "c:/Prog3/assets/Sprites/Lava.png", false, false, true, false, ge.getRen());
	shared_ptr<SpriteStationary> L2coin = SpriteStationary::getInstance({ 10,650,100,100 }, "c:/Prog3/assets/Sprites/CoinSprite_Cut.png", true, false, false, true, ge.getRen());
	shared_ptr<SpriteStationary> L2kill = SpriteStationary::getInstance({ 0,720,1800,500 }, "", false, false, true, false, ge.getRen());
	shared_ptr<SpriteEnemy> L2se = SpriteEnemy::getInstance({ 1600,200, 113, 67 }, "c:/Prog3/assets/Sprites/BirdEnemyIdleSprite_Cut.png", "c:/Prog3/assets/Sprites/BirdEnemyFlapSprite_Cut.png", 20, L2s, ge.getRen(), false);
	
	level3->addSp(L2s);

	level3->addSp(L2sg);
	level3->addSp(L2sg1);
	level3->addSp(L2sg2);
	level3->addSp(L2sg3);
	level3->addSp(L2sg4);
	level3->addSp(L2sg5);
	level3->addSp(L2sg6);
	level3->addSp(L2sg7);
	level3->addSp(L2sg8);
	level3->addSp(L2sg9);
	level3->addSp(L2sg10);
	level3->addSp(L2sg11);
	level3->addSp(L2sg12);
	level3->addSp(L2sg13);
	level3->addSp(L2sg14);
	level3->addSp(L2sg15);
	level3->addSp(L2sg16);
	level3->addSp(L2sg17);
	level3->addSp(L2sg18);
	level3->addSp(L2sg19);
	level3->addSp(L2sg20);
	level3->addSp(L2sg21);
	level3->addSp(L2sg22);
	level3->addSp(L2coin);
	level3->addSp(L2kill);
	level3->addSp(L2wall);
	level3->addSp(L2wall1);
	level3->addSp(L2se);
	ge.addLevel(level3);

	shared_ptr<SpriteLabel> winText = SpriteLabel::getInstance({ 0,0,100,50 }, "", 300, 50, "You WIN", 16, ge.getRen());
	level4->addSp(winText);
	ge.addLevel(level4);
	


	ge.run();
	

	return 0;
}
