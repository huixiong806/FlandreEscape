#pragma once
#include <SDL2\SDL.h>
#include <map>

// box.tga
const SDL_Rect
groundClip = { 0, 0, 100, 100 };

std::map<std::string, SDL_Rect> maidClip;

void InitSpriteSheet()
{
	maidClip["Cirno"] = { 146, 72, 72, 72 };
	maidClip["Reimu"] = { 1, 0, 72, 72 };
	maidClip["Sakuya"] = { 430, 72, 72, 72 };
	maidClip["Daiyousei"] = { 72, 75, 72, 72 };
	maidClip["Lily"] = { 218, 145, 72, 72 };
	maidClip["Marisa"] = { 71, 1, 72, 72 };
	maidClip["Sanae"] = { 432, 361, 72, 72 };
	maidClip["Satori"] = { 288, 434, 72, 72 };
	maidClip["Koishi"] = { 504, 433, 72, 72 };
	maidClip["Remilia"] = { 503, 73, 72, 72 };
	maidClip["Patchouli"] = { 358, 74, 72, 72 };
	maidClip["Koakuma"] = { 290, 73, 72, 72 };
}