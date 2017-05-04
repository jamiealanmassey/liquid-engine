#include "../base/DecoratorNode.h"

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
 * \date 04/05/2017
 *
 */

class InverterNode : public DecoratorNode
{
public:
    /// InverterNode Constructor
    InverterNode();

    /// InverterNode Destructor
    ~InverterNode();

    /** \brief Inverts the result of the child node (success = fail, fail = success)
      * \return Opposite of the child result, default: false
      */
    virtual bool process() override;
};

#endif // _INVERTERNODE_H
}}
