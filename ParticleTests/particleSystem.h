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
	particleSystem(sf::Vector2f posInitial, int numberOfParticles, sf::Color color, float mass, float coefOfFric);
	~particleSystem();

	void update(float dt, sf::RenderWindow& window, sf::Color color);

	void draw(sf::RenderWindow& window);
	void mouseClick(sf::Vector2i mousePos);
	void addForce(sf::Vector2f dForce);

	void initializeFormSpiral(float rayon, int dAngle, int windowWidth, int windowHeight);
	void randomSpeedAndDirection(int maxSpeed, sf::Vector2f initialPosition, sf::Color color);
	void setColor(sf::Color color);

private:
	void updateVelocity(int indewx, int windowWidth, int windowHeight, float dt, sf::Color color);

private:
	sf::VertexArray vertexParticles;
	std::vector<Particle> vectorParticles;
};

