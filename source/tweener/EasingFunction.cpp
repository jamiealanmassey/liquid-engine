#include "EasingFunction.h"

namespace liquid {
namespace tweener {
    
    EasingFunction::EasingFunction()
    {
        mEasingFunc = nullptr;
        mType = eEasingType::EASINGTYPE_IN;
    }

    EasingFunction::EasingFunction(std::function<double(double)> func, EasingFunction::eEasingType type)
    {
        mEasingFunc = func;
        mType = type;
    }

    EasingFunction::~EasingFunction()
    {}

    double EasingFunction::ease(double t)
    {
        if (mType == eEasingType::EASINGTYPE_IN)
            return in(t);
        else if (mType == eEasingType::EASINGTYPE_OUT)
            return out(t);
        else if (mType == eEasingType::EASINGTYPE_INOUT)
            return inout(t);
    }

    double EasingFunction::in(double t)
    {
        return mEasingFunc(t);
    }

    double EasingFunction::out(double t)
    {
        return 1.0 - in(1.0 - t);
    }

    double EasingFunction::inout(double t)
    {
        if (t < 0.5)
            return in(2.0 * t) / 2.0;
        else
            return 0.5 + out(2.0 * t - 1.0) / 2.0;
    }

}}
