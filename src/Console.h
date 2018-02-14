#pragma once
#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
#include "Log.h"
#include "Tool.h"
#include "Constants.h"
#include <string>
#include <vector>
#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <memory>
using namespace std;


class Console
{
private:
	static string command;
	static vector<string> history;
	static shared_ptr<Log> logger;
	//static Log * logger;
	static TTF_Font * font;
	static SDL_Rect pos;
	static int height;
	static string path;
	static SDL_Color logColor;
	static SDL_Color conColor;
public:
	// ���ò���
	static void Init(int x, int y, int h, string& AP);
	// ��¼��־
	static void add(string log);
	
	static vector<string> getLast(int s);
	// ��ӡ����Ļ
	static void print(SDL_Renderer * r);

	static void purge();
	// handle keyboard input
	static void input(SDL_KeyboardEvent key);
};
#endif