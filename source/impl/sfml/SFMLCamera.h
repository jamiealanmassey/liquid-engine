#ifdef SFML
#include "../../graphics/ICamera.h"
#include <SFML/Graphics.hpp>

namespace liquid { namespace impl {
#ifndef _SFMLCAMERA_H
#define _SFMLCAMERA_H

class SFMLCamera : public graphics::ICamera
{
public:
    SFMLCamera(float centreX, float centreY);
    SFMLCamera(float centreX, float centreY, float width, float height);
    ~SFMLCamera();

    virtual void update() override;
    virtual void setCentre(std::array<float, 2> position) override;
    virtual void setDimensions(std::array<float, 2> dimensions) override;
    virtual void setRotation(float rotation) override;
    virtual void setZoomFactor(float zoomFactor) override;

    virtual void easePosition(std::array<float, 2> targetPosition, float duration) override;
    virtual void easeRotation(float targetRotation, float duration) override;
    virtual void easeZoomFactor(float targetZoomFactor, float duration) override;

    virtual void shake(float duration, float radius, eShakeAxis axis) override;

    sf::View getSFMLView() const;

protected:
    void updateScreenShake();

protected:
    bool mShaking;
    float mShakeDuration;
    float mShakeAccumulator;
    float mShakeRadius;
    float mShakeRadiusBegin;
    float mShakeAngle;
    std::array<float, 2> mShakeOffset; 
    eShakeAxis mShakeAxis;
    sf::View mSFMLView;
};

#endif // _SFMLCAMERA_H
}}

#endif // SFML
