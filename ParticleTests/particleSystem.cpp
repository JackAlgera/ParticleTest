#include "particleSystem.h"



particleSystem::particleSystem(sf::Vector2f posInitial, int numberOfParticles, sf::Color color, float mass, float coefOfFric, bool reboundOnEdges)
{
	this->reboundOnEdges = reboundOnEdges;
	posInit = posInitial;
	vertexParticles = sf::VertexArray(sf::Points, numberOfParticles);
	for (int i = 0; i < numberOfParticles; i++)
	{
		vectorParticles.push_back(Particle(mass, coefOfFric));
		vertexParticles[i].position = posInitial;
		vertexParticles[i].color = color;
	}
}

particleSystem::~particleSystem()
{
}

void particleSystem::update(float dt, sf::RenderWindow& window, sf::Color color)	//Updates each particle's position
{
	int windowWidth = window.getSize().x;
	int windowHeight = window.getSize().y;
	for (int i = 0; i < vectorParticles.size(); i++)
	{
		updateVelocity(i, windowWidth, windowHeight, dt, color);
		vertexParticles[i].position = vectorParticles[i].position;
	}
}

void particleSystem::draw(sf::RenderWindow & window)
{
	window.draw(vertexParticles);
}

void particleSystem::mouseClick(sf::Vector2i mousePos)
{
	for (int i = 0; i < vectorParticles.size(); i++)
	{
		float distX = (float)(mousePos.x - vertexParticles[i].position.x);
		float distY = (float)(mousePos.y - vertexParticles[i].position.y);

		vectorParticles[i].acceleration = sf::Vector2f((distX / abs(distX)) * 100, (distY / abs(distY)) * 100);
	}
}

void particleSystem::addForce(sf::Vector2f dForce)	//Increase the acceleration of each particle in a given direction
{
	for (int i = 0; i < vectorParticles.size(); i++)
	{
		vectorParticles[i].addForce(dForce);
	}
}

void particleSystem::initializeFormSpiral(float rayon, int dAngle)	//Initialized the particle system with a spiral
{
	float angle = 0;
	float dr = rayon / ((float)vectorParticles.size());
	float r = 0;

	for (int i = 0; i < vectorParticles.size(); i++)													//gives each particle a position on the spiral
	{
		vectorParticles[i].position = sf::Vector2f(posInit.x + cos(angle)*r, posInit.y + sin(angle)*r);
		vertexParticles[i].position = vectorParticles[i].position;
		vectorParticles[i].velocity = sf::Vector2f(0, 0);
		r += dr;
		angle += dAngle*(3.1416/180);
	}

}

void particleSystem::randomSpeedAndDirection(int maxSpeed, sf::Vector2f initialPosition, sf::Color color)
{
	for (int i = 0; i < vectorParticles.size(); i++)
	{
		vectorParticles[i].position = initialPosition;
		vertexParticles[i].position = initialPosition;
		vertexParticles[i].color = color;
		vectorParticles[i].randomIni(maxSpeed, sf::Vector2f(0, 0));
	}
}

void particleSystem::setColor(sf::Color color)
{
	for (int i = 0; i < vectorParticles.size(); i++)
	{
		vertexParticles[i].color = color;
	}
}

void particleSystem::updateVelocity(int index, int windowWidth, int windowHeight, float dt, sf::Color color)	//Updates the position of each particle, and makes then "bounce" of the edges.
{
	vectorParticles[index].update(dt);

	sf::Vector2f position = vectorParticles[index].position;
	vertexParticles[index].position = position;

	float Xparticle = position.x;
	float Yparticle = position.y;

	if (reboundOnEdges)
	{
		if ((Xparticle > 0) && (Xparticle < windowWidth))
		{
			if (Yparticle <= 0)
			{
				if (vectorParticles[index].velocity.y < 0)
				{
					vectorParticles[index].velocity.y = -vectorParticles[index].velocity.y;
					vertexParticles[index].color = color;
				}
			}

			if (Yparticle >= windowHeight)
			{
				if (vectorParticles[index].velocity.y > 0)
				{
					vectorParticles[index].velocity.y = -vectorParticles[index].velocity.y;
					vertexParticles[index].color = color;
				}
			}
		}

		if ((Yparticle > 0) && (Yparticle < windowHeight))
		{
			if (Xparticle <= 0)
			{
				if (vectorParticles[index].velocity.x < 0)
				{
					vectorParticles[index].velocity.x = -vectorParticles[index].velocity.x;
					vertexParticles[index].color = color;
				}
			}

			if (Xparticle >= windowWidth)
			{
				if (vectorParticles[index].velocity.x > 0)
				{
					vectorParticles[index].velocity.x = -vectorParticles[index].velocity.x;
					vertexParticles[index].color = color;
				}
			}
		}
		else if ((Xparticle <= 0 && Yparticle <= 0) | (Xparticle <= 0 && Yparticle >= windowHeight) | (Xparticle >= windowWidth && Yparticle >= windowWidth) | (Xparticle >= windowWidth && Yparticle <= 0))
		{
			Particle actualParticle = vectorParticles[index];
			vectorParticles[index].velocity.x = -vectorParticles[index].velocity.x;
			vectorParticles[index].velocity.y = -vectorParticles[index].velocity.y;
			vertexParticles[index].color = color;
		}
	}
}
