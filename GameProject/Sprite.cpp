#include "Sprite.h"
#include <string>
#include <SDL_image.h>
#include <iostream>


using namespace std;

namespace engine {




	void Sprite::draw() {
		SDL_RenderCopy(ge.getRen(), texture , NULL, &getRect());
	}
	Sprite::Sprite(const SDL_Rect& r, std::string path):rect(r)	
	{
		texture = IMG_LoadTexture(ge.getRen(), path.c_str());
		if (texture == nullptr) {
			cout << "Bild hittas inte" << endl;
		}
	}


	Sprite::~Sprite()
	{
	}
}

