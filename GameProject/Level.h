#ifndef LEVEL_H
#define LEVEL_H
#include <memory>
#include <vector>
#include "Sprite.h"
class Sprite;


namespace engine {

	class Level
	{
	public:
		std::vector<std::shared_ptr<Sprite>> getSprites() const { return sprites; }
		static std::shared_ptr<Level> getInstance();
		void addSp(std::shared_ptr<Sprite> s);
		void fadeOut();
		~Level();
	protected:
		
	private:
		Level();
		std::vector<std::shared_ptr<Sprite>> sprites;
		
	};

}
#endif 
