#include "Level.h"
#include <vector>


using namespace std;

namespace engine {
	Level::Level(int x)
	{
	}

	shared_ptr<Level> Level::getInstance(int x) {
		return shared_ptr<Level>(new Level(x));
	}

	void Level::addSp(shared_ptr<Sprite> s)
	{
	}


void Level::fadeOut()
{
}

Level::~Level()
{
}


}
