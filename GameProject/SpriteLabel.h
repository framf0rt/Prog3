#ifndef SPRITELABEL_H_INCLUDED
#define SPRITELABEL_H_INCLUDED
#include "Sprite.h"
#include <memory>
#include <SDL_ttf.h>

namespace engine {
	class SpriteLabel :
		public Sprite
	{
	public:
		
		static 	std::shared_ptr<SpriteLabel> getInstance(const SDL_Rect & r, std::string path,int locX, int locY, std::string text, int charLimit, SDL_Renderer* re);
		~SpriteLabel();
		void drawed();
		void draw();
	protected:
		SpriteLabel(const SDL_Rect& r, std::string path, int locX, int locY,std::string text, int charLimit, SDL_Renderer* re);
		int locX;
		int locY;
		int charLimit;
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
		SDL_Rect* rect;
	private:
	};
}
#endif 
