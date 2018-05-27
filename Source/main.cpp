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

	SDL_Window *win = SDL_CreateWindow("Hello, world!", 0, 0, 640, 480, SDL_WINDOW_SHOWN); // Creating an SDL window
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

	SDL_DisplayMode cur;

	SDL_Texture *tex = loadTexture("Res/hello.bmp", ren);
	bool quit = false;
	SDL_Event e;
	int x = 0;
	int y = 0;
	while(!quit){
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
				case SDLK_q:
					SDL_CaptureMouse(SDL_FALSE);
					SDL_SetRelativeMouseMode(SDL_FALSE);
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_f:
					SDL_GetCurrentDisplayMode(0, &cur);
					SDL_SetWindowSize(win, cur.w, cur.h);
					SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
					break;
				default:
					printf("No function for key %c\n", e.key.keysym.sym);
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_CaptureMouse(SDL_TRUE);
				SDL_SetRelativeMouseMode(SDL_TRUE);
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				if(e.motion.xrel > x)
				{
					x = e.motion.xrel;
					printf("x: %i y: %i\n", x, y);
				}

				if(e.motion.yrel > y)
				{
					y = e.motion.yrel;
					printf("x: %i y: %i\n", x, y);
				}

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
