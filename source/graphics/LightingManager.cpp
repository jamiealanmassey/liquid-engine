#include "LightingManager.h"
#include "../graphics/Renderer.h"

namespace liquid {
namespace graphics {

    LightingManager::LightingManager(std::array<float, 4> ambientColour)
    {
        mAmbientColour = ambientColour;
    }

    LightingManager::~LightingManager()
    {
        for (uint32_t i = 0; i < mLights.size(); i++)
            delete mLights[i];

        mLights.clear();
    }

    void LightingManager::insertLight(Light* lightPtr)
    {
        mLights.push_back(lightPtr);
    }

    void LightingManager::removeLight(Light* lightPtr)
    {
        mLights.erase(
            std::find(mLights.begin(), mLights.end(), lightPtr));
    }

    void LightingManager::setAmbientColour(std::array<float, 4> colour)
    {
        mAmbientColour = colour;
    }

    const std::array<float, 4> LightingManager::getAmbientColour() const
    {
        return mAmbientColour;
    }

    const std::vector<Light*> LightingManager::getLights() const
    {
        return mLights;
    }

    const uint32_t LightingManager::getLightCount() const
    {
        return mLights.size();
    }

}}
