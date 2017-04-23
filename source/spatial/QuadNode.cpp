#include "QuadNode.h"

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

        for (uint32_t i = 0; i < 4; i++)
        {
            if (positionY < mCentre[1])
                return (positionX <= mCentre[0]) ? 0 : 1;
            else
                return (positionX <= mCentre[0]) ? 2 : 3;
        }

        return -1;
    }

    bool QuadNode::insertEntity(common::Entity* entityPtr)
    {
        if (intersection(entityPtr) == false)
            return false;

        if (mEntities.size() < mCapacity)
        {
            mEntities.push_back(entityPtr);
            return true;
        }

        int32_t quad = quadrant(entityPtr);
        if (mChildNodes[quad] == nullptr)
        {
            int32_t signX = (quad == 0 || quad == 2);
            int32_t signY = (quad == 0 || quad == 1);

            float halfWidth = mSize[0] / 4.0f;
            float halfHeight = mSize[1] / 4.0f;

            float centreX = mCentre[0] + (signX ? -halfWidth : halfWidth);
            float centreY = mCentre[1] + (signY ? -halfHeight : halfHeight);

            mChildNodes[quad] = new QuadNode(mCapacity);
            mChildNodes[quad]->setSize({ mSize[0] / 2.0f,mSize[1] / 2.0f });
            mChildNodes[quad]->setCentre({ centreX,centreY });
            mChildNodes[quad]->setParentQuadTree(mParentQuadTree);
            mChildNodes[quad]->setParentNode(mParentNode);

            return mChildNodes[quad]->insertEntity(entityPtr);
        }
        return mChildNodes[quad]->insertEntity(entityPtr);
    }

    bool QuadNode::removeEntity(common::Entity* entityPtr)
    {
        std::vector<common::Entity*>::iterator it;
        it = std::find(mEntities.begin(), mEntities.end(), entityPtr);

        if (it == mEntities.end())
        {
            int32_t q = quadrant(entityPtr);
            if (mChildNodes[q] != nullptr)
                return mChildNodes[q]->removeEntity(entityPtr);
        }
        else
        {
            mEntities.erase(it);
            return true;
        }

        return false;
    }

    void QuadNode::deleteChildNode(QuadNode* node)
    {
        for (uint32_t i = 0; i < 4; i++)
        {
            if (mChildNodes[i] == node)
                delete mChildNodes[i];
        }
    }

    void QuadNode::pruneDeadBranches()
    {
        for (int32_t i = 0; i < 4; i++)
        {
            if (mChildNodes[i] != nullptr)
            {
                mChildNodes[i]->pruneDeadBranches();

                if (mChildNodes[i]->getCount() == 0 && hasChildren() == false)
                {
                    delete mChildNodes[i];
                    mChildNodes[i] = nullptr;
                }
            }
        }
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

    const bool QuadNode::hasChildren() const
    {
        for (int32_t i = 0; i < 4; i++)
        {
            if (mChildNodes[i] != nullptr)
                return true;
        }

        return false;
    }

    const bool QuadNode::isRootNode() const
    {
        return mIsRootNode;
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

}}
