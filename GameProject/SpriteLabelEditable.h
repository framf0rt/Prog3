#ifndef SPRITELABELEDITABLE_H
#define SPRITELABELEDITABLE_H
#include "SpriteLabel.h"
#include <memory>
#include <SDL_ttf.h>

namespace engine {
	class SpriteLabelEditable :
		public SpriteLabel
	{
	public:
		static 	std::shared_ptr<SpriteLabelEditable> getInstance(const SDL_Rect & r, std::string path, int locX, int locY, std::string text, int charLimit);
		~SpriteLabelEditable();
		void draw();
		void addCharacter(const SDL_Event& e);
		void removeCharacter(const SDL_Event& e);
		void emptyText(const SDL_Event& e);
	protected:
		SpriteLabelEditable(const SDL_Rect& r, std::string path, int locX, int locY, std::string text, int charLimit);
	};
}
#endif
