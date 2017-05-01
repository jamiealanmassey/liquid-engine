#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _SELECTORNODE_H
#define _SELECTORNODE_H

/**
 * \class SelectorNode
 *
 * \ingroup AI
 * \brief Polar opposite to sequence composite nodes
 *
 * Polar opposite to sequence composite nodes it returns true to the parent node if any children
 * succeed and will stop processing further children; processed in order of priority
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class SelectorNode : public BehaviourNode
{
public:
    /// SelectorNode Constructor
    SelectorNode();

    /// SelectorNode Destructor
    ~SelectorNode();

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

#endif // _SELECTORNODE_H
}}
