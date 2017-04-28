#include "EasingFuncs.h"

namespace liquid {
namespace tweener {

    float EasingFuncs::linear(float t)
    {
        return t;
    }

    float EasingFuncs::sine(float t)
    {
        static const float pi = 3.141592653589793238462;
        return 1 - std::cos(t * pi / 2.0);
    }

    float EasingFuncs::quadratic(float t)
    {
        return std::pow(t, 2);
    }

    float EasingFuncs::cubic(float t)
    {
        return std::pow(t, 3);
    }

    float EasingFuncs::elastic(float t)
    {
        static const float pi = 3.141592653589793238462;
        const float v = t - 1;
        const float p = 0.3;

        return -std::pow(2, 10 * v) * std::sin((v - p / 4.0) * 2.0 * pi / p);
    }

    float EasingFuncs::exponential(float t)
    {
        if (t == 0)
            return 0;
        else
            return std::pow(2, 10 * (t - 1));
    }

    float EasingFuncs::bounce(float t)
    {
        const float v = 1 - t;
        float c;
        float d;

        if (v < (1.0 / 2.75))
        {
            c = v;
            d = 0;
        }
        else if (v < (2.0 / 2.75))
        {
            c = v - 1.5 / 2.75;
            d = 0.75;
        }
        else if (v < (2.5 / 2.75))
        {
            c = v - 2.25 / 2.75;
            d = 0.9375;
        }
        else
        {
            c = v - 2.625 / 2.75;
            d = 0.984375;
        }

        return 1 - (7.5625 * c * c + d);
    }

}}
