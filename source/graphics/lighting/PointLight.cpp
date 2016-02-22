#include "PointLight.h"

PointLight::PointLight(std::string identifier, sf::Vector2f position, sf::Color colour, float radius, float intensity) :
	Light(identifier, position, colour, intensity),
	m_Radius(radius)
{
	// Generate light geometry
	static uint32_t point_count = 34; // 32 outer + centre + repeated first
	m_LightGeom.resize(point_count);

	m_LightGeom[0].position = sf::Vector2f(0, 0);
	m_LightGeom[0].color = sf::Color(m_Colour.r, m_Colour.g, m_Colour.b, 
		m_Intensity*255.0f);

	for (uint32_t i = 1; i < (point_count - 1); i++)
	{
		float angle = TWO_PI * (float)i / (float)(point_count - 2.0f);
		float x = m_Radius * cos(angle);
		float y = m_Radius * sin(angle);

		m_LightGeom[i].position = sf::Vector2f(x, y);
		m_LightGeom[i].color = sf::Color::Transparent;
	}

	m_LightGeom[point_count - 1] = m_LightGeom[1];
	m_LightGeom.setPrimitiveType(sf::TrianglesFan);
}
