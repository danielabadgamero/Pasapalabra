#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Letter.h"

Letter::Letter(SDL_Renderer* renderer, char letter, SDL_Point position, std::string answer, std::string definition) : answer{ answer }, definition{ definition }
{
	TTF_Font* font{ TTF_OpenFont("font.ttf", 20) };

	SDL_Surface* surface{ TTF_RenderGlyph_Blended(font, letter, {0xcc, 0xcc, 0xcc, 0xff}) };
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &charRect.w, &charRect.h);
	charRect.x = position.x - charRect.w / 2;
	charRect.y = position.y - charRect.h / 2;

	circle = IMG_LoadTexture(renderer, "circle.png");
	SDL_QueryTexture(circle, NULL, NULL, &circleRect.w, &circleRect.h);
	circleRect.x = position.x - circleRect.w / 2;
	circleRect.y = position.y - circleRect.h / 2;

	status = pass;

	TTF_CloseFont(font);
}

void Letter::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &charRect);
	SDL_RenderCopy(renderer, circle, NULL, &circleRect);
}

void Letter::move(SDL_Point position)
{
	charRect.x = position.x - charRect.w / 2;
	charRect.y = position.y - charRect.h / 2;

	circleRect.x = position.x - circleRect.w / 2;
	circleRect.y = position.y - circleRect.h / 2;
}