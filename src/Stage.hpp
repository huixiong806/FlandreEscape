#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_image.h>
#include "Console.hpp"
void scene1(string AP, SDL_Renderer * renderer)
{
	shared_ptr<GameManager>game;
	game = make_shared<GameManager>();
	game->loadGame("test.txt");

	// perpare resources
	TTF_Font * font = TTF_OpenFont((AP + "\\consola.ttf").c_str(), 12);
	SDL_Color textColor = { 255 , 0 , 0 };
	SDL_Rect  groundDesPos;
	SDL_Texture * ground = IMG_LoadTexture(renderer, (AP + "\\box.tga").c_str()),
		*oscar = IMG_LoadTexture(renderer, (AP + "\\oscar.png").c_str()),
		*maidTex = IMG_LoadTexture(renderer, (AP + "\\th.png").c_str());
	SDL_Rect oscarLocation = { 500, 300, 0, 0 };
	//SDL_QueryTexture(oscar, NULL, NULL, &oscarLocation.w, &oscarLocation.h);


	/// Main event loop
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		if (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_RETURN:
					;
				}
			}
		}

		game->update();

		SDL_RenderClear(renderer);
		//game->update();
		// draw map
		int gSize = girdSize;
		auto map = game->getMapPtr();
		int c = map->getSizeC(), r = map->getSizeR();
		groundDesPos = { 0, 0, gSize, gSize };
		for (; groundDesPos.y < c * gSize; groundDesPos.y += gSize)
			for (groundDesPos.x = 0; groundDesPos.x < r * gSize; groundDesPos.x += gSize)
				//RenderImage(renderer, ground, groundDesPos, groundClip);
				SDL_RenderCopy(renderer, ground, &groundClip, &groundDesPos);
		// draw maids
		auto maids = game->getMaidSetPtr();
		for (auto maid : *maids)
		{
			//int x = maid->getPos() / c * gSize, y = maid->getPos() % c * gSize;
			SDL_Rect maidPos = { maid->getCoord().y - girdSize * 0.5,maid->getCoord().x - girdSize * 0.5, gSize, gSize };
			SDL_RenderCopy(renderer, maidTex, &characterClip[maid->getName()], &maidPos);
		}

		// log 
		Console::print(renderer);

		//oscar
		SDL_RenderCopy(renderer, oscar, NULL, &oscarLocation);

		SDL_RenderPresent(renderer);
	}
}