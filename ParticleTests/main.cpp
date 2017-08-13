#include <SFML\Graphics.hpp>
#include "Particle.h"
#include "particleSystem.h"
#include <stdio.h>
#include <cstdlib>
#include <windows.h>

sf::Vector2f screenDimensions(1000, 900);
float const nbrParticlesPerThread = 4000;
bool reboundOnEdges = true;

sf::Color randomColor(int val);

std::vector<particleSystem> particleThreads;

int main()
{
	printf("This is a program that simulates particles in a void\n\nUse the arrow keys to generate a force in that particular direction\nUse A and Z to restart the simulation with different starting positions, use R to remove everything.\nThe left mouse button generates a new explosion of particles.\n\nAuthor : Jacobus ALGERA");

	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Particle Test");	//Generates the window that will be used to display the particles

	sf::Clock clock;

	particleSystem particleSys(sf::Vector2f(screenDimensions.x * 3 / 4, screenDimensions.y / 2), nbrParticlesPerThread, sf::Color::Green, 100, 0.5, reboundOnEdges);
	particleSys.initializeFormSpiral(screenDimensions.x*0.2, 21);

	particleThreads.push_back(particleSys);

	particleSys = particleSystem(sf::Vector2f(screenDimensions.x / 4, screenDimensions.y / 2), nbrParticlesPerThread, sf::Color::Red, 100, 0.5, reboundOnEdges);
	particleSys.initializeFormSpiral(screenDimensions.x*0.2, 21);

	particleThreads.push_back(particleSys);

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
					for (int i = 0; i < particleThreads.size(); i++)
					{
						particleThreads[i].addForce(sf::Vector2f(0, -2000));
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					for (int i = 0; i < particleThreads.size(); i++)
					{
						particleThreads[i].addForce(sf::Vector2f(0, 2000));
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					for (int i = 0; i < particleThreads.size(); i++)
					{
						particleThreads[i].addForce(sf::Vector2f(2000, 0));
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					for (int i = 0; i < particleThreads.size(); i++)
					{
						particleThreads[i].addForce(sf::Vector2f(-2000, 0));
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					particleThreads.clear();

					particleSystem particleSys(sf::Vector2f(screenDimensions.x / 2, screenDimensions.y / 2), nbrParticlesPerThread*2, sf::Color::Blue, 100, 0.5, reboundOnEdges);
					particleSys.initializeFormSpiral(screenDimensions.x*0.4, 21);

					particleThreads.push_back(particleSys);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					particleThreads.clear();

					particleSystem particleSys(sf::Vector2f(screenDimensions.x * 3 / 4, screenDimensions.y / 2), nbrParticlesPerThread, sf::Color::Green, 100, 0.5, reboundOnEdges);
					particleSys.initializeFormSpiral(screenDimensions.x*0.2, 21);

					particleThreads.push_back(particleSys);

					particleSys = particleSystem(sf::Vector2f(screenDimensions.x / 4, screenDimensions.y / 2), nbrParticlesPerThread, sf::Color::Red, 100, 0.5, reboundOnEdges);
					particleSys.initializeFormSpiral(screenDimensions.x*0.2, 21);

					particleThreads.push_back(particleSys);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					particleThreads.clear();
				}
			}
			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
					particleSys = particleSystem(mousePos, nbrParticlesPerThread, sf::Color::Red, 100, 0.5, reboundOnEdges);
					particleSys.randomSpeedAndDirection(200, mousePos, randomColor(particleThreads.size() % 3));
					particleThreads.push_back(particleSys);
				}
			}
		}

		float dt = clock.restart().asSeconds();										//Used to keep track of the time thats passed during the simulation, which is then used to move each particle in accordance with its speed

		window.clear();
		if (particleThreads.size() >= 7)
		{
			particleThreads.erase(particleThreads.begin() + 0, particleThreads.begin() + 3);
		}
		for (int i = 0; i < particleThreads.size(); i++)
		{
			particleThreads[i].update(dt, window, sf::Color::White);
			particleThreads[i].draw(window);
		}
		window.display();


	}
}

sf::Color randomColor(int val)
{
	//int val = rand() % 3;
	if (val == 0)
	{
		return sf::Color::Red;
	}
	if (val == 1)
	{
		return sf::Color::Green;
	}
	else
	{
		return sf::Color::Blue;
	}
}