#include"GameManager.h"
#include<iostream>
#include<conio.h>
#include<SDL2\SDL.h>
#include<SDL2\SDL_ttf.h>
#include<SDL2\SDL_image.h>
#include<vector>
#include"Log.hpp"
#include"Toolset.hpp"
using namespace std;
const int interval = 1;
shared_ptr<GameManager>game;
int main(int argc, char** argv)
{
	srand(time(0));
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
	
	// perpare resources
	TTF_Font * font = TTF_OpenFont((AP + "\\consola.ttf").c_str(), 12);
	SDL_Color textColor = { 255 , 0 , 0 };
	SDL_Rect groundClip = { 0, 0, 100, 100 }, groundDesPos, maidClip = { 179, 302, 50, 50 };
	SDL_Texture * ground = IMG_LoadTexture(renderer, (AP + "\\box.bmp").c_str());


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
		SDL_RenderClear(renderer);
		//game->update();
		
		
		// draw map
		int gSize = 50;
		auto map = game->getMapPtr();
		int c = map->getSizeC(), r = map->getSizeR();
		groundDesPos = { 0, 0, gSize, gSize };
		for (; groundDesPos.y < c * gSize; groundDesPos.y += gSize)
			for (groundDesPos.x = 0; groundDesPos.x < r * gSize; groundDesPos.x += gSize)
				RenderImage(renderer, ground, groundDesPos, groundClip);
		// draw maids
		auto maids = game->getMaidSetPtr();
		for (auto maid : *maids)
		{
			int x = maid->getPos() / c * gSize, y = maid->getPos() % c * gSize;
			SDL_Rect maidPos = {y,x, gSize, gSize };
			RenderImage(renderer, ground, maidPos, maidClip);
		}

		// log 
		auto message = game->getLog()->getLast(15);
		RenderText(renderer, message, font, textColor, 10, 200);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}