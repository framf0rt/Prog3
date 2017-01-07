#include "Sprite.h"
#include <string>
#include <SDL_image.h>
#include <iostream>


using namespace std;

namespace engine {



	void Sprite::draw() {
		SDL_RenderCopy(ge.getRen(), texture, NULL, &getRect());
	}
	Sprite::Sprite(const SDL_Rect& r, std::string path) :rect(r)
	{
		surface = IMG_Load(path.c_str());
		texture = IMG_LoadTexture(ge.getRen(), path.c_str());
		
		if (texture == nullptr) {
			cout << "Bild hittas inte" << endl;
		}
	}

	int Sprite::getAlphaXY(int x, int y) {
		if (x < surface->w && y < surface->h) {
			SDL_LockSurface(surface);
			Uint32* pixels = static_cast<Uint32*>(surface->pixels);
			Uint32 pixel = pixels[y*surface->w + x];
			SDL_UnlockSurface(surface);
			int alpha = (pixel >> 24) & 0xFF;
			return alpha;
		}
	}

	void Sprite::animation(SDL_Texture &anitexture) {
		texture = &(anitexture);
		
	}

	Sprite::~Sprite()
	{
	}
}

