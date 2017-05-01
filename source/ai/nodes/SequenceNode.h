#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _SEQUENCENODE_H
#define _SEQUENCENODE_H

/**
 * \class SequenceNode
 *
 * \ingroup AI
 * \brief Visits each child in order with first to last, any fail and composite node will fail
 *
 * Polar opposite to sequence composite nodes it returns true to the parent node if any children
 * succeed and will stop processing further children; processed in order of priority
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class SequenceNode : public BehaviourNode
{
public:
    /// SequenceNode Constructor
    SequenceNode();

    /// SequenceNode Destructor
    ~SequenceNode();

    /// Overrides BehaviourNode::initialise
    virtual void initialise() override;

    /// Overrides BehaviourNode::process
    virtual void process() override;

    /** \brief Overrides BehaviourNode::nextNode using mCurrentlyProcessing
      * \return Either the mChildren[mCurrentlyProcessing] or nullptr
      */
    virtual BehaviourNode* nextNode() override;

protected:
    uint32_t mCurrentlyProcessing; ///< Index of the currently processing child node
};

#endif // _SEQUENCENODE_H
}}
