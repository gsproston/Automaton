// SFML_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>

#include "Map.h"

#define TILE_SIZE 32

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Automaton");
	Map map;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		map.draw(window);
		window.display();
	}

	return 0;
}