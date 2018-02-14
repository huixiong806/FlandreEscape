#include "Console.h"
string Console::command;
vector<string> Console::history;
shared_ptr<Log> Console::logger;
//static Log * logger;
TTF_Font * Console::font;
SDL_Rect Console::pos;
int Console::height;
string Console::path;
SDL_Color Console::logColor;
SDL_Color Console::conColor;
void Console::Init(int x, int y, int h, string& AP)
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
void Console::add(string log)
{
	logger->add(log);
}
vector<string> Console::getLast(int s = 18)
{
	//extern shared_ptr<Log> logger;

	vector<string> ret = logger.get()->getLast(s);
	return ret;
}
void Console::print(SDL_Renderer * r)
{
	auto message = logger->getLast(18);
	int ny = RenderText(r, message, font, logColor, pos.x, pos.y);
	RenderText(r, "Console:" + command, font, conColor, pos.x, ny);
}
void Console::purge()
{
	logger->add(command);
	command = "";
}
void Console::input(SDL_KeyboardEvent key)
{
	if (key.keysym.sym != '\n')
		command += key.keysym.sym;
	else
		purge();
}