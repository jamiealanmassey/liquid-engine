#include "ITweener.h"
#include "Tweener.h"
#include <list>

namespace liquid { namespace tweener {
#ifndef _TWEENERSEQUENCE_H
#define _TWEENERSEQUENCE_H

/**
 * \class TweenerSequence
 *
 * \ingroup Tweener
 * \brief Stores and executes Tweeners in the sequence they were added
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 19/04/2017
 *
 */

class TweenerSequence : public ITweener
{
public:
    /// TweenerSequence Constructor
    TweenerSequence();

    /// TweenerSequence Destructor
    ~TweenerSequence();

    /** \brief Inserts a new Tweener into the sequence at the back
      * \param t Tweener to add to this sequence
      */
    void insert(const Tweener& t);

    /// \brief Clears the current group of Tweeners
    void clear();

    /** \brief Denotes if the sequence is empty or not
      * \return True if empty, otherwise False
      */
    bool isEmpty() const;

    /** \brief Override called every step for updating
      * \return Deltatime of this step
      */
    float update() override;

    /** \brief Override for checking if the sequence of tweeners has finished
      * \return True if tweeners are done, otherwise False
      */
    bool isFinished() override;

protected:
    std::list<Tweener> mTweeners; ///< Collection of Tweeners in this sequence
};

#endif // _TWEENERSEQUENCE_H
}}
