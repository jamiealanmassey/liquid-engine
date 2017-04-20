#include "ITweener.h"
#include "Tweener.h"
#include <list>

namespace liquid { namespace tweener {
#ifndef _TWEENERGROUP_H
#define _TWEENERGROUP_H

/**
 * \class TweenerGroup
 *
 * \ingroup Tweener
 * \brief Stores and updates multiple Tweeners at once
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 19/04/2017
 *
 */

class TweenerGroup : public ITweener
{
public:
    /// TweenerGroup Constructor
    TweenerGroup();

    /// TweenerGroup Destructor
    ~TweenerGroup();

    /** \brief Inserts a new Tweener into the group
      * \param t Tweener to add to this group
      */
    void insert(const Tweener& t);

    /// \brief Clears the current group of Tweeners
    void clear();

    /** \brief Denotes if the group is empty or not
      * \return True if empty, otherwise False
      */
    bool isEmpty() const;

    /** \brief Override called every step for updating
      * \return Deltatime of this step
      */
    double update() override;
    
    /** \brief Override for checking if the group of tweeners have finished
      * \return True if tweeners are done, otherwise False
      */
    bool isFinished() override;

protected:
    std::list<Tweener> mTweeners; ///< Collection of Tweeners handled by this group

};

#endif // _TWEENERGROUP_H
}}
