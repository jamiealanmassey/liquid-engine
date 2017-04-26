#ifdef SFML
#include "SFMLRenderableBatch.h"
#include "SFMLRenderer.h"

namespace liquid {
namespace impl {

    SFMLRenderableBatch::SFMLRenderableBatch(sf::Texture& texture, uint32_t defaultCapacity) :
        graphics::RenderableBatch(defaultCapacity),
        mTexture(texture)
    {
        mRenderStates.texture = &mTexture;
        mRenderStates.blendMode = sf::BlendAlpha;
    }

    SFMLRenderableBatch::~SFMLRenderableBatch()
    {}

    void SFMLRenderableBatch::draw(graphics::Renderer* renderer)
    {
        std::vector<sf::Vertex> converted(mVertices.size());
        for (uint32_t i = 0; i < mVertices.size(); i++)
            converted[i] = convertFromVertex2(mVertices[i]);

        SFMLRenderer* sfml = static_cast<SFMLRenderer*>(renderer);
        sf::RenderWindow* window = sfml->getRenderWindow();
        window->draw(converted.data(), mBatchCount * 4, sf::Quads, mRenderStates);
    }

    std::array<utilities::Vertex2*, 4> SFMLRenderableBatch::nextVertices()
    {
        std::array<utilities::Vertex2*, 4> verts = RenderableBatch::nextVertices();
        sf::Vector2u size = getTextureSize();

        verts[0]->setTexCoord(0.0f, 0.0f);
        verts[1]->setTexCoord(size.x, 0.0f);
        verts[2]->setTexCoord(size.x, size.y);
        verts[3]->setTexCoord(0.0f, size.y);
        return verts;
    }

    void SFMLRenderableBatch::setBlendMode(sf::BlendMode mode)
    {
        mRenderStates.blendMode = mode;
    }

    void SFMLRenderableBatch::setShader(const sf::Shader shader)
    {
        mRenderStates.shader = &shader;
    }

    sf::Vector2u SFMLRenderableBatch::getTextureSize() const
    {
        return mTexture.getSize();
    }

    sf::Vertex SFMLRenderableBatch::convertFromVertex2(utilities::Vertex2* vert)
    {
        // TODO: Move this somewhere where both SFMLRenderable and SFMLRenderableBatch can get to it
        //       instead of duplicating code
        sf::Vertex vertex;
        std::array<float, 2> position = vert->getPosition();
        std::array<float, 2> texCoords = vert->getTexCoord();
        std::array<float, 4> colour = vert->getColour();

        vertex.position = sf::Vector2f(position[0], position[1]);
        vertex.texCoords = sf::Vector2f(texCoords[0], texCoords[1]);
        vertex.color = sf::Color(colour[0], colour[1], colour[2], colour[3]);

        return vertex;
    }

}}

#endif // SFML
