#include "Level.h"
#include <vector>


using namespace std;

namespace engine {
	Level::Level()
	{
	}

	shared_ptr<Level> Level::getInstance() {
		return shared_ptr<Level>(new Level());
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
