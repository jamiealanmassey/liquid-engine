#include "ITweener.h"
#include "Tweener.h"
#include <list>

namespace liquid { namespace tweener {
#ifndef _TWEENERSEQUENCE_H
#define _TWEENERSEQUENCE_H

class TweenerSequence : public ITweener
{
public:
    TweenerSequence();
    ~TweenerSequence();

    void insert(const Tweener& t);
    void clear();
    bool isEmpty() const;

    double update() override;
    bool isFinished() override;

protected:
    std::list<Tweener> mTweeners; ///< Collection of Tweeners in this sequence
};

#endif // _TWEENERSEQUENCE_H
}}
