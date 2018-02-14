#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
#include "Log.hpp"
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
	// 配置参数
	static void Init(int x, int y, int h, string& AP)
	{
		pos.x = x;
		pos.y = y;
		height = h;
		logger = make_shared<Log>();
		//logger = new Log;
		path = AP;
		font = TTF_OpenFont((AP + "\\consola.ttf").c_str(), 12);
		logColor = { 255, 0, 0 };
		conColor = { 255, 255, 255 };
	}
	// 记录日志
	static void add(string log)
	{
		logger->add(log);
	}
	
	static vector<string> getLast(int s = 18)
	{
		//extern shared_ptr<Log> logger;
		
		vector<string> ret = logger.get()->getLast(s);
		return ret;
	}
	// 打印到屏幕
	static void print(SDL_Renderer * r)
	{
		auto message = logger->getLast(18);
		int ny = RenderText(r, message, font, logColor, pos.x, pos.y);
		RenderText(r, "Console:" + command, font, conColor, pos.x, ny);
	}
	static void purge()
	{
		logger->add(command);
		command = "";
	}
	// handle keyboard input
	static void input(SDL_KeyboardEvent key)
	{
		if (key.keysym.sym != '\n')
			command += key.keysym.sym;
		else
			purge();
	}
};
shared_ptr<Log> Console::logger;
#endif