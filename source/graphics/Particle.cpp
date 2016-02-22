#include "Particle.h"

Particle::Particle(std::string texture) :
	Renderable(texture, 4),
	m_TimeAlive(1.0f),
	m_LifeSpan(0.0f)
{
	// Load material
	setBlendMode(sf::BlendAdd);
}

void Particle::emit()
{
	// Set defaults based on start variables
	m_Velocity	= m_VelocityLerp.start;
	m_Size		= m_SizeLerp.end;
	m_Colour	= m_ColourLerp.start;
	m_TimeAlive = 0.0f;

	// Reset the position of the material
	setPosition(m_Position);
	setColor(m_Colour);
	setScale(m_Size);
}

void Particle::update(float delta)
{
	m_TimeAlive += delta;

	// Interpolate
	float ratio = m_TimeAlive / m_LifeSpan;
	m_Velocity = m_VelocityLerp.at(ratio);
	m_Size = m_SizeLerp.at(ratio);
	m_Colour = m_ColourLerp.at(ratio);

	// Update position
	m_Position += m_Velocity * delta;

	// Update material
	setPosition(m_Position);
	setColor(m_Colour);
	setScale(m_Size);
}

void Particle::render(sf::RenderTarget& target)
{
	render(target);
}