#include "Game.h"

Game::Game()
{
	initVariables();
	initMap();
	initSnakeHead();
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Snake2D", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
	mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

Game::~Game()
{
	delete window;
}

void Game::initVariables()
{
	this->window = nullptr;
	timeBonusResp = 0;
	movementHorizontal = 1;
	movementVertical = 0;

}

void Game::initSnakeHead()
{
	sf::RectangleShape head(sf::Vector2f(23.f, 23.f));
	head.setFillColor(sf::Color::Green);
	head.setPosition(0, 0);
	segments.push_back(head);
	spawnSegment();
}

void Game::initMap()
{
	for (int i = 0; i < 600; i += 25)
	{
		for (int j = 0; j < 800; j += 25)
		{
			sf::RectangleShape mapTile(sf::Vector2f(25.f, 25.f));
			mapTile.setFillColor(sf::Color::White);
			mapTile.setOutlineColor(sf::Color::Black);
			mapTile.setOutlineThickness(2.f);
			mapTile.setPosition(sf::Vector2f(j, i));
			//mapTile.move(sf::Vector2f(j, i));
			mapTiles.push_back(mapTile);
		}
	}
}

bool Game::gameRunning()
{
	return window->isOpen();
}

void Game::mapRender()
{
	for (auto& x : mapTiles)
	{
		this->window->draw(x);
	}
}

void Game::segmentsRender()
{
	for (auto& x : segments)
	{
		window->draw(x);
	}
}

void Game::spawnSegment()
{
	sf::RectangleShape segment(sf::Vector2f(23.f,23.f));
	segment.move(1000, 1000);
	segment.setFillColor(sf::Color::Green);
	segments.push_back(segment);
}

void Game::appleRender()
{
	for (auto& x : apples)
	{
		window->draw(x);
	}
}

void Game::spawnApple()
{
	if (timeBonusResp >= timeBonusRespMax)
	{
		timeBonusResp = 0;

		sf::RectangleShape apple(sf::Vector2f(25.f, 25.f));
		apple.move(sf::Vector2f(rand() % 32 * 25, rand() % 24 * 25));
		apple.setFillColor(sf::Color::Magenta);
		apples.push_back(apple);
	}
	else
	{
		timeBonusResp++;
	}
}

void Game::updateApple()
{
	for (int i = 0; i < apples.size(); i++)
	{
		if (apples[i].getGlobalBounds().intersects(segments[0].getGlobalBounds()))
		{
			spawnSegment();
			apples.erase(apples.begin() + i);
		}
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			this->window->close();
			return;
		}
		if (this->event.type == sf::Event::KeyPressed)
		{
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				return;
			}
		}
		if (this->event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left && movementHorizontal!=1)
			{
				movementVertical = 0;
				movementHorizontal = -1;
			}
			if (event.key.code == sf::Keyboard::Right && movementHorizontal != -1)
			{
				movementVertical = 0;
				movementHorizontal = 1;
			}
			if (event.key.code == sf::Keyboard::Down && movementVertical !=-1)
			{
				movementHorizontal = 0;
				movementVertical = 1;
			}
			if (event.key.code == sf::Keyboard::Up && movementVertical != 1)
			{
				movementHorizontal = 0;
				movementVertical = -1;
			}
		}
	}
}

void Game::render()
{
	window->clear();

	mapRender();
	appleRender();
	segmentsRender();

	window->display();
}

void::Game::updatePosition()
{
	segments[0].move(movementHorizontal*25, movementVertical*25);
	for (int i = segments.size() - 1; i >= 1; i--)
	{
		segments[i].setPosition(segments[i - 1].getPosition());

		if (i != 1)
		{
			if (segments[i].getGlobalBounds().intersects(segments[0].getGlobalBounds()))
			{
				std::cout << "GAME OVER!\n";
				system("pause");
				window->close();
			}
		}

	}
	if (segments[0].getPosition().x < 0 || segments[0].getPosition().x > 800 ||
		segments[0].getPosition().y < 0 || segments[0].getPosition().y > 600)
	{
		std::cout << "GAME OVER!\n";
		system("pause");
		window->close();
	}
}

void Game::update()
{
	if (timer % 15 == 0)
	{
		timer = 1;
		mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		updatePosition();
		updateApple();
		spawnApple();
	}
	else
		timer++;

}

