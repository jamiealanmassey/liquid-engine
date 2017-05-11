#include "Camera.h"

namespace liquid {
namespace common {

    Camera::Camera()
    {
    }

    Camera::~Camera()
    {
    }

    const std::array<float, 2> Camera::getCentre() const
    {
        return mCentre;
    }

    const std::array<float, 2> Camera::getDimensions() const
    {
        return mDimensions;
    }

    const float Camera::getRotation() const
    {
        return mRotation;
    }

}}
