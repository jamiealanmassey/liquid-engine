#ifndef _LIGHTFXPROCESSOR_H
#define _LIGHTFXPROCESSOR_H

#include <SFML/Graphics.hpp>
#include "../PostProcessor.h"

class Light;
class Renderer;

class LightFXProcessor : public PostProcessor
{
public:
	LightFXProcessor(sf::Color ambientLight, std::string name, Renderer* renderer);
	~LightFXProcessor();

	virtual void userProcess() override;

	void	 addLight(Light* light);
	void     removeLight(Light* light);
	uint32_t getLightCount() const { return m_Lights.size(); }

protected:
	sf::Color		    m_AmbientLight; ///< Colour of light
	sf::RenderTexture*  m_AccumBuffer;  ///< Buffer for drawing light
	std::vector<Light*> m_Lights;		///< List of attached lights for the processor
};

#endif // _LIGHTFXPROCESSOR_H
