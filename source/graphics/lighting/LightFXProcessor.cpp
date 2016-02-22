#include "LightFXProcessor.h"
#include "Light.h"
#include "../Renderer.h"
#include "../../common/GameScene.h"
#include "../../common/GameManager.h"

LightFXProcessor::LightFXProcessor(sf::Color ambient_light, std::string name, Renderer* renderer) :
	PostProcessor(name, renderer),
	m_AmbientLight(ambient_light)
{
	// Create buffer
	sf::Vector2u screen_size = renderer->getParentScene()->getGameManager()->getRenderWindow()->getSize();
	m_AccumBuffer = new sf::RenderTexture();
	m_AccumBuffer->create(screen_size.x, screen_size.y);
}

LightFXProcessor::~LightFXProcessor()
{
	// Delete buffer
	delete m_AccumBuffer;
}

void LightFXProcessor::userProcess()
{
	if (getLightCount() == 0)
		return;

	m_AccumBuffer->setView(*m_RendererPtr->getWorldView());

	// First, render all the lights to the accumulation buffer
	m_AccumBuffer->clear(m_AmbientLight);
	for (auto light : m_Lights)
	{
		light->renderLight(light->getRenderable(), *m_AccumBuffer);
	}
	m_AccumBuffer->display();

	// Then render accumulation buffer over frame
	sf::BlendMode mode(sf::BlendMode::Zero, sf::BlendMode::SrcColor);

	sf::View prev_view = m_RenderTarget->getView();
	m_RenderTarget->setView(m_RenderTarget->getDefaultView());
	m_RenderTarget->draw(sf::Sprite(m_AccumBuffer->getTexture()), sf::RenderStates(mode));
	m_RenderTarget->setView(prev_view);
}

void LightFXProcessor::addLight(Light* light)
{
	// Register light source with the processor and the scene
	light->m_Processor = this;
	m_Lights.push_back(light);
	m_RendererPtr->getParentScene()->addEntity(light);
}

void LightFXProcessor::removeLight(Light* light)
{
	// Remove light from processor
	// Lights call this function when they get destroyed
	for (int32_t i = 0; i < m_Lights.size(); i++)
	{
		if (m_Lights[i] == light)
		{
			m_Lights[i]->m_Processor = nullptr;
			m_Lights.erase(m_Lights.begin() + i);
			return;
		}
	}
}
