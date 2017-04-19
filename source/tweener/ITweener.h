#include <functional>
#include <list>

namespace liquid { namespace tweener {
#ifndef _ITWEENER_H
#define _ITWEENER_H

class ITweener
{
public:
    typedef std::function<void()> FinishFunc;

public:
    ITweener();
    ~ITweener();

    virtual double update();
    //virtual ITweener* duplicate();
    virtual bool isFinished();
    virtual void finished() const;
    void addFinishedFunc(FinishFunc func);
    
protected:
    std::list<FinishFunc> mFinishedFuncs; ///< Collection of callback functions for when tweener is finished
};

#endif _ITWEENER_H // _ITWEENER_H
}}
