#pragma once
#include "Log.hpp"
#include "Toolset.hpp"
#include "Constants.h"
#include <string>
#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <memory>
using namespace std;
class Console
{
private:
	string command;
	vector<string> history;
	shared_ptr<Log> logger;
	TTF_Font * font;
	SDL_Rect pos;
	int height;
	string path;
	SDL_Color logColor;
	SDL_Color conColor;
public:
	// 配置参数
	Console(int x, int y, int h, string& AP)
	{
		pos.x = x;
		pos.y = y;
		height = h;
		logger = make_shared<Log>();
		path = AP;
		font = TTF_OpenFont((AP + fontPath).c_str(), 12);
		logColor = { 255, 0, 0 };
		conColor = { 255, 255, 255 };
	}
	// 记录日志
	void add(string log)
	{
		logger->add(log);
	}
	// 打印到屏幕
	void print(SDL_Renderer * r)
	{
		auto message = logger->getLast(18);
		int ny = RenderText(r, message, font, logColor, pos.x, pos.y);
		RenderText(r, "Console:" + command, font, conColor, pos.x, ny);
	}
	void purge()
	{
		logger->add(command);
		command = "";
	}
	// handle keyboard input
	void input(SDL_KeyboardEvent key)
	{
		switch (key.keysym.sym)
		{
		case  SDLK_UNKNOWN:
			command += (char)(0);
		case  SDLK_BACKSPACE:
			command += (char)(8);
		case  SDLK_TAB:
			command += (char)(9);
		case  SDLK_RETURN:
			purge();
		case  SDLK_ESCAPE:
			command += (char)(27);
		case  SDLK_SPACE:
			command += (char)(32);
		case  SDLK_EXCLAIM:
			command += (char)(33);
		case  SDLK_QUOTEDBL:
			command += (char)(34);
		case  SDLK_HASH:
			command += (char)(35);
		case  SDLK_DOLLAR:
			command += (char)(36);
		case  SDLK_PERCENT:
			command += (char)(37);
		case  SDLK_AMPERSAND:
			command += (char)(38);
		case  SDLK_QUOTE:
			command += (char)(39);
		case  SDLK_LEFTPAREN:
			command += (char)(40);
		case  SDLK_RIGHTPAREN:
			command += (char)(41);
		case  SDLK_ASTERISK:
			command += (char)(42);
		case  SDLK_PLUS:
			command += (char)(43);
		case  SDLK_COMMA:
			command += (char)(44);
		case  SDLK_MINUS:
			command += (char)(45);
		case  SDLK_PERIOD:
			command += (char)(46);
		case  SDLK_SLASH:
			command += (char)(47);
		case  SDLK_0:
			command += (char)(48);
		case  SDLK_1:
			command += (char)(49);
		case  SDLK_2:
			command += (char)(50);
		case  SDLK_3:
			command += (char)(51);
		case  SDLK_4:
			command += (char)(52);
		case  SDLK_5:
			command += (char)(53);
		case  SDLK_6:
			command += (char)(54);
		case  SDLK_7:
			command += (char)(55);
		case  SDLK_8:
			command += (char)(56);
		case  SDLK_9:
			command += (char)(57);
		case  SDLK_COLON:
			command += (char)(58);
		case  SDLK_SEMICOLON:
			command += (char)(59);
		case  SDLK_LESS:
			command += (char)(60);
		case  SDLK_EQUALS:
			command += (char)(61);
		case  SDLK_GREATER:
			command += (char)(62);
		case  SDLK_QUESTION:
			command += (char)(63);
		case  SDLK_AT:
			command += (char)(64);
		case  SDLK_LEFTBRACKET:
			command += (char)(91);
		case  SDLK_BACKSLASH:
			command += (char)(92);
		case  SDLK_RIGHTBRACKET:
			command += (char)(93);
		case  SDLK_CARET:
			command += (char)(94);
		case  SDLK_UNDERSCORE:
			command += (char)(95);
		case  SDLK_BACKQUOTE:
			command += (char)(96);
		case  SDLK_a:
			command += (char)(97);
		case  SDLK_b:
			command += (char)(98);
		case  SDLK_c:
			command += (char)(99);
		case  SDLK_d:
			command += (char)(100);
		case  SDLK_e:
			command += (char)(101);
		case  SDLK_f:
			command += (char)(102);
		case  SDLK_g:
			command += (char)(103);
		case  SDLK_h:
			command += (char)(104);
		case  SDLK_i:
			command += (char)(105);
		case  SDLK_j:
			command += (char)(106);
		case  SDLK_k:
			command += (char)(107);
		case  SDLK_l:
			command += (char)(108);
		case  SDLK_m:
			command += (char)(109);
		case  SDLK_n:
			command += (char)(110);
		case  SDLK_o:
			command += (char)(111);
		case  SDLK_p:
			command += (char)(112);
		case  SDLK_q:
			command += (char)(113);
		case  SDLK_r:
			command += (char)(114);
		case  SDLK_s:
			command += (char)(115);
		case  SDLK_t:
			command += (char)(116);
		case  SDLK_u:
			command += (char)(117);
		case  SDLK_v:
			command += (char)(118);
		case  SDLK_w:
			command += (char)(119);
		case  SDLK_x:
			command += (char)(120);
		case  SDLK_y:
			command += (char)(121);
		case  SDLK_z:
			command += (char)(122);
		case  SDLK_DELETE:
			command += (char)(127);
		}
	}
};