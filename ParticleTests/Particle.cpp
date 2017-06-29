#include "Particle.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>

Particle::Particle(int speedMax)
{
	float speed = rand() % speedMax + 10;
	float angle = (rand() % 360) * (3.1416 / 180);
	velocity = sf::Vector2f(std::cos(angle)*speed, std::sin(angle)*speed);
	acceleration = sf::Vector2f(0, 0);
}

Particle::~Particle()
{
}

