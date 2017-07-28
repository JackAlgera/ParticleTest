#pragma once
#include <SFML\Graphics.hpp>

/*
Class that handles each particle
Each particle has its own speed and acceleration.
*/

class Particle
{
public:
	Particle(float mass, float coefOfFric);
	~Particle();

	void update(float dt);
	
	void randomIni(int maxSpeed, sf::Vector2f screenDimensions);
	void addForce(sf::Vector2f dForce) { force += dForce; }

public:
	sf::Vector2f acceleration;
	sf::Vector2f velocity;										
	sf::Vector2f position;

	float mass;
	sf::Vector2f force = sf::Vector2f(0, 7000);
	float coefOfFric;
};

