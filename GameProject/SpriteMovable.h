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
		std::vector<SDL_Rect> getPixelCollisionRects() { return pixelCollisionRects; }
		~SpriteMovable();
		void setDirection(int i) { direction = i; }
		float getTimeSinceEvent() const { return timeSinceEvent; }
		void resetTimeSinceEvent() { timeSinceEvent = 0; }
		void updateTimeSinceEvent() { timeSinceEvent += ge.getDeltaTime(); }
	protected:
		
		int width = 0;
		SDL_Rect rt = { 0,0,0,0 };
		int y = 0;
		int x = 0;
		std::vector<SDL_Rect> pixelCollisionRects;
		SpriteMovable(const SDL_Rect& r, std::string path);
		void setPixelColliders();
		SDL_Rect pc = { 0,0,0,0 };
		float alphaModifier = 255;
		bool player;
		int direction;
		bool textureSwap;
		int rotation;
		int animationCount;
		bool invulnerable;
		bool fadeOutIn;
		SDL_Texture* textureMoving;
		SDL_Texture* textureStationary;
	private:
		float timeSinceEvent;
	};
}
#endif

