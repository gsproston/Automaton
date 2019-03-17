// SFML_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Map.h"

int main()
{
	Map map;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Automaton");

	sf::Texture texture;
	texture.loadFromFile("images/tileMap.png");
	sf::RenderStates states;
	states.texture = &texture;
	std::vector<sf::Vertex> vVertices;

	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Time elapsedTime = clock.restart();
	//map.tick(elapsedTime);
	//elapsedTime = clock.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// draw all quads
		map.addQuadVertices(vVertices);
		window.draw(vVertices.data(), vVertices.size(), sf::PrimitiveType::Quads, states);
		vVertices.clear();

		// draw all triangles
		map.addTriangleVertices(vVertices);
		window.draw(vVertices.data(), vVertices.size(), sf::PrimitiveType::Triangles);
		vVertices.clear();

		window.display();

		elapsedTime = clock.restart();
		map.tick(elapsedTime);
	}

	return 0;
}