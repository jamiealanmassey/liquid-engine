#include <cstdint>
#include <vector>
#include <SFML/Graphics.hpp>

namespace liquid { namespace impl {
#ifndef _SFMLBATCHGROUP_H
#define _SFMLBATCHGROUP_H

class SFMLBatchGroup
{
public:
    SFMLBatchGroup(int32_t atlasID, int32_t shaderID, int32_t blendMode);
    ~SFMLBatchGroup();

    void insertVertex(sf::Vertex& vertex);

    const int32_t getAtlasID() const;
    const int32_t getShaderID() const;
    const int32_t getBlendMode() const;
    const std::vector<sf::Vertex> getVertices() const;

protected:
    int32_t mAtlasID;
    int32_t mShaderID;
    int32_t mBlendMode;
    std::vector<sf::Vertex> mVertices;
};

#endif // _SFMLBATCHGROUP_H
}}
