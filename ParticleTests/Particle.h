#pragma once
#include <SFML\Graphics.hpp>

class Particle
{
public:
	Particle(int speedMax);
	~Particle();

	sf::Vector2f getVelocity() { return velocity; }
	float getVelocityX() { return velocity.x; }
	float getVelocityY() { return velocity.y; }

	void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
	void setVelocityX(float velocityX) { velocity.x = velocityX; }
	void setVelocityY(float velocityY) { velocity.y = velocityY; }

	void addVelocity(sf::Time timeTraveled) { velocity += acceleration*timeTraveled.asSeconds(); }

	void setAcceleration(sf::Vector2f newAcceleration) { acceleration = newAcceleration; }
	void addAcceleration(sf::Vector2f dAcceleration) { acceleration += dAcceleration; }

private:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};

