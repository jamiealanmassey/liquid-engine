#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _INVERTERNODE_H
#define _INVERTERNODE_H

/**
 * \class InverterNode
 *
 * \ingroup AI
 * \brief Takes the result of the child node and inverts the result (i.e. success to fail, fail to success)
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class InverterNode : public BehaviourNode
{
public:
    /// InverterNode Constructor
    InverterNode();

    /// InverterNode Destructor
    ~InverterNode();

    /// Overrides BehaviourNode::initialise
    virtual void initialise() override;

    /// Overrides BehaviourNode::process
    virtual void process() override;

    /** \brief Overrides BehaviourNode::insertChild to limit children to 1
      * \param node Child node to be inserted
      */
    virtual void insertChild(BehaviourNode* node) override;
};

#endif // _INVERTERNODE_H
}}
