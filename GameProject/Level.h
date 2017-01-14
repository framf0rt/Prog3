#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include <memory>
#include <vector>
#include "Sprite.h"

namespace engine {

	class Level
	{
	public:
		std::vector<std::shared_ptr<Sprite>>& getSprites(){ return sprites; }
		static std::shared_ptr<Level> getInstance(int x);
		void addSp(std::shared_ptr<Sprite> s);
		void fadeOut();
		~Level();
	protected:
		
	private:
		Level(int x);
		std::vector<std::shared_ptr<Sprite>> sprites;
		
	};

}
#endif 
