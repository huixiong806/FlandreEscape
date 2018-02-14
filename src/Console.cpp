#include "Console.h"
#include <SDL2\SDL.h>
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
map<string, int> Console::flags;
map<string, bool> Console::signal;
bool Console::enableConsole;
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
	flags["maidStatus"] = 0;
	enableConsole = true;
}
int Console::getFlag(string str)
{
	bool f = flags[str];
	return f;
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
	if (enableConsole)
		message.push_back("Command:" + command);
	else
		message.push_back("Console disabled");
	RenderText(r, message, font, logColor, pos.x, pos.y);
	//RenderText(r, "Console:" + command, font, logColor, pos.x, ny);
}
void Console::purge()
{
	logger->add(command);
	if (command.find("toggle maid status display") != string::npos)
		flags["maidStatus"] = !flags["maidStatus"];
	else if (command.find("signal") != string::npos)
	{
		string test = command.substr(7, command.size() - 7);
		string signalStatus = signal[test] ? " ON" : " OFF";
		add("signal " + command.substr(7) + signalStatus);
	}
	command = "";
}
void Console::input(SDL_KeyboardEvent key)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_GRAVE])
	{
		enableConsole = !enableConsole;
	}
	else
	{
		if (enableConsole && key.keysym.sym >= 32 && key.keysym.sym <= 255)
		{
			if(isgraph(key.keysym.sym) && !isupper(key.keysym.sym) || isspace(key.keysym.sym))
			{
			
				if (key.keysym.mod == 0x1000)
					command += key.keysym.sym;
				else if (~key.keysym.mod & KMOD_CAPS)
					command += isalpha(key.keysym.sym) && (~key.keysym.sym & KMOD_SHIFT) ? toupper(key.keysym.sym) : key.keysym.sym;
				else if (key.keysym.sym & KMOD_SHIFT)
					command += isalpha(key.keysym.sym) ? toupper(key.keysym.sym) : key.keysym.sym;
				// std::cout << command << "\n";
			}
		}
		if(enableConsole && key.keysym.sym == SDLK_RETURN)
		{
			purge();
			// std::cout << command << "\n";
		}
		if (!enableConsole && (key.keysym.sym == SDLK_DOWN || key.keysym.sym == SDLK_UP || key.keysym.sym == SDLK_LEFT || key.keysym.sym == SDLK_RIGHT || key.keysym.sym == SDLK_c))
		{
			cout << "event! " << (key.keysym.sym == SDLK_c) << "\n";
			switch (key.keysym.sym)
			{
			case SDLK_DOWN:
				signal["flanMoveDown"] = true;
			case SDLK_UP:
				signal["flanMoveUp"] = true;
			case SDLK_LEFT:
				signal["flanMoveLeft"] = true;
			case SDLK_RIGHT:
				signal["flanMoveRight"] = true;
			case SDLK_c:
				signal["flanAttack"] = true;
			}
		}
	}
	
		
}

bool Console::checkSignal(string str)
{
	return signal[str] ? signal[str] = false, true : false;
}
