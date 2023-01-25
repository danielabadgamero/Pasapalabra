#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include "Letter.h"

class Group
{
private:
	std::vector<Letter> circle{};
public:
	Group(SDL_Renderer*, SDL_Point, int);
	void draw(SDL_Renderer*);
};

#endif