#include "QuadNode.h"
#include "QuadTree.h"

namespace liquid {
namespace spatial {

    QuadNode::QuadNode(int32_t capacity, bool isRootNode)
    {
        mCapacity = capacity;
        mIsRootNode = isRootNode;
        mParentNode = nullptr;
        mParentQuadTree = nullptr;
        mEntities.reserve(mCapacity);
    }

    QuadNode::~QuadNode()
    {}

    int32_t QuadNode::quadrant(common::Entity* entityPtr)
    {
        float positionX = entityPtr->getPositionX();
        float positionY = entityPtr->getPositionY();

        if (positionY < mCentre[1])
            return (positionX <= mCentre[0]) ? 0 : 1;
        else
            return (positionX <= mCentre[0]) ? 2 : 3;

        return -1;
    }

    void QuadNode::insertEntity(common::Entity* entityPtr)
    {
        if (isSubdivided() == true)
        {
            int32_t q = quadrant(entityPtr);
            return mChildNodes[q]->insertEntity(entityPtr);
        }

        mEntities.push_back(entityPtr);
        mParentQuadTree->setTrackedNode(entityPtr, this);

        if (mEntities.size() > mCapacity)
        {
            subdivide();

            for (auto entity : mEntities)
            {
                int32_t q = quadrant(entity);
                mChildNodes[q]->insertEntity(entity);
            }
            
            mEntities.clear();
        }
    }

    void QuadNode::insertEntity(std::vector<common::Entity*> entities)
    {
        // TODO
    }

    void QuadNode::removeEntity(common::Entity* entityPtr)
    {
        mEntities.erase(std::find(mEntities.begin(), mEntities.end(), entityPtr));
    }

    void QuadNode::pruneDeadBranches()
    {
        int32_t empty = 0;

        if (isSubdivided() == false)
            return;

        for (uint32_t i = 0; i < 4; i++)
        {
            mChildNodes[i]->pruneDeadBranches();
            empty += (mChildNodes[i]->getCount() == 0);
        }

        if (empty == 4)
            combine();
    }

    void QuadNode::setParentNode(QuadNode* quadNode)
    {
        mParentNode = quadNode;
    }

    void QuadNode::setParentQuadTree(QuadTree* quadTree)
    {
        mParentQuadTree = quadTree;
    }

    void QuadNode::setCapacity(int32_t capacity)
    {
        mCapacity = capacity;
    }

    void QuadNode::setCentre(std::array<float, 2> centre)
    {
        mCentre = centre;
    }

    void QuadNode::setSize(std::array<float, 2> size)
    {
        mSize = size;
    }

    const bool QuadNode::isRootNode() const
    {
        return mIsRootNode;
    }

    const bool QuadNode::isSubdivided() const
    {
        return mChildNodes[0] != nullptr;
    }

    const int32_t QuadNode::getCapacity() const
    {
        return mCapacity;
    }

    const int32_t QuadNode::getCount() const
    {
        return mEntities.size();
    }

    QuadNode* QuadNode::getParentNode() const
    {
        return mParentNode;
    }

    QuadTree* QuadNode::getParentQuadTree() const
    {
        return mParentQuadTree;
    }

    const std::array<QuadNode*, 4> QuadNode::getChildNodes() const
    {
        return mChildNodes;
    }

    const std::array<float, 2> QuadNode::getCentre() const
    {
        return mCentre;
    }

    const std::array<float, 2> QuadNode::getSize() const
    {
        return mSize;
    }

    const std::vector<common::Entity*> QuadNode::getEntities() const
    {
        return mEntities;
    }

    const bool QuadNode::intersection(common::Entity* entityPtr) const
    {
        float positionX = entityPtr->getPositionX();
        float positionY = entityPtr->getPositionY();

        return (positionX >= mCentre[0] - mSize[0] / 2.0f && positionX <= mCentre[0] + mSize[0] / 2.0f &&
                positionY >= mCentre[1] - mSize[1] / 2.0f && positionY <= mCentre[1] + mSize[1] / 2.0f);
    }

    void QuadNode::subdivide()
    {
        mChildNodes[0] = new QuadNode(mCapacity);
        mChildNodes[1] = new QuadNode(mCapacity);
        mChildNodes[2] = new QuadNode(mCapacity);
        mChildNodes[3] = new QuadNode(mCapacity);

        float w = mSize[0] / 4.0f;
        float h = mSize[1] / 4.0f;

        mChildNodes[0]->setCentre({ mCentre[0] - w, mCentre[1] - h });
        mChildNodes[1]->setCentre({ mCentre[0] + w, mCentre[1] - h });
        mChildNodes[2]->setCentre({ mCentre[0] + w, mCentre[1] + h });
        mChildNodes[3]->setCentre({ mCentre[0] - w, mCentre[1] + h });

        for (uint32_t i = 0; i < 4; i++)
        {
            mChildNodes[i]->setParentNode(this);
            mChildNodes[i]->setParentQuadTree(mParentQuadTree);
            mChildNodes[i]->setSize({ w*2.0f,h*2.0f });
        }
    }

    void QuadNode::combine()
    {
        for (uint32_t i = 0; i < 4; i++)
        {
            delete mChildNodes[i];
            mChildNodes[i] = nullptr;
        }
    }

}}
