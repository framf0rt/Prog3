#ifndef SPRITEMOVABLE_H
#define SPRITEMOVABLE_H
#include "Sprite.h"
namespace engine {
	class SpriteMovable :
		public Sprite
	{
	public:
		virtual void tick() {};
		void draw();
		~SpriteMovable();
		
	protected:
		SpriteMovable(const SDL_Rect& r, std::string path);
		float alphaModifier;
		int direction;
		bool textureSwap;
		int rotation;
		int animationCount;
		SDL_Texture* textureMoving;
		SDL_Texture* textureStationary;
	};
}
#endif

