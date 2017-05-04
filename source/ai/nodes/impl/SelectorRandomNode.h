#include "../base/CompositeNode.h"

namespace liquid { namespace ai {
#ifndef _SELECTORRANDOMNODE_H
#define _SELECTORRANDOMNODE_H

/**
 * \class SelectorRandomNode
 *
 * \ingroup AI
 * \brief Polar opposite to sequence composite nodes it returns true to the parent node if any children
 *        succeed and will stop processing further children; processed in random order
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class SelectorRandomNode : public CompositeNode
{
public:
    /// SelectorRandomNode Constructor
    SelectorRandomNode();

    /// SelectorRandomNode Destructor
    ~SelectorRandomNode();

    /// \brief Overload BehaviourNode::process, processes until a child succeeds
    virtual bool process() override;
};

#endif // _SELECTORRANDOMNODE_H
}}
