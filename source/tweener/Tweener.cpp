#include "Tweener.h"
#include "../utilities/DeltaTime.h"

namespace liquid {
namespace tweener {

    Tweener::Tweener() :
        ITweener()
    {
        mElapsed = 0.0f;
        mInitial = 0.0f;
        mTarget = 0.0f;
        mDuration = 0.0f;
        mValue = 0.0f;
        mUpdateFunc = nullptr;
    }

    Tweener::Tweener(double value, double target, double duration, EasingFunction easingFunc) :
        ITweener()
    {
        mElapsed = 0;
        mInitial = value;
        mTarget = target;
        mDuration = duration;
        mValue = value;
        mEasingFunc = easingFunc;
        mUpdateFunc = nullptr;
    }

    Tweener::Tweener(double value, double target, double duration, EasingFunction easingFunc, UpdateFunc updateFunc) :
        ITweener()
    {
        mElapsed = 0;
        mInitial = value;
        mTarget = target;
        mDuration = duration;
        mValue = 0.0;
        mEasingFunc = easingFunc;
        mUpdateFunc = updateFunc;
    }

    Tweener::~Tweener()
    {}

    double Tweener::update()
    {
        float dt = utilities::DELTA;
        if (mElapsed >= mDuration)
            return dt;

        mValue = calculateValue();
        mElapsed += dt;

        if (mUpdateFunc != nullptr)
            mUpdateFunc(mValue);

        return dt;
    }

    //virtual ITweener* duplicate() override;

    bool Tweener::isFinished()
    {
        if (mElapsed >= mDuration)
        {
            finished();
            return true;
        }

        return false;
    }

    void Tweener::reset()
    {
        mElapsed = 0.0f;
        mValue = mInitial;
    }

    void Tweener::setInitial(double value)
    {
        mInitial = value;
    }

    void Tweener::setTarget(double value)
    {
        mTarget = value;
    }

    void Tweener::setDuration(double value)
    {
        mDuration = value;
    }

    void Tweener::setUpdateFunc(UpdateFunc func)
    {
        mUpdateFunc = func;
    }

    void Tweener::setEasingFunc(EasingFunction func)
    {
        mEasingFunc = func;
    }

    double Tweener::calculateValue()
    {
        double x = mEasingFunc.ease(mElapsed / mDuration);
        double r = mInitial + x * (mTarget - mInitial);
        return r;
    }

    double Tweener::getValue()
    {
        return mValue;
    }

    double Tweener::getInitial() const
    {
        return mInitial;
    }

    double Tweener::getTarget() const
    {
        return mTarget;
    }

    double Tweener::getElapsed() const
    {
        return mElapsed;
    }

    double Tweener::getDuration() const
    {
        return mDuration;
    }

}}
