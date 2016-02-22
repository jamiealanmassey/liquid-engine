#include "Renderer.h"
#include "Renderable.h"
#include "PostProcessor.h"
#include "../common/GameScene.h"
#include "../common/GameManager.h"
#include "../utilities/DeltaTime.h"

Renderer::Renderer(GameScene* scene_ptr)
{
	// Pass parent scene as ptr
	m_ParentScene = scene_ptr;

	// Create new Renderer Buffer
	m_WorldBuffer = new sf::RenderTexture;
	m_WorldBuffer->create(scene_ptr->getGameManager()->getRenderWindow()->getSize().x,
		scene_ptr->getGameManager()->getRenderWindow()->getSize().y);

	// Create new UI buffer
	m_UIBuffer = new sf::RenderTexture;
	m_UIBuffer->create(scene_ptr->getGameManager()->getRenderWindow()->getSize().x,
		scene_ptr->getGameManager()->getRenderWindow()->getSize().y);

	// Create both the world view and UI view for rendering
	m_WorldView = new sf::View(scene_ptr->getGameManager()->getRenderWindow()->getDefaultView());
	m_UIView    = new sf::View(scene_ptr->getGameManager()->getRenderWindow()->getDefaultView());
	
	// Set the world view to the default view
	scene_ptr->getGameManager()->getRenderWindow()->setView(*m_WorldView);
}

Renderer::~Renderer()
{
	// Delete all renderables
	for (auto renderable : m_WorldPipeline)
		delete renderable;

	for (auto renderable : m_UIPipeline)
		delete renderable;

	// Delete all textures
	for (auto texture : m_Textures)
		delete texture;

	// Clear both the rendering pipeline and textures
	m_WorldPipeline.clear();
	m_UIPipeline.clear();
	m_Textures.clear();

	// Delete WorldBuffer and UIBuffer
	delete m_WorldBuffer;
	delete m_UIBuffer;
}

void Renderer::update()
{
	// Update any renderables for animation and shader data
	for (auto renderable : m_WorldPipeline)
		renderable->update();

	for (auto renderable : m_UIPipeline)
		renderable->update();

	// Update all post processors
	for (auto processor : m_PostProcessors)
	{
		if (processor->getEnabled())
			processor->implUpdate();
	}
}

void Renderer::render(sf::RenderTarget& target)
{
	// Clear window
	m_ParentScene->getGameManager()->getRenderWindow()->clear(sf::Color::Black);

	// Clear buffers
	m_WorldBuffer->clear(sf::Color::Transparent);
	m_UIBuffer->clear(sf::Color::Transparent);

	// Update views (failsafe)
	m_WorldBuffer->setView(*m_WorldView);
	m_UIBuffer->setView(*m_UIView);

	// Render World and UI to buffers
	renderWorld(*m_WorldBuffer);
	RenderUI(*m_UIBuffer);

	// Display buffers
	m_WorldBuffer->display();
	m_UIBuffer->display();

	// Apply post-processors to the scene
	for (auto processor : m_PostProcessors)
	{
		if (processor->getEnabled())
			processor->userProcess();
	}

	// Display buffers
	m_WorldBuffer->display();
	m_UIBuffer->display();

	// Get pointer to game manager and draw buffers to the render window
	GameManager* game_mgr = m_ParentScene->getGameManager();
	game_mgr->getRenderWindow()->draw(sf::Sprite(m_WorldBuffer->getTexture()));
	game_mgr->getRenderWindow()->draw(sf::Sprite(m_UIBuffer->getTexture()));
	game_mgr->getRenderWindow()->display();
}

void Renderer::renderWorld(sf::RenderTarget& target)
{
	// Draw renderables to the Screen
	for (auto renderable : m_WorldPipeline)
		renderable->render(target);
}

void Renderer::RenderUI(sf::RenderTarget& target)
{
	// Draw renderables to the Screen
	for (auto renderable : m_UIPipeline)
		renderable->render(target);
}

void Renderer::addRenderable(Renderable* renderable)
{
	if (renderable->getRenderableType() == Renderable::eRenderableType::WORLD)
	{
		// Add new renderable to the pipeline
		m_WorldPipeline.push_back(renderable);

		// Sort the rendering pipeline based on the scene depth of each
		// renderable
		std::sort(m_WorldPipeline.begin(), m_WorldPipeline.end(),
			[](const Renderable* r1, const Renderable* r2) -> bool
			{ return (r1->getSceneDepth() < r2->getSceneDepth()); }
		);
	}
	else
	{
		// Add new renderable to the pipeline
		m_UIPipeline.push_back(renderable);

		// Sort the rendering pipeline based on the scene depth of each
		// renderable
		std::sort(m_UIPipeline.begin(), m_UIPipeline.end(),
			[](const Renderable* r1, const Renderable* r2) -> bool
			{ return (r1->getSceneDepth() < r2->getSceneDepth()); }
		);
	}
}

void Renderer::removeRenderable(Renderable* renderable)
{
	if (renderable->getRenderableType() == Renderable::eRenderableType::WORLD)
	{
		// Create iterator for the render pipeline
		std::vector<Renderable*>::iterator render_it = m_WorldPipeline.begin();

		// Iterate through each renderable util we find the matching renderable and 
		// remove it from the vector
		for (; render_it != m_WorldPipeline.end(); ++render_it)
		{
			if ((*render_it) == renderable)
			{
				m_WorldPipeline.erase(render_it);
				break;
			}
		}
	}
	else
	{
		// Create iterator for the render pipeline
		std::vector<Renderable*>::iterator render_it = m_UIPipeline.begin();

		// Iterate through each renderable util we find the matching renderable and 
		// remove it from the vector
		for (; render_it != m_UIPipeline.end(); ++render_it)
		{
			if ((*render_it) == renderable)
			{
				m_UIPipeline.erase(render_it);
				break;
			}
		}
	}
}

void Renderer::addPostProcessor(PostProcessor* processor)
{
	// Make sure processor isn't null
	if (processor == nullptr)
		return;

	// Add post processor to vector
	m_PostProcessors.push_back(processor);
}

void Renderer::removePostProcessor(std::string name)
{
	// Find and remove all post-processing fx of that name
	std::vector<PostProcessor*>::iterator it = m_PostProcessors.begin();
	for (; it != m_PostProcessors.end(); it++)
	{
		if ((*it)->getName() == name)
		{
			it = m_PostProcessors.erase(it);
			if (it == m_PostProcessors.end())
				return;
		}
	}
}

void Renderer::removeAllPostProcessors()
{
	// Delete every processor
	for (auto processor : m_PostProcessors)
		delete processor;

	// Clear vector
	m_PostProcessors.clear();
}

PostProcessor* Renderer::getPostProcessor(std::string name)
{
	// Iterate through each processor comparing its name and returning the element
	// if we have found a match
	for (auto processor : m_PostProcessors)
	{
		if (processor->getName() == name)
			return processor;
	}

	// Otherwise no match was found
	return nullptr;
}
