#pragma once
#include <SDL_ttf.h>
#include <SDL2\SDL.h>
#include <string>
class text
{
public:
	text(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
	~text();

	void display(int x, int y, SDL_Renderer *renderer) const;

	static SDL_Texture *loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);

private:
	SDL_Texture *text_texture = nullptr;
	mutable SDL_Rect text_rect;
};

