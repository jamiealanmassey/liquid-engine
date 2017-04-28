#include "ITweener.h"

namespace liquid {
namespace tweener {

    ITweener::ITweener()
    {}

    ITweener::~ITweener()
    {}

    float ITweener::update()
    {
        return 0.0f;
    }

    bool ITweener::isFinished()
    {
        return true;
    }

    //virtual ITweener* duplicate();

    void ITweener::finished() const
    {
        const std::list<FinishFunc> funcs(mFinishedFuncs);

        for (auto f : funcs)
            f();
    }

    void ITweener::addFinishedFunc(FinishFunc func)
    {
        mFinishedFuncs.push_back(func);
    }

}}
