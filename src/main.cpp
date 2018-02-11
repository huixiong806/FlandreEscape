#include"GameManager.h"
#include<iostream>
#include<conio.h>
#include<SDL.h>
#include<SDL_ttf.h>
#include<vector>
using namespace std;
const int interval = 14;
shared_ptr<GameManager>game;
int main(int argc, char ** argv)
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
	
	TTF_Font * font = TTF_OpenFont("C:\\Users\\axunl\\source\\repos\\FlandreEscape\\consola.ttf", 20);
	SDL_Texture * text;
	SDL_Surface * maidStateDisplay;
	SDL_Color textColor = { 255, 0, 0 };
	SDL_Rect pos = { 10, 100, 200, 20 }, clip;

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
		auto message = game->getInfo();
		pos.y = 100;
		SDL_RenderClear(renderer);
		for (auto i : message)
		{
			maidStateDisplay = TTF_RenderText_Blended(font, i.c_str(), textColor);
			text = SDL_CreateTextureFromSurface(renderer, maidStateDisplay);
			SDL_QueryTexture(text, NULL, NULL, &pos.w, &pos.h);
			SDL_RenderCopy(renderer, text, NULL, &pos);
			pos.y += interval;
			SDL_FreeSurface(maidStateDisplay);
			SDL_DestroyTexture(text);
		}
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}