#include "ITweener.h"
#include "EasingFunction.h"
#include <algorithm>

namespace liquid { namespace tweener {
#ifndef _TWEENER_H
#define _TWEENER_H

class Tweener : public ITweener
{
public: 
    typedef std::function<void(double)> UpdateFunc;

public:
    Tweener(double value, double target, double duration, EasingFunction easingFunc, UpdateFunc updateFunc);
    Tweener(double value, double target, double duration, EasingFunction easingFunc);
    ~Tweener();

    virtual double update() override;
    virtual bool isFinished() override;
    //virtual ITweener* duplicate() override;

    void setTarget(double value);
    void setDuration(double value);

    void setUpdateFunc(UpdateFunc func);
    void setEasingFunc(EasingFunction func);

    double calculateValue();
    double getValue();

    double getInitial() const;
    double getTarget() const;
    double getElapsed() const;
    double getDuration() const;

protected:
    double mElapsed;  ///< The elapsed time
    double mInitial;  ///< The initial value given to the tweener
    double mTarget;   ///< The final value that the tweener should land at, the 'target'
    double mDuration; ///< Duration that the tweener has been running
    double mValue;    ///< Actual value of Tweener
    
protected:
    UpdateFunc     mUpdateFunc; ///< Function callback called everytime this tweener is updated
    EasingFunction mEasingFunc; ///< Function callback called to calculate the tweeners new value
};

#endif // _TWEENER_H
}}
