#include "../base/CompositeNode.h"

namespace liquid { namespace ai {
#ifndef _SELECTORNODE_H
#define _SELECTORNODE_H

/**
 * \class SelectorNode
 *
 * \ingroup AI
 * \brief Polar opposite to sequence composite nodes it returns true to the parent node if any children
 *        succeed and will stop processing further children; processed in order of priority
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class SelectorNode : public CompositeNode
{
public:
    /// SelectorNode Constructor
    SelectorNode();

    /// SelectorNode Destructor
    ~SelectorNode();

    /// \brief Overload BehaviourNode::process, processes until a child succeeds
    virtual bool process(BehaviourContext* context) override;
};

#endif // _SELECTORNODE_H
}}


