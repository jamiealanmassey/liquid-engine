#ifndef _LIGHT_H
#define _LIGHT_H

#include "../../common/Entity.h"
#include <SFML/Graphics.hpp>

class LightFXProcessor;

class Light : public Entity
{
public:
	Light(std::string identifier, sf::Vector2f position, sf::Color colour, float intensity);
	virtual ~Light() {}

	/* Entity overriders */
	virtual void implInitialise()					 override;
	virtual void implUpdate()	 override {}
	virtual void implUpdatePost() override {}
	virtual void implKill()					 override;

	/* Custom render pass functions */
	void renderLight(Renderable* renderable, sf::RenderTarget& target);

	/* Overrideable getter */
	virtual std::string getLightType() { return "Light"; }

	/* Getter Functions */
	sf::Color getColour()	  const { return m_Colour;    }
	float     getIntensity()  const { return m_Intensity; }

	/* Setter Functions */
	void setColour(sf::Color colour)   { m_Colour = colour;		  }
	void setIntensity(float intensity) { m_Intensity = intensity; }

protected:
	LightFXProcessor* m_Processor;
	sf::VertexArray   m_LightGeom;
	sf::Color		  m_Colour;
	float		      m_Intensity;

	friend class LightFXProcessor;
};

#endif // _LIGHT_H
