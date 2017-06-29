#include <SFML\Graphics.hpp>
#include "Particle.h"
#include "particleSystem.h"
#include <stdio.h>
#include <cstdlib>
#include <windows.h>

sf::Vector2f screenDimensions(900, 900);

int main()
{
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Particle Test");

	sf::Clock clock;

	particleSystem particleSys(sf::Vector2f(screenDimensions.x/2, screenDimensions.y/2), 25000, 200);
	particleSys.initializeFormSpiral(400, 21, screenDimensions.x, screenDimensions.y);
	window.display();

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					particleSys.increaseAcceleration(sf::Vector2f(0, -20));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					particleSys.increaseAcceleration(sf::Vector2f(0, 20));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					particleSys.increaseAcceleration(sf::Vector2f(20, 0));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					particleSys.increaseAcceleration(sf::Vector2f(-20, 0));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					//particleSys.initializeFormSpiral(200, 21, screenDimensions.x, screenDimensions.y);
					particleSys.randomSpeedAndDirection(200,sf::Vector2f(screenDimensions.x/2, screenDimensions.y/2));
				}
			}
		}

		sf::Time timePassed = clock.restart();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
			particleSys.randomSpeedAndDirection(200, mousePos);
		}
		else 
		{
			particleSys.update(timePassed, 20, window);
		}
		window.clear();
		particleSys.draw(window);
		window.display();


	}
}