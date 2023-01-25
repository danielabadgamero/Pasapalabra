#include <SDL.h>

#include <cmath>

#include "Group.h"
#include "Definitions.h"

static SDL_Point calcPos(SDL_Point windowSize, char c)
{
	double deg{ static_cast<double>(c - 'A') / ('Z' - 'A' + 1) * 2 * M_PI };
	return { static_cast<int>(sin(deg) * (windowSize.y * 0.3) + windowSize.x / 2), static_cast<int>(cos(deg) * (-windowSize.y * 0.3) + windowSize.y / 2) - 75 };
}

static void advanceCurrentLetter(std::vector<Letter>::iterator* currentLetter, std::vector<Letter>::iterator first, std::vector<Letter>::iterator last)
{
	int rounds{};
	while ((*currentLetter)->getStatus() != 0)
	{
		(*currentLetter)++;
		if (*currentLetter == last)
			*currentLetter = first;
		rounds++;
		if (rounds > 50)
			break;
	}
}

Group::Group(SDL_Renderer* renderer, SDL_Point windowSize, int group)
{
	for (char c{ 'A' }; c <= 'Z'; c++)
		circle.push_back({ renderer, c, calcPos(windowSize, c), definitions[group - 1].at(c - 'A')[0], definitions[group - 1].at(c - 'A')[1] });
	timeLeft = 200.0;

	currentLetter = circle.begin();
}

void Group::draw(SDL_Renderer* renderer)
{
	for (Letter letter : circle)
		letter.draw(renderer);
}

void Group::drawGui(SDL_Point windowSize, int* turn, double dt)
{
	ImGui::GetStyle().ItemSpacing.y = 10.0f;

	ImGui::SetNextWindowPos({ windowSize.x * 0.5f, windowSize.y * 0.05f }, 0, { 0.5f, 0.5f });
	ImGui::Begin("header", NULL, windowFlags);
	ImGui::Text("Grupo %d", *turn);
	ImGui::End();

	ImGui::SetNextWindowPos({ windowSize.x * 0.95f, windowSize.y * 0.9f }, 0, { 0.5f, 0.5f });
	ImGui::Begin("timer", NULL, windowFlags);
	ImGui::TextColored({ (200.0f - static_cast<float>(timeLeft)) / 200.0f, static_cast<float>(timeLeft) / 200.0f, 0, 1.0f }, "%d", static_cast<int>(timeLeft));
	ImGui::End();

	if (running)
	{
		timeLeft -= dt;

		ImGui::SetNextWindowPos({ windowSize.x * 0.5f, windowSize.y * 0.9f }, 0, { 0.5f, 0.5f });
		ImGui::SetNextWindowSize({ windowSize.x * 0.75f, windowSize.y * 0.1f });
		ImGui::Begin((std::string{ "Letra: " } + currentLetter->getLetter()).c_str(), NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::Text((char*)currentLetter->getDefinition().c_str());
		ImGui::End();

		ImGui::SetNextWindowPos({ windowSize.x * 0.15f, windowSize.y * 0.5f }, 0, { 0.5f, 0.5f });
		ImGui::Begin("ControlButtons", 0, windowFlags);
		ImGui::PushStyleColor(ImGuiCol_Button, { 0x20 / 255.0f, 0x80 / 255.0f, 0x20 / 255.0f, 1.0f });
		if (ImGui::Button("Correcto", { 200.0f, 50.0f }))
		{
			currentLetter->setStatus(1);
			advanceCurrentLetter(&currentLetter, circle.begin(), circle.end());
		}
		ImGui::PopStyleColor();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0x20 / 255.0f, 0x20 / 255.0f, 0x80 / 255.0f, 1.0f });
		if (ImGui::Button("Pasapalabra", { 200.0f, 50.0f }))
		{
			if (currentLetter == circle.end())
				currentLetter = circle.begin();
			else
				currentLetter++;
			running = false;
			advanceCurrentLetter(&currentLetter, circle.begin(), circle.end());
		}
		ImGui::PopStyleColor();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0x80 / 255.0f, 0x20 / 255.0f, 0x20 / 255.0f, 1.0f });
		if (ImGui::Button("Incorrecto", { 200.0f, 50.0f }))
		{
			currentLetter->setStatus(-1);
			running = false;
			advanceCurrentLetter(&currentLetter, circle.begin(), circle.end());
		}
		ImGui::PopStyleColor();
		ImGui::End();
	}
	else
	{
		ImGui::SetNextWindowPos({ windowSize.x * 0.15f, windowSize.y * 0.5f }, 0, { 0.5f, 0.5f });
		ImGui::Begin("ControlButtons", NULL, windowFlags);
		if (ImGui::Button("Empezar", { 200.0f, 50.0f }))
			running = true;
		if (ImGui::Button("Cambiar grupo", { 200.0f, 50.0f }))
			if (*turn == 1) *turn = 2;
			else *turn = 1;
		ImGui::End();
	}
}

void Group::resize(SDL_Point windowSize)
{
	for (char c{ 'A' }; c <= 'Z'; c++)
		circle.at(c - 'A').move(calcPos(windowSize, c));
}