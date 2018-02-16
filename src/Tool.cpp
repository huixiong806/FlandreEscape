#include "Tool.h"

int RenderText(SDL_Renderer * r, std::vector<std::string> message, TTF_Font * font,
	SDL_Color textColor, int x = 10, int y = 10)
{
	static int interval = 1;
	SDL_Surface * maidStateDisplay;
	SDL_Texture * text;
	SDL_Rect pos = { x, y, 0, 0 };
	for (auto i : message)
	{
		i == "" ? i = " " : i;
		maidStateDisplay = TTF_RenderText_Blended(font, i.c_str(), textColor);
		text = SDL_CreateTextureFromSurface(r, maidStateDisplay);
		SDL_QueryTexture(text, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(r, text, NULL, &pos);
		pos.y += interval + pos.h;
		SDL_FreeSurface(maidStateDisplay);
		SDL_DestroyTexture(text);
	}
	return pos.y;
}

int RenderText(SDL_Renderer * r, std::string message, TTF_Font * font,
	SDL_Color textColor, int x = 10, int y = 10)
{
	static int interval = 1;
	SDL_Surface * maidStateDisplay;
	SDL_Texture * text;
	SDL_Rect pos = { x, y, 200, 300 };
	{
		maidStateDisplay = TTF_RenderText_Blended(font, message.c_str(), textColor);
		text = SDL_CreateTextureFromSurface(r, maidStateDisplay);
		SDL_QueryTexture(text, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(r, text, NULL, &pos);
		pos.y += interval + pos.h;
		SDL_FreeSurface(maidStateDisplay);
		SDL_DestroyTexture(text);
	}
	return pos.y;
}

void RenderImage(SDL_Renderer * r, SDL_Texture * tex, SDL_Rect pos, SDL_Rect clip)
{   // δ�����ܸ���SDL_RendererCopyEX���ȷ�װһ����˵
	SDL_RenderCopy(r, tex, &clip, &pos);
}

std::string getAbsolutePath(char* argv)
{
	std::string str(argv);
	str = str.substr(0, str.find_last_of("FlandreEscape.exe") - sizeof("FlandreEscape.exe") + 1);
	return str;
}