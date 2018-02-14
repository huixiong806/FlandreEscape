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
#include <iostream>
#include <iomanip>
#include <map>
#include <cctype>
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
	static map<string, int> flags;
	static map<string, bool> signal;
	// console输入开启状态
	static bool enableConsole;
public:
	// 配置参数
	static void Init(int x, int y, int h, string& AP);
	// 获取状态标记
	static int getFlag(string str);
	// 记录日志
	static void add(string log);
	
	static vector<string> getLast(int s);
	// 打印到屏幕
	static void print(SDL_Renderer * r);

	static void purge();
	// handle keyboard input
	static void input(SDL_KeyboardEvent key);
	// check signal
	static bool checkSignal(string str);
};
#endif