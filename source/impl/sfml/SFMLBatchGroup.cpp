#include "SFMLBatchGroup.h"

namespace liquid {
namespace impl {

    SFMLBatchGroup::SFMLBatchGroup(int32_t atlasID, int32_t shaderID, int32_t blendMode, int32_t primitiveType)
    {
        mAtlasID = atlasID;
        mShaderID = shaderID;
        mBlendMode = blendMode;
        mPrimitiveType = primitiveType;
    }

    SFMLBatchGroup::~SFMLBatchGroup()
    {
    }

    void SFMLBatchGroup::insertVertex(sf::Vertex& vertex)
    {
        mVertices.push_back(vertex);
    }

    const int32_t SFMLBatchGroup::getAtlasID() const
    {
        return mAtlasID;
    }

    const int32_t SFMLBatchGroup::getShaderID() const
    {
        return mShaderID;
    }

    const int32_t SFMLBatchGroup::getBlendMode() const
    {
        return mBlendMode;
    }

    const int32_t SFMLBatchGroup::getPrimitiveType() const
    {
        return mPrimitiveType;
    }

    const std::vector<sf::Vertex> SFMLBatchGroup::getVertices() const
    {
        return mVertices;
    }

}}
