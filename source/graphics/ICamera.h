#include "../tweener/Tweener.h"
#include <array>

namespace liquid { namespace graphics {
#ifndef _ICAMERA_H
#define _ICAMERA_H

class ICamera
{
public:
    ICamera() {}
    ~ICamera() {}

    virtual void update() = 0;
    virtual void setCentre(std::array<float, 2> position) = 0;
    virtual void setDimensions(std::array<float, 2> dimensions) = 0;
    virtual void setRotation(float rotation) = 0;

    virtual void easePosition(std::array<float, 2> targetPosition, float duration) = 0;
    virtual void easeRotation(float targetRotation, float duration) = 0;
    virtual void easeZoomFactor(float targetZoomFactor, float duration) = 0;

    virtual void shake() = 0;

protected:
    std::array<float, 2> mCentre;
    std::array<float, 2> mDimensions;
    float                mRotation;
    float                mZoomFactor;

protected:
    tweener::Tweener mPositionTweener;
    tweener::Tweener mRotationTweener;
    tweener::Tweener mZoomTweener;
};

#endif // _ICAMERA_H
}}
