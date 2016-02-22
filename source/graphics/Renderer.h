#ifndef _RENDERER_H
#define _RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

class Renderable;
class GameManager;
class GameScene;
class PostProcessor;

class Renderer
{
public:
	Renderer(GameScene* scene_ptr);
	~Renderer();

	/* Core renderer functionality */
	void update();
	void render(sf::RenderTarget& target);
	void renderWorld(sf::RenderTarget& target);
	void RenderUI(sf::RenderTarget& target);

	/* Helper functions for Renderables */
	void addRenderable(Renderable* renderable);
	void removeRenderable(Renderable* renderable);

	/* Helper functions for PostProcessors */
	void addPostProcessor(PostProcessor* processor);
	void removePostProcessor(std::string name);
	void removeAllPostProcessors();

	PostProcessor* getPostProcessor(std::string name);

	/* Getter functions */
	GameScene*				   getParentScene()	  { return m_ParentScene;	}
	std::vector<Renderable*>&  getWorldPipeline() { return m_WorldPipeline; }
	std::vector<sf::Texture*>& getTextures()	  { return m_Textures;		}
	sf::RenderTexture*		   getWorldBuffer()   { return m_WorldBuffer;	}
	sf::RenderTexture*		   getUIBuffer()	  { return m_UIBuffer;		}
	sf::View*				   getWorldView()	  { return m_WorldView;		}
	sf::View*				   getUIView()		  { return m_UIView;		}

protected:
	GameScene*				    m_ParentScene;	  ///< Pointer to parent Game Scene
	std::vector<PostProcessor*> m_PostProcessors; ///< List of active PostProcessors
	std::vector<Renderable*>    m_WorldPipeline;  ///< List of World Renderables to draw
	std::vector<Renderable*>	m_UIPipeline;	  ///< List of UI Renderables to draw
	std::vector<sf::Texture*>   m_Textures;		  ///< List of stored textures in game
	sf::RenderTexture*		    m_WorldBuffer;    ///< Buffer to draw game world to screen
	sf::RenderTexture*		    m_UIBuffer;		  ///< Buffer to draw game interface to screen
	sf::View*				    m_WorldView;	  ///< View for the World buffer
	sf::View*				    m_UIView;		  ///< View for the UI buffer
};

#endif // _RENDERER_H
