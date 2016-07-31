#ifndef _PARTICLEEMITTER_H
#define _PARTICLEEMITTER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include <PugiXML/pugixml.hpp>
#include "../utilities/LerpValue.h"
#include "../common/Entity.h"

class Particle;

// TODO: Maybe make a ParticleEffect class that can hold multiple emitters
class ParticleEmitter : public Entity
{
public:
	enum eEmitterType
	{
		Type_Undefined	 = 0,
		Type_Directional = 1,
		Type_Circular	 = 2
		// TODO: Particle Beams?
	};

public:
	ParticleEmitter(std::string identifier, sf::Vector2f position, std::string xml_file = "");
	~ParticleEmitter();

	virtual void implInitialise() override;
	virtual void implUpdate() override;
	virtual void implUpdatePost() {}
	
	void emit(Particle* part);
	bool loadXMLData(std::string xml_file);

protected:
	// Emitter data
	Particle**	 m_Particles;
	uint32_t	 m_ParticleCount;
	eEmitterType m_EmitterType;
	float        m_BirthRate;
	float        m_BirthAccum;
	std::string  m_ParticleTexture;
	std::string  m_XMLFile;

	// Particle data
	LerpVector	 m_Direction;
	LerpFloat	 m_Speed;
	LerpVector	 m_Size;
	LerpColour	 m_Colour;
	float		 m_LifeSpan;
	float		 m_LifeSpanVariant;
	float		 m_PulseLength;
	sf::Vector2f m_PosVariant;
};

#endif // _PARTICLEEMITTER_H
