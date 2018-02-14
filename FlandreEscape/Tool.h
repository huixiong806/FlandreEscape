#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <vector>
#include <string>
// »æÖÆÒ»¶ÎÎÄ×Ö
int RenderText(SDL_Renderer *, std::vector<std::string>, TTF_Font *,
	SDL_Color, int, int);

int RenderText(SDL_Renderer *, std::string, TTF_Font *,
	SDL_Color, int, int);

void RenderImage(SDL_Renderer *, SDL_Texture *, SDL_Rect, SDL_Rect);

std::string getAbsolutePath(char*);