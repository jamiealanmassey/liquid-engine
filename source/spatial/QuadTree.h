#include "Spatial.h"
#include "QuadNode.h"

namespace liquid { namespace spatial {
#ifndef _QUADTREE_H
#define _QUADTREE_H

class QuadTree : public Spatial
{
public:
    QuadTree(int32_t capacity, std::array<float, 2> centre, std::array<float, 2> size);
    ~QuadTree();

    virtual void initialise() override;
    virtual void dispose() override;
    virtual void update() override;

    virtual void insertEntity(common::Entity* entityPtr) override;
    virtual void removeEntity(common::Entity* entityPtr) override;

    virtual std::vector<common::Entity*> query(std::array<float, 4> region) override;
    virtual std::vector<common::Entity*> query(std::array<float, 4> region, int32_t type) override;

protected:
    std::vector<common::Entity*> depthSearch(QuadNode* node, std::array<float, 4> region);

protected:
    QuadNode* mRootNode; ///< 
    int32_t mNumEntities; ///< 
};

#endif // _QUADTREE_H
}}
