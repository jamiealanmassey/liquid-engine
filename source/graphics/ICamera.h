#include "../tweener/Tweener.h"
#include <array>

namespace liquid {
namespace graphics {
#ifndef _ICAMERA_H
#define _ICAMERA_H

class ICamera
{
public:
    enum eShakeAxis
    {
        SHAKEAXIS_X = 0,
        SHAKEAXIS_Y = 1,
        SHAKEAXIS_XY = 2,
    };

public:
    ICamera() {}
    ~ICamera() {}

    virtual void update() = 0;
    virtual void setCentre(std::array<float, 2> position) = 0;
    virtual void setDimensions(std::array<float, 2> dimensions) = 0;
    virtual void setRotation(float rotation) = 0;
    virtual void setZoomFactor(float zoomFactor) = 0;

    virtual void easePosition(std::array<float, 2> targetPosition, float duration) = 0;
    virtual void easeRotation(float targetRotation, float duration) = 0;
    virtual void easeZoomFactor(float targetZoomFactor, float duration) = 0;

    virtual void shake(float duration, float radius, eShakeAxis axis) = 0;

    const std::array<float, 2> getCentre() const
    {
        return mCentre;
    }

    const std::array<float, 2> getDimensions() const
    {
        return mDimensions;
    }

    const float getRotation() const
    {
        return mRotation;
    }

protected:
    std::array<float, 2> mCentre;
    std::array<float, 2> mDimensions;
    float                mRotation;
    float                mZoomFactor;

protected:
    tweener::Tweener mPositionTweener[2];
    tweener::Tweener mRotationTweener;
    tweener::Tweener mZoomTweener;
};

#endif // _ICAMERA_H
}
}
