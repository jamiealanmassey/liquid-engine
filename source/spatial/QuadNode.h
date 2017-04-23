#include "../common/Entity.h"
#include <map>

namespace liquid { namespace spatial {
#ifndef _QUADNODE_H
#define _QUADNODE_H

/** 
 * \class QuadTree
 *
 * \ingroup Spatial
 * \brief Splits space into quadrants for sorting and querying of common::Entity objects
 * 
 * \author Jamie Massey
 * \version 1.0
 * \date 23/04/2017
 *
 */

class QuadTree;
class QuadNode
{
public:
    /** \brief QuadNode Constructor
      * \param capacity Limit of the QuadNode before sub-division
      * \param isRootNode Denotes if this is the initial root node
      */
    QuadNode(int32_t capacity, bool isRootNode = false);

    /// QuadNode Destructor
    ~QuadNode();

    /** \brief Finds the quadrant that the common::Entity belongs to
      * \param entityPtr Pointer to the Entity to query
      * \return Value relating to the quadrant the Entity is in
      *
      * The found quadrant is represented as a 32-bit integer where the given value
      * of 0 == top left, 1 == top right, 2 = bottom left and 3 = bottom right
      */
    int32_t quadrant(common::Entity* entityPtr);

    /** \brief Insert a new common::Entity into the QuadNode or its children
      * \param entityPtr Pointer to the Entity to be added
      * \return True of the Entity was added, otherwise false
      */
    bool insertEntity(common::Entity* entityPtr);

    /** \brief Removes a common::Entity from the QuadNode or its children
      * \param entityPtr Pointer to the Entity to be removed
      * \return True of the Entity was removed, otherwise false
      */
    bool removeEntity(common::Entity* entityPtr);

    /** \brief Deletes the specified child node from this Node
      * \param node Pointer to QuadNode for removal
      */
    void deleteChildNode(QuadNode* node);

    /// \brief Search each child branch and this one recursively, removing unused ones
    void pruneDeadBranches();

    /** \brief Set parent QuadNode to this node
      * \param quadNode Parent QuadNode to set
      */
    void setParentNode(QuadNode* quadNode);

    /** \brief Set parent QuadTree to this node
      * \param quadTree Parent QuadTree to set
      */
    void setParentQuadTree(QuadTree* quadTree);

    /** \brief Assign the capacity of this QuadNode
      * \param capacity New capacity of the QuadNode
      */
    void setCapacity(int32_t capacity);

    /** \brief Set the centre of this QuadNode
      * \param centre Array representing where the centre of this node is in 2D-space
      */
    void setCentre(std::array<float, 2> centre);

    /** \brief Set the size of this QuadNode
      * \param centre Array representing where the size of this node is in 2D-space
      */
    void setSize(std::array<float, 2> size);
    
    /// \return True if at least one child QuadNode is not a nullptr, otherwise false
    const bool hasChildren() const;

    /// \return True if this is the root QuadNode to the QuadTree
    const bool isRootNode() const;

    /// \return The Capacity of this QuadNode
    const int32_t getCapacity() const;

    /// \return Number of common::Entity objects stored in mEntities
    const int32_t getCount() const;

    /// \return Pointer to the parent QuadNode
    QuadNode* getParentNode() const;

    /// \return Pointer to the parent QuadTree
    QuadTree* getParentQuadTree() const;

    /// \return Array of the child QuadNode objects to this QuadNode
    const std::array<QuadNode*, 4> getChildNodes() const;

    /// \return Array representing the centre of this QuadNode in 2D-space
    const std::array<float, 2> getCentre() const;

    /// \return Array representing the size of this QuadNode in 2D-space
    const std::array<float, 2> getSize() const;

    /// \return Collection of common::Entity objects stored in this QuadNode
    const std::vector<common::Entity*> getEntities() const;

    /** \brief Checks if the given Entity is contained in this QuadNode
      * \param entityPtr Pointer to the Entity to be added
      * \return True if the Entity is inside, otherwise false
      */
    const bool intersection(common::Entity* entityPtr) const;

protected:
    bool                         mIsRootNode;     ///< Denotes of this QuadNode is the root node
    int32_t                      mCapacity;       ///< The capacity of the QuadNode before sub-division
    QuadNode*                    mParentNode;     ///< Pointer to the parent node of this QuadNode
    QuadTree*                    mParentQuadTree; ///< Pointer to the parent QuadTree of this QuadNode
    std::array<QuadNode*, 4>     mChildNodes;     ///< Array of the four possible child QuadNode objects
    std::array<float, 2>         mCentre;         ///< Array representing the centre of this node in 2D-space
    std::array<float, 2>         mSize;           ///< Array representing the size of this node in 2D-space
    std::vector<common::Entity*> mEntities;       ///< Collection of common::Entities in this QuadNode
};

#endif // _QUADNODE_H
}}
