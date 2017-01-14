#include "SpriteLabel.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

namespace engine {

	shared_ptr<SpriteLabel> SpriteLabel::getInstance(const SDL_Rect& r, std::string path, int locX, int locY, std::string text, int charLimit, bool inputEnabled) {
		return shared_ptr<SpriteLabel>(new SpriteLabel(r, path,locX,locY,text,charLimit,inputEnabled));
	}

	SpriteLabel::SpriteLabel(const SDL_Rect& r, std::string path, int locX, int locY, std::string text, int charLimit, bool inputEnabled) :Sprite(r, path)
	{
		this->locX = locX;
		this->locY = locY;
		this->inputText = text;
		this->charLimit = charLimit;
		this->inputEnabled = inputEnabled;
	}


	SpriteLabel::~SpriteLabel()
	{
	}

	void SpriteLabel::draw() {

			SDL_StartTextInput();

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
					tex = SDL_CreateTextureFromSurface(ge.getRen(), textSurface);
					setTexture(tex);
					if (getTexture() == NULL) {
						return;
					}
					else {
						SDL_Rect* rect = &(fontRect);
						const char *cstr = inputText.c_str();
						TTF_SizeText(gFont, cstr, &(fontRect.w), &(fontRect.h));
						fontRect = { locX - (fontRect.w / 2),locY,fontRect.w,fontRect.h };
						SDL_RenderCopyEx(ge.getRen(), getTexture(), nullptr, rect, 0, nullptr, SDL_FLIP_NONE);
					}
				}
			}
	
	}


	void SpriteLabel::addCharacter(const SDL_Event& e)
	{
		
		fontRect = { 0,0,0,0 };
		if (changed == true && inputText.size() < charLimit) {
			inputText += e.text.text;	
		}
		else if (changed == false){
			inputText = e.text.text;
			changed = true;
		}
	}
	void SpriteLabel::removeCharacter(const SDL_Event & e)
	{
		if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
			inputText.pop_back();
		}
	}

	void SpriteLabel::emptyText(const SDL_Event & e)
	{
		SDL_DestroyTexture(getTexture());
		inputText.empty();
		SDL_StopTextInput();
	}

	
}
