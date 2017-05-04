#ifdef SFML
#include "../../graphics/LightingManager.h"
#include "../../data/Settings.h"
#include <SFML/Graphics.hpp>

namespace liquid { namespace impl {
#ifndef _SFMLLIGHTINGMANAGER_H
#define _SFMLLIGHTINGMANAGER_H

class SFMLLightingManager : public graphics::LightingManager
{
public:
    SFMLLightingManager(data::Settings* settings, std::array<float, 4> ambientColour);
    ~SFMLLightingManager();

    virtual void draw(graphics::Renderer* renderer) override;

protected:
    sf::RenderTexture* mAcummulationBuffer;
};

#endif // _SFMLLIGHTINGMANAGER_H
}}

#endif // SFML
