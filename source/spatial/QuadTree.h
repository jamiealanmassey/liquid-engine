#include "Spatial.h"
#include "QuadNode.h"

namespace liquid { namespace spatial {
#ifndef _QUADTREE_H
#define _QUADTREE_H

/**
 * \class QuadTree
 *
 * \ingroup Spatial
 * \brief Controls and stores a root QuadNode, allows for Query of the Nodes and utility functions
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 23/04/2017
 *
 */

class QuadTree : public Spatial
{
public:
    /** \brief QuadTree Constructor
      * \param capacity Default capacity for any QuadNode created in this tree
      * \param centre Centre point of the root QuadNode in the QuadTree
      * \param size Size of the root QuadNode in the QuadTree
      */
    QuadTree(int32_t capacity, std::array<float, 2> centre, std::array<float, 2> size);
    
    /// QuadTree Destructor
    ~QuadTree();

    /// \brief Initialise function overrider
    virtual void initialise() override;

    /// \brief Dispose function overrider
    virtual void dispose() override;

    /// \brief Update function overrider
    virtual void update() override;

    /** \brief Insert a new common::Entity into the QuadTree
      * \param entityPtr Pointer to the Entity to be added
      *
      * Inserts a new Entity into the QuadTree by calling down to the root
      * QuadNode object and recursively searching
      */
    virtual void insertEntity(common::Entity* entityPtr) override;

    /** \brief Remove a  common::Entity from the QuadTree
      * \param entityPtr Pointer to the Entity to be removed
      *
      * Removes an Entity from the QuadTree by calling down to the root
      * QuadNode object and recursively searching
      */
    virtual void removeEntity(common::Entity* entityPtr) override;

    QuadNode* getRootNode() const;

    /** \brief Query the QuadTree and find all common::Entity objects in the given region
      * \param region Area to search in an Array format where = (x, y, width, height)
      */
    virtual std::vector<common::Entity*> query(std::array<float, 4> region) override;
    
    /** \brief Query the QuadTree and find all common::Entity objects in the given region
      * \param region Area to search in an Array format where = (x, y, width, height)
      * \param type Specific Entity type to search for
      */
    virtual std::vector<common::Entity*> query(std::array<float, 4> region, int32_t type) override;

    void setTrackedNode(common::Entity* entity, QuadNode* node);

protected:
    /** \brief Search recursively using a depth search to find all Entities in the region
      * \param node Next node to use for the search
      * \param region Region area to search around
      * \return Collection of found common::Entity objects
      */
    std::vector<common::Entity*> depthSearch(QuadNode* node, std::array<float, 4> region);

protected:
    QuadNode* mRootNode;    ///< Pointer to the stored root QuadNode for this QuadTree
    int32_t   mNumEntities; ///< Number of Entities that exist in the whole tree

private:
    std::map<common::Entity*, QuadNode*> mTrackedEntities;
};

#endif // _QUADTREE_H
}}
