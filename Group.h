#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include <imgui.h>

#include "Letter.h"

class Group
{
private:
	ImGuiWindowFlags windowFlags{ ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground };
	std::vector<Letter> circle{};
	double timeLeft{};
	bool running{};
public:
	Group(SDL_Renderer*, SDL_Point, int);
	void draw(SDL_Renderer*);
	void drawGui(SDL_Point, int*, double);
	void resize(SDL_Point);
};

#endif