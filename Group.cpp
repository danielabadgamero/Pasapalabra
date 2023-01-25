#include <SDL.h>

#include <cmath>

#include "Group.h"
#include "Definitions.h"

static SDL_Point calcPos(SDL_Point windowSize, char c)
{
	double deg{ static_cast<double>(c - 'A') / ('Z' - 'A' + 1) * 2 * M_PI };
	return { static_cast<int>(sin(deg) * (windowSize.y / 3) + windowSize.x / 2), static_cast<int>(cos(deg) * (-windowSize.y / 3) + windowSize.y / 2) };
}

Group::Group(SDL_Renderer* renderer, SDL_Point windowSize, int group)
{
	for (char c{ 'A' }; c <= 'Z'; c++)
		circle.push_back({ renderer, c, calcPos(windowSize, c), definitions[group - 1].at(c - 'A')[0], definitions[group - 1].at(c - 'A')[1] });
	timeLeft = 200.0;
}

void Group::draw(SDL_Renderer* renderer)
{
	for (Letter letter : circle)
		letter.draw(renderer);
}

void Group::drawGui(SDL_Point windowSize, int* turn, double dt)
{
	ImGui::SetNextWindowPos({ windowSize.x * 0.5f, windowSize.y * 0.1f }, 0, { 0.5, 0.5 });
	ImGui::Begin("header", NULL, windowFlags);
	ImGui::Text("Grupo %d", *turn);
	ImGui::End();

	ImGui::SetNextWindowPos({ windowSize.x * 0.9f, windowSize.y * 0.9f }, 0, { 0.5, 0.5 });
	ImGui::Begin("timer", NULL, windowFlags);
	ImGui::TextColored({ (200.0f - static_cast<float>(timeLeft)) / 200.0f, static_cast<float>(timeLeft) / 200.0f, 0, 1.0f }, "%d", static_cast<int>(timeLeft));
	ImGui::End();

}

void Group::resize(SDL_Point windowSize)
{
	for (char c{ 'A' }; c <= 'Z'; c++)
		circle.at(c - 'A').move(calcPos(windowSize, c));
}