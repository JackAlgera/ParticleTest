#include <SFML\Graphics.hpp>
#include "Particle.h"
#include "particleSystem.h"
#include <stdio.h>
#include <cstdlib>
#include <windows.h>

sf::Vector2f screenDimensions(900, 900);

int main()
{
	printf("This is a program that simulates particles in a void\n\nUse the arrow keys to generate a traction in that particular direction\nUse R to restart the simulation.\nThe left mouse button generates a new explosion of particles.\n\nAuthor : Jacobus ALGERA");

	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Particle Test");	//Generates the window that will be used to display the particles

	sf::Clock clock;

	particleSystem particleSys(sf::Vector2f(screenDimensions.x/2, screenDimensions.y/2), 15000, sf::Color::Green, 100, 0.5);
	particleSys.initializeFormSpiral(400, 21, screenDimensions.x, screenDimensions.y);
	window.display();

	while (window.isOpen())															//Main loop
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))												//Handles the events
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					particleSys.addForce(sf::Vector2f(0, -2000));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					particleSys.addForce(sf::Vector2f(0, 2000));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					particleSys.addForce(sf::Vector2f(2000, 0));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					particleSys.addForce(sf::Vector2f(-2000, 0));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					particleSys.setColor(sf::Color::Green);
					particleSys.initializeFormSpiral(400, 21, screenDimensions.x, screenDimensions.y);
				}
			}
		}

		float dt = clock.restart().asSeconds();										//Used to keep track of the time thats passed during the simulation, which is then used to move each particle in accordance with its speed

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
			particleSys.randomSpeedAndDirection(400, mousePos, sf::Color::Green);
		}
		else 
		{
			particleSys.update(dt, window, sf::Color::White);
		}
		window.clear();
		particleSys.draw(window);
		window.display();


	}
}