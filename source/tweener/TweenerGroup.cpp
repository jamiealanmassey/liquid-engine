#include "TweenerGroup.h"

namespace liquid {
namespace tweener {

    TweenerGroup::TweenerGroup()
    {}

    TweenerGroup::~TweenerGroup()
    {}

    void TweenerGroup::insert(const Tweener& t)
    {
        mTweeners.push_back(t);
    }

    void TweenerGroup::clear()
    {
        mTweeners.clear();
    }

    bool TweenerGroup::isEmpty() const
    {
        return mTweeners.empty();
    }

    double TweenerGroup::update()
    {
        for (auto tweener : mTweeners)
            tweener.update();

        return 0.0f;
    }

    bool TweenerGroup::isFinished()
    {
        uint32_t done = mTweeners.size();
        for (auto tweener : mTweeners)
            done -= tweener.isFinished();

        if (done == 0)
        {
            finished();
            return true;
        }

        return false;
    }

}}
