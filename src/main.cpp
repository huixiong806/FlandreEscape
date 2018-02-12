#include"GameManager.h"
#include<iostream>
#include<conio.h>
#include<SDL2\SDL.h>
#include<SDL2\SDL_ttf.h>
#include<vector>
#include"Log.hpp"
#include"Toolset.hpp"
using namespace std;
const int interval = 1;
shared_ptr<GameManager>game;
int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) + TTF_Init())
	{
		cerr << "Failed to init SDL : \n" << SDL_GetError() << "\n" << TTF_GetError();
		return -1;
	}
	SDL_Window * win = SDL_CreateWindow("Flandre Escape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_Renderer * renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	game = make_shared<GameManager>();
	game->loadGame("test.txt");

	string AP = getAbsolutePath(argv[0]);

	// cout << (AP + "\\consola.ttf").c_str();
	
	TTF_Font * font = TTF_OpenFont((AP + "\\consola.ttf").c_str(), 12);
	SDL_Color textColor = { 255 , 255 , 255 };
	SDL_Rect pos = { 10, 100, 200, 20 };

	/// Main event loop
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_RETURN:
					game->update();
				}
			}
		}
		auto message = game->getLog().getLast(15);
		pos.y = 100;
		SDL_RenderClear(renderer);
		RenderText(renderer, message, font, textColor);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}