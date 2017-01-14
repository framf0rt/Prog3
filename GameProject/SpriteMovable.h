#ifndef SPRITEMOVABLE_H_INCLUDED
#define SPRITEMOVABLE_H_INCLUDED
#include "Sprite.h"
#include <memory>
namespace engine {
	class SpriteMovable :
		public Sprite
	{
	public:
		virtual void tick(float dt) {};
		void draw();
		std::vector<SDL_Rect> getPixelCollisionRects() { return pixelCollisionRects; }
		~SpriteMovable();
		void setDirection(int i) { direction = i; }
		float getTimeSinceEvent() const { return timeSinceEvent; }
		void resetTimeSinceEvent() { timeSinceEvent = 0; }
		void updateTimeSinceEvent(float dt) { timeSinceEvent += dt; }
		void setGravity(bool g) { gravity = g; }
		void setAntigravity(bool a) { antiGravity = a; }
		bool hasGravity() const { return gravity; };
		bool hasAntigravity() const { return antiGravity; }
	protected:
		int yCoordAtEvent;
		int getYDistance() const { return yCoordAtEvent +((ySpeed*timeSinceEvent + timeSinceEvent*timeSinceEvent * 600 / 2)*((antiGravity)?-1:1));}
		int ySpeed = 200;
		int width = 0;
		SDL_Rect rt = { 0,0,0,0 };
		int y = 0;
		int x = 0;
		std::vector<SDL_Rect> pixelCollisionRects;
		SpriteMovable(const SDL_Rect& r, std::string path, SDL_Renderer* re, bool g);
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
		bool antiGravity;
		bool gravity;
		float timeSinceEvent;
	};
}
#endif

