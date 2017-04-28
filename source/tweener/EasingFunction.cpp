#include "EasingFunction.h"

namespace liquid {
namespace tweener {
    
    EasingFunction::EasingFunction()
    {
        mEasingFunc = nullptr;
        mType = eEasingType::EASINGTYPE_IN;
    }

    EasingFunction::EasingFunction(std::function<float(float)> func, EasingFunction::eEasingType type)
    {
        mEasingFunc = func;
        mType = type;
    }

    EasingFunction::~EasingFunction()
    {}

    float EasingFunction::ease(float t)
    {
        if (mType == eEasingType::EASINGTYPE_IN)
            return in(t);
        else if (mType == eEasingType::EASINGTYPE_OUT)
            return out(t);
        else if (mType == eEasingType::EASINGTYPE_INOUT)
            return inout(t);
        else
            return 0.f;
    }

    float EasingFunction::in(float t)
    {
        return mEasingFunc(t);
    }

    float EasingFunction::out(float t)
    {
        return 1.0f - in(1.0f - t);
    }

    float EasingFunction::inout(float t)
    {
        if (t < 0.5f)
            return in(2.0f * t) / 2.0f;
        else
            return 0.5f + out(2.0f * t - 1.0f) / 2.0f;
    }

}}
