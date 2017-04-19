#include "ITweener.h"
#include "Tweener.h"
#include <list>

namespace liquid { namespace tweener {
#ifndef _TWEENERGROUP_H
#define _TWEENERGROUP_H

class TweenerGroup : public ITweener
{
public:
    TweenerGroup();
    ~TweenerGroup();

    void insert(const Tweener& t);
    void clear();
    bool isEmpty() const;

    double update() override;
    bool isFinished() override;

protected:
    std::list<Tweener> mTweeners; ///< Collection of Tweeners handled by this group

};

#endif // _TWEENERGROUP_H
}}
