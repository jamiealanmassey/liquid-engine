#include "Light.h"
#include "LightFXProcessor.h"

Light::Light(std::string identifier, sf::Vector2f position, sf::Color colour, float intensity) :
	Entity(position, identifier),
	m_Processor(nullptr),
	m_Colour(colour),
	m_Intensity(intensity)
{
}

void Light::implInitialise()
{
	// Create a new light renderable, pass custom render function and attach it to this
	// light entity
	Renderable* light_renderable = new Renderable("", 5);
	light_renderable->f_RenderOverride = std::bind(&Light::renderLight, this, std::placeholders::_1, std::placeholders::_2);
	attachRenderable(light_renderable);
}

void Light::implKill()
{
	// Remove the light from the processor
	if (m_Processor)
		m_Processor->removeLight(this);
}

void Light::renderLight(Renderable* renderable, sf::RenderTarget& target)
{
	// Render light geometry
	if (m_LightGeom.getVertexCount() == 0)
		return;

	sf::RenderStates states;
	states.blendMode = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::One);
	states.transform.translate(m_Position);

	target.draw(m_LightGeom, states);
}
