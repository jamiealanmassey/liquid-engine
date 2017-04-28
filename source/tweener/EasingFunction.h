#include <functional>

namespace liquid { namespace tweener {
#ifndef _EASINGFUNC_H
#define _EASINGFUNC_H

/** 
 * \class EasingFunction
 * 
 * \ingroup Tweener
 * \brief Defines an EasingFunction for use in the Tweener, stores the function to use for easing
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 19/04/2017
 *
 */

class EasingFunction
{
public:
    /// Enumerator for defining how to ease: In, Out or In & Out
    enum eEasingType
    {
        EASINGTYPE_IN = 0,
        EASINGTYPE_OUT = 1,
        EASINGTYPE_INOUT = 2,
    };

public:
    /// EasingFunction Constructor
    EasingFunction();

    /** \brief EasingFunction Constructor
      * \param func Function pointer for the Easing Function to use
      * \param type Type of Easing to use
      */
    EasingFunction(std::function<float(float)> func, eEasingType type = eEasingType::EASINGTYPE_IN);

    /// EasingFunction Destructor
    ~EasingFunction();

    /** \brief Calculates the ease for the given time-point
      * \param t Current time slice (0 - 1)
      * \return Result of the easing function given the time-point
      */
    float ease(float t);

private:
    /// Special wrapper to be called for EASINGTYPE_IN
    float in(float t);

    /// Special wrapper to be called for EASINGTYPE_OUT
    float out(float t);

    /// Special wrapper to be called for EASINGTYPE_IN
    float inout(float t);

protected:
    std::function<float(float)> mEasingFunc; ///< Function callback to the easing method
    eEasingType                 mType;       ///< Type of easing to use
};

#endif // _EASINGFUNC_H
}}
