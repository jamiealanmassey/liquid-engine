#include "EasingFunction.h"

namespace liquid { namespace tweener {
#ifndef _EASINGFUNCS_H
#define _EASINGFUNCS_H

/**
 * \class EasingFuncs
 *
 * \ingroup Tweener
 * \brief Wrapper function to implement easing functions, pass these to the EasingFunction class as the function pointer
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 19/04/2017
 *
 */

class EasingFuncs
{
public:
    /** \brief Linear Easing
      * \param t Time-slice (0 - 1)
      * \return Calculated time-slice result based on function
      *
      * where f(t) = t
      */
    static double linear(double t);

    /** \brief Sine Easing
      * \param t Time-slice (0 - 1)
      * \return Calculated time-slice result based on function
      *
      * where f(t) = 1 - cos(t * pi / 2)
      */
    static double sine(double t);

    /** \brief Quadratic Easing
      * \param t Time-slice (0 - 1)
      * \return Calculated time-slice result based on function
      *
      * where f(t) = t^2
      */
    static double quadratic(double t);

    /** \brief Cubic Easing
      * \param t Time-slice (0 - 1)
      * \return Calculated time-slice result based on function
      *
      * where f(t) = t^3
      */
    static double cubic(double t);

    /** \brief Elastic Easing
      * \param t Time-slice (0 - 1)
      * \return Calculated time-slice result based on function
      *
      * where f(t) = -2^(10 * (t - 1)) * sin(((t - 1) - 0.3 / 4) * 2 * pi / 0.3)
      */
    static double elastic(double t);

    /** \brief Exponential Easing
      * \param t Time-slice (0 - 1)
      * \return Calculated time-slice result based on function
      *
      * where f(t) = 0 if t == 0 || 2^(10 * (t - 1))
      */
    static double exponential(double t);

    /** \brief Bounce Easing
      * \param t Time-slice (0 - 1)
      * \return Calculated time-slice result based on function
      *
      * where v = 1 - t
      *       f(t) = if (v < (1 / 2.75))   -> 1 - (7.5625 * (1 - t) * (1 - t) + 0                               or
      *              if (v < (2 / 2.75))   -> 1 - (7.5625 * (v - 1.5 / 2.75) * (v - 1.5 / 2.75) + 0.75          or
      *              if (v < (2.5 / 2.75)) -> 1 - (7.5625 * (v - 2.25 / 2.75) * (v - 2.25 / 2.75) + 0.9375      or
      *              otherwise             -> 1 - (7.5625 * (v - 2.625 / 2.75) * (v - 2.625 / 2.75) + 0.984375
      */
    static double bounce(double t);
};

#endif // _EASINGFUNCS_H
}}
