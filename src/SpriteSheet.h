#pragma once
#include <SDL2\SDL.h>
#include <map>

// box.tga
const SDL_Rect
groundClip = { 0, 0, 100, 100 };

std::map<std::string, SDL_Rect> characterClip;

void InitSpriteSheet()
{
	characterClip["Cirno"] = { 146, 72, 72, 72 };
	characterClip["Reimu"] = { 1, 0, 72, 72 };
	characterClip["Sakuya"] = { 430, 72, 72, 72 };
	characterClip["Daiyousei"] = { 72, 75, 72, 72 };
	characterClip["Lily"] = { 218, 145, 72, 72 };
	characterClip["Marisa"] = { 71, 1, 72, 72 };
	characterClip["Sanae"] = { 432, 361, 72, 72 };
	characterClip["Satori"] = { 288, 434, 72, 72 };
	characterClip["Koishi"] = { 504, 433, 72, 72 };
	characterClip["Remilia"] = { 503, 73, 72, 72 };
	characterClip["Flandre"] = { 578, 73, 72, 72 };
	characterClip["Patchouli"] = { 358, 74, 72, 72 };
	characterClip["Koakuma"] = { 290, 73, 72, 72 };
}