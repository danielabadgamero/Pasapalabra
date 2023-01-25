#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include <imgui.h>

#include "Letter.h"

class Group
{
private:
	ImGuiWindowFlags headerFlags{ ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground };
	std::vector<Letter> circle{};
public:
	Group(SDL_Renderer*, SDL_Point, int);
	void draw(SDL_Renderer*);
	void drawGui(SDL_Point, int*);
	void resize(SDL_Point);
};

#endif