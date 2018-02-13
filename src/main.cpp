#include"GameManager.h"
#include<iostream>
#include<conio.h>
#include<SDL2\SDL.h>
#include<SDL2\SDL_ttf.h>
#include<SDL2\SDL_image.h>
#include<vector>
#include"Log.hpp"
#include"Toolset.hpp"
#include"SpriteSheet.h"
#include"Stage.hpp"
#include"Console.hpp"
using namespace std;
const int interval = 1;

int main(int argc, char** argv)
{
	InitSpriteSheet();
	srand(time(0));
	if (SDL_Init(SDL_INIT_EVERYTHING) + TTF_Init())
	{
		cerr << "Failed to init SDL : \n" << SDL_GetError() << "\n" << TTF_GetError();
		return -1;
	}
	SDL_Window * win = SDL_CreateWindow("Flandre Escape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_Renderer * renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	

	string AP = getAbsolutePath(argv[0]);
	Console con(10, 200, 18, AP);

	// cout << (AP + "\\consola.ttf").c_str();
	scene1(AP, renderer);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}