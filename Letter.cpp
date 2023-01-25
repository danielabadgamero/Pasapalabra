#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Letter.h"

Letter::Letter(SDL_Renderer* renderer, char letter, SDL_Point position, std::u8string answer, std::u8string definition)
	: answer{ answer }, definition{ definition }, letter{ letter }
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
	switch (status)
	{
	case pass:
		SDL_SetTextureColorMod(circle, 0x20, 0x20, 0x80);
		break;
	case right:
		SDL_SetTextureColorMod(circle, 0x20, 0x80, 0x20);
		break;
	case wrong:
		SDL_SetTextureColorMod(circle, 0x80, 0x20, 0x20);
		break;
	case selected:
		SDL_SetTextureColorMod(circle, 0x40, 0x40, 0xb0);
		break;
	}
	SDL_RenderCopy(renderer, circle, NULL, &circleRect);
	SDL_RenderCopy(renderer, texture, NULL, &charRect);
}

void Letter::move(SDL_Point position)
{
	charRect.x = position.x - charRect.w / 2;
	charRect.y = position.y - charRect.h / 2;

	circleRect.x = position.x - circleRect.w / 2;
	circleRect.y = position.y - circleRect.h / 2;
}

char Letter::getLetter()
{
	return letter;
}

std::u8string Letter::getDefinition()
{
	return definition;
}

void Letter::setStatus(int st)
{
	status = static_cast<Status>(st);
}

int Letter::getStatus()
{
	return static_cast<int>(status);
}