#ifndef SPRITEMOVABLE_H
#define SPRITEMOVABLE_H
#include "Sprite.h"
namespace engine {
	class SpriteMovable :
		public Sprite
	{
	public:
		virtual void tick() {};
		~SpriteMovable();
		
	protected:
		SpriteMovable(const SDL_Rect& r, std::string path);
		void deltaTime();
		float dt;
		long last = SDL_GetTicks();
	};
}
#endif

