#include "particleSystem.h"



particleSystem::particleSystem(sf::Vector2f posInitial, int numberOfParticles, int maxSpeed)		
{
	vertexParticles = sf::VertexArray(sf::Points, numberOfParticles);
	for (int i = 0; i < numberOfParticles; i++)
	{
		vectorParticles.push_back(Particle(maxSpeed));
		vertexParticles[i].position = posInitial;
		vertexParticles[i].color = sf::Color::Yellow;
	}
}

particleSystem::~particleSystem()
{
}

void particleSystem::update(sf::Time timeTraveled, sf::RenderWindow& window)	//Updates each particle's position
{
	int windowWidth = window.getSize().x;
	int windowHeight = window.getSize().y;
	for (int i = 0; i < vectorParticles.size(); i++)
	{
		updatePosition(i, windowWidth, windowHeight, timeTraveled);
		vertexParticles[i].position += vectorParticles[i].getVelocity()*timeTraveled.asSeconds();
	}
}

void particleSystem::draw(sf::RenderWindow & window)
{
	window.draw(vertexParticles);
}

void particleSystem::increaseAcceleration(sf::Vector2f dAcceleration)	//Increase the acceleration of each particle in a given direction
{
	for (int i = 0; i < vectorParticles.size(); i++)
	{
		vectorParticles[i].addAcceleration(dAcceleration);
	}
}

void particleSystem::initializeFormSpiral(float rayon, int dAngle, int windowWidth, int windowHeight)	//Initialized the particle system with a spiral
{
	float angle = 0;
	float dr = rayon / ((float)vectorParticles.size());
	float r = 0;

	for (int i = 0; i < vectorParticles.size(); i++)													//gives each particle a position on the spiral
	{
		vectorParticles[i].setAcceleration(sf::Vector2f(0, 0));
		vertexParticles[i].position = sf::Vector2f(windowWidth/2 + cos(angle)*r, windowHeight/2 + sin(angle)*r);
		vertexParticles[i].color = sf::Color::Yellow;
		vectorParticles[i].setVelocity(sf::Vector2f(0, 0));
		r += dr;
		angle += dAngle*(3.1416/180);
	}

}

void particleSystem::randomSpeedAndDirection(int maxSpeed, sf::Vector2f initialPosition)
{
	for (int i = 0; i < vectorParticles.size(); i++)
	{
		vertexParticles[i].position = initialPosition;
		vertexParticles[i].color = sf::Color::Yellow;
		vectorParticles[i] = Particle(maxSpeed);
	}
}

void particleSystem::updatePosition(int index, int windowWidth, int windowHeight, sf::Time timeTraveled)	//Updates the position of each particle, and makes then "bounce" of the edges.
{
	vectorParticles[index].addVelocity(timeTraveled);
	float Xparticle = vertexParticles[index].position.x;
	float Yparticle = vertexParticles[index].position.y;

	if ((Xparticle > 0) && (Xparticle < windowWidth))
	{
		if ((Yparticle <= 0) | (Yparticle >= windowHeight))
		{
			Particle actualParticle = vectorParticles[index];
			vectorParticles[index].setVelocityY(-actualParticle.getVelocityY());
			vertexParticles[index].color = sf::Color::White;
		}
	}

	if ((Yparticle > 0) && (Yparticle < windowHeight))
	{
		if ((Xparticle <= 0) | (Xparticle >= windowWidth))
		{
			Particle actualParticle = vectorParticles[index];
			vectorParticles[index].setVelocityX(-actualParticle.getVelocityX());
			vertexParticles[index].color = sf::Color::White;
		}
	}
	else if ((Xparticle <= 0 && Yparticle <= 0) | (Xparticle <= 0 && Yparticle >= windowHeight) | (Xparticle >= windowWidth && Yparticle >= windowWidth) | (Xparticle >= windowWidth && Yparticle <= 0))
	{
		Particle actualParticle = vectorParticles[index];
		vectorParticles[index].setVelocity(sf::Vector2f(-actualParticle.getVelocityX(), -actualParticle.getVelocityY()));
		vertexParticles[index].color = sf::Color::White;
	}
	

}
