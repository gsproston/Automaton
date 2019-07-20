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

	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Time elapsedTime = clock.restart();

	while (window.isOpen())
	{
		static float fOffsetX = -(WORLD_WIDTH * TILE_SIZE / 2.f);
		static float fOffsetY = -(WORLD_HEIGHT * TILE_SIZE / 2.f);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			fOffsetX++;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			fOffsetX--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			fOffsetY++;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			fOffsetY--;

		window.clear();

		std::vector<sf::Vertex> vTriangleVertices;
		std::vector<sf::Vertex> vQuadVertices;
		map.addVertices(vTriangleVertices, vQuadVertices);

		for (size_t i = 0; i < vTriangleVertices.size(); ++i)
		{
			vTriangleVertices[i].position += sf::Vector2f(fOffsetX, fOffsetY);
		}
		for (size_t i = 0; i < vQuadVertices.size(); ++i)
		{
			vQuadVertices[i].position += sf::Vector2f(fOffsetX, fOffsetY);
		}

		// draw all quads
		window.draw(vQuadVertices.data(), vQuadVertices.size(), sf::PrimitiveType::Quads, states);
		// draw all triangles
		window.draw(vTriangleVertices.data(), vTriangleVertices.size(), sf::PrimitiveType::Triangles);

		window.display();

		elapsedTime = clock.restart();
		map.tick(elapsedTime);
	}

	return 0;
}