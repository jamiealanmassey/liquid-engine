#include "Light.h"

namespace liquid { namespace graphics {
#ifndef _LIGHTINGMANAGER_H
#define _LIGHTINGMANAGER_H

class Renderer;
class LightingManager
{
public:
    LightingManager(std::array<float, 4> ambientColour);
    ~LightingManager();

    virtual void draw(graphics::Renderer* renderer) = 0;

    virtual void insertLight(Light* lightPtr);
    virtual void removeLight(Light* lightPtr);

    void setAmbientColour(std::array<float, 4> colour);

    const std::array<float, 4> getAmbientColour() const;
    const std::vector<Light*> getLights() const;
    const uint32_t getLightCount() const;

protected:
    std::array<float, 4> mAmbientColour;
    std::vector<Light*>  mLights;
};

#endif // _LIGHTINGMANAGER_H
}}
