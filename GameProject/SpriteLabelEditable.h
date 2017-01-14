#ifndef SPRITELABELEDITABLE_H_INCLUDED
#define SPRITELABELEDITABLE_H_INCLUDED
#include "SpriteLabel.h"
#include <memory>
#include <SDL_ttf.h>

namespace engine {
	class SpriteLabelEditable :
		public SpriteLabel
	{
	public:
		static 	std::shared_ptr<SpriteLabelEditable> getInstance(const SDL_Rect & r, std::string path, int locX, int locY, std::string text, int charLimit, SDL_Renderer* re);
		~SpriteLabelEditable();
		void draw();
		void addCharacter(const SDL_Event& e);
		void removeCharacter(const SDL_Event& e);
		void emptyText(const SDL_Event& e);
	protected:
		SpriteLabelEditable(const SDL_Rect& r, std::string path, int locX, int locY, std::string text, int charLimit, SDL_Renderer* re);
	private:
		const char *cstr;
		void setFontRect();
		SDL_Rect* rect;
	};
}
#endif
