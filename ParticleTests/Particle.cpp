#include "Particle.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>

Particle::Particle(float mass, float coefOfFric)
{
	position = sf::Vector2f(0,0);
	velocity = sf::Vector2f(0,0);
	this->mass = rand()%(int)mass + mass*0.4;
	acceleration = sf::Vector2f(0, force.y*mass);
	this->coefOfFric = coefOfFric;
}

Particle::~Particle()
{
}

void Particle::update(float dt)
{
	acceleration = sf::Vector2f((force.x - coefOfFric*velocity.x) / mass, (force.y - coefOfFric*velocity.y)/mass);
	velocity += acceleration*dt;
	position += velocity*dt;
}

void Particle::randomIni(int maxSpeed, sf::Vector2f screenDimensions)
{
	if(!((screenDimensions.x == 0) && (screenDimensions.y == 0)))
		position = sf::Vector2f(rand() % (int)screenDimensions.x, rand() % (int)screenDimensions.y);

	float speed = rand() % maxSpeed + 10;
	float angle = (rand() % 360) * (3.1416 / 180);
	velocity = sf::Vector2f(std::cos(angle)*speed, std::sin(angle)*speed);
}

