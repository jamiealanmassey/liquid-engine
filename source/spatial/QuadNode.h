#include "../common/Entity.h"
#include <map>

namespace liquid { namespace spatial {
#ifndef _QUADNODE_H
#define _QUADNODE_H

class QuadTree;
class QuadNode
{
public:
    QuadNode(int32_t capacity, bool isRootNode = false);
    ~QuadNode();

    int32_t quadrant(common::Entity* entityPtr);

    bool insertEntity(common::Entity* entityPtr);
    bool removeEntity(common::Entity* entityPtr);

    void deleteChildNode(QuadNode* node);

    void setParentNode(QuadNode* quadNode);
    void setParentQuadTree(QuadTree* quadTree);
    void setCapacity(int32_t capacity);
    void setCentre(std::array<float, 2> centre);
    void setSize(std::array<float, 2> size);

    const bool isRootNode() const;
    const int32_t getCapacity() const;
    const int32_t getCount() const;
    QuadNode* getParentNode() const;
    QuadTree* getParentQuadTree() const;
    const std::array<QuadNode*, 4> getChildNodes() const;
    const std::array<float, 2> getCentre() const;
    const std::array<float, 2> getSize() const;
    const std::vector<common::Entity*> getEntities() const;

    const bool intersection(common::Entity* entityPtr) const;

protected:
    bool mIsRootNode; /// <
    int32_t mCapacity; ///< 
    QuadNode* mParentNode; ///< 
    QuadTree* mParentQuadTree; ///< 
    std::array<QuadNode*, 4> mChildNodes;
    std::array<float, 2> mCentre; ///<
    std::array<float, 2> mSize; ///< 
    std::vector<common::Entity*> mEntities; ///< 
};

#endif // _QUADNODE_H
}}
