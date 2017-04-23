#include "Spatial.h"
#include <map>

namespace liquid { namespace spatial {
#ifndef _QUADTREE_H
#define _QUADTREE_H

class QuadNode; // TODO: remove this forward def
class QuadTree : public Spatial
{
public:
    QuadTree();
    ~QuadTree();

    virtual void initialise() override;
    virtual void dispose() override;
    virtual void update() override;

    virtual void trackEntity(common::Entity* entityPtr) override;
    virtual void untrackEntity(common::Entity* entityPtr) override;

    virtual const std::vector<common::Entity*>& query(std::array<float, 4> region) const override;
    virtual const std::vector<common::Entity*>& query(std::array<float, 4> region, int32_t type) const override;

protected:
    std::vector<QuadNode*> mActiveNodes;
    QuadNode*              mRootNode;
};

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
    std::map<common::Entity*, QuadNode*> mEntityQuads; ///< 
};

#endif // _QUADTREE_H
}}
