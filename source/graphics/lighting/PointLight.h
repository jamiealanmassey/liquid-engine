#ifndef _POINT_LIGHT_H
#define _POINT_LIGHT_H

#include "Light.h"

#define PI 3.14159265
#define TWO_PI 6.28318531

class PointLight : public Light
{
public:
	PointLight(std::string identifier, sf::Vector2f position, sf::Color colour, float radius, float intensity);
	~PointLight() {}

	float getRadius() const { return m_Radius; }
	
	virtual std::string getLightType() override
	{
		return "PointLight";
	}

protected:
	float m_Radius;
};

#endif // _POINT_LIGHT_H
