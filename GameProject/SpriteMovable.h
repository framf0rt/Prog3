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
		void setPixelColliders();
		SDL_Rect pc = { 0,0,0,0 };
		float alphaModifier = 255;
		int direction;
		bool textureSwap;
		int rotation;
		int animationCount;
		bool invulnerable;
		bool fadeOutIn;
		SDL_Texture* textureMoving;
		SDL_Texture* textureStationary;
	};
}
#endif

