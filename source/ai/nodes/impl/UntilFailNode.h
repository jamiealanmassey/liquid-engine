#include "../base/DecoratorNode.h"

namespace liquid {
namespace ai {
#ifndef _UNTILFAILNODE_H
#define _UNTILFAILNODE_H

/**
 * \class UntilFailNode
 *
 * \ingroup AI
 * \brief Keeps processing until the child node returns fail
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class UntilFailNode : public DecoratorNode
{
public:
    /// UntilFailNode Constructor
    UntilFailNode();

    /// UntilFailNode Destructor
    ~UntilFailNode();

    /// \brief Overload BehaviourNode::process, processes until the child fails
    virtual bool process() override;
};

#endif // _UNTILFAILNODE_H
}}
