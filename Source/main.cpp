#include "init.hpp"
#include <string>
#include <cstdint>

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING ^ SDL_INIT_GAMECONTROLLER) != 0) // Initializing SDL's VIDEO submodule
	{
		logSDLError("Failed to initialize SDL");
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello, world!", 100, 100, 640, 480, SDL_WINDOW_SHOWN); // Creating an SDL window
	if(win == nullptr)
	{
		logSDLError("Failed to create an SDL window");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Creating an SDL renderer.
	if(ren == nullptr)
	{
		logSDLError("Failed to create an SDL renderer");
		SDL_Quit();
		return 1;
	}

	SDL_Texture *tex = loadTexture("Res/hello.bmp", ren);
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				if(e.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				quit = true;
			}
		}
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(tex); //
	SDL_DestroyRenderer(ren);// Cleanup
	SDL_DestroyWindow(win);  //
	SDL_Quit();
	return 0;
}
