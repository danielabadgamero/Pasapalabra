#ifndef LETTER_H
#define LETTER_H

#include <SDL.h>

#include <string>

class Letter
{
private:
	SDL_Texture* texture{};
	SDL_Rect rect{};

	std::string definition{};
	std::string answer{};

	enum
	{
		pass,
		right,
		wrong
	} status{};
public:
	Letter(SDL_Renderer*, char, SDL_Point, std::string, std::string);
	void draw(SDL_Renderer*);
};

#endif