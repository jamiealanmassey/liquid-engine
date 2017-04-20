#include <functional>
#include <list>

namespace liquid { namespace tweener {
#ifndef _ITWEENER_H
#define _ITWEENER_H

/**
 * \class ITweener
 *
 * \ingroup Tweener
 * \brief Interface class to tie all Tweening objects together
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 19/04/2017
 *
 */

class ITweener
{
public:
    /// Defines a function callback for when the Tweener is finished
    typedef std::function<void()> FinishFunc;

public:
    /// ITweener Constructor
    ITweener();

    /// ITweener Destructor
    ~ITweener();

    /** \brief Call this to step the Tweener forward (GAME MUST BE RUNNING)
      * \return Deltatime of this step
      */
    virtual double update();

    /** \brief Checks to see if the Tweener has finished
      * \return True if done, otherwise False
      */
    virtual bool isFinished();

    /// Called when the Tweener is done, triggers finished callbacks
    virtual void finished() const;

    /** \brief Add a callback for when the tweener is done
      * \param func Function pointer to add to the collection
      */
    void addFinishedFunc(FinishFunc func);
    
protected:
    std::list<FinishFunc> mFinishedFuncs; ///< Collection of callback functions for when tweener is finished
};

#endif _ITWEENER_H // _ITWEENER_H
}}
