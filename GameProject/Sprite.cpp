#include "Sprite.h"
#include <string>
#include <SDL_image.h>
#include <iostream>


using namespace std;

namespace engine {

	Sprite:: ~Sprite() {
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}

	void Sprite::draw() {
		if (texture == nullptr) {
			return;
		}
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
			int red = pixel & 0XFF;
			int green = (pixel >> 8) & 0xFF;
			int blue = (pixel >> 16) & 0xFF;
			int alpha = (pixel >> 24) & 0xFF;
			return alpha;
		}
		else {
			return 0;
		}
	}

	void Sprite::animation(SDL_Texture &anitexture) {
		texture = &(anitexture);
		
	}

	void Sprite::onCollision(shared_ptr<Sprite> spriteA, shared_ptr<Sprite> spriteB) {

	}

	
}

