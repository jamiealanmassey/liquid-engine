#include "EasingFunction.h"

namespace liquid { namespace tweener {
#ifndef _EASINGFUNCS_H
#define _EASINGFUNCS_H

class EasingFuncs
{
public:
    static double linear(double t);
    static double sine(double t);
    static double quadratic(double t);
    static double cubic(double t);
    static double elastic(double t);
    static double exponential(double t);
    static double bounce(double t);
};

#endif // _EASINGFUNCS_H
}}
