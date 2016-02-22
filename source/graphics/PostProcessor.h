#ifndef _POST_PROCESSOR_H
#define _POST_PROCESSOR_H

#include <SFML/Graphics.hpp>
#include <string>

class Renderer;

class PostProcessor
{
public:
	PostProcessor(std::string name, Renderer* renderer);
	virtual ~PostProcessor() {}

	/* Core functions */
	virtual void implUpdate() {}
	virtual void userProcess() = 0;

	/* Setter functions */
	void setEnabled(bool enabled) { m_Enabled = enabled; }

	/* Getter functions */
	std::string getName()    const { return m_Name;    }
	bool		getEnabled() const { return m_Enabled; }

protected:
	bool			  m_Enabled;	  ///< Flag to denote whether processor is active
	Renderer*		  m_RendererPtr;  ///< Pointer to parent renderer
	std::string		  m_Name;		  ///< String identifier for processor
	sf::RenderTarget* m_RenderTarget; ///< Target to draw to
};

#endif //_POST_PROCESSOR_H
