#include"GameManager.h"
#include<iostream>
#include<conio.h>
using namespace std;
shared_ptr<GameManager>game;
int main()
{
	game = make_shared<GameManager>();
	game->loadGame("test.txt");
	while (1)
	{
		game->update();
		_getch();
	}
	return 0;
}