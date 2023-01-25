#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_sdlrenderer.h>

#include "Group.h"

int main(int argc, char* argv[])
{	argc; argv;

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
	SDL_Event e{};
	SDL_Point windowSize{ 1600, 900 };

	window = SDL_CreateWindow("Pasapalabra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io{ ImGui::GetIO() }; (void)io;
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	Group A{ renderer, windowSize, 1 };
	Group B{ renderer, windowSize, 2 };

	bool isRunning{ true };
	while (isRunning)
	{
		while (SDL_PollEvent(&e))
		{
			ImGui_ImplSDL2_ProcessEvent(&e);

			switch (e.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_WINDOWEVENT:
				SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);
				break;
			}
		}

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		ImGui::Render();
		SDL_SetRenderDrawColor(renderer, 0x10, 0x10, 0x10, 0xFF);
		SDL_RenderClear(renderer);

		A.draw(renderer);
		B.draw(renderer);

		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(renderer);
	}

	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	window = nullptr;
	renderer = nullptr;
	
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

	return 0;
}