#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _REPEATERNODE_H
#define _REPEATERNODE_H

/**
 * \class RepeaterNode
 *
 * \ingroup AI
 * \brief Keeps processing the child node on each result
 *
 * Keeps processing the child node on each result, usually used at the base of a tree to keep it
 * running continuously, can be given a set number of times to process
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class RepeaterNode : public BehaviourNode
{
public:
    /// RepeaterNode Constructor
    RepeaterNode();

    /// RepeaterNode Destructor
    ~RepeaterNode();

    /// Overrides BehaviourNode::initialise
    virtual void initialise() override;

    /// Overrides BehaviourNode::process
    virtual void process() override;

    /** \brief Overrides BehaviourNode::insertChild to limit children to 1
      * \param node Child node to be inserted
      */
    virtual void insertChild(BehaviourNode* node) override;

    /** \brief Sets the limit for how many times the repeater can repeat
      * \param limit Limit to assign as an integer
      */
    void setRepeaterLimit(uint32_t limit);

    /// \return Gets the limit of the repeater (x amount of cycles)
    const uint32_t getRepeaterLimit() const;

    /// \return Gets the amount of the times the repeater has ran
    const uint32_t getRepeaterCount() const;

protected:
    uint32_t mRepeaterLimit; ///< Limit of how many times the repeater can run
    uint32_t mRepeaterCount; ///< Amount of times that the repeater has ran
};

#endif // _REPEATERNODE_H
}}
