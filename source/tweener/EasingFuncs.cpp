#include "EasingFuncs.h"

namespace liquid {
namespace tweener {

    double EasingFuncs::linear(double t)
    {
        return t;
    }

    double EasingFuncs::sine(double t)
    {
        static const double pi = 3.141592653589793238462;
        return 1 - std::cos(t * pi / 2.0);
    }

    double EasingFuncs::quadratic(double t)
    {
        return std::pow(t, 2);
    }

    double EasingFuncs::cubic(double t)
    {
        return std::pow(t, 3);
    }

    double EasingFuncs::elastic(double t)
    {
        static const double pi = 3.141592653589793238462;
        const double v = t - 1;
        const double p = 0.3;

        return -std::pow(2, 10 * v) * std::sin((v - p / 4.0) * 2.0 * pi / p);
    }

    double EasingFuncs::exponential(double t)
    {
        if (t == 0)
            return 0;
        else
            return std::pow(2, 10 * (t - 1));
    }

    double EasingFuncs::bounce(double t)
    {
        const double v = 1 - t;
        double c;
        double d;

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
