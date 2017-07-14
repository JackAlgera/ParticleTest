#pragma once
#include <SFML\Graphics.hpp>
#include "Particle.h"

/*
Class that handles each particle from the particle class.
Has a vector that updates the speed and acceleration of each particle, and a
VertexArray that is used to update each particle's position and to draw it onto the window.
*/
class particleSystem
{
public:
	particleSystem(sf::Vector2f posInitial, int numberOfParticles, int maxSpeed);
	~particleSystem();

	void update(sf::Time timeTraveled, sf::RenderWindow& window);
	void updateWithMouse(sf::Time timeTraveled, int frottement, sf::RenderWindow& window);

	void draw(sf::RenderWindow& window);
	void mouseClick(sf::Vector2i mousePos);
	void increaseAcceleration(sf::Vector2f dAcceleration);

	void initializeFormSpiral(float rayon, int dAngle, int windowWidth, int windowHeight);
	void randomSpeedAndDirection(int maxSpeed, sf::Vector2f initialPosition);

private:
	void updatePosition(int indewx, int windowWidth, int windowHeight, sf::Time timeTraveled);

private:
	sf::VertexArray vertexParticles;
	std::vector<Particle> vectorParticles;
};

