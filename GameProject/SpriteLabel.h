#ifndef SPRITELABEL_H
#define SPRITELABEL_H
#include "Sprite.h"
#include <memory>
#include <SDL_ttf.h>

namespace engine {
	class SpriteLabel :
		public Sprite
	{
	public:
		
		static 	std::shared_ptr<SpriteLabel> getInstance(const SDL_Rect & r, std::string path);
		~SpriteLabel();
		void draw();
		void addCharacter(const SDL_Event& e);
		void removeCharacter(const SDL_Event& e);
		void emptyText(const SDL_Event& e);
	protected:
		
		SpriteLabel(const SDL_Rect& r, std::string path);
	private:
		int width;
		int height;
		bool changed = false;
		bool stopWriting = false;
		SDL_Event e;
		SDL_Texture* tex;
		TTF_Font *gFont = NULL;
		SDL_Rect fontRect;
		SDL_Color textColor = { 255,255, 255,255 };
		std::string textureText;
		std::string inputText = "Some Text";
		SDL_Surface* textSurface;
	};
}
#endif 
