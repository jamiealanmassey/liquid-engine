#include "../base/DecoratorNode.h"

namespace liquid { namespace ai {
#ifndef _REPEATERNODE_H
#define _REPEATERNODE_H

/**
 * \class RepeaterNode
 *
 * \ingroup AI
 * \brief Keeps processing the child node on each result, usually used at the base of a tree to keep it
 *        running continuously, can be given a set number of times to process
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class RepeaterNode : public DecoratorNode
{
public:
    /// RepeaterNode Constructor
    RepeaterNode();

    /// RepeaterNode Destructor
    ~RepeaterNode();

    /// \brief Called when the parent node is initialised
    virtual void initialise() override;

    /** \brief Called to process the current node, called continuously or until the repeat limit is hit
      * \return Gives a result of true if the repeat limit is hit if it is set, otherwise false
      */
    virtual bool process() override;

    /** \brief Sets the limit of the repeater, 0 = continuous
      * \param limit New limit of the repeater
      */
    void setRepeaterLimit(uint32_t limit);

    /// \return Gets the limit of the RepeaterNode
    const uint32_t getRepeaterLimit() const;

    /// \return Number of times the RepeaterNode has repeated
    const uint32_t getRepeaterCount() const;

protected:
    uint32_t mRepeaterLimit; ///< Number of times before the repeater ends
    uint32_t mRepeaterCount; ///< Number of times the repeater has ran
};

#endif // _REPEATERNODE_H
}}
