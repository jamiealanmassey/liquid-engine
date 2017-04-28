#include "ITweener.h"
#include "EasingFunction.h"
#include <algorithm>

namespace liquid { namespace tweener {
#ifndef _TWEENER_H
#define _TWEENER_H

/**
 * \class Tweener
 *
 * \ingroup Tweener
 * \brief Core tweening class for dealing with interporlation of two points
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 19/04/2017
 *
 */

class Tweener : public ITweener
{
public: 
    /// Defines a Function Callback for updates
    typedef std::function<void(float)> UpdateFunc;

public:
    /// Tweener Constructor
    Tweener();

    /** \brief Tweener Constructor
      * \param value The initial value of this Tweener
      * \param target The target value of this Tweener
      * \param duration Duration you want the Tweener to run in milliseconds (ms)
      * \param easingFunc The EasingFunction to use during steps
      * \param updateFunc Update Function called every step
      */
    Tweener(float value, float target, float duration, EasingFunction easingFunc, UpdateFunc updateFunc);

    /** \brief Tweener Constructor
      * \param value The initial value of this Tweener
      * \param target The target value of this Tweener
      * \param duration Duration you want the Tweener to run in milliseconds (ms)
      * \param easingFunc The EasingFunction to use during steps
      */
    Tweener(float value, float target, float duration, EasingFunction easingFunc);

    /// Tweener Destructr
    ~Tweener();

    /** \brief Overrides the update function, calculates the next value from the time-slice
      * \return Delta time of this step
      */
    virtual float update() override;

    /** \brief Overrides the ITweener::isFinished function, ends when time has elapsed the duration
      * \return True if the Tweener has finished, otherwise False
      */
    virtual bool isFinished() override;

    /// \brief Resets the Tweener to its initial state
    void reset();

    /** \brief Sets the initial value of the Tweener
      * \param value Value to assign
      */
    void setInitial(float value);

    /** \brief Sets the target value of the Tweener
      * \param value Value to assign
      */
    void setTarget(float value);

    /** \brief Sets the duration value of the Tweener
      * \param value Value to assign
      */
    void setDuration(float value);

    /** \brief Sets the UpdateFunc to use, called every step
      * \param func Function Pointer to assign
      */
    void setUpdateFunc(UpdateFunc func);

    /** \brief Sets the EasingFunction to use, called every step to get the new value
      * \param func Function Pointer to assign
      */
    void setEasingFunc(EasingFunction func);

    /** \brief Calculates the next value of the Tweener from the timeslice
      * \return The next value from the Tweener
      */
    float calculateValue();

    /// \return Gets the stored value
    float getValue();

    /// \return Gets the initial stored value
    float getInitial() const;

    /// \return Gets the stored target value
    float getTarget() const;

    /// \return Gets the elapsed time value
    float getElapsed() const;

    /// \return Gets the duration of the Tweener
    float getDuration() const;

protected:
    float mElapsed;  ///< The elapsed time
    float mInitial;  ///< The initial value given to the tweener
    float mTarget;   ///< The final value that the tweener should land at, the 'target'
    float mDuration; ///< Duration that the tweener has been running
    float mValue;    ///< Actual value of Tweener
    
protected:
    UpdateFunc     mUpdateFunc; ///< Function callback called everytime this tweener is updated
    EasingFunction mEasingFunc; ///< Function callback called to calculate the tweeners new value
};

#endif // _TWEENER_H
}}
