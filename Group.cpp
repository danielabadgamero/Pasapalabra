#include <SDL.h>

#include <cmath>

#include "Group.h"
#include "Definitions.h"

Group::Group(SDL_Renderer* renderer, SDL_Point windowSize, int group)
{
	for (char c{ 'A' }; c <= 'Z'; c++)
	{
		double deg{ static_cast<double>(c - 'A') / ('Z' - 'A' + 1) * 2 * M_PI };
		SDL_Point pos{ static_cast<int>(sin(deg) * 200 + windowSize.x / 2), static_cast<int>(cos(deg) * -200 + windowSize.y / 2) };
		circle.push_back({ renderer, c, pos, definitions[group - 1].at(c - 'A')[0], definitions[group - 1].at(c - 'A')[1] });
	}
}

void Group::draw(SDL_Renderer* renderer)
{
	for (Letter letter : circle)
		letter.draw(renderer);
}