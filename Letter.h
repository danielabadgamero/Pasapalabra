#ifndef LETTER_H
#define LETTER_H

#include <SDL.h>

#include <string>

class Letter
{
private:
	SDL_Texture* texture{};
	SDL_Texture* circle{};
	SDL_Rect charRect{};
	SDL_Rect circleRect{};
	char letter{};

	std::u8string definition{};
	std::u8string answer{};

	enum Status
	{
		pass = 0,
		right = 1,
		wrong = -1
	} status{};
public:
	Letter(SDL_Renderer*, char, SDL_Point, std::u8string, std::u8string);
	void draw(SDL_Renderer*);
	void move(SDL_Point);
	char getLetter();
	std::u8string getDefinition();
	void setStatus(int);
	int getStatus();
};

#endif