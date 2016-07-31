#include "ParticleEmitter.h"
#include "Particle.h"
#include "../utilities/Random.h"
#include "../utilities/Vectors.h"
#include "../utilities/DeltaTime.h"
#include "../common/GameScene.h"

ParticleEmitter::ParticleEmitter(std::string identifier, sf::Vector2f position, std::string xml_file) :
	Entity(position, identifier),
	m_Particles(nullptr),
	m_ParticleCount(0),
	m_EmitterType(Type_Undefined),
	m_BirthRate(0.0f),
	m_BirthAccum(0.0f),
	m_Speed({ 0.0f, 0.0f, 0.0f }),
	m_LifeSpan(0.0f),
	m_LifeSpanVariant(0.0f),
	m_PulseLength(0.0f),
	m_XMLFile(xml_file)
{
}

ParticleEmitter::~ParticleEmitter()
{
	// Remove renderables from renderer
	for (uint32_t i = 0; i < m_ParticleCount; i++)
	{
		m_ParentScene->getRenderer()->removeRenderable(m_Particles[i]);
		delete m_Particles[i];
	}

	// Delete particles
	if (m_Particles)
		delete[] m_Particles;
}

void ParticleEmitter::implInitialise()
{
	// Load XML file if provided
	if (!m_XMLFile.empty())
		loadXMLData(m_XMLFile);
}

void ParticleEmitter::implUpdate()
{
	// Update birth timer
	m_BirthAccum += Delta;

	// Update every particle
	for (int32_t p = 0; p < m_ParticleCount; p++)
	{
		Particle* part = m_Particles[p];

		if (part->isAlive())
			part->update(Delta);
		else
		{
			// If we need more particles, (re-)emit this one
			if (m_BirthAccum >= m_BirthRate)
			{
				emit(part);
				m_BirthAccum -= m_BirthRate;
			}
		}
	}
}

bool ParticleEmitter::loadXMLData(std::string xml_file)
{
	// Open as XML file
	pugi::xml_document xml;
	if (!xml.load_file(xml_file.c_str()))
	{
		std::cout << "Could not parse XML file " << xml_file << std::endl;
		return false;
	}

	// Get root node
	pugi::xml_node& root = xml.child("ParticleEmitter");
	m_ParticleCount = root.attribute("particles").as_uint();

	// Parse emitter type
	std::string type = root.attribute("type").as_string();
	if (type == "Directional")
		m_EmitterType = eEmitterType::Type_Directional;
	else if (type == "Circular")
		m_EmitterType = eEmitterType::Type_Circular;

	// Parse particle information
	if (m_EmitterType == eEmitterType::Type_Directional)
	{
		// Direction
		m_Direction.start = vecFromStr(root.child("Direction").attribute("start").as_string());
		if (root.child("Direction").attribute("end").empty())
			m_Direction.end = m_Direction.start;
		else
			m_Direction.end = vecFromStr(root.child("Direction").attribute("end").as_string());

		if (!root.child("Direction").attribute("variant").empty())
			m_Direction.variant = vecFromStr(root.child("Direction").attribute("variant").as_string());
	}

	// Texture
	m_ParticleTexture = root.child("Texture").attribute("file").as_string();

	// Speed
	m_Speed.start = root.child("Speed").attribute("start").as_float();
	if (root.child("Speed").attribute("end").empty())
		m_Speed.end = m_Speed.start;
	else
		m_Speed.end = root.child("Speed").attribute("end").as_float();

	if (!root.child("Speed").attribute("variant").empty())
		m_Speed.variant = root.child("Speed").attribute("variant").as_float();
	else
		m_Speed.variant = 0.0f;

	// Size
	m_Size.start = vecFromStr(root.child("Size").attribute("start").as_string());
	if (root.child("Size").attribute("end").empty())
		m_Size.end = m_Size.start;
	else
		m_Size.end = vecFromStr(root.child("Size").attribute("end").as_string());

	if (!root.child("Size").attribute("variant").empty())
		m_Size.variant = vecFromStr(root.child("Size").attribute("variant").as_string());

	// Colour
	m_Colour.start = colFromStr(root.child("Colour").attribute("start").as_string());
	if (root.child("Colour").attribute("end").empty())
		m_Colour.end = m_Colour.start;
	else
		m_Colour.end = colFromStr(root.child("Colour").attribute("end").as_string());

	if (!root.child("Colour").attribute("variant").empty())
		m_Colour.variant = colFromStr(root.child("Colour").attribute("variant").as_string());
	else
		m_Colour.variant = sf::Color::Transparent;

	// Life Span
	m_LifeSpan = root.child("LifeSpan").attribute("value").as_float();
	if (!root.child("LifeSpan").attribute("variant").empty())
		m_LifeSpanVariant = root.child("LifeSpan").attribute("variant").as_float();

	if (!root.child("LifeSpan").attribute("pulse").empty())
		m_PulseLength = root.child("LifeSpan").attribute("pulse").as_float();

	// Position Variant
	if (!root.child("PositionVariant").attribute("variant").empty())
		m_PosVariant = vecFromStr(root.child("PositionVariant").attribute("variant").as_string());

	// Create particles
	m_Particles = new Particle*[m_ParticleCount];
	for (int32_t p = 0; p < m_ParticleCount; p++)
	{
		m_Particles[p] = new Particle(m_ParticleTexture);
		m_ParentScene->getRenderer()->addRenderable(m_Particles[p]);
	}

	// Calculate birth rate
	if (m_PulseLength == 0.0f)
		m_PulseLength = (m_LifeSpan + m_LifeSpanVariant); // Continual stream of particles

	m_BirthRate = m_PulseLength / (float)m_ParticleCount;
	return true;
}

void ParticleEmitter::emit(Particle* part)
{
	// Reset particle data
	part->m_SizeLerp = m_Size.vary();
	part->m_ColourLerp = m_Colour.vary();
	part->m_LifeSpan = m_LifeSpan + randomRangeF(-m_LifeSpanVariant, m_LifeSpanVariant);
	part->m_Position = m_Position + randomRangeV(-m_PosVariant, m_PosVariant);

	// Choose direction based on emitter type
	if (m_EmitterType == Type_Circular)
	{
		// Random direction if position is centre, else
		// velocity points outwards from centre
		sf::Vector2f dist = part->m_Position - m_Position;
		if (lengthSq(dist) == 0.0f)
			part->m_VelocityLerp.start = randomUnitVector();
		else
			part->m_VelocityLerp.start = normalize(dist);

		part->m_VelocityLerp.end = part->m_VelocityLerp.start;
	}
	else
		part->m_VelocityLerp = m_Direction.vary();

	// Velocity = Direction * Speed
	LerpFloat speed = m_Speed.vary();
	part->m_VelocityLerp.start *= speed.start;
	part->m_VelocityLerp.end *= speed.end;

	part->emit();
}
