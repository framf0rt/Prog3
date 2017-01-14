#include "SpriteLabel.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

namespace engine {

	shared_ptr<SpriteLabel> SpriteLabel::getInstance(const SDL_Rect& r, std::string path, int locX, int locY, std::string text, int charLimit, SDL_Renderer* re) {
		return shared_ptr<SpriteLabel>(new SpriteLabel(r, path,locX,locY,text,charLimit,re));
	}

	SpriteLabel::SpriteLabel(const SDL_Rect& r, std::string path, int locX, int locY, std::string text, int charLimit, SDL_Renderer* re) :Sprite(r, path,re)
	{
		this->locX = locX;
		this->locY = locY;
		this->inputText = text;
		this->charLimit = charLimit;
		
	}


	SpriteLabel::~SpriteLabel()
	{

		//TTF_CloseFont(gFont);
		//SDL_FreeSurface(textSurface);
		//SDL_DestroyTexture(tex);
	}

	void SpriteLabel::draw() {

			if (TTF_Init() == -1)
			{
				cout << "Ttf startar ej" << endl;
				return;
			}
			else {

				gFont = TTF_OpenFont("arial.ttf", 28);
				if (gFont == NULL) {
					cout << "Hittar inte font" << endl;
					return;
				}

				SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, inputText.c_str(), textColor);
				if (textSurface != NULL)
				{
				
					tex = SDL_CreateTextureFromSurface(getRen(), textSurface);
					setTexture(tex);
					if (getTexture() == NULL) {
						return;
					}
					else {
						SDL_Rect* rect = &(fontRect);
						const char *cstr = inputText.c_str();
						TTF_SizeText(gFont, cstr, &(fontRect.w), &(fontRect.h));
						fontRect = { locX - (fontRect.w / 2),locY,fontRect.w,fontRect.h };
						SDL_RenderCopyEx(getRen(), getTexture(), nullptr, rect, 0, nullptr, SDL_FLIP_NONE);
					}
				}
			}

			TTF_CloseFont(gFont);
			SDL_FreeSurface(textSurface);
			SDL_DestroyTexture(tex);
			TTF_Quit();
	
	}



	
}
