#include <SDL.h>
#include <SDL_ttf.h>

#include "Letter.h"

Letter::Letter(SDL_Renderer* renderer, char letter, SDL_Point position, std::string answer, std::string definition) : answer{ answer }, definition{ definition }
{
	TTF_Font* font{ TTF_OpenFont("font.ttf", 20) };

	SDL_Surface* surface{ TTF_RenderGlyph_Blended(font, letter, {0xcc, 0xcc, 0xcc, 0xff}) };
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

	rect.x = position.x - rect.w / 2;
	rect.y = position.y - rect.h / 2;

	status = pass;

	TTF_CloseFont(font);
}

void Letter::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}