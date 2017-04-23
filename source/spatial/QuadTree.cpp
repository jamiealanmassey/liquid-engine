#include "QuadTree.h"

namespace liquid {
namespace spatial {

    QuadTree::QuadTree() :
        Spatial(0x00001)
    {
    }

    QuadTree::~QuadTree()
    {}

    void QuadTree::initialise()
    {}
    void QuadTree::dispose()
    {}
    void QuadTree::update()
    {}

    void QuadTree::trackEntity(common::Entity* entityPtr)
    {}
    void QuadTree::untrackEntity(common::Entity* entityPtr)
    {}

    const std::vector<common::Entity*>& QuadTree::query(std::array<float, 4> region) const
    {
        return std::vector<common::Entity*>();
    }

    const std::vector<common::Entity*>& QuadTree::query(std::array<float, 4> region, int32_t type) const
    {
        return std::vector<common::Entity*>();
    }

    /////////////////////////////
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

    /*bool QuadNode::addEntity(common::Entity* entityPtr)
    {
        bool added = false;

        if (mChildNodes[0] == nullptr)
        {
            if (intersection(entityPtr))
            {
                mEntities.push_back(entityPtr);
                added = true;

                if (mEntities.size() > mCapacity)
                {
                    for (uint32_t i = 0; i < 4; i++)
                    {
                        float sizeHalfX = mRegion[2] / 2.0f;
                        float sizeHalfY = mRegion[3] / 2.0f;
                        float positionX = sizeHalfX * ((i % 2) == 1);
                        float positionY = sizeHalfY * (i == 2 || i == 3);

                        mChildNodes[i] = new QuadNode(mCapacity);
                        mChildNodes[i]->setParentQuadTree(mParentQuadTree);
                        mChildNodes[i]->setParentNode(this);
                        mChildNodes[i]->setRegion({ positionX, positionY, sizeHalfX, sizeHalfY });
                    }

                    for (uint32_t n = 0; n < mEntities.size(); n++)
                    {
                        for (uint32_t i = 0; i < 4; i++)
                        {
                            if (mChildNodes[i]->intersection(mEntities[n]))
                            {
                                mChildNodes[i]->addEntity(mEntities[n]);
                                //mChildNodes[i]->mEntities.push_back(mEntities[n]);
                                break;
                            }
                        }
                    }

                    mEntities.clear();
                }
            }
        }
        else
        {
            for (uint32_t i = 0; i < 4; i++)
            {
                if ((added = mChildNodes[i]->addEntity(entityPtr)) == true)
                    break;
            }
        }

        return added;
    }*/

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
    }

    bool QuadNode::insertEntity(common::Entity* entityPtr)
    {
        if (intersection(entityPtr) == false)
            return false;

        if (mEntities.size() < mCapacity)
        {
            mEntityQuads[entityPtr] = this;
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
