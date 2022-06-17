#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "Game.h"

int main()
{
	srand(time(nullptr));
	Game game = Game();

	while (game.gameRunning())
	{
		game.pollEvents();

		game.update();

		game.render();
	}
}
