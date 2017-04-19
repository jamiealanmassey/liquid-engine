#include "TweenerSequence.h"

namespace liquid {
namespace tweener {

    TweenerSequence::TweenerSequence()
    {}

    TweenerSequence::~TweenerSequence()
    {}

    void TweenerSequence::insert(const Tweener& t)
    {
        mTweeners.push_back(t);
    }

    void TweenerSequence::clear()
    {
        mTweeners.clear();
    }

    bool TweenerSequence::isEmpty() const
    {
        return mTweeners.empty();
    }

    double TweenerSequence::update()
    {
        if (mTweeners.empty() == false)
            return mTweeners.front().update();
       
        return 0.0f;
    }

    bool TweenerSequence::isFinished()
    {
        if (mTweeners.empty() == false && mTweeners.front().isFinished())
            mTweeners.pop_front();

        return mTweeners.empty();
    }

}}
