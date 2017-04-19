#include <functional>

namespace liquid { namespace tweener {
#ifndef _EASINGFUNC_H
#define _EASINGFUNC_H

class EasingFunction
{
public:
    enum eEasingType
    {
        EASINGTYPE_IN = 0,
        EASINGTYPE_OUT = 1,
        EASINGTYPE_INOUT = 2,
    };

public:
    EasingFunction();
    EasingFunction(std::function<double(double)> func, eEasingType type = eEasingType::EASINGTYPE_IN);
    ~EasingFunction();

    double ease(double t);

private:
    double in(double t);
    double out(double t);
    double inout(double t);

protected:
    std::function<double(double)> mEasingFunc; ///< Function callback to the easing method
    eEasingType                   mType;       ///< Type of easing to use
};

#endif // _EASINGFUNC_H
}}
