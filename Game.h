#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <ctime>

class Game
{
private:
	sf::Event event;
	sf::RenderWindow* window;
	sf::Vector2f mouse;

	int points = 0;
	int timer = 1;

	float timeBonusResp;
	const float timeBonusRespMax=10.f;
	int movementHorizontal = 1;
	int movementVertical = 1;



	std::vector<sf::RectangleShape> segments;
	std::vector<sf::RectangleShape> mapTiles;
	std::vector<sf::RectangleShape> apples;
public:
	Game();
	~Game();

	void initVariables();
	void initSnakeHead();
	void initMap();

	bool gameRunning();
	void pollEvents();


	void render();
	void mapRender();
	void segmentsRender();
	void appleRender();



	void spawnSegment();
	void spawnApple();


	void updateApple();
	void update();
	void updatePosition();
};

