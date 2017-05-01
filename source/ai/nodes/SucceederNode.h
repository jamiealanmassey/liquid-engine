#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _SUCCEEDERNODE_H
#define _SUCCEEDERNODE_H

/**
 * \class SucceederNode
 *
 * \ingroup AI
 * \brief Always returns success from the child node, regardless of actual result
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class SucceederNode : public BehaviourNode
{
public:
    /// SucceederNode Constructor
    SucceederNode();

    /// SucceederNode Destructor
    ~SucceederNode();

    /// Overrides BehaviourNode::initialise
    virtual void initialise() override;

    /// Overrides BehaviourNode::process
    virtual void process() override;

    /** \brief Overrides BehaviourNode::insertChild to limit children to 1
      * \param node Child node to be inserted
      */
    virtual void insertChild(BehaviourNode* node) override;
};

#endif // _SUCCEEDERNODE_H
}}
