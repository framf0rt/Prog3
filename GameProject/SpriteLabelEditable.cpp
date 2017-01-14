#include "SpriteLabelEditable.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
using namespace std;

namespace engine {

	shared_ptr<SpriteLabelEditable> SpriteLabelEditable::getInstance(const SDL_Rect& r, std::string path, int locX, int locY, std::string text, int charLimit, SDL_Renderer* re) {
		return shared_ptr<SpriteLabelEditable>(new SpriteLabelEditable(r, path, locX, locY, text, charLimit,re));
	}

	SpriteLabelEditable::SpriteLabelEditable(const SDL_Rect & r, std::string path, int locX, int locY, std::string text, int charLimit, SDL_Renderer* re) :SpriteLabel(r, path, locX, locY, text, charLimit, re)
	{
	}


	SpriteLabelEditable::~SpriteLabelEditable()
	{
	}

	void SpriteLabelEditable::draw() {

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
				tex = SDL_CreateTextureFromSurface(getRen(), textSurface);
				setTexture(tex);
				if (getTexture() == NULL) {
					return;
				}
				else {
					rect = &(fontRect);
					cstr = inputText.c_str();
					TTF_SizeText(gFont, cstr, &(fontRect.w), &(fontRect.h));
					fontRect = { locX - (fontRect.w / 2),locY,fontRect.w,fontRect.h };
					SDL_RenderCopyEx(getRen(), getTexture(), nullptr, rect, 0, nullptr, SDL_FLIP_NONE);
				}
			}
		}
		TTF_CloseFont(gFont);
		TTF_Quit();
		SDL_StopTextInput();
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(tex);
		
	}

	void SpriteLabelEditable::addCharacter(const SDL_Event& e)
	{

		fontRect = { 0,0,0,0 };
		if (changed == true && inputText.size() < charLimit) {
			inputText += e.text.text;
		}
		else if (changed == false) {
			inputText = e.text.text;
			changed = true;
		}
		//setFontRect();
	}
	void SpriteLabelEditable::setFontRect() {
		rect = &(fontRect);
		cstr = inputText.c_str();
		TTF_SizeText(gFont, cstr, &(fontRect.w), &(fontRect.h));
		fontRect = { locX - (fontRect.w / 2),locY,fontRect.w,fontRect.h };
	}
	void SpriteLabelEditable::removeCharacter(const SDL_Event & e)
	{
		if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
			inputText.pop_back();
		}
		//setFontRect();
	}

	void SpriteLabelEditable::emptyText(const SDL_Event & e)
	{
		SDL_DestroyTexture(getTexture());
		inputText.empty();
		SDL_StopTextInput();
	}

}