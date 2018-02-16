#include"GameManager.h"
#include<iostream>
#include<conio.h>
#include<SDL2\SDL.h>
#include<SDL2\SDL_ttf.h>
#include<SDL2\SDL_image.h>
#include<vector>
#include"Tool.h"
#include"SpriteSheet.h"
#include"Console.h"
using namespace std;
const int interval = 1;
shared_ptr<GameManager>game;
int main(int argc, char** argv)
{
	InitSpriteSheet();
	srand(time(0));
	if (SDL_Init(SDL_INIT_EVERYTHING) + TTF_Init())
	{
		cerr << "Failed to init SDL : \n" << SDL_GetError() << "\n" << TTF_GetError();
		return -1;
	}
	atexit(SDL_Quit);
	SDL_Window * win = SDL_CreateWindow("Flandre Escape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_Renderer * renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	game = make_shared<GameManager>();
	game->loadGame("test.txt");

	string AP = getAbsolutePath(argv[0]);

	// cout << (AP + "\\consola.ttf").c_str();
	
	// perpare resources
	TTF_Font * font = TTF_OpenFont((AP + "\\consola.ttf").c_str(), 12);
	SDL_Color textColor = { 255 , 0 , 0 };
	SDL_Rect  groundDesPos;
	SDL_Texture * ground = IMG_LoadTexture(renderer, (AP + "\\box.tga").c_str()),
		* oscar = IMG_LoadTexture(renderer, (AP + "\\oscar.png").c_str()),
		* maidTex = IMG_LoadTexture(renderer, (AP + "\\th.png").c_str());
	SDL_Rect oscarLocation = { 500, 300, 0, 0 };
	//SDL_QueryTexture(oscar, NULL, NULL, &oscarLocation.w, &oscarLocation.h);

	Console::Init(10, 200, 18, AP);
	
	/// Main event loop
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		//Console::resetAllSignal();
		while (SDL_PollEvent(&e))
		{
			//cout << hex << e.key.keysym.mod << "\n";
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				Console::input(e.key, SDL_KEYDOWN);
				break;
			case SDL_KEYUP:
				Console::input(e.key, SDL_KEYUP);
				break;
			default:
				break;
			}
		}
		
		game->update();

		SDL_RenderClear(renderer);
		//game->update();
		// draw map
		int gSize = girdSize;
		auto map = game->getMap();
		int c = map->getSizeC(), r = map->getSizeR();
		groundDesPos = { 0, 0, gSize, gSize };
		for (int rr = 0; groundDesPos.y < c * gSize; groundDesPos.y += gSize, ++rr)
		{
			groundDesPos.x = 0;
			for (int cc = 0; groundDesPos.x < r * gSize; groundDesPos.x += gSize, ++cc)
				if (map->getVertex(map->getPos(rr,cc)).getEnable())
					RenderImage(renderer, ground, groundDesPos, groundClip);
		}
		// draw maids
		auto maids = game->getMaidSet();
		for (auto maid : *maids)
		{
			//int x = maid->getPos() / c * gSize, y = maid->getPos() % c * gSize;
			SDL_Rect maidPos = { maid->getCoord().y- girdSize*0.5,maid->getCoord().x- girdSize*0.5, gSize, gSize };
			RenderImage(renderer, maidTex, maidPos, characterClip[maid->getName()]);
		}
		//draw flan
		auto flan = game->getFlan();
		SDL_Rect flanPos = { flan->getCoord().y - girdSize * 0.5,flan->getCoord().x - girdSize * 0.5, gSize, gSize };
		RenderImage(renderer, maidTex, flanPos, characterClip[flan->getName()]);
		// log 
		Console::print(renderer);
		cout << Console::checkSignal("flanMoveUp") << endl;
		//oscar
		SDL_RenderCopy(renderer, oscar, NULL, &oscarLocation);

		SDL_RenderPresent(renderer);
	}
	//scene1(AP, renderer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}