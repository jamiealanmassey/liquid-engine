#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Renderable.h"
#include "../utilities/LerpValue.h"

class ParticleEmitter;

class Particle : public Renderable
{
public:
	Particle(std::string texture);
	~Particle() {}

	void emit();
	void update(float delta);
	void render(sf::RenderTarget& target);

	sf::Vector2f getPosition() const { return m_Position;				}
	sf::Vector2f getVelocity() const { return m_Velocity;				}
	sf::Vector2f getSize()     const { return m_Size;					}
	sf::Color	 getColour()   const { return m_Colour;					}
	bool		 isAlive()     const { return m_TimeAlive < m_LifeSpan; }

protected:
	LerpVector   m_VelocityLerp;
	LerpVector   m_SizeLerp;
	LerpColour   m_ColourLerp;
	float		 m_TimeAlive;
	float		 m_LifeSpan;
	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Size;
	sf::Color	 m_Colour;

	friend class ParticleEmitter;
};

#endif // _PARTICLE_H
